# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/Prog/Otskok/cmake-build-debug/_deps/imgui-sfml-src"
  "D:/Prog/Otskok/cmake-build-debug/_deps/imgui-sfml-build"
  "D:/Prog/Otskok/cmake-build-debug/_deps/imgui-sfml-subbuild/imgui-sfml-populate-prefix"
  "D:/Prog/Otskok/cmake-build-debug/_deps/imgui-sfml-subbuild/imgui-sfml-populate-prefix/tmp"
  "D:/Prog/Otskok/cmake-build-debug/_deps/imgui-sfml-subbuild/imgui-sfml-populate-prefix/src/imgui-sfml-populate-stamp"
  "D:/Prog/Otskok/cmake-build-debug/_deps/imgui-sfml-subbuild/imgui-sfml-populate-prefix/src"
  "D:/Prog/Otskok/cmake-build-debug/_deps/imgui-sfml-subbuild/imgui-sfml-populate-prefix/src/imgui-sfml-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/Prog/Otskok/cmake-build-debug/_deps/imgui-sfml-subbuild/imgui-sfml-populate-prefix/src/imgui-sfml-populate-stamp/${subDir}")
endforeach()
