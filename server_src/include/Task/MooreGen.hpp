#ifndef MOOREGEN_HPP
#define MOOREGEN_HPP

#include <sstream>
#include <QJsonObject>
#include <stdint.h>
#include <string>
#include <unordered_map>
#include <Task/MooreState.hpp>

class MooreGen
{
public:
//    std::string genTable(
//        const char *states,
//        const char *statesOut,
//        int statesN,
//        int inputsN
//    ) {
//        std::stringstream result;
//        result << inputsN<< "|" << statesN << "|";

//        for (int i = 0; i < statesN; i++) {
//            result << states[i] << "|" << statesOut[i] << "|";
//        }

//        for (int i = 0, totalStates = statesN * inputsN; i < totalStates; i++) {
//            result <<
//        }
//    }

//    MooreState* parseTable(std::string table)
//    {

//    }

//    MooreState* genSng(const char* alphabet, )
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

    MooreState* genS(std::string input)
    {
        for (char c : input) {
            switch(c) {
                case '0': {
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

                    state = 1;

                    return stateA;
                }
                default: {
                    MooreState* stateX = new MooreState('X');
                    MooreState* stateY = new MooreState('Y');
                    MooreState* stateZ = new MooreState('Z');

                    // Установка переходов для первого автомата
                    stateZ->addTransition('0', stateY);
                    stateZ->addTransition('1', stateZ);

                    stateX->addTransition('0', stateX);
                    stateX->addTransition('1', stateZ);

                    stateY->addTransition('0', stateZ);
                    stateY->addTransition('1', stateY);

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

#endif // MOOREGEN_HPP
