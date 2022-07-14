#!/bin/bash

if [[ "$1" =~ .*bash.* ]]; then
    "$@"
elif [ "$1" != "math_parser-bin" ]; then
    math_parser-bin $@
else
    "$@"
fi
