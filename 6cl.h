#pragma once
#include <stddef.h>

// SixStr is a 0 copy window into a string
typedef struct {
  const char *p;
  size_t len;
} SixStr;

#define SIX_STR_NEW(CSTR) (SixStr){.p = (CSTR), .len = sizeof(CSTR) - 1}
#define SIX_STR_NEW_RUNTIME(CSTR)                                              \
  (SixStr) { .p = (CSTR), .len = strnlen(CSTR, 256) }

typedef enum {
  SIX_STR,
  SIX_BOOL,
  SIX_CHAR,
  SIX_INT,
  SIX_LONG,
  SIX_FLOAT,
  SIX_DOUBLE,
} SixFlagType;

// SixClFlag defines a singular command line option and will hold the value once
// parsing is done
typedef struct {
  // name of the flag, for instance +<name>; +help
  const char *name;
  // short name, like +<short_name>; +h
  char short_name;
  // Defines the datatype
  SixFlagType type;
  // used in the help page
  const char *description;

  // typed result values, will be filled with the value if any is found found
  // for the option, or with the default value thats already set.
  union {
    SixStr s;
    bool b;
    char c;
    int i;
    long l;
    float f;
    double d;
  };
} SixFlag;

typedef struct {
  SixFlag *flags;
  size_t flag_count;
  // usage will be postfixed with this
  const char *name_for_rest_arguments;
  // rest holds all arguments not matching any defined options
  SixStr *rest;
  size_t rest_count;
} Six;

void SixParse(Six *six, size_t argc, char **argv);
