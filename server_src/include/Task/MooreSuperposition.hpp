#ifndef MOORESUPERPOSITION_HPP
#define MOORESUPERPOSITION_HPP

#include <string>
#include <QJsonObject>
#include "Task/MachineSolver.hpp"
#include "Task/MooreState.hpp"
#include "Task/MooreGen.hpp"

class MooreSuperposition: public MachineSolver
{
public:
    MooreSuperposition(MooreState* first, MooreState* second)
        : initFirst(first)
        , initSecond(second)
    {
    }

    std::string run(const std::string &input)
    {
        MooreState *currentFirst = initFirst, *currentSecond = initSecond;
        std::string result;

        for (char c : input) {
            if (currentFirst == nullptr || currentFirst == nullptr) {
                break;
            }

            result += currentFirst->getOutput();
            result += currentSecond->getOutput();

            currentFirst = currentFirst->doTransition(c);
            currentSecond = currentSecond->doTransition(c);
        }

        return result;
    }

    static QJsonObject gen(const std::string &request, std::string &solution)
    {
        char *m1States = new char[3] {
            'A', 'B', 'C'
        };
        std::string m1 = MooreGen::genTable(m1States, 3, 2, 0);

        char *m2States = new char[3] {
            'X', 'Y', 'Z'
        };
        std::string m2 = MooreGen::genTable(m2States, 3, 2, 0);

        delete[] m1States;
        delete[] m2States;

        QJsonObject result = {
            {"rq", request.c_str()},
            {"m1", m1.c_str()},
            {"m2", m2.c_str()},
        };

        MooreState* m1Machine = MooreGen::parseTable(m1);
        MooreState* m2Machine = MooreGen::parseTable(m2);
        MooreSuperposition* ms = new MooreSuperposition(m1Machine, m2Machine);
        solution = ms->run(request);

        delete ms;
        delete m1Machine;
        delete m2Machine;

        return result;
    }

protected:
    MooreState* initFirst;
    MooreState* initSecond;
};

#endif // MOORESUPERPOSITION_HPP
