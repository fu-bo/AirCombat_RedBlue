cmake_minimum_required(VERSION 3.3)

project(gurobi_template)

option(CXX "enable C++ compilation" ON)
if(CXX)
    enable_language(CXX)
endif()

set(CMAKE_CXX_STANDARD 11)

find_package(OpenGL REQUIRED)
set(SRC_DIR src/)
if(MSVC)
    message("This is Windows.")
elseif(APPLE)
    message("This is MAC OS.")
    set(GRAPH_DIR fssimplewindow/macosx/)
    set(SOUND_DIR yssimplesound/)
    set(SOUND_SUBDIR yssimplesound/macosx/)
    find_library(COCOA_LIBRARY Cocoa REQUIRED)
    include_directories(include ${GRAPH_DIR} ${SOUND_DIR} ${SOUND_SUBDIR} ${OPENGL_INCLUDE_DIR})
elseif(UNIX)
    message("This is Linux.")
    set(GRAPH_DIR fssimplewindow/linux/)
    set(SOUND_DIR yssimplesound/)
    set(SOUND_SUBDIR yssimplesound/linux_alsa/)
    find_package(ALSA REQUIRED)
    find_package(X11 REQUIRED)
    include_directories(include ${GRAPH_DIR} ${SOUND_DIR} ${SOUND_SUBDIR} ${OPENGL_INCLUDE_DIR} ${ALSA_INCLUDE_DIRS} ${X11_INCLUDE_DIR})
else()
endif()

if(MSVC)
elseif(APPLE)
    add_library(yssimplesound ${SOUND_DIR}yssimplesound.cpp ${SOUND_SUBDIR}yssimplesound_macosx_cpp.cpp ${SOUND_SUBDIR}yssimplesound_macosx_objc.m)
    add_library(fssimplewindowcpp ${GRAPH_DIR}fssimplewindowcpp.cpp ${GRAPH_DIR}fssimplewindowobjc.m)
    target_link_libraries(fssimplewindowcpp ${OPENGL_LIBRARIES} )
elseif(UNIX)
    add_library(yssimplesound ${SOUND_DIR}yssimplesound.cpp ${SOUND_SUBDIR}yssimplesound_linux_alsa.cpp)
    target_link_libraries(yssimplesound ${ALSA_LIBRARIES} )
    add_library(fssimplewindowcpp ${GRAPH_DIR}fssimplewindow.cpp)
    target_link_libraries(fssimplewindowcpp ${OPENGL_LIBRARIES} ${X11_LIBRARIES})
else()
endif()

add_library(Common ${SRC_DIR}Common.cpp)

add_library(StringPaser ${SRC_DIR}StringPaser.cpp)

add_library(Colored ${SRC_DIR}Colored.cpp)
target_link_libraries(Colored fssimplewindowcpp)

add_library(ColorObj ${SRC_DIR}ColorObj.cpp)
target_link_libraries(ColorObj Colored fssimplewindowcpp)

add_library(ColorCircle ${SRC_DIR}ColorCircle.cpp)
target_link_libraries(ColorCircle Colored fssimplewindowcpp)

add_library(ColorQuad ${SRC_DIR}ColorQuad.cpp)
target_link_libraries(ColorQuad Colored fssimplewindowcpp)

add_library(Bullet ${SRC_DIR}Bullet.cpp)
target_link_libraries(Bullet ColorCircle)

add_library(ColorFunction ${SRC_DIR}ColorFunction.cpp)
target_link_libraries(ColorFunction Colored ColorObj ColorQuad ColorCircle Bullet)

add_executable(game_main ${SRC_DIR}main.cpp)

if(MSVC)
elseif(APPLE)
    target_link_libraries(game_main Common StringPaser ColorFunction Colored ColorObj ColorQuad ColorCircle Bullet fssimplewindowcpp yssimplesound  ${COCOA_LIBRARY})
elseif(UNIX)
    target_link_libraries(game_main Common StringPaser ColorFunction Colored ColorObj ColorQuad ColorCircle Bullet fssimplewindowcpp yssimplesound)
else()
endif()

