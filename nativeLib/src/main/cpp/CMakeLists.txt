cmake_minimum_required(VERSION 3.22.1)

ENABLE_LANGUAGE(ASM)


find_library(
        log-lib
        log
)

include_directories(
        ./includes/
)

add_subdirectory(dlfc)
add_subdirectory(libpath)
add_subdirectory(adapter)
add_subdirectory(mmkv)
add_subdirectory(utils)
add_subdirectory(hook)
add_subdirectory(raw_syscall)
add_subdirectory(xunwind)
add_subdirectory(linker)
add_subdirectory(findsyscall)







