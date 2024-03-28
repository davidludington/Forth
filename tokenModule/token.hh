
// This header ensures C linkage is enforced when running C++ unit tessts on C code.

#include <math.h>

#ifdef __cplusplus

extern "C" {

#include "stack.h"
#include "token.h"
#include "push-tokens.h"
#include <stdlib.h>
#include <stdio.h>

}

#else

#include "stack.h"
#include "token.h"
#include "push-tokens.h"

#endif