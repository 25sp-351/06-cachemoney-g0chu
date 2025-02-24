make clean
make

# Test cases in the format "input|expected_output"
tests=(
"4734|forty-seven dollars and thirty-four cents"
"122309|one thousand two hundred twenty-three dollars and nine cents"
"0|zero dollars and zero cents"
"100|one dollar and zero cents"
"101|one dollar and one cent"
)

failed=0

for test in "${tests[@]}"; do
    input=$(echo "$test" | cut -d'|' -f1)
    expected=$(echo "$test" | cut -d'|' -f2)

    output=$(echo "$input" | ./money)

    if [ "$output" != "$expected" ]; then
        echo "failed: input '$input' expected '$expected' but got '$output'"
        failed=1
    else
        echo "test passed"
    fi
done

if [ $failed -eq 0 ]; then
    echo "success"
else
    exit 1
fi
