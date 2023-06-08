QT -= gui
QT += core network sql

CONFIG -= app_bundle
CONFIG += c++17 console
#sanitizer sanitize_address

QMAKE_CXXFLAGS += "-D_GLIBCXX_USE_CXX11_ABI=0"

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += $$PWD/include/

#LIBS += -largon2

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/ClientCore.cpp \
    src/Migration/AbstractMigration.cpp \
    src/Migration/MigrationsIndex.cpp \
    src/Migration/UserMigration.cpp \
    src/Model/StatModel.cpp \
    src/Model/TaskModel.cpp \
    src/Model/UserModel.cpp \
    src/Model/UserStateModel.cpp \
    src/Processor/AbstractProcessor.cpp \
    src/Processor/AuthUserProcessor.cpp \
    src/Processor/CreateUserProcessor.cpp \
    src/Processor/GetStatProcessor.cpp \
    src/Processor/GetTaskProcessor.cpp \
    src/Processor/SendTaskProcessor.cpp \
    src/SharedObjects.cpp \
    src/Tools/PasswordTools.cpp \
    src/Tools/TaskTools.cpp \
        src/main.cpp \
        src/ServerCore.cpp \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    include/ClientCore.hpp \
    include/Enum/FSMTypeEnum.hpp \
    include/Enum/RequestMethod.hpp \
    include/Enum/StatType.hpp \
    include/Enum/UserAuthStateEnum.hpp \
    include/Exception/AbstractRuntimeException.hpp \
    include/Exception/ConfigurationException.hpp \
    include/Exception/ConnectionException.hpp \
    include/Migration/AbstractMigration.hpp \
    include/Migration/MigrationsIndex.hpp \
    include/Migration/StatMigration.hpp \
    include/Migration/TaskMigration.hpp \
    include/Migration/UserMigration.hpp \
    include/Model/StatModel.hpp \
    include/Model/TaskModel.hpp \
    include/Model/UserModel.hpp \
    include/Model/UserStateModel.hpp \
    include/Processor/AbstractProcessor.hpp \
    include/Processor/AuthUserProcessor.hpp \
    include/Processor/CreateUserProcessor.hpp \
    include/Processor/GetStatProcessor.hpp \
    include/Processor/GetTaskProcessor.hpp \
    include/Processor/SendTaskProcessor.hpp \
    include/ServerCore.hpp \
    include/SharedObjects.hpp \
    include/Task/MachineSolver.hpp \
    include/Task/MachineState.hpp \
    include/Task/MealyGen.hpp \
    include/Task/MealySolve.hpp \
    include/Task/MealyState.hpp \
    include/Task/MealySuperposition.hpp \
    include/Task/MealyToMoore.hpp \
    include/Task/MooreGen.hpp \
    include/Task/MooreSolve.hpp \
    include/Task/MooreState.hpp \
    include/Task/MooreSuperposition.hpp \
    include/Task/SuperState.hpp \
    include/Task/SuperpositionMoore.hpp \
    include/Tools/PasswordTools.hpp \
    include/Tools/TaskTools.hpp

DISTFILES += \
    Dockerfile \
    Doxyfile
