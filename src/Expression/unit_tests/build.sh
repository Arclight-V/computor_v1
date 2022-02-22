#!/bin/sh
mkdir build
cd build
cmake ../
make &&
./expression_unit_tests