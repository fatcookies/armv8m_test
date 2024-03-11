# This requires toolchain in path
CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld
OBJDUMP=arm-none-eabi-objdump

RUST_ARCH=thumbv8m.main-none-eabihf
CC_ARCH=armv8.1-m.main+fp

SRC=src/main.c
OBJ=target/main.o
RUSTLIB=libarmv8m_test.a
BIN=target/myapp.elf

# rustup target add thumbv8m.main-none-eabihf

cargo build --target $RUST_ARCH --release
$CC -mthumb -march=$CC_ARCH -mfloat-abi=hard -Os -Wall -Wextra -Werror -ffunction-sections -fdata-sections -fno-exceptions -c $SRC -o $OBJ
$LD --gc-sections $OBJ target/$RUST_ARCH/release/$RUSTLIB -o $BIN

arm-none-eabi-size -B $BIN
arm-none-eabi-objdump --disassemble=rust_function $BIN
arm-none-eabi-objdump --disassemble=c_function $BIN
