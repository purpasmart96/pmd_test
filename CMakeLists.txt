
# Disable in-source builds to prevent source tree corruption.
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "FATAL: In-source builds are not allowed. Please create a separate directory for build files.")
endif()

project( pmd-engine )
cmake_minimum_required( VERSION 3.6 )

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
)

# Requires: OpenAL
find_package(OpenAL REQUIRED)
#find_package(SOIL REQUIRED) # !!


# And wrap everything on the main executable.
add_executable( ${CMAKE_PROJECT_NAME} ${SOURCES} )

include_directories(
    ${PROJECT_SOURCE_DIR}/inc
    
    ${OpenAL_INCLUDE_DIRS}
#    ${SOIL_INCLUDE_DIRS}
)

target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    
    ${OpenAL_LIBRARIES}
#    ${SOIL_LIBRARIES}
)