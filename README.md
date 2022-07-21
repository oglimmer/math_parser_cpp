# A mathematical function parser for C++

## Supported syntax

It can debugResolve `+ - * / ^ ( )` as in `53 * 34` or `(2+3)*4^2`

It can debugResolve `sqrt log logten sin cos tan asin acos atan` as in `sqrt(9) or cos(343)` (`log` is log to base of 2, and `logten` is log to the base of 10)

It can debugResolve `pi e` to return the constants pi and e.

Finally, it can debugResolve any variable name matching `^\w+$`.

## How to use it

### via Docker

Build it

```
docker build --tag mathparser .
```

Run it

```
docker run --rm mathparser "((2+3)*-3)+2+x*y*sin(pi/2)" "x" "-34" "y" "3"
```

### local compile

You need to have a C++20 compatible compiler, cmake > 3.13 and conan installed.

Then run this to build, test and install:

```bash
mkdir build && cd build
conan install ..
cmake ..
cmake --build .
ctest
sudo cmake --install . 
```

Run via:

```
math_parser-bin "((2+3)*-3)+2+x*y*sin(pi/2)" "x" "-34" "y" "3"
```

(First parameter is the function, any 2nd and 3rd is a variable and its value)

