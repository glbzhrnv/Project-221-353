#ifndef MEALYTOMOORE_HPP
#define MEALYTOMOORE_HPP

#include <string>
#include <sstream>
#include <unordered_map>
#include <QJsonObject>
#include "Task/MachineSolver.hpp"
#include "Task/MealyGen.hpp"

class MealyToMoore: public MachineSolver
{
public:
    MealyToMoore()
    {
    }

    ~MealyToMoore()
    {
    }

    std::string run(const std::string& table)
    {
        std::stringstream states(table);
        std::string value = "";

        uint32_t pairCounter = 0;

        std::unordered_map<std::string, uint32_t> bStates;
        std::unordered_map<char, std::unordered_map<uint32_t, uint32_t>> rBStates;

        std::getline(states, value, '|');
        uint32_t inputsN = std::stoi(value);

        std::getline(states, value, '|');
        uint32_t statesN = std::stoi(value);

        for (uint32_t i = 0; i < statesN; i++) {
            std::getline(states, value, '|');
        }

        std::string bState;
        int nextStateI, nextInputI;
        char nextState;
        for (uint32_t stateId = 0; stateId < statesN; stateId++) {
            for (uint32_t memState = 0; memState < inputsN; memState++) {
                std::getline(states, value, '|');
                nextInputI = std::stoi(value);

                std::getline(states, value, '|');
                nextState = *value.c_str();
                nextStateI = std::stoi(value);

                bState = std::to_string(nextStateI) + std::to_string(nextInputI);

                auto bStateIter = bStates.find(bState);
                if (bStateIter == bStates.end()) {
                    bStates[bState] = pairCounter;
                    rBStates[nextState][memState] = pairCounter;

                    pairCounter++;
                } else {
                    rBStates[nextState][memState] = bStateIter->second;
                }
            }
        }

        std::getline(states, value, '|');
        int n0 = std::stoi(value);

        std::stringstream result;

        result << inputsN << "|" << bStates.size() << "|";

        for (auto state : bStates) {
            result << state.second << "|";
        }

        for (auto state : bStates) {
            for (uint32_t memState = 0; memState < inputsN; memState++) {
                result << rBStates[state.first[0]][memState] << "|";
            }
        }
        result << n0;

        return result.str();
    }

    static QJsonObject gen(std::string &solution)
    {
        char *m1States = new char[3] {
            'A', 'B', 'C'
        };
        std::string m1 = MealyGen::genTable(m1States, 3, 2, 0);

        delete[] m1States;

        QJsonObject result = {
            {"m1", m1.c_str()},
        };

        MealyToMoore* ms = new MealyToMoore();
        solution = ms->run(m1);

        delete ms;

        return result;
    }
};

#endif // MEALYTOMOORE_HPP
