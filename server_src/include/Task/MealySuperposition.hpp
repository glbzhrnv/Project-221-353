#ifndef MEALYSUPERPOSITION_HPP
#define MEALYSUPERPOSITION_HPP

#include <string>
#include <QJsonObject>
#include "Task/MachineSolver.hpp"
#include "Task/MealyState.hpp"
#include "Task/MealyGen.hpp"

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
        QJsonObject result = {
            {"rq", request.c_str()},
            {"m1", "0"},
            {"m2", "1"},
        };

        MealyGen mg = MealyGen();
        MealyState* m1 = mg.genS(result["m1"].toString().toStdString());
        MealyState* m2 = mg.genS(result["m2"].toString().toStdString());
        MealySuperposition* ms = new MealySuperposition(m1, m2);
        solution = ms->run(request);

        delete ms;
        delete m2;
        delete m1;

        return result;
    }

protected:
    MealyState* initFirst;
    MealyState* initSecond;
};

#endif // MEALYSUPERPOSITION_HPP
