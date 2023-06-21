cmake_minimum_required(VERSION 3.16)
project(server VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set up AUTOMOC and some sensible defaults for runtime execution
# When using Qt 6.3, you can replace the code block below with
# qt_standard_project_setup()
set(CMAKE_AUTOMOC ON)
include(GNUInstallDirs)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network Sql)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})

add_executable(server
    include/ClientCore.hpp
    include/Enum/FSMTypeEnum.hpp
    include/Enum/RequestMethod.hpp
    include/Enum/StatType.hpp
    include/Enum/UserAuthStateEnum.hpp
    include/Exception/AbstractRuntimeException.hpp
    include/Exception/ConfigurationException.hpp
    include/Exception/ConnectionException.hpp
    include/Migration/AbstractMigration.hpp
    include/Migration/MigrationsIndex.hpp
    include/Migration/StatMigration.hpp
    include/Migration/TaskMigration.hpp
    include/Migration/UserMigration.hpp
    include/Model/StatModel.hpp
    include/Model/TaskModel.hpp
    include/Model/UserModel.hpp
    include/Model/UserStateModel.hpp
    include/Processor/AbstractProcessor.hpp
    include/Processor/AuthUserProcessor.hpp
    include/Processor/CreateUserProcessor.hpp
    include/Processor/GetStatProcessor.hpp
    include/Processor/GetTaskProcessor.hpp
    include/Processor/SendTaskProcessor.hpp
    include/ServerCore.hpp
    include/SharedObjects.hpp
    include/Task/MachineSolver.hpp
    include/Task/MachineState.hpp
    include/Task/MealyGen.hpp
    include/Task/MealySolve.hpp
    include/Task/MealyState.hpp
    include/Task/MealySuperposition.hpp
    include/Task/MealyToMoore.hpp
    include/Task/MooreGen.hpp
    include/Task/MooreSolve.hpp
    include/Task/MooreState.hpp
    include/Task/MooreSuperposition.hpp
    include/Tools/PasswordTools.hpp
    include/Tools/TaskTools.hpp
    src/ClientCore.cpp
    src/Migration/AbstractMigration.cpp
    src/Migration/MigrationsIndex.cpp
    src/Migration/UserMigration.cpp
    src/Model/StatModel.cpp
    src/Model/TaskModel.cpp
    src/Model/UserModel.cpp
    src/Model/UserStateModel.cpp
    src/Processor/AbstractProcessor.cpp
    src/Processor/AuthUserProcessor.cpp
    src/Processor/CreateUserProcessor.cpp
    src/Processor/GetStatProcessor.cpp
    src/Processor/GetTaskProcessor.cpp
    src/Processor/SendTaskProcessor.cpp
    src/ServerCore.cpp
    src/SharedObjects.cpp
    src/Tools/PasswordTools.cpp
    src/Tools/TaskTools.cpp
    src/main.cpp
)
target_include_directories(server PRIVATE
    include
)

target_compile_definitions(server PRIVATE
    QT_DEPRECATED_WARNINGS
    _GLIBCXX_USE_CXX11_ABI=0
)

target_link_libraries(server PRIVATE
    Qt::Core
    Qt::Network
    Qt::Sql
    argon2
)

install(TARGETS server
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Consider using qt_generate_deploy_app_script() for app deployment if
# the project can use Qt 6.3. In that case rerun qmake2cmake with
# --min-qt-version=6.3.
