#pragma once

#include <deggua/types.h>

typedef struct {
    // registers
    // stack
    // etc.
} Fiber;

bool Fiber_New(Fiber* self, usize stack_size);
bool Fiber_Delete(Fiber* self);

void  Fiber_Start(Fiber* self, void* (*entry_point)(void* arg));
void* Fiber_Join(Fiber* self);

void Fiber_Sleep(usize time_ms);
void Fiber_Yield(void);
int  Fiber_WaitUntil(int fd, int ev_mask);

#define Fiber_YieldUntil(cond) do { while (!(cond)) Fiber_Yield(); } while (0)

// Fiber local storage?
