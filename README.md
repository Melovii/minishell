# 🐚 Minishell

*A minimalist yet powerful shell implementation - as beautiful as a shell*

---

## 📖 Introduction

Minishell is a custom shell implementation written in C that mimics the core functionality of bash. This project demonstrates deep understanding of system programming concepts including process management, file descriptors, signal handling, and command parsing. Built with elegance and efficiency in mind, Minishell provides a robust command-line interface that handles complex scenarios with the grace of a seasoned shell.

## ✨ Features

### Core Shell Functionality
- **Interactive Prompt**: Displays a clean prompt waiting for user commands
- **Command History**: Maintains a working history of executed commands
- **Executable Search**: Locates and launches programs using PATH variable or absolute/relative paths
- **Signal Management**: Proper handling of shell signals with bash-like behavior
- **Memory Safety**: Zero memory leaks with comprehensive cleanup

### Advanced Parsing & Execution
- **Quote Handling**: Sophisticated parsing of single and double quotes
- **Variable Expansion**: Environment variable substitution with `$VAR` syntax
- **Exit Status Tracking**: Access last command's exit code via `$?`
- **Pipeline Support**: Command chaining with pipes (`|`)
- **I/O Redirection**: Complete redirection suite (`<`, `>`, `>>`, `<<`)

### Built-in Commands
A comprehensive set of essential shell built-ins, each implemented to match bash behavior:
- `echo` (with `-n` option support)
- `cd` (relative and absolute path navigation)
- `pwd` (current directory display)
- `export` (environment variable management)
- `unset` (variable removal)
- `env` (environment display)
- `exit` (graceful shell termination)

## 🛠️ Installation & Compilation

### Prerequisites
- GCC compiler
- Make utility
- Standard C library
- Readline library

### Build Process
```bash
# Clone the repository
git clone [repository-url]
cd minishell

# Compile the project
make
```

The Makefile includes all standard rules and compiles with strict flags (`-Wall -Wextra -Werror`) ensuring code quality.

## 🚀 Usage

### Starting Minishell
```bash
./minishell
```

### Basic Command Examples
```bash
minishell> echo "Hello, World!"
Hello, World!

minishell> ls -la | grep minishell
-rwxr-xr-x  1 user  staff  12345 Jan 01 12:00 minishell

minishell> export MY_VAR="test value"
minishell> echo $MY_VAR
test value

minishell> pwd
/path/to/current/directory
```

## 🔧 Built-in Commands

| Command | Syntax | Description |
|---------|--------|-------------|
| `echo` | `echo [-n] [text...]` | Display text with optional newline suppression |
| `cd` | `cd [path]` | Change current directory |
| `pwd` | `pwd` | Print current working directory |
| `export` | `export [VAR=value]` | Set environment variables |
| `unset` | `unset [VAR]` | Remove environment variables |
| `env` | `env` | Display all environment variables |
| `exit` | `exit [status]` | Exit shell with optional status code |

## 🔄 Parsing and Execution Flow

Minishell processes commands through a sophisticated multi-stage pipeline:

1. **Tokenization**: Input string is broken into meaningful tokens
2. **Parsing**: Tokens are organized into command structures with proper syntax validation
3. **Expansion**: Environment variables and special parameters are expanded
4. **Execution**: Commands are executed with proper process management and I/O handling

This design ensures robust command processing while maintaining excellent performance.

## 📡 Redirections and Pipes

### Input/Output Redirection
- `command < file` - Redirect input from file
- `command > file` - Redirect output to file (overwrite)
- `command >> file` - Redirect output to file (append)
- `command << delimiter` - Here-document input until delimiter

### Pipeline Processing
- `cmd1 | cmd2 | cmd3` - Chain commands with seamless data flow
- Supports complex multi-stage pipelines with proper error propagation

## 🎛️ Signal Handling

Minishell implements bash-compatible signal behavior:

- **Ctrl+C**: Interrupts current command and displays new prompt
- **Ctrl+D**: Gracefully exits the shell (EOF)  
- **Ctrl+\\**: Ignored (no action taken)

Signal handling uses minimal global state (single global variable) for clean implementation.

## 🌍 Environment Variables & Exit Status

### Variable Expansion
- `$VAR` - Expands to the value of environment variable VAR
- `$?` - Expands to exit status of last executed command
- Handles unset variables gracefully

### Special Quote Behavior
A sophisticated quoting system that perfectly matches bash behavior:

```bash
# Set USER environment variable for testing
minishell> export USER="john_doe"

# Test single quotes within double quotes
minishell> echo "'$USER'"
'john_doe'

# Test double quotes within single quotes  
minishell> echo '"$USER"'
"$USER"
```

This nuanced handling demonstrates the shell's advanced parsing capabilities!

## 🔤 Quoting System

### Single Quotes (`'`)
- Preserve literal value of all characters within quotes
- No variable expansion or special character interpretation
- Cannot contain single quotes

### Double Quotes (`"`)
- Allow variable expansion with `$`
- Preserve literal value of most characters
- Enable complex string construction with embedded variables

## 🛡️ Error Handling and Edge Cases

Minishell is built for robustness, gracefully handling:

- **Input Validation**: Empty commands, malformed syntax, unclosed quotes
- **File Operations**: Permission errors, non-existent files, invalid paths
- **Variable Handling**: Unset variables, complex expansion scenarios
- **Memory Management**: Comprehensive leak prevention and cleanup
- **Process Control**: Proper signal handling and child process management
- **Special Characters**: Filenames with spaces, complex quoting scenarios
- **Pipeline Edge Cases**: Empty commands in pipelines, multiple redirections

## 🎁 Bonus Features

### Advanced Quote Processing
The shell includes sophisticated quote handling that perfectly replicates bash behavior, including the complex interaction between single and double quotes in nested scenarios.

## ⚠️ Known Limitations

- Does not support command line editing features (arrow keys for history navigation)
- Backslash escaping is not implemented
- Advanced bash features like command substitution are not supported

## 📁 Project Structure

```
minishell/
├── includes/         # Header files
├── libft/            # Custom C library  
├── srcs/             # Source code
│   ├── builtins/     # Built-in command implementations
│   ├── execution/    # Command execution and process management
│   ├── parsing/      # Tokenization and command parsing
│   ├── utils/        # Utility functions
│   └── main.c        # Entry point
└── Makefile          # Build configuration
```

*Created as part of the 42 School curriculum - a testament to systems programming mastery.*

---

*"The shell is not just a program, but a philosophy of elegant simplicity."*
