#ifndef MOORESOLVE_HPP
#define MOORESOLVE_HPP

#include <iostream>
#include <unordered_map>
#include "Task/MachineSolver.hpp"
#include "Task/MooreState.hpp"
#include "Task/MooreGen.hpp"

class MooreSolve: public MachineSolver
{
public:
    MooreSolve(MooreState* init): initialState(init)
    {
    }

    std::string run(const std::string& input)
    {
        MooreState* currentState = initialState;
        std::string result;

        for (char c : input) {
            currentState = currentState->doTransition(c);
            if (currentState == nullptr) {
                break;
            }
            result += currentState->getOutput();
        }

        return result;
    }

    static QJsonObject gen(const std::string &request, std::string &solution)
    {
        QJsonObject result = {
            {"rq", request.c_str()},
            {"m1", "0"},
        };

        MooreGen mg = MooreGen();
        MooreState* m1 = mg.genS(result["m1"].toString().toStdString());
        MooreSolve* ms = new MooreSolve(m1);
        solution = ms->run(request);

        delete ms;
        delete m1;

        return result;
    }

protected:
    MooreState* initialState;
};

#endif // MOORESOLVE_HPP
