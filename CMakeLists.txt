cmake_minimum_required(VERSION 3.14)

project(final_final)


include_directories (${PROJECT_SOURCE_DIR})
include_directories (${PROJECT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR}/gameserver)
include_directories(${PROJECT_BINARY_DIR}/gameserver)
add_subdirectory(${PROJECT_SOURCE_DIR}/gameserver)

find_package(Qt6 REQUIRED Widgets Network Qml Quick LinguistTools)

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
)

qt_wrap_cpp(
    MOC_WRAPPERS
    sessionmodel.h
    fieldmodel.h
    dfsthread.h
    cell.h)

qt_add_resources(
    QRC_WRAPPERS
    main.qrc)

add_executable(
    gameserver WIN32
    serverlauncher.cpp
    )

target_link_libraries(gameserver PRIVATE server)


add_executable(final_final
  ${PROJECT_SOURCES}

  ${MOC_WRAPPERS}
  ${QRC_WRAPPERS}
)

target_link_libraries(final_final Qt6::Widgets Qt6::Network Qt6::Qml Qt6::Quick)
