# Exercise 1 — Pointer Arithmetic on Raw Memory

## Goal 

Practice precise pointer math, alignment, and safe traversal without array indexing.

## Task

Implement three functions operating on a raw byte buffer.

### Function 1

Write a function that returns a pointer to the first occurrence of byte `needle` in [buf, buf+len), or NULL if not found. 

```
const uint8_t* memscan8(const void* buf, size_t len, uint8_t needle);
```

Use only pointer arithmetic (no [] indexing).
If you are unfamiliar with what uint8_t means, please check [https://sourceware.org/glibc/manual/latest/html_mono/libc.html](https://sourceware.org/glibc/manual/latest/html_mono/libc.html). These types of data are often used in embedded OS.

### Function 2

Write a function that reverses a buffer in-place. Operate via two moving pointers; no indexing.

```
void memrev(void* buf, size_t len);
```

### Function 3

Write a function that reads an aligned 32-bit little-endian unsigned integer from memory at location `buf + offset`.
Little-endian is a byte-ordering scheme in computer architecture where the least significant byte (LSB) of a multi-byte data value, such as an integer, is stored at the lowest memory address. 

Return true and write to `*out` if success; false if out-of-bounds or misaligned.

What “alignment” means:
	* Every type in C/C++ has an alignment requirement, which is the number of bytes at which objects of that type must be stored in memory.
	* On most architectures, this means the address of an object of that type must be a multiple of its alignment.
	*	`alignof(T)` (or `_Alignof(T)` in pure C11) gives you this alignment requirement at compile time as a constant expression.

You can therefore check the alignment of an address by checking if: `(uintptr_t)(buf+offset) % alignof(uint32_t) == 0`.

```
bool read_u32_le_aligned(const void* buf, size_t len, size_t offset, uint32_t* out);
```
To use the `bool` data type in C you must include `#include <stdbool.h>`

## Constraints

* Use only pointer increments/decrements when traversing the buffer; no [].
* Avoid strict-aliasing violations. In C, the compiler is allowed to assume that two pointers of different types don’t point to the same memory (they don’t “alias”). This assumption helps the compiler optimize aggressively. Treat buf as const uint8_t* for traversal.
* Don’t read past len, i.e., check the buffer size.

## Tests
 
* `memscan8("hello",5,'l')` ⇒ address of first l.
* `memrev on {0,1,2,3,4}` ⇒ {4,3,2,1,0}.
* `read_u32_le_aligned` on a 16-byte buffer; test aligned and misaligned offsets.