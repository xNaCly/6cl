#include "6cl.h"
#include <string.h>

#ifndef OPTION_PREFIX
#define OPTION_PREFIX "+"
#endif

#include <stdio.h>

static char *SIX_FLAG_TYPE_TO_MAP[] = {
    [SIX_STR] = "string",    [SIX_BOOL] = "bool", [SIX_CHAR] = "char",
    [SIX_INT] = "int",       [SIX_LONG] = "long", [SIX_FLOAT] = "float",
    [SIX_DOUBLE] = "double",
};

// part of -h, --help, +h, +help and any unknown option
static void usage(const char *pname, SixHeader *h) {
  // should i put this to stdout or stderr
  printf("usage %s: ", pname);
  size_t len = strlen(pname) + 7;
  for (size_t i = 0; i < h->flag_count; i++) {
    SixFlag *f = &h->flags[i];
    char *pre_and_postfix = f->required ? "<>" : "[]";
    printf("%c-%c | --%s", pre_and_postfix[0], f->short_name, f->name);
    if (f->type != SIX_BOOL) {
      printf("=<%s=", SIX_FLAG_TYPE_TO_MAP[f->type]);
      switch (f->type) {
      case SIX_STR:
        printf("%.*s", (int)f->s.len, f->s.start);
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

SixResult SixParse(SixHeader header, size_t argc, char **argv) {
  // TODO: only do this if there is a least one flag thats required.
  if (argc == 1) {
    usage(argv[0], &header);
    return (SixResult){.error = "Not enough arguments"};
  }

  // TODO: do parsing here höhö
  return (SixResult){};
}
