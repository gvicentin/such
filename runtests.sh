#!/usr/bin/env bash
#
# runtests.sh
#
# Run all tests inside 'build' directory.
# Usage: ./runtests.sh
# ------------------------------------------------------------------------------

no_tests_error() {
    echo "Nothing to be tested. Try running 'make compile-tests' first." >&2
    exit 1
}

find_longest_length() {
  local ENTRIES=$1
  local LONGEST=0

  for LINE in $ENTRIES; do
    local LENGTH=${#LINE}

    if [ "$LENGTH" -gt "$LONGEST" ]; then
      LONGEST=$LENGTH
    fi
  done

  echo "$LONGEST"
}

# ------------------------------------------------------------------------------
#  ENTRYPOINT
# ------------------------------------------------------------------------------
BUILDDIR="build"
[ -d "$BUILDDIR" ] || no_tests_error

pushd "$BUILDDIR" &>/dev/null
TESTSBIN=$(find '.' -name '*_test' -printf "%f\n")
[ -z "$TESTSBIN" ] && no_tests_error
popd &>/dev/null

RTABLE=$(mktemp)
MAXLEN=$(find_longest_length "$TESTSBIN")
printf "%-*s %-5s %-6s\n" "$MAXLEN" "FILE" "COUNT" "STATUS" >>"$RTABLE"

ERRORS=()
TOTAL=0
for TEST in $TESTSBIN; do
    RESULT=$("$BUILDDIR/$TEST")
    CODE=$?
    STATUS="Passed"

    if [ "$CODE" -ne 0 ]; then
        ERRORS+=("$RESULT")
        STATUS="Failed"
        RESULT="-"
    else
        TOTAL=$((TOTAL + RESULT))
    fi
    printf "%-*s %-5s %-6s\n" "$MAXLEN" "$TEST" "$RESULT" "$STATUS" >>"$RTABLE"
done

cat "$RTABLE"
rm "$RTABLE"
echo ""

echo "SUMMARY:" 
if [ "${#ERRORS[@]}" -gt 0 ]; then
    for ERROR in "${ERRORS[@]}"; do
        echo "$ERROR"
    done
    exit 1
else
    echo "Test count: $TOTAL"
    echo "All tests passed."
fi
