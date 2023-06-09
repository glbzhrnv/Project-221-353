QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += $$PWD/../server_src/include/

HEADERS += \
    ../server_src/include/Task/MachineSolver.hpp \
    ../server_src/include/Task/MachineState.hpp \
    ../server_src/include/Task/MealyGen.hpp \
    ../server_src/include/Task/MealySolve.hpp \
    ../server_src/include/Task/MealyState.hpp \
    ../server_src/include/Task/MealySuperposition.hpp \
    ../server_src/include/Task/MealyToMoore.hpp\
    ../server_src/include/Task/MooreGen.hpp \
    ../server_src/include/Task/MooreSolve.hpp \
    ../server_src/include/Task/MooreState.hpp \
    ../server_src/include/Task/MooreSuperposition.hpp

SOURCES += \
    src/FSMTest.cpp
