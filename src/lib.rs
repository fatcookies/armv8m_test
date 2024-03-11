#![no_std]

use core::slice;
use crc::{Crc, CRC_8_CDMA2000};

mod panic;
mod alloc;

fn do_something(left: usize, right: usize) -> usize {
    (left * left) + (right * right)
}

#[no_mangle]
pub extern "C" fn rust_function(left: usize, right: usize) -> usize {
    do_something(left, right)
}

#[no_mangle]
pub extern "C" fn rust_function_that_panics() {
    panic!("this is a terrible mistake!");
}

// Example of exposing Rust crate function to C
pub const CRC8: Crc<u8> = Crc::<u8>::new(&CRC_8_CDMA2000);
#[no_mangle]
pub extern "C" fn rust_crc(_data: *const u8, _len: usize) -> u8 {
    CRC8.checksum(unsafe {slice::from_raw_parts(_data, _len) })
}
