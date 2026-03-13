#!/bin/bash

sed="sed"

check_defined() {
  local ref="$1"
  : "${!ref:?$ref is not defined}"
}

replace_str() {
  local ref="$1"
  printf -- '-e s|@%s@|%s|g' "$ref" "${!ref}"
}

work_directory="$(realpath "$(dirname "${BASH_SOURCE[0]}")")"
cd "$work_directory" || echo "work directory not found"

# include configurations and tools
config_sh="$work_directory/config.sh"
source "$config_sh" || echo "config.sh is missing"

check_defined CC

# makefile to produce
makefile_in="$work_directory/makefile.in"
makefile="$work_directory/makefile"

"$sed" \
  "$(replace_str CC)" \
  "$makefile_in" > "$makefile"
