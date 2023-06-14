#ifndef MACHINESOLVER_HPP
#define MACHINESOLVER_HPP

#include <string>

/**
 * @brief Абстрактный класс, представляющий алгоритм решения автомата
 */
class MachineSolver
{
public:
    virtual ~MachineSolver()
    {
    }

    virtual std::string run(const std::string& input) = 0;
};

#endif // MACHINESOLVER_HPP
