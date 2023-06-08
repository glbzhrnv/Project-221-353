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
        QJsonObject result = {
            {"rq", request.c_str()},
            {"m1", "0"},
            {"m2", "1"},
        };

        MooreGen mg = MooreGen();
        MooreState* m1 = mg.genS(result["m1"].toString().toStdString());
        MooreState* m2 = mg.genS(result["m2"].toString().toStdString());
        MooreSuperposition* ms = new MooreSuperposition(m1, m2);
        solution = ms->run(request);

        delete ms;
        delete m2;
        delete m1;

        return result;
    }

protected:
    MooreState* initFirst;
    MooreState* initSecond;
};

#endif // MOORESUPERPOSITION_HPP
