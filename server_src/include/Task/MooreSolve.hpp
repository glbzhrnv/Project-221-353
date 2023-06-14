#ifndef MOORESOLVE_HPP
#define MOORESOLVE_HPP

#include <iostream>
#include <unordered_map>
#include <QJsonObject>
#include "Task/MachineSolver.hpp"
#include "Task/MooreState.hpp"
#include "Task/MooreGen.hpp"

/**
 * @brief Находит решение автомата Мура
 */
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
        char *m1States = new char[3] {
            'A', 'B', 'C'
        };
        std::string m1 = MooreGen::genTable(m1States, 3, 2, 0);

        delete[] m1States;

        QJsonObject result = {
            {"rq", request.c_str()},
            {"m1", m1.c_str()},
        };

        MooreState* m1Machine = MooreGen::parseTable(m1);
        MooreSolve* ms = new MooreSolve(m1Machine);
        solution = ms->run(request);

        delete ms;
        delete m1Machine;

        return result;
    }

protected:
    MooreState* initialState;
};

#endif // MOORESOLVE_HPP
