#!/bin/bash
set -Eeuo pipefail

file_test () {
  # Read first line of test with RUN:
  local first_line=$(head -n 1 "$1")
  if [[ $first_line =~ //[[:space:]]*RUN:[[:space:]]*(.*) ]]; then
    local cmd="${BASH_REMATCH[1]}"
    cmd=${cmd//%s/$1}
    # Execute the command
    local got_val=$(eval "$cmd")
  else
    echo "No RUN command found in $1"
    return 1
  fi

  # Read second line of test with CHECK:
  local second_line=$(sed -n '2p' "$1")
  if [[ $second_line =~ //[[:space:]]*CHECK:[[:space:]]*(.*) ]]; then
    local expected_val="${BASH_REMATCH[1]}"
  else
    echo "No CHECK command found in $1"
    return 1
  fi

  # Compare results
  if [[ "$got_val" != "$expected_val" ]]; then
    echo -n "FAIL: $1 "
  else
    echo -n "PASS: $1 "
  fi

  echo "expected: $expected_val, got: $got_val"
}

# Run all tests
for test_file in *.c; do
  file_test "$test_file"
done
