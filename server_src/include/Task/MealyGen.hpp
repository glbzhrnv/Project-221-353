#ifndef MEALYGEN_HPP
#define MEALYGEN_HPP

#include <stdint.h>
#include <string>
#include <unordered_map>
#include <Task/MealyState.hpp>

class MealyGen
{
public:
//    MooreState* genS(const std::string &input)
//    {
//        int genState = 0;
//        std::unordered_map<char, MooreState*> states;

//        for (char c : input) {
//            switch (c) {
//                case '-':
//                    genState = 0;
//                    continue;
//                case ':':
//                    genState = 1;
//                    continue;
//                case ';':
//                    genState = 2;
//                    continue;
//            }

//            switch (genState) {
//                case 1:
//                    states[c] = new MooreState(c);
//                    break;
//                case 2:
//                    break;
//            }
//        }

//        return nullptr;
//    }

    MealyState* genS(std::string input)
    {
        for (char c : input) {
            switch(c) {
                case '0': {
                    // Создание состояний
                    MealyState* stateA = new MealyState('A');
                    MealyState* stateB = new MealyState('B');
                    MealyState* stateC = new MealyState('C');

                    // Установка переходов для состояния A
                    stateA->addTransition('0', stateB, '1');
                    stateA->addTransition('1', stateC, '0');

                    // Установка переходов для состояния B
                    stateB->addTransition('0', stateA, '0');
                    stateB->addTransition('1', stateC, '1');

                    // Установка переходов для состояния C
                    stateC->addTransition('0', stateC, '1');
                    stateC->addTransition('1', stateB, '1');

                    state = 1;

                    return stateA;
                }
                default: {
                    MealyState* stateX = new MealyState('X');
                    MealyState* stateY = new MealyState('Y');
                    MealyState* stateZ = new MealyState('Z');

                    // Установка переходов для первого автомата
                    stateZ->addTransition('0', stateY, '0');
                    stateZ->addTransition('1', stateZ, '1');

                    stateX->addTransition('0', stateX, '1');
                    stateX->addTransition('1', stateZ, '0');

                    stateY->addTransition('0', stateZ, '0');
                    stateY->addTransition('1', stateY, '0');

                    state = 0;

                    return stateX;
                }
            }
        }

        return nullptr;
    }

protected:
    int state = 0 ;
};

#endif // MEALYGEN_HPP
