#ifndef MEALYSOLVE_HPP
#define MEALYSOLVE_HPP

#include <string>
#include <QJsonObject>
#include "Task/MachineSolver.hpp"
#include "Task/MealyState.hpp"
#include "Task/MealyGen.hpp"

class MealySolve: public MachineSolver
{
public:
    MealySolve(MealyState* init): initialState(init)
    {
    }

    std::string run(const std::string& input)
    {
        MealyState* currentState = initialState;
        std::string result;

        for (char c : input) {
            auto transition = currentState->doTransition(c);
            if (transition.first == nullptr) {
                break;
            }
            currentState = transition.first;

            result += transition.second;
        }

        return result;
    }

    static QJsonObject gen(const std::string &request, std::string &solution)
    {
        QJsonObject result = {
            {"rq", request.c_str()},
            {"m1", "1"}
        };

        MealyGen mg = MealyGen();
        MealyState* m1 = mg.genS(result["m1"].toString().toStdString());
        MealySolve* ms = new MealySolve(m1);
        solution = ms->run(request);

        delete ms;
        delete m1;

        return result;
    }

protected:
    MealyState* initialState;
};

#endif // MEALYSOLVE_HPP
