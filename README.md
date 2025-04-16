
# Qunish

**Qunish** is a lightweight, custom Unix shell implemented in C. Designed with modularity and clarity in mind, it supports basic built-in commands, external program execution, and simple piping using `posix_spawnp` — making it suitable for POSIX-compliant systems like QNX that may lack `fork()`.

## Features

- Built-in support for:
  - `cd` – Change directories
  - `exit` – Exit the shell
- Execution of external commands via `posix_spawnp()`
- Single pipe command support: `cmd1 | cmd2`
- Dynamic prompt displaying current working directory
- Organized modular structure for maintainability

## Why `posix_spawnp`?

Unlike traditional shells that use `fork()` and `exec()`, `qunish` uses `posix_spawnp()` for process creation, improving compatibility with operating systems like QNX which restrict `fork()` usage. This also reduces overhead in embedded environments.

## Build Instructions

Make sure you have `make` and `gcc` installed. 

### Build for QNX (Default)

```bash
make
```

This uses the QNX toolchain (qcc) with aarch64 support and places the compiled binary in the bin/ directory.

Tested on Raspberry Pi 4B with QNX SDP 8.0.

### Build for x86
```bash
make x86
```
Uses gcc and builds for standard Linux systems.

### Clean
To clean build artifacts:
```bash
make clean
```

## Usage

Example commands:

```bash
cd /tmp
ls | grep log
exit
```

## License

This project is released under the MIT License.