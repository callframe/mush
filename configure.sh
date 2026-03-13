#!/bin/bash

set -euo pipefail

BY="${BASH_SOURCE[0]}"
work_directory="$(realpath "$(dirname "$BY")")"
cd "$work_directory" || echo "work directory not found"

sources=(
  "$work_directory/mush.c"
)
OBJECTS=(${sources[@]%.c}.o)
MUSH="$work_directory/mush"

## helpers and tools
sed="sed"

check_defined() {
  local ref="$1"
  : "${!ref:?$ref is not defined}"
}

replace_str() {
  local ref="$1"
  printf -- '-e s|@%s@|%s|g' "$ref" "${!ref}"
}

## include configurations and tools
config_sh="$work_directory/config.sh"
source "$config_sh" || echo "config.sh is missing"

check_defined CC
check_defined RM

## makefile sources and generation
makefile_in="$work_directory/makefile.in"
makefile="$work_directory/makefile"

"$sed" \
  "$(replace_str BY)" \
  "$(replace_str BASH)" \
  "$(replace_str RM)" \
  "$(replace_str CC)" \
  "$(replace_str OBJECTS)" \
  "$(replace_str MUSH)" \
  "$makefile_in" > "$makefile"
