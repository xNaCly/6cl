/*
 * A calculator like interface accepting a calcuation action via +add, +sub,
 * +div, +mul, performs said operation on further arguments and prints the
 * result. Also has +V/+verbose to print the whole equation.
 *
 * $ gcc ./calc.c ../6cl.c -o calc
 * $ ./calc +add 25 15
 * =40
 * $ ./calc +sub 25 10
 * =10
 * $ ./calc +div 25 5
 * =5
 * $ ./calc +mul 5 5
 * =25
 * $ ./calc +mul 5 5 +V
 * 5*5=25
 * $ ./calc +mul 5 5 +verbose
 * 5*5=25
 */
#include "../6cl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR(FMT, ...) fprintf(stderr, "calc: " FMT "\n", ##__VA_ARGS__);

typedef enum { UNKNOWN = -1, ADD, SUB, DIV, MUL, VERBOSE } Option;

int main(int argc, char **argv) {
  SixFlag options[] = {
      [ADD] =
          {
              .name = "add",
              .short_name = 'a',
              .description = "Add all arguments together",
              .b = false,
              .type = SIX_BOOL,
          },
      [SUB] =
          {
              .name = "sub",
              .short_name = 's',
              .description = "Subtract all arguments",
              .b = false,
              .type = SIX_BOOL,
          },
      [DIV] =
          {
              .name = "div",
              .short_name = 'd',
              .description = "Divide all arguments",
              .b = false,
              .type = SIX_BOOL,
          },
      [MUL] =
          {
              .name = "mul",
              .short_name = 'm',
              .description = "Multiply all arguments",
              .b = false,
              .type = SIX_BOOL,
          },
      [VERBOSE] =
          {
              .name = "verbose",
              .short_name = 'V',
              .description = "Print the equation",
              .b = false,
              .type = SIX_BOOL,
          },

  };
  Six s = {0};
  s.flags = options;
  s.flag_count = sizeof(options) / sizeof(SixFlag);
  s.name_for_rest_arguments = "<numbers>";

  SixParse(&s, argc, argv);
  if (s.rest_count < 2) {
    ERR("Wanted at least two arguments, got %zu", s.rest_count);
    return EXIT_FAILURE;
  }

  bool verbose = s.flags[VERBOSE].b;

  Option op = UNKNOWN;
  for (Option i = 0; i < VERBOSE; i++) {
    if (!s.flags[i].b) {
      continue;
    }
    if (op != UNKNOWN) {
      ERR("Got more than one action, exiting...");
      exit(EXIT_FAILURE);
    } else {
      op = i;
    }
  }

  switch (op) {
  case ADD:
  case SUB:
  case DIV:
  case MUL:
  case VERBOSE:
    break;
  case UNKNOWN:
  default:
    ERR("Unkown option / no option provided")
    exit(EXIT_FAILURE);
  }

  double acum = 0;
  for (size_t i = 0; i < s.rest_count; i++) {
    double d = strtod(s.rest[i], NULL);

    if (verbose) {
      printf("%g", d);
      if (i + 1 < s.rest_count) {
        switch (op) {
        case ADD:
          printf("+");
          break;
        case SUB:
          printf("-");
          break;
        case DIV:
          printf("/");
          break;
        case MUL:
          printf("*");
          break;
        default:
        }
      }
    }

    if (i == 0) {
      acum = d;
      continue;
    }

    switch (op) {
    case ADD:
      acum += d;
      break;
    case SUB:
      acum -= d;
      break;
    case DIV:
      acum /= d;
      break;
    case MUL:
      acum *= d;
      break;
    default:
    }
  }

  printf("=%g\n", acum);

  return EXIT_SUCCESS;
}
