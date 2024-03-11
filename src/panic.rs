use core::panic::PanicInfo;
use cstr_core::CString;
use cty::c_char;

extern "C" {
    pub fn panic_c_wrapper(file: *const c_char, line: u32);
}

#[panic_handler]
fn panic(panic_info: &PanicInfo) -> ! {
    if let Some(location) = panic_info.location() {
        let file_str = CString::new(location.file()).unwrap();
        let line = location.line();

        unsafe {
            panic_c_wrapper(file_str.into_raw(), line);
        }
    }
    loop {}
}
