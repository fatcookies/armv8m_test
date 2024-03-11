use core::alloc::GlobalAlloc;
use core::alloc::Layout;

extern "C" {
    fn alloc_c_wrapper(size: usize, align: usize) -> *mut u8;
    fn free_c_wrapper(ptr: *mut u8);
}

#[global_allocator]
static ALLOCATOR: CustomAllocator = CustomAllocator;
struct CustomAllocator;
unsafe impl GlobalAlloc for CustomAllocator {
    unsafe fn alloc(&self, layout: Layout) -> *mut u8 {
        let size = layout.size();
        let align = layout.align();
        // Delegate to C function
        alloc_c_wrapper(size, align)
    }
    unsafe fn dealloc(&self, ptr: *mut u8, _: Layout) {
        // Delegate to C function
        free_c_wrapper(ptr);
    }
}
