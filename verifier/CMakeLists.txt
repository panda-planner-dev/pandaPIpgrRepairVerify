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
        ${pandaPIpgrRepairVerify_SOURCE_DIR}/verifier/
        ${pandaPIpgrRepairVerify_SOURCE_DIR}/to_verifier/
        ${pandaPIpgrRepairVerify_SOURCE_DIR}/util
        ${pandaPIpgrRepairVerify_SOURCE_DIR}/htnModel
        ${pandaPIpgrRepairVerify_SOURCE_DIR}/utils
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
        ${pandaPIpgrRepairVerify_SOURCE_DIR}/verifier/
        ${pandaPIpgrRepairVerify_SOURCE_DIR}/to_verifier/
        ${pandaPIpgrRepairVerify_SOURCE_DIR}/htnModel
        ${pandaPIpgrRepairVerify_SOURCE_DIR}/utils
        ${pandaPIpgrRepairVerify_SOURCE_DIR}/
        to_verifier
)

target_link_libraries(to_verifier
    PUBLIC
        util
)
