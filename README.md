# JT808ProtocolCPP
Implementation of JT808 protocol on C++

## Introduction

## Getting Started

Clone this repository
```sh
git clone git@github.com:bienxanh1901/JT808ProtocolCPP.git

```

Build library

```sh
mkdir build && cd build
cmake ..
cmake --build . --parallel
```

Build without unit tests

```sh
cmake -D JT808_TEST=OFF ..
cmake --build . --parallel
```

Run Unit tests

```sh
ctest
```

## Integrating To Cmake Project

Add to CmakeLists.txt

```c++
// Fetch this library
include(FetchContent)
FetchContent_Declare(
  JT808Protocol
  GIT_REPOSITORY https://github.com/bienxanh1901/JT808ProtocolCPP.git
  GIT_TAG        <release tag>
)

FetchContent_MakeAvailable(JT808Protocol)

...

// Link library
target_link_libraries(myapp PRIVATE JT808Protocol)
```