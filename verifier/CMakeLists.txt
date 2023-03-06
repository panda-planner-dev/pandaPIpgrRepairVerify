project(to-verifier)


# commands for the util library
file(GLOB UTIL_SOURCE_FILES 
    "util/*.cpp"
    "../htnModel/Model.cpp" 
    "../htnModel/ProgressionNetwork.cpp"
    "../utils/*.cpp"
)

add_library(util
    ${UTIL_SOURCE_FILES}
)

target_include_directories(util
    PUBLIC
        ${htnPrefixEncoding_SOURCE_DIR}/htnModel
        ${htnPrefixEncoding_SOURCE_DIR}/utils
        util/
)

# commands for the TO verifier
file(GLOB TO_SOURCE_FILES 
    "to_verifier/*.cpp" 
)

add_library(to_verifier
    ${TO_SOURCE_FILES}
)

target_include_directories(to_verifier
    PUBLIC
        ${PROJECT_SOURCE_DIR}/to_verifier/
        ${htnPrefixEncoding_SOURCE_DIR}/htnModel
        ${PROJECT_SOURCE_DIR}/
)

target_link_libraries(to_verifier
    PUBLIC
        util
)