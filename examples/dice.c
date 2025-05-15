/*
 * A dice roller that simulates rolling N dice with M sides, optionally
 * labeled, and with verbose output to print each roll result.
 *
 * $ gcc ./dice.c ../6cl.c -o dice
 * $ ./dice +n 4 +m 6
 * => 14
 * $ ./dice +rolls 2 +sides 20 +label "STR"
 * STR: => 29
 * $ ./dice +n 3 +m 10 +v
 * Rolled: 3 + 7 + 5 =15
 */
#include "../6cl.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ERR(FMT, ...) fprintf(stderr, "dice: " FMT "\n", ##__VA_ARGS__);

void dice(int *throws, unsigned int n, unsigned int m) {
  for (size_t i = 0; i < n; i++) {
    throws[i] = (rand() % m) + 1;
  }
}

typedef enum { UNKNOWN = -1, ROLLS, SIDES, LABEL, VERBOSE } Option;

int main(int argc, char **argv) {
  srand((unsigned int)time(NULL));

  SixFlag options[] = {
      [ROLLS] = {.name = "rolls",
                 .short_name = 'n',
                 .i = 2,
                 .type = SIX_INT,
                 .description = "times to roll"},
      [SIDES] = {.name = "sides",
                 .short_name = 'm',
                 .i = 6,
                 .type = SIX_INT,
                 .description = "sides the dice has"},
      [LABEL] =
          {
              .name = "label",
              .short_name = 'l',
              .s = "=> ",
              .type = SIX_STR,
              .description = "prefix for the dice roll result",
          },
      [VERBOSE] =
          {
              .name = "verbose",
              .short_name = 'v',
              .type = SIX_BOOL,
              .description = "print all rolls, not only the result",
          },
  };
  Six s = {0};
  s.flags = options;
  s.flag_count = sizeof(options) / sizeof(SixFlag);

  SixParse(&s, argc, argv);
  if (s.flags[VERBOSE].b) {
    printf("Config{rolls=%d, sides=%d, label=`%s`}\n", s.flags[ROLLS].i,
           s.flags[SIDES].i, s.flags[LABEL].s);
  }

  if (options[ROLLS].i < 1) {
    ERR("Rolls can't be < 1");
    return EXIT_FAILURE;
  }

  int throws[options[ROLLS].i];
  dice(throws, options[ROLLS].i, options[SIDES].i);

  int cum = 0;
  for (int i = 0; i < options[ROLLS].i; i++) {
    int roll = throws[i];
    cum += roll;
    if (options[VERBOSE].b) {
      printf("[roll=%02d]::[%02d/%02d]\n", i + 1, roll, options[SIDES].i);
    }
  }

  printf("%s%d\n", options[LABEL].s, cum);

  return EXIT_SUCCESS;
}
