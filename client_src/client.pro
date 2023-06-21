QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QMAKE_CXXFLAGS += "-D_GLIBCXX_USE_CXX11_ABI=0"

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/src/

SOURCES += \
    src/Adapter/AbstractAdapter.cpp \
    src/Adapter/ConnectionStatusAdapter.cpp \
    src/Model/UserStateModel.cpp \
    src/SharedObjects.cpp \
    src/Window/ClientCredentialsWindow.cpp \
    src/Window/NotificationWindow.cpp \
    src/Window/StudentGetTaskWindow.cpp \
    src/Window/StudentTaskWindow.cpp \
    src/Window/TeacherStatsWindow.cpp \
    src/main.cpp \

HEADERS += \
    src/Adapter/AbstractAdapter.hpp \
    src/Adapter/ConnectionStatusAdapter.hpp \
    src/Enum/FSMType.hpp \
    src/Enum/RequestMethod.hpp \
    src/Enum/StatType.hpp \
    src/Model/UserStateModel.hpp \
    src/SharedObjects.hpp \
    src/Exception/AbstractRuntimeException.hpp \
    src/Exception/ConfigurationException.hpp \
    src/Exception/ConnectionException.hpp \
    src/Transport.hpp \
    src/Window/ClientCredentialsWindow.hpp \
    src/Window/NotificationWindow.hpp \
    src/Window/StudentGetTaskWindow.hpp \
    src/Window/StudentTaskWindow.hpp \
    src/Window/TeacherStatsWindow.hpp

FORMS += \
    src/Window/ClientCredentialsWindow.ui \
    src/Window/NotificationWindow.ui \
    src/Window/TeacherStatsWindow.ui \
    src/Window/StudentGetTaskWindow.ui \
    src/Window/StudentTaskWindow.ui \

CONFIG += ldebug
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
