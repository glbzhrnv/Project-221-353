#ifndef MEALYSTATE_HPP
#define MEALYSTATE_HPP

#include <unordered_map>
#include "Task/MachineState.hpp"

class MealyState: public MachineState
{
public:
    // Конструктор
    MealyState(char output): output_(output)
    {
    }

    // Метод для получения выходного значения
    char getOutput() const
    {
        return output_;
    }

    // Метод для добавления перехода
    void addTransition(char input, MealyState* nextState, char nextOutput)
    {
        transitions_[input] = std::make_pair(nextState, nextOutput);
    }

    // Метод для выполнения перехода
    std::pair<MealyState*, char> doTransition(char input) const
    {
        auto it = transitions_.find(input);
        if (it != transitions_.end()) {
            return it->second;
        }

        return std::make_pair(nullptr, '\0');
    }

    std::unordered_map<char, std::pair<MealyState*, char>>* getTransitions()
    {
        return &transitions_;
    }

protected:
    char output_;
    std::unordered_map<char, std::pair<MealyState*, char>> transitions_;
};

#endif // MEALYSTATE_HPP
