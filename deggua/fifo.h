#pragma once

#include <deggua/types.h>

typedef struct {
    usize size;
    usize capacity;
    usize head;
    u8*   base;
} Fifo;

bool Fifo_New(Fifo* self, usize min_size);
void Fifo_Delete(Fifo* self);

bool Fifo_Resize(Fifo* self, usize min_size);
void Fifo_Clear(Fifo* self);

usize Fifo_Write(Fifo* self, const void* data, usize len);
usize Fifo_Read(Fifo* self, void* data, usize len);

bool Fifo_WriteAll(Fifo* self, const void* data, usize len);
bool Fifo_ReadAll(Fifo* self, void* data, usize len);

void* Fifo_BeginWrite(Fifo* self, usize* maxlen);
void  Fifo_CompleteWrite(Fifo* self, usize write_len);

const void* Fifo_BeginRead(Fifo* self, usize* maxlen);
void        Fifo_CompleteRead(Fifo* self, usize read_len);

usize Fifo_BytesUsed(const Fifo* self);
usize Fifo_BytesFree(const Fifo* self);
