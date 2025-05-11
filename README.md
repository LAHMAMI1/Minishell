# Minishell

Minishell is a simplified Unix-like command-line interpreter written in C. It replicates key features of common shells (e.g., bash) for educational purposes, including command execution, built-in commands, pipelines, redirections, quoting, and signal handling.

## Table of Contents

- [Features](#features)
- [Project Structure](#project-structure)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Parsing](#parsing)
- [Execution](#execution)
- [Contributors](#contributing)

## Features

- Execute external programs found in `PATH`
- Built-in commands: `cd`, `echo`, `env`, `exit`, `export`, `unset`, `pwd`
- Environment variable management
- Support for single and multi-stage pipelines (`|`)
- Input/output redirections: `>`, `>>`, `<`, `<<`
- Handling of single and double quotes
- Proper process and signal handling (SIGINT, SIGQUIT)
- Graceful error messages and exit statuses

## Project Structure

```
Minishell/
├── builtin/          # Built-in command implementations
├── executor/         # Process execution, piping, redirections
├── include/          # Project headers
├── libft/            # Custom C utility library
├── parser/           # Lexing, parsing, tokenization
├── Makefile          # Build scripts
└── minishell.c       # Main loop
```

## Requirements

- GNU Make
- GCC (or compatible C compiler)
- Unix-like OS (Linux, macOS)

## Installation

```bash
git clone https://github.com/LAHMAMI1/Minishell
cd Minishell
make
```

## Usage

```bash
./minishell
```

Type commands as you would in a standard shell. Use the `exit` command or press `Ctrl+D` to leave the shell.

## Built-in Commands

- **cd**: Change the current directory
- **echo**: Print arguments to standard output
- **env**: Display the current environment variables
- **exit**: Exit the shell with a status code
- **export**: Set or modify environment variables
- **unset**: Remove environment variables
- **pwd**: Print the current working directory

## Parsing

The parser module tokenizes the command line, handles quoting, and builds the data structures for command execution, including redirection and pipeline metadata.

## Execution

The executor module forks child processes, sets up pipes, redirects file descriptors, and invokes built-in or external commands, managing process statuses and signals in the parent shell.

## Contributors

- **Fatima ezzahrae Diraa (*Parsing Part*)**: [GitHub Profile](https://github.com/Raven-79)
- **Oussama Lahmami (*Execution Part*)**: [GitHub Profile](https://github.com/LAHMAMI1)
