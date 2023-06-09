#ifndef MOOREGEN_HPP
#define MOOREGEN_HPP

#include <string>
#include <sstream>
#include <stdint.h>
#include <map>
#include <Task/MooreState.hpp>

class MooreGen
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
            result << std::rand() % statesN << "|";
        }

        result << n0;

        return result.str();
    }

    static MooreState* parseTable(std::string table)
    {
        std::map<int32_t, MooreState*> states;

        std::stringstream values(table);
        std::string value = "";

        std::getline(values, value, '|');
        int32_t inputsN = std::stoi(value);

        std::getline(values, value, '|');
        int32_t statesN = std::stoi(value);

        for (int32_t i = 0; i < statesN; i++) {
            std::getline(values, value, '|');

            states[i] = new MooreState(*value.c_str());
        }

        for (auto state : states) {
            for (int32_t j = 0; j < inputsN; j++) {
                std::getline(values, value, '|');

                state.second->addTransition(*std::to_string(j).c_str(), states[std::stoi(value)]);
            }
        }

        std::getline(values, value, '|');

        return states[std::stoi(value)];
    }
};

#endif // MOOREGEN_HPP
