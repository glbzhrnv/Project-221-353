#ifndef MEALYSUPERPOSITION_HPP
#define MEALYSUPERPOSITION_HPP

#include <string>
#include <QJsonObject>
#include "Task/MachineSolver.hpp"
#include "Task/MealyState.hpp"
#include "Task/MealyGen.hpp"

/**
 * @brief Находит суперпозицию двух автоматов Мили
 */
class MealySuperposition: public MachineSolver
{
public:
    MealySuperposition(MealyState* first, MealyState* second)
        : initFirst(first)
        , initSecond(second)
    {
    }

    std::string run(const std::string &input)
    {
        MealyState *currentFirst = initFirst, *currentSecond = initSecond;
        std::string result;


        for (char c : input) {
            auto transitionFirst = currentFirst->doTransition(c);
            auto transitionSecond = currentSecond->doTransition(c);
            if (
                transitionFirst.first == nullptr
                || transitionSecond.first == nullptr
            ) {
                break;
            }
            currentFirst = transitionFirst.first;
            currentSecond = transitionSecond.first;

            result += transitionFirst.second;
            result += transitionSecond.second;
        }

        return result;
    }

    static QJsonObject gen(const std::string &request, std::string &solution)
    {
        char *m1States = new char[3] {
            'A', 'B', 'C'
        };
        std::string m1 = MealyGen::genTable(m1States, 3, 2, 0);

        char *m2States = new char[3] {
            'X', 'Y', 'Z'
        };
        std::string m2 = MealyGen::genTable(m2States, 3, 2, 0);

        delete[] m1States;
        delete[] m2States;

        QJsonObject result = {
            {"rq", request.c_str()},
            {"m1", m1.c_str()},
            {"m2", m2.c_str()},
        };

        MealyState* m1Machine = MealyGen::parseTable(m1);
        MealyState* m2Machine = MealyGen::parseTable(m2);
        MealySuperposition* ms = new MealySuperposition(m1Machine, m2Machine);
        solution = ms->run(request);

        delete ms;
        delete m1Machine;
        delete m2Machine;

        return result;
    }

protected:
    MealyState* initFirst;
    MealyState* initSecond;
};

#endif // MEALYSUPERPOSITION_HPP
