cmake_minimum_required (VERSION 3.12)

project("Simulation")

if(POLICY CMP0091)
    cmake_policy(SET CMP0091 NEW)
endif()

# conan profile
set(CONAN_PROFILE "default" CACHE STRING "Conan profile")
# conanfile.txt file
set(CONANFILE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/conanfile.py")
# conan install command
set(CONAN_INSTALL_COMMAND "conan install ${CONANFILE_PATH} -pr ${CONAN_PROFILE} --build=missing --output-folder=${CMAKE_BINARY_DIR} --build=missing")

if(WIN32)
    set(COMMAND_TO_RUN "powershell")
else()
    set(COMMAND_TO_RUN "bash")
endif()

# run conan install
if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan_toolchain.cmake")
    message("Running conan install... Please wait")
    execute_process(
        COMMAND ${COMMAND_TO_RUN}
            ${CONAN_INSTALL_COMMAND}
        OUTPUT_VARIABLE FOO
        RESULT_VARIABLE FOOR
        ERROR_VARIABLE  FOO_ER
    )
    message("conan install finished")
    message(${FOO_ER})
endif()

include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)
include(GenerateExportHeader)

#######################
# YOUR MODULES HERE
#######################

add_subdirectory("src")
add_subdirectory("examples")

#######################
# END
#######################

