#ifndef FSMTYPEENUM_H
#define FSMTYPEENUM_H

#include <stdint.h>

namespace ENUM
{

/**
 * @brief Идентификаторы возможных заданий
 */
enum FSMTypeEnum: int32_t
{   
    MEALY_SOLVE = 0,
    MEALY_SUPER = 1,
    MEALY_TO_MOORE = 2,
    MOORE_SOLVE = 3,
    MOORE_SUPER = 4,
};

}

#endif // FSMTYPEENUM_H
