#include <sys/types.h>
#include <errno.h>
#include <stdint.h>

extern char _end;    // Provided by the linker script: end of the bss section.
extern char _estack; // Start of the stack (end of RAM).

static char* current_heap_end = &_end;

void* _sbrk(ptrdiff_t incr) {
    char* prev_heap_end = current_heap_end;
    char* new_heap_end = current_heap_end + incr;

    // Use a register variable to get the value of the stack pointer.
    register char* stack_ptr asm ("sp");

    // Check if the new heap end would collide with the current stack pointer.
    if (new_heap_end > stack_ptr) {
        // If they collide, set errno to ENOMEM and return (void*)-1.
        errno = ENOMEM;
        return (void*)-1;
    }

    // Check if the new heap end would exceed _estack (bottom of the stack).
    if (new_heap_end >= &_estack) {
        // If there's no room for stack growth, set errno to ENOMEM and return (void*)-1.
        errno = ENOMEM;
        return (void*)-1;
    }

    // Update the heap end marker to the new value.
    current_heap_end = new_heap_end;

    // Return the previous heap end for allocation.
    return (void*)prev_heap_end;
}