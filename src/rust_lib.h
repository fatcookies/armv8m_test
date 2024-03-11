#ifndef __RUST_LIB_H__
#define __RUST_LIB_H__

#include <stddef.h>
#include <stdint.h>

extern uint8_t* alloc_c_wrapper(size_t size, size_t align);
extern void     free_c_wrapper(uint8_t *ptr);

extern void panic_c_wrapper(const char *file, const uint32_t line);

extern size_t rust_function(size_t left, size_t right);
extern void rust_function_that_panics(void);
extern uint8_t rust_crc(const uint8_t *data, const size_t len);

#endif 
