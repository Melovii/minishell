# 🐚 Minishell

*A minimalist yet powerful shell implementation - as beautiful as a shell*

---

## 📖 Introduction

Minishell is a custom shell implementation written in C that mimics the core functionality of bash. This project demonstrates deep understanding of system programming concepts including process management, file descriptors, signal handling, and command parsing. Built with elegance and efficiency in mind, Minishell provides a robust command-line interface that handles complex scenarios with the grace of a seasoned shell.

## ✨ Features

### Core Shell Functionality
- **Interactive Prompt**: Clean prompt with command history support
- **Executable Search**: Locates programs using PATH variable or absolute/relative paths
- **Signal Management**: Proper handling of Ctrl+C, Ctrl+D, and Ctrl+\ with bash-like behavior
- **Memory Safety**: Zero memory leaks with comprehensive cleanup

### Advanced Command Processing
- **Quote Handling**: Sophisticated parsing of single (`'`) and double (`"`) quotes
- **Variable Expansion**: Environment variable substitution with `$VAR` and exit status via `$?`
- **Pipeline Support**: Command chaining with pipes (`|`) and proper error propagation
- **I/O Redirection**: Complete suite (`<`, `>`, `>>`, `<<`) with here-document support

### Built-in Commands
Essential shell built-ins implemented to match bash behavior:
`echo` • `cd` • `pwd` • `export` • `unset` • `env` • `exit`

## 🛠️ Installation & Setup

### Prerequisites
- GCC compiler
- Make utility
- Standard C library
- Readline library (libreadline-dev)

### Dependencies Installation
Before compiling, install each required component:

```bash
# Ubuntu/Debian
sudo apt update
sudo apt install gcc make libreadline-dev

# CentOS/RHEL/Fedora
sudo dnf install gcc make readline-devel

# macOS
# Install Xcode Command Line Tools (includes GCC and Make)
xcode-select --install
# Install readline via Homebrew
brew install readline
```

### Quick Start
```bash
# Clone and build
git clone git@github.com:Melovii/minishell.git
cd minishell
make

# Run minishell
./minishell
```

## 🚀 Usage Examples

```bash
# Basic commands
minishell> echo "Goodbye, World?"
Goodbye, World?

# Pipelines and redirections
minishell> ls -la | grep minishell > output.txt
minishell> cat < input.txt | sort | uniq >> results.txt

# Environment variables
minishell> export MY_VAR="test value"
minishell> echo "Value: $MY_VAR, Exit code: $?"
Value: test value, Exit code: 0

# Complex quoting
minishell> export USER="Melovi"
minishell> echo "'Hello $USER'" vs '"Hello $USER"'
'Hello Melovi' vs "Hello $USER"
```

## 🔧 Built-in Commands Reference

| Command | Syntax | Description |
|---------|--------|-------------|
| `echo` | `echo [-n] [text...]` | Display text with optional newline suppression |
| `cd` | `cd [path]` | Change current directory (supports relative/absolute paths) |
| `pwd` | `pwd` | Print current working directory |
| `export` | `export [VAR=value]` | Set/display environment variables |
| `unset` | `unset [VAR]` | Remove environment variables |
| `env` | `env` | Display all environment variables |
| `exit` | `exit [status]` | Exit shell with optional status code |

## 🔄 Architecture & Processing Flow

Minishell processes commands through a sophisticated pipeline:

1. **Tokenization** → Break input into meaningful tokens
2. **Parsing** → Build command structures with syntax validation  
3. **Expansion** → Resolve variables and special parameters
4. **Execution** → Launch processes with proper I/O and signal handling

This multi-stage design ensures robust command processing while maintaining excellent performance.

## 📡 Advanced Features

### Redirection & Pipes
```bash
# Input/Output redirection
command < infile          # Read from file
command > outfile         # Write to file (overwrite)
command >> outfile        # Append to file
command << EOF            # Here-document until "EOF"

# Pipeline processing
cmd1 | cmd2 | cmd3        # Chain commands with data flow
```

### Quote System Mastery
- **Single quotes (`'`)**: Preserve all characters literally (no expansion)
- **Double quotes (`"`)**: Allow variable expansion while preserving most characters
- **Nested quoting**: Handles complex scenarios like `"'$VAR'"` and `'"$VAR"'`

### Signal Handling
- **Ctrl+C**: Interrupt current command, display new prompt
- **Ctrl+D**: Graceful shell exit (EOF)
- **Ctrl+\\**: Ignored (bash-compatible behavior)

## 🛡️ Robustness & Error Handling

Minishell gracefully handles edge cases including:
- Malformed syntax and unclosed quotes
- Permission errors and invalid file paths  
- Unset variables and complex expansion scenarios
- Memory management with comprehensive leak prevention
- Process control and child process management
- Special characters and complex quoting scenarios

## ⚠️ Current Limitations

- No command line editing (arrow key history navigation)
- Backslash escaping not implemented
- Advanced bash features (command substitution, wildcards) not supported

## 📁 Project Structure

```
minishell/
├── includes/         # Header files and function prototypes
├── libft/           # Custom C utility library
├── srcs/            # Source code organized by functionality
│   ├── builtins/    # Built-in command implementations
│   ├── execution/   # Process management and execution
│   ├── parsing/     # Tokenization and command parsing
│   ├── utils/       # Helper functions and utilities
│   └── main.c       # Program entry point
└── Makefile         # Build configuration with strict flags
```

## 🎓 Technical Highlights

This implementation showcases advanced C programming concepts:
- **Process Management**: Fork, exec, wait, and pipe system calls
- **File Descriptor Manipulation**: Complex I/O redirection handling
- **Memory Management**: Custom allocation strategies with zero leaks
- **Signal Processing**: Proper signal handling in multi-process environment
- **String Processing**: Sophisticated tokenization and parsing algorithms

---

*Built as part of the 42 School curriculum - a testament to systems programming excellence.*

**"The shell is not just a program, but a philosophy of elegant simplicity."**
