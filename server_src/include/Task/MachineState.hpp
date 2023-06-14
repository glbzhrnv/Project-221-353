#ifndef MACHINESTATE_HPP
#define MACHINESTATE_HPP

#include <string>
#include <unordered_map>

/**
 * @brief Абстрактный класс, представляющий состояние автомата
 */
class MachineState
{
public:
    virtual ~MachineState()
    {
    }
};

#endif // MACHINESTATE_HPP
