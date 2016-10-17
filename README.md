# Unit Tests for [libigl](https://github.com/libigl/libigl)
[![Build Status](https://travis-ci.org/libigl/libigl-unit-tests.svg?branch=master)](https://travis-ci.org/libigl/libigl-unit-tests)

Get started with

```
git clone --recursive git@github.com:libigl/libigl-unit-tests.git
```

## Dependencies

[googletest](https://github.com/google/googletest) is a submodule


## Build and test

Use `cmake` to generate a `Makefile` that will build _and test_ upon issuing
`make`:

```
mkdir build
cd build
cmake ..
```

Then build and test with

```
make
```

This will first compile the tests and then immediately run the tests. If tests
are succeeding you should see output similar to:

```
[       OK ] Example.Sub1 (1056 ms)
[ RUN      ] Example.Sub2 
[       OK ] Example.Sub2 (4 ms)
[ RUN      ] Example.Sub4
[       OK ] Example.Sub4 (2 ms)
[----------] 3 tests from Example (1062 ms total)
```

