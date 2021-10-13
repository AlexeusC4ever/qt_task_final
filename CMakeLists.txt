cmake_minimum_required(VERSION 3.14)

project(final_10)


include_directories (${PROJECT_SOURCE_DIR})
include_directories (${PROJECT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR}/gameserver)
include_directories(${PROJECT_BINARY_DIR}/gameserver)
add_subdirectory(${PROJECT_SOURCE_DIR}/gameserver)

find_package(Qt6 REQUIRED Widgets Network Qml Quick)

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
    netdialog.h
    netdialog.cpp
#    gameserver.h
#    gameserver.cpp
#    mainwindow.h
#    mainwindow.cpp
#    mainwindow.ui
)

qt_wrap_cpp(
    MOC_WRAPPERS
#    mainwindow.h
#    gameserver.h
    netdialog.h
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

#qt_wrap_cpp(
#    NET_MOC_WRAPPERS
#    server-dlg.h)

#qt_wrap_ui(
#    NET_UIC_WRAPPERS
#    server-dlg.ui)

add_executable(
    gameserver WIN32
    serverlauncher.cpp
    )

target_link_libraries(gameserver PRIVATE server)


add_executable(final_10
  ${PROJECT_SOURCES}
#  ${UIC_WRAPPERS}
  ${MOC_WRAPPERS}
  ${QRC_WRAPPERS}
)

target_link_libraries(final_10 Qt6::Widgets Qt6::Network Qt6::Qml Qt6::Quick)
