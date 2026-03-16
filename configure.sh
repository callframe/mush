#!/bin/bash

set -euo pipefail

BY="${BASH_SOURCE[0]}"
work_directory="$(realpath "$(dirname "$BY")")"
cd "$work_directory"

WORK_DIR="$work_directory"

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
source "$config_sh"

check_defined CC
check_defined RM
check_defined RANLIB
check_defined AUTORECONF

## makefile sources and generation
makefile_in="$work_directory/makefile.in"
makefile="$work_directory/makefile"

"$sed" \
  "$(replace_str BY)" \
  "$(replace_str BASH)" \
  "$(replace_str RM)" \
  "$(replace_str RANLIB)" \
  "$(replace_str CC)" \
  "$(replace_str AUTORECONF)" \
  "$(replace_str WORK_DIR)" \
  "$makefile_in" > "$makefile"
