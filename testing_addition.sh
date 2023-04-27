#!/bin/bash
size=$1
./"test" "$size" "10000"
./"test_jit" "$size" "10000"
