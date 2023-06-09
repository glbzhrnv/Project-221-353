#ifndef MEALYGEN_HPP
#define MEALYGEN_HPP

#include <string>
#include <sstream>
#include <stdint.h>
#include <map>
#include <Task/MealyState.hpp>

class MealyGen
{
public:
    static std::string genTable(
        const char *statesOut,
        int32_t statesN,
        int32_t inputsN,
        int32_t n0
    ) {
        if (n0 > inputsN) {
            return "";
        }

        std::stringstream result;
        result << inputsN << "|" << statesN << "|";

        for (int32_t i = 0; i < statesN; i++) {
            result << statesOut[i] << "|";
        }

        for (int32_t i = 0, totalStates = statesN * inputsN; i < totalStates; i++) {
            result << std::rand() % inputsN << "|" << std::rand() % statesN << "|";
        }

        result << n0;

        return result.str();
    }

    static MealyState* parseTable(std::string table)
    {
        std::map<int32_t, MealyState*> states;

        std::stringstream values(table);
        std::string value = "";

        std::getline(values, value, '|');
        int32_t inputsN = std::stoi(value);

        std::getline(values, value, '|');
        int32_t statesN = std::stoi(value);

        for (int32_t i = 0; i < statesN; i++) {
            std::getline(values, value, '|');

            states[i] = new MealyState(*value.c_str());
        }

        int32_t nextOutput;
        for (auto state : states) {
            for (int32_t j = 0; j < inputsN; j++) {
                std::getline(values, value, '|');
                nextOutput = std::stoi(value);

                std::getline(values, value, '|');

                state.second->addTransition(
                    *std::to_string(j).c_str(),
                    states[std::stoi(value)],
                    *std::to_string(nextOutput).c_str()
                );
            }
        }

        std::getline(values, value, '|');

        return states[std::stoi(value)];
    }
};

#endif // MEALYGEN_HPP
