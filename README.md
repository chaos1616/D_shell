# D_shell: A Simple Unix Shell in C

This document serves as the North Star for this project, outlining the philosophy, core mechanics, and development roadmap for building a basic Unix shell.

## The Philosophy: What is a Shell?

A shell is a **command-line interpreter**. It is not a compiler or a transpiler.

- A **compiler** translates an entire program into machine code ahead of time (e.g., GCC compiling C code).
- An **interpreter** reads a single line of code, evaluates it immediately, and then waits for the next line.

The shell is a special-purpose interpreter. Its language is the set of user commands (like `ls -la`), and the "machine" it runs on is the operating system's **kernel**.

The best analogy is a waiter at a restaurant:
- **You (The User):** The customer who gives high-level orders.
- **Your Command (`ls -la`):** Your order in plain English.
- **The Shell (This Program):** The waiter, who interprets your order.
- **The Kernel:** The kitchen, which only understands specific, low-level instructions.
- **System Calls (`fork`, `exec`):** The shorthand ticket the waiter writes for the kitchen.

The shell's entire job is to run a **REPL (Read-Evaluate-Print Loop)**, acting as the middleman between the user and the kernel.

## The Core Mechanism: The `fork-exec-wait` Cycle

The "magic" of running another program is accomplished by a fundamental three-step dance of system calls:

1.  **`fork()` - The Clone:** The shell creates an identical copy of itself, known as the **child process**. The original **parent process** receives the child's Process ID (PID), while the child receives `0`. This is how they know who they are.

2.  **`exec()` - The Transformation:** The child process's sole mission is to become the desired command. It calls `execvp()`, which tells the kernel to completely replace the child's code and memory with the new program (e.g., `/bin/ls`). If `execvp` succeeds, it never returns.

3.  **`wait()` - The Responsible Parent:** The parent process calls `waitpid()` and sleeps until the child process completes its task. This ensures output is orderly and prevents the child from becoming a "zombie process" after it finishes.

Mastering this `fork-exec-wait` cycle is the primary technical goal of this project.

## Project Blueprint: The Roadmap

This project is divided into tiers. Completing Tier 1 means the project is a success.

### Tier 1: The Minimum Viable Shell (The Finish Line)

This is the core goal. A shell with these features is a complete and impressive project.

-   [ ] **A Functioning REPL:** The shell prints a prompt (e.g., `> `), accepts user input, and loops continuously.
-   [ ] **Command Parsing:** It correctly parses a string like `"ls -la /home"` into a `NULL`-terminated array of strings: `["ls", "-la", "/home", NULL]`.
-   [ ] **Command Execution:** It correctly implements the `fork-exec-wait` cycle to run external commands found in the system's `PATH`.
-   [ ] **Built-in Commands:** It implements the following commands internally, without forking a new process:
    -   `exit`: Terminates the shell.
    -   `cd [directory]`: Changes the current working directory. This *must* be a built-in because a child process cannot change its parent's directory.

---

### Tier 2: Advanced Features (Stretch Goals)

If Tier 1 is complete, attempt ONE of these to demonstrate deeper understanding.

-   [ ] **I/O Redirection (`>` and `<`):** Implement output and input redirection using `open()` and `dup2()` to manipulate file descriptors before calling `exec()`.
-   [ ] **Pipes (`|`):** Implement inter-process communication to pipe the output of one command to the input of another. This requires using `pipe()`, `fork()`ing two children, and coordinating them with `dup2()`.

### Tier 3: Professional Polish

These are not core features but demonstrate robust programming practices.

-   [ ] **Error Handling:** Check the return value of every system call (`fork`, `malloc`, `exec`, etc.) and use `perror()` to print meaningful error messages.
-   [ ] **Signal Handling:** Handle signals like `Ctrl-C` gracefully.
