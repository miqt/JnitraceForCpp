cmake_minimum_required(VERSION 3.22.1)


add_library(
        findsyscall

        STATIC

        BinarySyscallFinder.cpp

)

target_link_libraries(
        findsyscall

        ${log-lib}
)

