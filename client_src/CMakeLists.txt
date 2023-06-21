cmake_minimum_required(VERSION 3.16)
project(client VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set up AUTOMOC and some sensible defaults for runtime execution
# When using Qt 6.3, you can replace the code block below with
# qt_standard_project_setup()
set(CMAKE_AUTOMOC ON)
include(GNUInstallDirs)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui Network)
find_package(Qt${QT_VERSION_MAJOR} OPTIONAL_COMPONENTS Widgets)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})

add_executable(client WIN32 MACOSX_BUNDLE
    src/Adapter/AbstractAdapter.cpp src/Adapter/AbstractAdapter.hpp
    src/Adapter/ConnectionStatusAdapter.cpp src/Adapter/ConnectionStatusAdapter.hpp
    src/Enum/FSMType.hpp
    src/Enum/RequestMethod.hpp
    src/Enum/StatType.hpp
    src/Exception/AbstractRuntimeException.hpp
    src/Exception/ConfigurationException.hpp
    src/Exception/ConnectionException.hpp
    src/Model/UserStateModel.cpp src/Model/UserStateModel.hpp
    src/SharedObjects.cpp src/SharedObjects.hpp
    src/Transport.hpp
    src/Window/ClientCredentialsWindow.cpp src/Window/ClientCredentialsWindow.hpp src/Window/ClientCredentialsWindow.ui
    src/Window/NotificationWindow.cpp src/Window/NotificationWindow.hpp src/Window/NotificationWindow.ui
    src/Window/StudentGetTaskWindow.cpp src/Window/StudentGetTaskWindow.hpp src/Window/StudentGetTaskWindow.ui
    src/Window/StudentTaskWindow.cpp src/Window/StudentTaskWindow.hpp src/Window/StudentTaskWindow.ui
    src/Window/TeacherStatsWindow.cpp src/Window/TeacherStatsWindow.hpp src/Window/TeacherStatsWindow.ui
    src/main.cpp
)
target_include_directories(client PRIVATE
    src
)

target_compile_definitions(client PRIVATE
    _GLIBCXX_USE_CXX11_ABI=0
)

target_link_libraries(client PRIVATE
    Qt::Core
    Qt::Gui
    Qt::Network
)

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(client PRIVATE
        Qt::Widgets
    )
endif()

install(TARGETS client
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Consider using qt_generate_deploy_app_script() for app deployment if
# the project can use Qt 6.3. In that case rerun qmake2cmake with
# --min-qt-version=6.3.
