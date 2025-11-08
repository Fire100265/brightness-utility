find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

find_package(PkgConfig REQUIRED)
pkg_check_modules(DDCUTIL REQUIRED ddcutil)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${DDCUTIL_INCLUDE_DIRS}
)

qt_add_resources(APP_RESOURCES resources.qrc)

set(SOURCES
    ddcutil.c
    ui.cpp
    main.cpp
    ${APP_RESOURCES}
)

qt_add_executable(brightness-utility ${SOURCES})

target_link_libraries(brightness-utility
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        ${DDCUTIL_LIBRARIES}
)

target_compile_options(brightness-utility PRIVATE ${DDCUTIL_CFLAGS_OTHER})
