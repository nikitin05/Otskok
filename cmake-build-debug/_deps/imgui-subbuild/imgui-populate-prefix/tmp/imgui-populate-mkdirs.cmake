# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/Prog/Otskok/cmake-build-debug/_deps/imgui-src"
  "D:/Prog/Otskok/cmake-build-debug/_deps/imgui-build"
  "D:/Prog/Otskok/cmake-build-debug/_deps/imgui-subbuild/imgui-populate-prefix"
  "D:/Prog/Otskok/cmake-build-debug/_deps/imgui-subbuild/imgui-populate-prefix/tmp"
  "D:/Prog/Otskok/cmake-build-debug/_deps/imgui-subbuild/imgui-populate-prefix/src/imgui-populate-stamp"
  "D:/Prog/Otskok/cmake-build-debug/_deps/imgui-subbuild/imgui-populate-prefix/src"
  "D:/Prog/Otskok/cmake-build-debug/_deps/imgui-subbuild/imgui-populate-prefix/src/imgui-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/Prog/Otskok/cmake-build-debug/_deps/imgui-subbuild/imgui-populate-prefix/src/imgui-populate-stamp/${subDir}")
endforeach()
