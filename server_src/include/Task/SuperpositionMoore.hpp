#ifndef MOOREFSMTASK_HPP
#define MOOREFSMTASK_HPP

#include <iostream>
#include <unordered_map>
#include "Task/MooreState.hpp"

// Класс суперпозиции автоматов Мура
class SuperpositionMoore
{
public:
    // Конструктор
    SuperpositionMoore() : initialState_(nullptr)
    {
    }

    // Метод для установки начального состояния
    void setInitialState(MooreState* state)
    {
        initialState_ = state;
    }

    // Метод для выполнения автомата с заданным входом
    void run(const std::string& input) const
    {
        MooreState* currentState = initialState_;
        if (currentState == nullptr) {
            std::cout << "Ошибка: начальное состояние не установлено." << std::endl;
            return;
        }

        std::cout << "Выходные значения: ";
        for (char c : input) {
            currentState = currentState->doTransition(c);
            if (currentState == nullptr) {
                std::cout << "Ошибка: переход для входного символа '" << c << "' не определен." << std::endl;
                return;
            }
            std::cout << currentState->getOutput();
        }
        std::cout << std::endl;
    }

private:
    MooreState* initialState_;
};

int main()
{
    // Создание состояний
    MooreState* stateA = new MooreState('A');
    MooreState* stateB = new MooreState('B');
    MooreState* stateC = new MooreState('C');

    // Установка переходов для состояния A
    stateA->addTransition('0', stateB);
    stateA->addTransition('1', stateC);

    // Установка переходов для состояния B
    stateB->addTransition('0', stateA);
    stateB->addTransition('1', stateC);

    // Установка переходов для состояния C
    stateC->addTransition('0', stateC);
    stateC->addTransition('1', stateB);

    // Создание суперпозиции автоматов Мура
    SuperpositionMoore automaton;
    automaton.setInitialState(stateA);

    // Выполнение суперпозиции автоматов Мура с входным значением "010101"
    automaton.run("010101");

    // Освобождение памяти
    delete stateA;
    delete stateB;
    delete stateC;

    return 0;
}

std::string runSuperposition(const std::string &input, MooreState* initFirst, MooreState* initSecond)
{
    MooreState *currentFirst = initFirst, *currentSecond = initSecond;
    std::string result;

    for (int c : input) {
        if (currentFirst == nullptr || currentFirst == nullptr) {
            std::cout << "Ошибка: переход для входного символа '" << c << "' не определен." << std::endl;

            return result;
        }

        result += currentFirst->getOutput();
        result += currentSecond->getOutput();

        currentFirst = currentFirst->doTransition(c);
        currentSecond = currentSecond->doTransition(c);
    }

    return result;
}

#endif // MOOREFSMTASK_HPP
