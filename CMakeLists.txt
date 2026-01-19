cmake_minimum_required(VERSION 3.16)
project(SeaSim LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
find_package(JPEG REQUIRED)
find_package(PNG REQUIRED)

add_executable(SeaSim WIN32
        main.cpp
        Fish.cpp
        Fish.h
        UnitVector.cpp
        UnitVector.h
        Utils.h
        Slider.cpp
        Slider.h
        Utils.cpp
)

target_link_libraries(SeaSim PRIVATE SDL3::SDL3 SDL3_image::SDL3_image JPEG::JPEG PNG::PNG)

if(WIN32)
    add_custom_command(TARGET SeaSim POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:SDL3::SDL3>"
            "$<TARGET_FILE_DIR:SeaSim>"
    )
    add_custom_command(TARGET SeaSim POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:SDL3_image::SDL3_image>"
            "$<TARGET_FILE_DIR:SeaSim>"
    )

    add_custom_command(TARGET SeaSim POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/czcionka.bmp"
            "$<TARGET_FILE_DIR:SeaSim>"
    )
endif()