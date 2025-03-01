#!/bin/bash

MINISHELL=./minishell
LOG_FILE=tests.log

# Clear previous log
> "$LOG_FILE"

echo "Running tests..."

run_test() {
    input="$1"
    expected="$2"
    output=$(echo "$input" | $MINISHELL 2>&1)
    if [ "$output" == "$expected" ]; then
        echo "✅ PASSED: $input"
    else
        echo "❌ FAILED: $input" | tee -a "$LOG_FILE"
        echo "Expected: '$expected'" | tee -a "$LOG_FILE"
        echo "Got:      '$output'" | tee -a "$LOG_FILE"
        echo "--------------------" | tee -a "$LOG_FILE"
    fi
}

# --- Quotes ---
run_test "echo 'hello world'" "hello world"
run_test "echo \"hello world\"" "hello world"
run_test "echo 'hello \\"world\\"'" "hello \"world\""
run_test "echo \"hello 'world'\"" "hello 'world'"
run_test "echo \"\"" ""
run_test "echo ''" ""
run_test "echo 'hello" "Syntax error"

# --- Special Characters ---
run_test "echo \|" "|"
run_test "echo \>" ">"

# --- Redirections ---
echo "test" > testfile
run_test "cat < testfile" "test"
rm -f testfile

# --- Pipes ---
run_test "echo hello | cat" "hello"
run_test "ls | wc -l" "$(ls | wc -l)"
run_test "ls |" "Syntax error"

# --- Logical Operators ---
run_test "echo A && echo B" "A
B"
run_test "false && echo never" ""
run_test "true || echo fallback" ""
run_test "false || echo fallback" "fallback"

# --- Environment Variables ---
export TESTVAR="hello"
run_test "echo $TESTVAR" "hello"
run_test "echo '$TESTVAR'" "$TESTVAR"
unset TESTVAR

# --- Miscellaneous ---
run_test "echo \`pwd\`" "$(pwd)"
run_test "cd /invalid_path" "Error: No such file or directory"
run_test "echo \"A\" && echo \"B\" || echo \"C\"" "A
B"

echo "Tests complete. Check $LOG_FILE for failures."
