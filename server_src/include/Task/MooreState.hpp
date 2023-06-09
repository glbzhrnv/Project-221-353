#ifndef MOORESTATE_HPP
#define MOORESTATE_HPP

#include <unordered_map>
#include "Task/MachineState.hpp"

// Класс состояния автомата Мура
class MooreState: public MachineState
{
public:
    // Конструктор
    MooreState(char output): output_(output)
    {
    }

    // Метод для получения выходного значения
    char getOutput() const
    {
        return output_;
    }

    // Метод для добавления перехода
    void addTransition(char input, MooreState* nextState)
    {
        transitions_[input] = nextState;
    }

    // Метод для выполнения перехода
    MooreState* doTransition(char input) const
    {
        auto it = transitions_.find(input);
        if (it != transitions_.end()) {
            return it->second;
        }

        return nullptr;
    }

    std::unordered_map<char, MooreState*>* getTransitions()
    {
        return &transitions_;
    }

protected:
    char output_;
    std::unordered_map<char, MooreState*> transitions_;
};

#endif // MOORESTATE_HPP
