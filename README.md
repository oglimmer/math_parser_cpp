# A mathematical function parser for C++

## Supported syntax

It can parse `+ - * / ^ ( )` as in `53 * 34` or `(2+3)*4^2`

It can parse `sqrt log logten sin cos tan asin acos atan` as in `sqrt(9) or cos(343)` (`log` is log to base of 2, and `logten` is log to the base of 10)

It can parse `pi e` to return the constants pi and e.

Finally it can parse any variable name matching `^\w+$`.

## How to use it

build:

```bash
mkdir build && cd build
cmake ..
make 
```

test

```
# inside build
make test
```

run

```
# inside build
./math_parser-bin "((2+3)*-3)+2+x*y*sin(pi/2)" "x" "-34" "y" "3"
```

(First parameter is the function, any 2nd and 3rd is a variable and its value)

