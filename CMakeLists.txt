cmake_minimum_required(VERSION 3.16)
project(server VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_compile_definitions(_GLIBCXX_USE_CXX11_ABI=0)

# Set up AUTOMOC and some sensible defaults for runtime execution
# When using Qt 6.3, you can replace the code block below with
# qt_standard_project_setup()
set(CMAKE_AUTOMOC ON)
include(GNUInstallDirs)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network Sql)

add_executable(server
    include/ClientCore.hpp
    include/Exception/AbstractRuntimeException.hpp
    include/Exception/ConfigurationException.hpp
    include/Exception/ConnectionException.hpp
    include/Migration/AbstractMigration.hpp
    include/Migration/MigrationsIndex.hpp
    include/Migration/UserMigration.hpp
    include/Model/AbstractModel.hpp
    include/Model/UserModel.hpp
    include/Processor/AbstractProcessor.hpp
    include/Processor/AuthUserProcessor.hpp
    include/Processor/CreateUserProcessor.hpp
    include/ServerCore.hpp
    include/SharedObjects.hpp
    include/Tools/PasswordTools.hpp
    src/ClientCore.cpp
    src/Migration/AbstractMigration.cpp
    src/Model/UserModel.cpp
    src/Processor/AbstractProcessor.cpp
    src/Processor/AuthUserProcessor.cpp
    src/Processor/CreateUserProcessor.cpp
    src/ServerCore.cpp
    src/SharedObjects.cpp
    src/Tools/PasswordTools.cpp
    src/main.cpp
)
target_include_directories(server PRIVATE
    include
)

target_compile_definitions(server PRIVATE
    QT_DEPRECATED_WARNINGS
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
