
# Qunish

**qunish** is a lightweight, custom Unix shell implemented in C. Designed with modularity and clarity in mind, it supports basic built-in commands, external program execution, and simple piping using `posix_spawnp` — making it suitable for POSIX-compliant systems like QNX that may lack `fork()`.

## Features

- Built-in support for:
  - `cd` – Change directories
  - `exit` – Exit the shell
- ⚙️ Execution of external commands via `posix_spawnp()`
- Single pipe command support: `cmd1 | cmd2`
- Dynamic prompt displaying current working directory
- Organized modular structure for maintainability

## Why `posix_spawnp`?

Unlike traditional shells that use `fork()` and `exec()`, `qunish` uses `posix_spawnp()` for process creation, improving compatibility with operating systems like QNX which restrict `fork()` usage. This also reduces overhead in embedded environments.

## Build Instructions

Make sure you have `make` and `gcc` installed. Then:

```bash
make
```

This will produce the `qunish` executable in the `bin/` directory.

To clean build artifacts:

```bash
make clean
```

## Usage

After building, run:

```bash
./bin/qunish
```

Example commands:

```bash
cd /tmp
ls | grep log
exit
```

## License

This project is released under the MIT License.