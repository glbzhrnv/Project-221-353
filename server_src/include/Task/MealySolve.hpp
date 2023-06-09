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
        char *m1States = new char[3] {
            'A', 'B', 'C'
        };
        std::string m1 = MealyGen::genTable(m1States, 3, 2, 0);

        delete[] m1States;

        QJsonObject result = {
            {"rq", request.c_str()},
            {"m1", m1.c_str()},
        };

        MealyState* m1Machine = MealyGen::parseTable(m1);
        MealySolve* ms = new MealySolve(m1Machine);
        solution = ms->run(request);

        delete ms;
        delete m1Machine;

        return result;
    }

protected:
    MealyState* initialState;
};

#endif // MEALYSOLVE_HPP
