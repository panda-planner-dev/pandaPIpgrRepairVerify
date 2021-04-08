cmake_minimum_required(VERSION 3.17)
project(TOAD)

set(CMAKE_CXX_STANDARD 14)

add_executable(verificationAsPlanning main.cpp
        htnModel/Model.cpp htnModel/ProgressionNetwork.cpp
        verification/GroundVerifier.cpp verification/GroundVerifier.h
        utils/noDelIntSet.h utils/FlexIntStack.h utils/IntUtil.h utils/StringUtil.h
        utils/noDelIntSet.cpp utils/FlexIntStack.cpp utils/IntUtil.cpp utils/StringUtil.cpp
        )
