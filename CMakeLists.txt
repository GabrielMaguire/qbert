cmake_minimum_required(VERSION 3.16)
project(qbert LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(SRC_FILES
    src/CharacterManager.cpp
    src/KeyHandler.cpp
    src/Pyramid.cpp
    src/main.cpp
)
set(RES_DIR "res")

add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${CMAKE_PROJECT_NAME}
  PRIVATE
    sfml-graphics
)

target_compile_features(${CMAKE_PROJECT_NAME}
  PRIVATE
    cxx_std_17
)

target_compile_options(${CMAKE_PROJECT_NAME}
  PUBLIC
    -g
)

target_compile_definitions(${CMAKE_PROJECT_NAME}
  PUBLIC
    RES_DIR="${CMAKE_SOURCE_DIR}/${RES_DIR}/"
    FONT_DIR="${CMAKE_SOURCE_DIR}/${RES_DIR}/font/"
)

if(WIN32)
    add_custom_command(
        TARGET ${CMAKE_PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>
        VERBATIM)
endif()

#install(TARGETS ${CMAKE_PROJECT_NAME})
