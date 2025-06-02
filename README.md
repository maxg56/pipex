# Pipex

A C implementation that reproduces the behavior of shell piping, allowing you to chain commands together just like using pipes (`|`) in bash.

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Usage](#usage)
- [Installation](#installation)
- [Examples](#examples)
- [Project Structure](#project-structure)
- [Technical Details](#technical-details)
- [Author](#author)

## 🔍 Overview

Pipex is a system programming project that implements pipe functionality in C. It takes an input file, executes two or more commands in sequence (with the output of each command being piped to the next), and writes the final result to an output file.

**What it replicates:**
```bash
# Instead of this shell command:
< file1 cmd1 | cmd2 | cmd3 > file2

# You can use:
./pipex file1 "cmd1" "cmd2" "cmd3" file2
```

## ✨ Features

- **Multi-command piping**: Chain multiple commands together
- **Here document support**: Use heredoc syntax for input
- **Error handling**: Comprehensive error messages with colored output
- **Memory management**: Proper cleanup and leak prevention
- **Path resolution**: Automatic command path finding using `$PATH`
- **File operations**: Handles input/output file operations securely

## 🚀 Usage

### Basic Syntax
```bash
./pipex infile "cmd1" "cmd2" ... "cmdN" outfile
```

### Here Document Syntax
```bash
./pipex here_doc LIMITER "cmd1" "cmd2" ... "cmdN" outfile
```

### Parameters
- `infile`: Input file to read from
- `cmd1`, `cmd2`, etc.: Commands to execute (with arguments in quotes)
- `outfile`: Output file to write to
- `LIMITER`: End marker for here document input

## 🛠 Installation

1. **Clone the repository:**
   ```bash
   git clone <your-repo-url>
   cd pipex
   ```

2. **Compile the project:**
   ```bash
   make
   ```

3. **Clean build files (optional):**
   ```bash
   make clean    # Remove object files
   make fclean   # Remove all generated files
   ```

## 📚 Examples

### Example 1: Basic Piping
```bash
# Equivalent to: < input.txt grep "hello" | wc -l > output.txt
./pipex input.txt "grep hello" "wc -l" output.txt
```

### Example 2: Multiple Commands
```bash
# Equivalent to: < file.txt cat | sort | uniq > result.txt
./pipex file.txt "cat" "sort" "uniq" result.txt
```

### Example 3: Here Document
```bash
# Equivalent to: cat << EOF | grep "test" | wc -l > count.txt
./pipex here_doc EOF "grep test" "wc -l" count.txt
```
Then type your input lines and end with `EOF`.

### Example 4: Complex Pipeline
```bash
# Equivalent to: < data.txt cut -d',' -f2 | sort -n | tail -5 > top5.txt
./pipex data.txt "cut -d, -f2" "sort -n" "tail -5" top5.txt
```

## 📁 Project Structure

```
pipex/
├── Makefile              # Build configuration
├── README.md            # This file
├── include/
│   └── pipex.h          # Header file with definitions
└── src/
    ├── main.c           # Entry point
    ├── pipex_parsing.c  # Command line parsing
    ├── pipex_execution.c # Command execution logic
    ├── pipex_pathing.c  # Path resolution
    ├── pipex_here_doc.c # Here document handling
    ├── pipex_structure.c # Memory management
    └── pipex_error.c    # Error handling
```

## 🔧 Technical Details

### Key Components

- **Process Management**: Uses `fork()` and `execve()` for command execution
- **Inter-Process Communication**: Implements pipes using `pipe()` system call
- **File Descriptors**: Manages stdin/stdout redirection with `dup2()`
- **Path Resolution**: Searches `$PATH` environment variable for executables
- **Memory Management**: Proper allocation and deallocation with error handling

### Data Structures

```c
typedef struct s_pipex {
    int         fd_infile;      // Input file descriptor
    int         fd_outfile;     // Output file descriptor
    char        **paths;        // PATH environment variable split
    size_t      cmd_count;      // Number of commands
    t_cmd       *cmd;           // Array of command structures
    int         *pid_list;      // Process IDs for child processes
} t_pipex;
```

### Error Handling

The program provides detailed error messages for various scenarios:
- Missing arguments
- File not found
- Command not found
- Permission errors
- Internal system errors

### Dependencies

- **libft**: Custom C library (automatically cloned and compiled)
- **Standard C libraries**: `unistd.h`, `fcntl.h`, `sys/wait.h`, etc.

## 🎯 Learning Objectives

This project teaches:
- **Process creation and management**
- **Inter-process communication using pipes**
- **File descriptor manipulation**
- **Environment variable handling**
- **Memory management in C**
- **Error handling and debugging**
- **Makefile configuration**

## 🐛 Troubleshooting

### Common Issues

1. **Command not found**: Ensure the command exists in your `$PATH`
2. **Permission denied**: Check file permissions for input/output files
3. **Compilation errors**: Ensure you have `gcc` and `make` installed

### Debug Mode

For debugging, you can compile with additional flags:
```bash
make CFLAGS="-Wall -Wextra -Werror -g -fsanitize=address"
```

## 📝 Notes

- The program handles both absolute and relative paths for commands
- Input files that don't exist will be handled gracefully
- Here document input is stored in a temporary file (`/tmp/tmp-heredoc-pipex`)
- The program respects shell behavior for command execution and error codes

## 👤 Author

**mgendrot** - 42 School Student

Created as part of the 42 School curriculum - a project focused on system programming and understanding Unix pipes.

---

*This project is part of the 42 School curriculum and demonstrates fundamental concepts in system programming, process management, and inter-process communication.*
