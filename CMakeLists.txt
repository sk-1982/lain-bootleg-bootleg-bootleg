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


set(CMAKE_EXECUTABLE_SUFFIX ".html")
set(USE_FLAGS "--use-preload-plugins --preload-file=../res/sprites/@/res/sprites/ --preload-file=../res/sounds/@/res/sounds/  --embed-file=../res/animations.json@/res/animations.json --use-port=contrib.glfw3 -s DISABLE_EXCEPTION_CATCHING=0 -s DEMANGLE_SUPPORT=1 -s SAFE_HEAP=1 --bind -s WASM=1 -O2 -s LEGACY_GL_EMULATION=0  -s GL_UNSAFE_OPTS=1 -s ASSERTIONS=1 -s GL_ASSERTIONS=1 -s FULL_ES3=1 -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 -s ALLOW_MEMORY_GROWTH=1 -s ASYNCIFY=1 -s EXPORTED_FUNCTIONS=setValue,_main -s USE_SDL")
set(CMAKE_C_FLAGS "-s USE_SDL")

if(DEBUG)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
    set(USE_FLAGS "-g3 -gsource-map -gseparate-dwarf ${USE_FLAGS}")
endif()


add_executable(${PROJECT_NAME} ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS ${USE_FLAGS})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src)
