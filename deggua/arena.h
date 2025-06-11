#pragma once

#include <deggua/types.h>

typedef struct {
    char* base;     // base of arena allocation
    char* head;     // next free position
    usize virt_size; // virtual space reserved
    usize phys_size; // physical space committed
} MemoryArena;

typedef struct {
    char* head;
} MemoryArenaCheckpoint;

// WARNING: breaking control flow (return, break, goto) will not work correctly with this macro
#define MemoryArena_Scope(_arena) for (MemoryArenaCheckpoint state = MemoryArena_Checkpoint((_arena)), loop_terminator_ = {(void*)~(uintptr_t)NULL}; loop_terminator_.head; MemoryArena_Restore((_arena), &state), loop_terminator_.head = NULL)

/* --- Arena Management --- */

bool MemoryArena_New(MemoryArena* arena, usize max_size); // Initializes a virtually mapped memory arena of `max_size` bytes (rounded up to the page size)
void MemoryArena_Delete(MemoryArena* arena);                  // Destroys a memory arena, releasing all the memory back to the OS
void MemoryArena_Reset(MemoryArena* arena);                   // Resets the arena, does not release the memory to the OS (very cheap)
bool MemoryArena_Release(MemoryArena* arena);                 // Resets the arena and releases the physical memory back to the OS
bool MemoryArena_Shrink(MemoryArena* arena);                  // Releases currently unused physical memory back to the OS

/* --- Uninitialized Arena Allocation --- */

void* MemoryArena_UAlignedAlloc(MemoryArena* arena, usize alignment_pow2, usize size); // Allocate aligned memory from the arena (uninitialized)
void* MemoryArena_UAlloc(MemoryArena* arena, usize size);                               // Allocate memory with default platform alignment (typically 16 byte aligned) (uninitialized)
void* MemoryArena_UPackedAlloc(MemoryArena* arena, usize size);                         // Allocate memory with no alignment requirement (uninitialized)

/* --- Zero Filled Arena Allocation --- */

void* MemoryArena_ZAlignedAlloc(MemoryArena* arena, usize alignment_pow2, usize size); // Allocate aligned memory from the arena (zero filled)
void* MemoryArena_ZAlloc(MemoryArena* arena, usize size);                               // Allocate memory with default platform alignment (typically 16 byte aligned) (zero filled)
void* MemoryArena_ZPackedAlloc(MemoryArena* arena, usize size);                         // Allocate memory with no alignment requirement (zero filled)

/* --- Scoped Arena Allocations --- */

MemoryArenaCheckpoint MemoryArena_Checkpoint(MemoryArena* arena);                   // Begin a local scope in an arena (begin temporary free-able sub-arena)
void MemoryArena_Restore(MemoryArena* arena, MemoryArenaCheckpoint* restore_from); // End a local scope in an arena (free temporary sub-arena)
