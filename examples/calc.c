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

#define ERR(FMT, ...) fprintf(stderr, "calc: " FMT "\n", __VA_ARGS__);

int main(int argc, char **argv) {
  SixFlag options[] = {
      {
          .name = "add",
          .short_name = 'a',
          .b = false,
          .type = SIX_BOOL,
      },
      {
          .name = "sub",
          .short_name = 's',
          .b = false,
          .type = SIX_BOOL,
      },
      {
          .name = "div",
          .short_name = 'd',
          .b = false,
          .type = SIX_BOOL,
      },
      {
          .name = "mul",
          .short_name = 'm',
          .b = false,
          .type = SIX_BOOL,
      },
      {
          .name = "verbose",
          .short_name = 'V',
          .b = false,
          .type = SIX_BOOL,
      },

  };
  SixHeader s = {0};
  s.flags = options;
  s.flag_count = sizeof(options) / sizeof(SixFlag);
  s.name_for_rest_arguments = "<numbers>";

  SixResult sr = SixParse(s, argc, argv);
  if (sr.error) {
    ERR("%s", sr.error);
    return EXIT_FAILURE;
  } else if (sr.rest_count < 2) {
    ERR("Wanted at least two arguments, got %zu", sr.rest_count);
    return EXIT_FAILURE;
  }

  if (sr.flags[0].b) {
    puts("VERBOSE MODE");
  }

  return EXIT_SUCCESS;
}
