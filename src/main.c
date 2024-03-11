#include "rust_lib.h"

#ifdef PC_TEST
#include <stdio.h>
#include <stdlib.h>
#endif

void panic_c_wrapper(const char *file, const uint32_t line) {
    (void)file;
    (void)line;

    // Do panic with file and line
#ifdef PC_TEST
    printf("Panic @ %s %u\n", file, line);
    exit(0);
#endif
}

uint8_t fake_heap[8096];

uint8_t* alloc_c_wrapper(size_t size, size_t align) {
    (void)size;
    (void)align;

    // Allocate size bytes aligned to align bytes
    // Return pointer
    return fake_heap;
}

void free_c_wrapper(uint8_t *ptr) {
    (void)ptr;

    // Free allocated ptr
}

// C version of rust_function for comparison
extern size_t c_function(size_t left, size_t right);
__attribute__((__noinline__))
size_t c_function(size_t left, size_t right)
{
    return (left * left) + (right * right);
}

// Dummy functions to keep linker happy
extern void __aeabi_unwind_cpp_pr0(void);
void __aeabi_unwind_cpp_pr0(void) {}
extern void rust_eh_personality(void);
void rust_eh_personality(void) {}

int main(int argc, char ** argv) {
    (void)argc;
    (void)argv;

    // c_function is identical to rust_function
    // Implemented as a comparison
    volatile size_t i = c_function(10,5);
    (void)i;

    // Basic function that passes and returns values
    size_t a = rust_function(10,5);
#if PC_TEST
    printf("Calling rust_function(10,5) = %lu\n", a);
#else
    (void)a;
#endif

    // Pass C pointer to Rust function
    uint8_t data[] = {1,2,3,4};
    uint8_t crc = rust_crc(data, sizeof(data)/sizeof(data[0]));
#if PC_TEST
    printf("Calling rust_crc({1,2,3,4}) = %u\n", crc);
#else
    (void)crc;
#endif

    // Function that panics and redirects back to panic_c_wrapper()
    rust_function_that_panics();
    return 0;
}

#ifndef PC_TEST
void _start(void) {
    main(0,0);
}
#endif
