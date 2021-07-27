cmake_minimum_required(VERSION 3.19)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4)
    #add_compile_options(/WX)
else ()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic)
    #add_compile_options(-Werror)
endif ()

project(popsim LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Charts REQUIRED)
#find_package(Qt5 COMPONENTS LinguistTools REQUIRED)

set(UI_FILES mainwindow.ui)
set(HPP_FILES mainwindow.h sim.h pop.h)
set(CPP_FILES main.cpp mainwindow.cpp sim.cpp pop.cpp)

#set(TS_FILES popsim_en_US.ts)
#qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

add_executable(
        popsim
        ${UI_FILES}
        ${HPP_FILES}
        ${CPP_FILES}
        #${TS_FILES}
)

target_link_libraries(popsim PRIVATE Qt5::Widgets)
target_link_libraries(popsim PRIVATE Qt5::Charts)
