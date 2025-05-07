#include "6cl.h"
#include <stdlib.h>
#include <string.h>

#ifndef OPTION_PREFIX
#define OPTION_PREFIX '+'
#endif

#define __HASH_TABLE_SIZE 512
#define __HASH_TABLE_MASK (__HASH_TABLE_SIZE - 1)

#include <stdio.h>

static char *SIX_FLAG_TYPE_TO_MAP[] = {
    [SIX_STR] = "string",    [SIX_BOOL] = "bool", [SIX_CHAR] = "char",
    [SIX_INT] = "int",       [SIX_LONG] = "long", [SIX_FLOAT] = "float",
    [SIX_DOUBLE] = "double",
};

// part of -h, --help, +h, +help and any unknown option
static void usage(const char *pname, Six *h) {
  // should i put this to stdout or stderr
  printf("usage %s: ", pname);
  size_t len = strlen(pname) + 7;
  for (size_t i = 0; i < h->flag_count; i++) {
    SixFlag *f = &h->flags[i];
    char *pre_and_postfix = "[]";
    printf("%c %c%c | %c%s", pre_and_postfix[0], OPTION_PREFIX, f->short_name,
           OPTION_PREFIX, f->name);

    if (f->type != SIX_BOOL) {
      printf("=<%s=", SIX_FLAG_TYPE_TO_MAP[f->type]);
      switch (f->type) {
      case SIX_STR:
        printf("%.*s", (int)f->s.len, f->s.p);
        break;
      case SIX_CHAR:
        putc(f->c, stdout);
        break;
      case SIX_INT:
        printf("%d", f->i);
        break;
      case SIX_LONG:
        printf("%ld", f->l);
        break;
      case SIX_FLOAT:
        printf("%g", f->f);
        break;
      case SIX_DOUBLE:
        printf("%g", f->d);
        break;
      default:
      }
      putc('>', stdout);
    }
    putc(pre_and_postfix[1], stdout);
    putc(' ', stdout);

    if ((i + 1) % 3 == 0 && i + 1 < len) {
      printf("\n%*.s ", (int)len, "");
    }
  }
  if (h->name_for_rest_arguments) {
    puts(h->name_for_rest_arguments);
  } else {
    puts("");
  }
}

static size_t fnv1a(const char *str) {
#define FNV_OFFSET_BASIS 0x811c9dc5
#define FNV_PRIME 0x01000193

  size_t hash = FNV_OFFSET_BASIS;
  while (*str++) {
    hash ^= *str;
    hash *= FNV_PRIME;
  }

  return hash;
}

void SixParse(Six *six, size_t argc, char **argv) {
  SixStr help = SIX_STR_NEW("help");

  // maps a strings hash to its index into the option array
  short hash_table_long[__HASH_TABLE_SIZE] = {0};

  // ASCII, since there is just these for short options, there should be even
  // less, since we dont really support nonprintable chars, but yeah, also we
  // zero this
  short table_short[256] = {0};

  // registering all options
  for (size_t i = 0; i < six->flag_count; i++) {
    SixFlag *f = &six->flags[i];

    // we increment the index by one here, since we use all tables and arrays
    // zero indexed, distinguishing between a not found and the option at index
    // 0 is therefore clear
    hash_table_long[fnv1a(f->name) & __HASH_TABLE_MASK] = i + 1;
    if (f->short_name) {
      table_short[(int)f->short_name] = i + 1;
    }
  }

  // i = 1 since we are skipping the process name (pname)
  for (size_t i = 1; i < argc; i++) {
    SixStr arg_cur = (SixStr){.p = (argv[i]), .len = strnlen(argv[i], 256)};

    // not starting with + means: no option, thus rest
    if (arg_cur.p[0] != OPTION_PREFIX) {
      six->rest[six->rest_count++] =
          (SixStr){.p = (argv[i]), .len = strnlen(argv[i], 256)};
      continue;
    }

    // check if short option
    if (arg_cur.len == 2) {
      // single char option usage/help page
      if (arg_cur.p[1] == 'h') {
        usage(argv[0], six);
        exit(EXIT_SUCCESS);
        return;
      }

      // check if short option is a registered one
      short option_idx = table_short[(short)arg_cur.p[1]];
      if (!option_idx) {
        fprintf(stderr, "Unkown short option '%c'\n", arg_cur.p[1]);
        goto err;
      }

      // we decrement option_idx, since we zero the lookup table, thus an
      // empty value is 0 and the index of the first option is 1, we correct
      // this here
      option_idx--;

      // if not boolean, the next argument is the argument
      if (six->flags[option_idx].type != SIX_BOOL) {
        // TODO: parse arguments
      } else {
        six->flags[option_idx].b = true;
      }
    } else {
      // strip first char by moving the start of the window one to the right
      arg_cur.p++;
      arg_cur.len--;

      // long help page with option description and stuff
      if (strncmp(arg_cur.p, help.p, help.len) == 0) {
        usage(argv[0], six);
        // TODO: print rest here
        puts("HELPPAGE");
        exit(EXIT_SUCCESS);
      }
    }
  }

  return;

err:
  usage(argv[0], six);
  exit(EXIT_FAILURE);
  return;
}
