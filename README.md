# GetNextLine

## Description

`get_next_line` is a function that reads from a file descriptor and returns one line at a time.

The objective of the project is to gain a deeper understanding of:

* Static variables
* Dynamic memory allocation
* File descriptors
* Reading from files using `read()`
* String manipulation
* Memory management and leak prevention

The function prototype is:

```c
char    *get_next_line(int fd);
```

Each call returns:

* The next line from the file, including the newline character when present
* `NULL` when the end of the file is reached or when an error occurs

The function must remember unread data between calls, allowing it to continue reading exactly where the previous call stopped.

---

## Instructions

### Compilation

Compile the project with:

### Test Program

The following `main.c` file was used during development and testing:

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

This test program opens a file provided as a command-line argument, repeatedly calls `get_next_line()`, prints each returned line, frees the allocated memory, and closes the file descriptor when finished.

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
main.c get_next_line.c get_next_line_utils.c
```

The project can also be compiled with different buffer sizes:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 \
main.c get_next_line.c get_next_line_utils.c
```

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=9999 \
main.c get_next_line.c get_next_line_utils.c
```

---

## Testing

### Create Test Files

```bash
touch empty.txt

printf "hello\nworld\n" > normal.txt

printf "hello" > no_newline.txt

printf "abc\nxyz" > last_no_newline.txt

printf "\n\n\n" > only_newlines.txt

printf "\nabc\n\ndef\n\n" > evil.txt

printf "A\nBC\nDEF\nGHIJ\nKLMNO\n" > buffer1_test.txt

python3 -c "print('a' * 10000)" > long_line.txt
```

### Standard Execution Tests

```bash
./a.out empty.txt
./a.out normal.txt
./a.out no_newline.txt
./a.out last_no_newline.txt
./a.out only_newlines.txt
./a.out evil.txt
./a.out long_line.txt
```

### BUFFER_SIZE = 1

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 \
main.c get_next_line.c get_next_line_utils.c

./a.out buffer1_test.txt
./a.out evil.txt
./a.out long_line.txt
```

### BUFFER_SIZE = 42

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
main.c get_next_line.c get_next_line_utils.c

./a.out normal.txt
./a.out no_newline.txt
./a.out last_no_newline.txt
./a.out only_newlines.txt
```

### BUFFER_SIZE = 9999

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=9999 \
main.c get_next_line.c get_next_line_utils.c

./a.out normal.txt
./a.out long_line.txt
```

### Memory Leak Checks

```bash
valgrind --leak-check=full ./a.out empty.txt
valgrind --leak-check=full ./a.out normal.txt
valgrind --leak-check=full ./a.out no_newline.txt
valgrind --leak-check=full ./a.out last_no_newline.txt
valgrind --leak-check=full ./a.out only_newlines.txt
valgrind --leak-check=full ./a.out evil.txt
valgrind --leak-check=full ./a.out long_line.txt
```

Expected output:

```txt
All heap blocks were freed -- no leaks are possible
ERROR SUMMARY: 0 errors
```

### Norminette

```bash
norminette get_next_line.c get_next_line_utils.c get_next_line.h
```

---

## Algorithm

### Overview

The implementation uses a static string called `stash`.

The stash stores unread characters between function calls, allowing the function to continue reading from the exact position where the previous call stopped.

The algorithm is divided into three stages.

### 1. Read and Append

`read_and_append()` repeatedly reads data from the file descriptor into a temporary buffer.

The contents of the buffer are appended to the stash until:

* A newline character is found
* End-of-file is reached

Example:

```txt
File:
Hello
World
```

After reading:

```txt
stash = "Hello\nWorld\n"
```

The temporary buffer is then freed.

---

### 2. Extract Line

`extract_line()` allocates memory for the next line and copies characters from the beginning of the stash.

Example:

```txt
stash = "Hello\nWorld\n"
```

Returns:

```txt
line = "Hello\n"
```

The extracted line is returned to the caller.

---

### 3. Update Stash

`update_stash()` removes the extracted line from the stash and keeps only the remaining unread characters.

Example:

```txt
Before:
"Hello\nWorld\n"
```

```txt
After:
"World\n"
```

The old stash is freed and replaced with a newly allocated string containing the remaining data.

This allows the next call to `get_next_line()` to continue exactly where the previous call stopped.

---

## Memory Management

Dynamic memory allocation is used throughout the project.

To avoid memory leaks:

* Temporary buffers are freed after reading
* Previous stash allocations are freed after concatenation
* Old stash memory is freed when updating the stash
* Error paths free allocated memory before returning

Memory correctness was verified using Valgrind.

Example result:

```txt
All heap blocks were freed -- no leaks are possible
ERROR SUMMARY: 0 errors
```

---

## Project Structure

### get_next_line.c

Contains:

* `get_next_line`
* `read_and_append`
* `join_and_free`
* `extract_line`
* `update_stash`

### get_next_line_utils.c

Contains:

* `ft_strlen`
* `ft_strchr`
* `ft_strjoin`
* `free_stash_buffer`

### get_next_line.h

Contains:

* Function prototypes
* Required includes
* `BUFFER_SIZE` definition

---

## Resources

### Documentation

Linux Manual Pages:

* https://man7.org/linux/man-pages/man2/read.2.html
* https://man7.org/linux/man-pages/man3/malloc.3.html
* https://man7.org/linux/man-pages/man2/open.2.html

Additional References:

* https://www.gnu.org/software/libc/manual/
* https://en.cppreference.com/

### AI Usage

ChatGPT was used as a supplementary learning tool during development.

AI assistance was primarily used for:

* Understanding the purpose and behaviour of static variables
* Clarifying memory allocation and memory freeing concepts
* discussing possible bugs
* Asking questions about the code to verify understanding

The implementation itself was written, modified, compiled, debugged, and tested manually. AI was used to support learning and verification rather than to generate the final solution.
