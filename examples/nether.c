/*
 * A CLI fee splitter that divides a total amount across people, with optional
 * tip percent, labeling, and rounding.
 *
 * $ gcc ./nether.c ../6cl.c -o nether
 * $ ./nether +amount 42.5 +people 3
 * Each pays: 14.17
 * $ ./nether +amount 60 +people 4 +tip 10
 * Each pays: 16.5
 * $ ./nether +amount 100 +people 2 +label "Dinner" +round
 * Dinner: Each pays: 55
 */
#include "../6cl.h"
#include <stdlib.h>

#define ERR(FMT, ...) fprintf(stderr, "nether: " FMT "\n", __VA_ARGS__);

int main(int argc, char **argv) {
  SixFlag options[] = {};
  Six s = {0};
  s.flags = options;
  s.flag_count = sizeof(options) / sizeof(SixFlag);

  SixParse(&s, argc, argv);
  return EXIT_SUCCESS;
}
