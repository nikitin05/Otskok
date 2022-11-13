# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.23.2)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(sfml-populate NONE)



include(ExternalProject)
ExternalProject_Add(sfml-populate
                     "UPDATE_DISCONNECTED" "False" "URL" "https://github.com/SFML/SFML/archive/refs/tags/2.5.1.zip" "URL_MD5" "2c4438b3e5b2d81a6e626ecf72bf75be"
                    SOURCE_DIR          "D:/Prog/Otskok/cmake-build-debug/_deps/sfml-src"
                    BINARY_DIR          "D:/Prog/Otskok/cmake-build-debug/_deps/sfml-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
                    USES_TERMINAL_PATCH     YES
)


