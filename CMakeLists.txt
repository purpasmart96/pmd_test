
# Disable in-source builds to prevent source tree corruption.
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "FATAL: In-source builds are not allowed. Please create a separate directory for build files.")
endif()

project( pmd-engine )
cmake_minimum_required( VERSION 3.6 )

set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# Add all the CMake modules you find in the cmake-modules folder.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake-modules/")

if( COMPILER_SUPPORTS_CXX11 )
    if( CMAKE_COMPILER_IS_GNUCXX )
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11" )
    else()
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
    endif()
elseif( COMPILER_SUPPORTS_CXX0X)
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x" )
else()
    # MSVC, On by default (if available)
endif()

# Choose a proper threading library
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_subdirectory(third-party/lodepng)

# Just amalgamated all the C files in the SOURCES variable.
# May change in a future, but if it works...
set(SOURCES
    src/main.c

    src/audio_core/al_common.c
    src/audio_core/sound_core.c

    src/common/dynamic_array.c
    src/common/file_io.c
    src/common/list_generic.c
    src/common/mem_pool.c
    src/common/rand_num.c
    src/common/stack.c
    src/common/stack_generic.c
    src/common/string.c
    src/common/strlcat.c
    src/common/strlcpy.c
    src/common/vec.c

    src/dungeon/dungeon_gen.c
    src/dungeon/floor_function.c

    src/game_common/display.c
    src/game_common/dungeon.c
    src/game_common/game.c
    src/game_common/health.c
    src/game_common/input.c
    src/game_common/item.c
    src/game_common/hunger.c
    src/game_common/menu.c
    src/game_common/move.c
    src/game_common/player.c
    src/game_common/pokemon.c
    src/game_common/shader.c
    src/game_common/shop.c
    src/game_common/sound.c
    src/game_common/sprites.c
    src/game_common/text.c
    src/game_common/tile.c
    src/game_common/items/apples.c
    src/game_common/items/bands.c
    src/game_common/items/berries.c
    src/game_common/items/chests.c
    src/game_common/items/gummies.c
    src/game_common/items/misc.c
    src/game_common/items/orbs.c
    src/game_common/items/projectiles.c
    src/game_common/items/ribbons.c
    src/game_common/items/scarfs.c
    src/game_common/items/seeds.c
    src/game_common/items/specs.c
    src/game_common/items/tm.c
    src/game_common/items/vitamins.c

    src/pokemon/database.c
    src/pokemon/stats.c

    inc/audio_core/al_common.h
    inc/audio_core/sound_core.h
    inc/common/dynamic_array.h
    inc/common/error.h
    inc/common/exception.h
    inc/common/file_io.h
    inc/common/list_generic.h
    inc/common/list_types.h
    inc/common/mem_pool.h
    inc/common/rand_num.h
    inc/common/stack.h
    inc/common/stack_error.h
    inc/common/stack_generic.h
    inc/common/stack_types.h
    inc/common/string.h
    inc/common/strlcat.h
    inc/common/strlcpy.h
    inc/common/template.h
    inc/common/types.h
    inc/common/vec.h
    inc/dungeon/dungeon_gen.h
    inc/dungeon/floor_function.h
    inc/game_common/display.h
    inc/game_common/dungeon.h
    inc/game_common/game.h
    inc/game_common/health.h
    inc/game_common/hunger.h
    inc/game_common/input.h
    inc/game_common/items/apples.h
    inc/game_common/items/bands.h
    inc/game_common/items/berries.h
    inc/game_common/items/chests.h
    inc/game_common/items/gummies.h
    inc/game_common/items/misc.h
    inc/game_common/items/orbs.h
    inc/game_common/items/projectiles.h
    inc/game_common/items/ribbons.h
    inc/game_common/items/scarfs.h
    inc/game_common/items/seeds.h
    inc/game_common/items/specs.h
    inc/game_common/items/tm.h
    inc/game_common/items/vitamins.h
    inc/game_common/item.h
    inc/game_common/map.h
    inc/game_common/move.h
    inc/game_common/player.h
    inc/game_common/pokemon.h
    inc/game_common/shader.h
    inc/game_common/sound.h
    inc/game_common/sprites.h
    inc/game_common/text.h
    inc/game_common/tile.h
    inc/pokemon/stats.h
    inc/pokemon/database.h
    inc/util.h
)

find_package(OpenAL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW REQUIRED)
find_package(SDL2 REQUIRED)

# And wrap everything on the main executable.
add_executable( ${CMAKE_PROJECT_NAME} ${SOURCES} )

include_directories(
    ${CMAKE_SOURCE_DIR}/inc

    ${lodepng_SOURCE_DIR}
    
    ${OpenAL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(
    ${CMAKE_PROJECT_NAME}

    ${lodepng_LIBRARIES}
    
    ${OpenAL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${GLFW_LIBRARIES}
    ${SDL2_LIBRARIES}
    Threads::Threads
)
