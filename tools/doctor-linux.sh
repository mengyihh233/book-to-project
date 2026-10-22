#!/usr/bin/env bash
set -eu
for tool in bash g++ gdb cmake ninja shellcheck python3; do
    command -v "$tool"
done
