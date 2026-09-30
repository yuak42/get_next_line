# get_next_line

## 📖 About

**get_next_line** is a project from the 42 School curriculum. The goal of the project is to implement a function that reads and returns one line at a time from a file descriptor.

The main challenge is that a single `read()` call does not necessarily correspond to a complete line. The function must therefore preserve unread data between calls and continue reading from where it previously stopped.

This project provides practical experience with file descriptors, static variables, dynamic memory management, and low-level file I/O in C.

## ⚙️ Function Prototype

```c
char *get_next_line(int fd);
```

The function returns:

- The next line read from the file descriptor.
- `NULL` when there is nothing left to read.
- `NULL` if an error occurs.

A returned line includes the terminating newline character (`\n`) when one is present.

## 🧠 How It Works

`get_next_line` reads data from a file descriptor using a configurable buffer size.

```c
read(fd, buffer, BUFFER_SIZE);
```

Since `BUFFER_SIZE` can be smaller or larger than the length of a line, the function may need to perform multiple `read()` calls before finding a complete line.

For example, consider the following file:

```text
Hello World
42 School
```

With:

```text
BUFFER_SIZE = 4
```

the file may be read in chunks similar to:

```text
"Hell"
"o Wo"
"rld\n"
"42 S"
"choo"
"l\n"
```

The function combines these chunks until it encounters a newline, returns the complete line, and preserves the remaining data for the next call.

### Static Storage

A static variable is used to preserve unread data between function calls.

Conceptually:

```text
read()
   ↓
[ accumulated data ]
   ↓
find '\n'
   ↓
┌──────────────────┐
│                  │
▼                  ▼
return line     save leftover
                   │
                   ▼
              next function call
```

This allows consecutive calls to continue reading from the same file descriptor without losing previously read data.

## 📦 BUFFER_SIZE

The buffer size can be specified during compilation:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 *.c
```

For example:

```bash
-D BUFFER_SIZE=1
-D BUFFER_SIZE=42
-D BUFFER_SIZE=1024
```

A correct implementation should work with different valid `BUFFER_SIZE` values.

## ⭐ Bonus

The bonus part extends `get_next_line` to support multiple file descriptors at the same time.

For example:

```c
char *line1;
char *line2;

line1 = get_next_line(fd1);
line2 = get_next_line(fd2);
line1 = get_next_line(fd1);
```

The function must preserve the reading state of each file descriptor independently.

This is typically achieved by maintaining separate static storage for each file descriptor.

## 🚀 Getting Started

### Prerequisites

You will need:

- A C compiler such as `cc` or `gcc`
- A Unix-like environment providing the `read()` system call

### Compilation

Clone the repository:

```bash
git clone <repository-url>
cd get_next_line
```

Since this project implements a function rather than a standalone executable, you can compile it together with a test program.

Example:

```bash
cc -Wall -Wextra -Werror \
    -D BUFFER_SIZE=42 \
    get_next_line.c \
    get_next_line_utils.c \
    main.c \
    -o gnl_test
```

Then run:

```bash
./gnl_test
```

## 💻 Example Usage

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("example.txt", O_RDONLY);
    if (fd == -1)
        return (1);

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return (0);
}
```

## 🧪 Concepts Practiced

This project focuses on several important C and system programming concepts:

- File descriptors
- The `read()` system call
- Static variables
- Dynamic memory allocation
- Memory management
- String manipulation
- Buffer management
- EOF and error handling
- Maintaining state between function calls

## 🛠️ Built With

- C
- Unix system calls
- CC

## 🎓 42 Project

This project was developed as part of the curriculum at **42 School**.
