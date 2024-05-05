cmake_minimum_required(VERSION 3.13)

project(lain-bootleg-bootleg)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES
   src/main.c
   src/engine.c
   src/input.c
   src/menu.c
   src/scene.c
   src/shader.c
   src/sprite.c
   src/text.c
   src/texture.c
   src/window.c
   src/state.c
   src/kumashoot.c
   src/minigame.c
   src/vector2d.c
   src/random.c
   src/animations.c
   src/dressup.c
   src/theater.c
   src/cJSON.c
   src/resources.c
   src/sound.c
   src/movie.c
)

set_source_files_properties(src/movie.c PROPERTIES
        OBJECT_DEPENDS ${PROJECT_SOURCE_DIR}/src/library.js
)
set_source_files_properties(src/engine.c PROPERTIES
        OBJECT_DEPENDS ${PROJECT_SOURCE_DIR}/src/library.js
)


set(CMAKE_EXECUTABLE_SUFFIX ".html")
set(USE_FLAGS --use-preload-plugins
        --preload-file=${PROJECT_SOURCE_DIR}/res/sprites/@/res/sprites/
        --preload-file=${PROJECT_SOURCE_DIR}/res/sounds/@/res/sounds/
        --embed-file=${PROJECT_SOURCE_DIR}/res/animations.json@/res/animations.json
        --use-port=contrib.glfw3
        --bind
        --js-library=${PROJECT_SOURCE_DIR}/src/library.js
        -s SAFE_HEAP=1
        -s WASM=1
        -s LEGACY_GL_EMULATION=0
        -s GL_UNSAFE_OPTS=1
        -s FULL_ES3=1
        -s MIN_WEBGL_VERSION=2
        -s MAX_WEBGL_VERSION=2
        -s ALLOW_MEMORY_GROWTH=1
        -s ASYNCIFY=1
        -s USE_SDL
        -s EXPORTED_FUNCTIONS=setValue,_main)
set(CMAKE_C_FLAGS "-s USE_SDL")

if(DEFINED DEBUG)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
    set(USE_FLAGS -g3 -gsource-map -gseparate-dwarf -s DISABLE_EXCEPTION_CATCHING=0 -s ASSERTIONS=1 -s GL_ASSERTIONS=1 ${USE_FLAGS})
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
    set(USE_FLAGS -O3 ${USE_FLAGS})
endif()


add_executable(${PROJECT_NAME} ${SOURCES})
list(JOIN USE_FLAGS " " USE_FLAGS)
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "${USE_FLAGS}")
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src)
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/res/lain_mov.webm
        ${CMAKE_CURRENT_BINARY_DIR}/lain_mov.webm)
