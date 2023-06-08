#ifndef FSMTYPE_H
#define FSMTYPE_H

#include <stdint.h>

namespace ENUM
{

enum FSMType: int32_t
{
    MEALY_SOLVE = 0,
    MEALY_SUPER = 1,
    MEALY_TO_MOORE = 2,
    MOORE_SOLVE = 3,
    MOORE_SUPER = 4,
};

}

#endif // FSMTYPE_H
