# SIMPLE SHELL

## What is it?

A school project with the aim of writing a simple UNIX command interpreter. The objective is to code a simple shell that behaves like `sh` (man or run `sh`in your terminal to know more).

## How to use it?

**1) Download it:**

```
$ git clone https://github.com/huy75/simple_shell.git
```

**2) Run it:**

If you want to run it in your current environment:

```
$ ./hsh
```

If you want to run it with the `sh` environment:

```
$ sh
$$ ./hsh
```

**3) Quit it:**

Run `exit` or `ctrl + D`

## Commands featured in this simple_shell

You can check the list of commands and builtins of this shell by running `$ man ./man_1_simple_shell`.

To get the details of each available commands, run `ls /bin/` and to then `man COMMAND_NAME` to get more info about the command behaviour.

To get the details of each builtin command, run `help BUILTIN_CMD`.

## Examples

**List directory contents:**

```
$ ls
checkexit.c  _getline.c  hsh      path.c     _realloc.c  shell.h
fork.c       hello       parse.c  README.md  shell.c     strings.c
```

**Create a new directory:**

```
$ mkdir strtok
$ ls
checkexit.c  _getline.c  hsh      path.c     _realloc.c  shell.h    strtok
fork.c       hello       parse.c  README.md  shell.c     strings.c
```

## Learning objectives and limitations

**1) Objectives**

The goal is to understand how does a shell work, what is a pid and a ppid, how to manipulate the environment of the current process, what is the difference between a function and a system call, how to create processes, what are the three prototypes of `main`, how does the shell use the `PATH` to find the programs, how to execute another program with the `execve` system call, how to suspend the execution of a process until one of its children terminates, what is `EOF` / “end-of-file”?

**2) Limitations**

Functions allowed: `access`, `chdir`, `close`, `closedir`, `execve`, `exit`, `_exit`, `fflush`, `fork`, `free`, `getcwd`, `getline`, `isatty`, `kill`, `malloc`, `open`, `opendir`, `perror`, `read`, `readdir`, `signal`, `stat`, `lstat`, `fstat`, `strtok`, `wait`, `waitpid`, `wait3`, `wait4`, and `write`.

`man`any of these to know more about them.

## Authors

[Huy Nguyen](https://github.com/huy75) & [Yago Martinez-Falero Hein](https://github.com/Yagomfh)
