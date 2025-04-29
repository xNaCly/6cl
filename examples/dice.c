/*
 * A dice roller that simulates rolling N dice with M sides, optionally
 * labeled, and with verbose output for each roll.
 *
 * $ gcc ./dice.c ../6cl.c -o dice
 * $ ./dice +n 4 +sides 6
 * =14
 * $ ./dice +n 2 +sides 20 +label "STR"
 * STR: =29
 * $ ./dice +n 3 +sides 10 +v
 * Rolled: 3 + 7 + 5 =15
 */
#include "../6cl.h"
#include <stdlib.h>

#define ERR(FMT, ...) fprintf(stderr, "dice: " FMT "\n", __VA_ARGS__);

int main(int argc, char **argv) {
  SixFlag options[] = {
      {.name = "amount", .short_name = 'a', .d = 0.0, .type = SIX_DOUBLE},
      {.name = "people", .short_name = 'p', .i = 1, .type = SIX_INT},
      {.name = "tip", .short_name = 't', .i = 0, .type = SIX_INT},
      {.name = "label",
       .short_name = 'l',
       .s = SIX_STR_NEW(""),
       .type = SIX_STR},
      {.name = "round", .short_name = 'r', .b = false, .type = SIX_BOOL},
  };
  Six s = {0};
  s.flags = options;
  s.flag_count = sizeof(options) / sizeof(SixFlag);

  SixParse(&s, argc, argv);
  return EXIT_SUCCESS;
}
