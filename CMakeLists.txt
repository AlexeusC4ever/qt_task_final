cmake_minimum_required(VERSION 3.14)

project(final_7)


include_directories (${PROJECT_SOURCE_DIR})
include_directories (${PROJECT_BINARY_DIR})

find_package(Qt6 REQUIRED Widgets Qml Quick)

set(DIRECTORI_FOR_SAVE ${PROJECT_BINARY_DIR}/savedgames)

file(MAKE_DIRECTORY ${DIRECTORI_FOR_SAVE})

set(PROJECT_SOURCES
    main.cpp
    cell.h
    cell.cpp
    fieldmodel.h
    fieldmodel.cpp
    dfsthread.h
    dfsthread.cpp
    sessionmodel.h
    sessionmodel.cpp
#    mainwindow.h
#    mainwindow.cpp
#    mainwindow.ui
)

qt_wrap_cpp(
    MOC_WRAPPERS
#    mainwindow.h
    sessionmodel.h
    fieldmodel.h
    dfsthread.h
    cell.h)

#qt_wrap_ui(
#    UIC_WRAPPERS
#    mainwindow.ui)

qt_add_resources(
    QRC_WRAPPERS
    main.qrc)

add_executable(final_7
  ${PROJECT_SOURCES}
#  ${UIC_WRAPPERS}
  ${MOC_WRAPPERS}
  ${QRC_WRAPPERS}
)

target_link_libraries(final_7 Qt6::Widgets Qt6::Qml Qt6::Quick)
