cmake_minimum_required(VERSION 3.22.1)



SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wwritable-strings")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wwritable-strings")




add_library(
        linkerHandler

        STATIC

        Symbol.cpp
        linkerHandler.cpp

        )

target_link_libraries(
                linkerHandler

                ${log-lib}
)

