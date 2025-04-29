#pragma once
#include <stddef.h>

// SixStr is a 0 copy window into a string
typedef struct {
  const char *start;
  size_t len;
} SixStr;

#define SIX_STR_NEW(CSTR) (SixStr){.start = (CSTR), .len = sizeof(CSTR) - 1}

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
  // name of the flag, for instance --<name>; --option
  const char *name;
  // short name, like -<short_name>; -h
  char short_name;
  // Defines the datatype
  SixFlagType type;
  // Flag is required
  bool required;

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
} SixHeader;

typedef struct {
  // rest holds all arguments not matching any defined options
  const SixStr *rest;
  size_t rest_count;
  // filled if parsing runs into an error
  const char *error;
  SixFlag *flags;
} SixResult;

SixResult SixParse(SixHeader header, size_t argc, char **argv);
