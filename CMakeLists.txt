cmake_minimum_required(VERSION 3.16)

### if no build type is set, it is "Release"
if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()

FIND_PACKAGE(Boost)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MACOSX TRUE)
endif()

list(APPEND compiler_flags -Wall -Wextra -Wno-unused-parameter -Wno-sign-compare -pedantic "$<$<CONFIG:DEBUG>:-Og;-ggdb3>" "$<$<CONFIG:RELEASE>:-O2>")
IF ( MACOSX )
   list(APPEND linker_flags "$<$<CONFIG:RELEASE>:-flto>")
ELSE
   list(APPEND linker_flags "$<$<CONFIG:RELEASE>:-flto;-static;-static-libgcc>")
ENDIF()

project(pandaPIpgrRepairVerify)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(verifier)

add_executable(pandaPIpgrRepairVerify main.cpp
        htnModel/Model.cpp htnModel/ProgressionNetwork.cpp
        prefEncoding/GroundPrefixEncoding.cpp prefEncoding/GroundPrefixEncoding.h
        utils/noDelIntSet.h utils/FlexIntStack.h utils/IntUtil.h utils/StringUtil.h
        utils/noDelIntSet.cpp utils/FlexIntStack.cpp utils/IntUtil.cpp utils/StringUtil.cpp
        )
target_link_libraries(pandaPIpgrRepairVerify
    PUBLIC
        to_verifier)
target_compile_options(pandaPIpgrRepairVerify PUBLIC ${compiler_flags})
target_link_options(pandaPIpgrRepairVerify  PUBLIC ${linker_flags})

