#include "../6cl.h"
#include <stdlib.h>

int main(int argc, char **argv) {
  SixHeader s = {
      .flag_count = 0,
  };
  SixResult sr = SixParse(s, argc, argv);
  return EXIT_SUCCESS;
}
