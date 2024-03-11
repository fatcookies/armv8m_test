# armv8m_test
Testing Rust integrated into a C project targetting ARMv8-M/ARMv8.1-M

Includes three rust functions which are exposed to C:
* rust_function
    * Very basic pure function

* rust_crc
    * Implements CRC8 from a Rust CRC crate.

* rust_function_that_panics
    * Panics to demonstrate allocator and panic handling

Provides hooks for panics and memory allocation.

## Requirements
* Rust (2021 edition)
* Arm GNU Toolchain
* gcc

# Build

For thumbv8m.main-none-eabihf compatible build:
```
./build.sh
```

To build for x86_64-unknown-linux-gnu and see printf of results:
```
./pcbuild.sh
```


