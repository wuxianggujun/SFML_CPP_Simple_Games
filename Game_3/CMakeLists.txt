cmake_minimum_required(VERSION 3.26)
project(Game_3 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# 添加源文件目录
aux_source_directory(src SOURCE_FILES)

# 添加头文件目录
include_directories(${PROJECT_SOURCE_DIR})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:Game_3> $<TARGET_FILE_DIR:Game_3> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS ${PROJECT_NAME})