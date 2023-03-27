#ifndef _MY_STRING_H_
#define _MY_STRING_H_
#include "sm.h"
#include "mprv.h"
#include <sbi/sbi_console.h>

unsigned long
print_string(uintptr_t string, size_t len, uintptr_t retbuf);

#endif