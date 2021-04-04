cmake_minimum_required(VERSION 3.16)

project(tic-tac-toe LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 COMPONENTS Core Quick QuickControls2 REQUIRED)
find_package(Qt6 COMPONENTS Core Quick QuickControls2 REQUIRED)

set(PROJECT_SOURCES
    main.cpp
    model.h model.cpp
)

qt_add_executable(tic-tac-toe
    ${PROJECT_SOURCES}
)
set_target_properties(tic-tac-toe PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

set(tic-tac-toe_resource_files
    qml/main.qml
    qml/Cell.qml
    qml/GameMenu.qml
    qml/GameWindow.qml
    images/cross.png
    images/ellips.png
)

qt6_add_resources(tic-tac-toe "tic-tac-toe"
    PREFIX
        "/"
    FILES
        ${tic-tac-toe_resource_files}
)


target_compile_definitions(tic-tac-toe
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(tic-tac-toe
  PRIVATE Qt6::Core Qt6::Quick Qt6::QuickControls2)

set_target_properties(tic-tac-toe PROPERTIES
    QT_QML_MODULE_VERSION 1.0
    QT_QML_MODULE_URI TicTacToe
)
qt6_qml_type_registration(tic-tac-toe)
