cmake_minimum_required(VERSION 3.16)

list(APPEND compiler_flags -Wall -Wextra -Wno-unused-parameter -Wno-sign-compare -pedantic "$<$<CONFIG:DEBUG>:-Og;-ggdb3>" "$<$<CONFIG:RELEASE>:-O2>")
list(APPEND linker_flags "$<$<CONFIG:RELEASE>:-flto;-static;-static-libgcc>")

project(htnPrefixEncoding)

set(CMAKE_CXX_STANDARD 14)


add_executable(htnPrefixEncoding main.cpp
        htnModel/Model.cpp htnModel/ProgressionNetwork.cpp
        prefEncoding/GroundPrefixEncoding.cpp prefEncoding/GroundPrefixEncoding.h
        utils/noDelIntSet.h utils/FlexIntStack.h utils/IntUtil.h utils/StringUtil.h
        utils/noDelIntSet.cpp utils/FlexIntStack.cpp utils/IntUtil.cpp utils/StringUtil.cpp
        )

target_compile_options(htnPrefixEncoding PUBLIC ${compiler_flags})
target_link_options(htnPrefixEncoding  PUBLIC ${linker_flags})
