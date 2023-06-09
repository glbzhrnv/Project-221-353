#ifndef MACHINESOLVER_HPP
#define MACHINESOLVER_HPP

#include <string>

class MachineSolver
{
public:
    virtual ~MachineSolver()
    {
    }

    virtual std::string run(const std::string& input) = 0;
};

#endif // MACHINESOLVER_HPP
