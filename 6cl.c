#include "6cl.h"

static void usage(const char *pname, SixHeader *h) {}

SixResult SixParse(SixHeader header, size_t argc, char **argv) {
  // TODO: only do this if there is a least one flag thats required.
  if (argc == 1) {
    usage(argv[0], &header);
    return (SixResult){.error = "Not enough arguments"};
  }
  // TODO: do parsing here höhö
  return (SixResult){};
}
