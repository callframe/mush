#!/bin/bash

set -euo pipefail

GIT="${GIT:-git}"
pattern='%ad%x09%an%x09%ae%x09%s%x09%h'
prev_key=""

while IFS=$'\t' read -r date author email subject hash; do
    key="${date}|${author}|${email}"

    if [[ "$key" != "$prev_key" ]]; then
        [[ -n "$prev_key" ]] && printf '\n'
        printf '%s  %s  <%s>\n\n' "$date" "$author" "$email"
    fi

    printf ' * %s (%s)\n' "$subject" "$hash"

    prev_key="$key"
done < <(
    "$GIT" log --date=short --pretty="$pattern"
)
