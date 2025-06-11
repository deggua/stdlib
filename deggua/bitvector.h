#pragma once

#include <deggua/types.h>

typedef struct {
    usize length;
    usize capacity;
    u64*  u64s;
} BitVector;

bool BitVector_New(BitVector* self, usize init_capacity_bits);
bool BitVector_New_Copy(BitVector* self, const BitVector* src);
bool BitVector_New_FromBits(BitVector* self, const u64* bits, usize nbits);
bool BitVector_New_FromSlice(BitVector* self, const BitVector* src, usize index_start, usize index_end);

void BitVector_Delete(BitVector* self);

bool BitVector_Reserve(BitVector* self, usize capacity_bits);
bool BitVector_Shrink(BitVector* self);

bool BitVector_Append_Bit(BitVector* self, u64 bit);
bool BitVector_Append_Bits(BitVector* self, const u64* bits, usize nbits);
bool BitVector_Append_Zeros(BitVector* self, usize nzeros);
bool BitVector_Append_Ones(BitVector* self, usize nones);
bool BitVector_Append_BitVector(BitVector* self, const BitVector* src);
bool BitVector_Append_Slice(BitVector* self, const BitVector* src, usize index_start, usize index_end);

bool BitVector_Prepend_Bit(BitVector* self, u64 bit);
bool BitVector_Prepend_Bits(BitVector* self, const u64* bits, usize nbits);
bool BitVector_Prepend_Zeros(BitVector* self, usize nzeros);
bool BitVector_Prepend_Ones(BitVector* self, usize nones);
bool BitVector_Prepend_BitVector(BitVector* self, const BitVector* src);
bool BitVector_Prepend_Slice(BitVector* self, const BitVector* src, usize index_start, usize index_end);

bool BitVector_Insert_Bit(BitVector* self, usize index, u64 bit);
bool BitVector_Insert_Bits(BitVector* self, usize index, const u64* bits, usize nbits);
bool BitVector_Insert_Zeros(BitVector* self, usize index, usize nzeros);
bool BitVector_Insert_Ones(BitVector* self, usize index, usize nones);
bool BitVector_Insert_BitVector(BitVector* self, usize index, const BitVector* src);
bool BitVector_Insert_Slice(BitVector* self, usize index, const BitVector* src, usize index_start, usize index_end);

bool BitVector_Remove_Range(BitVector* self, usize index_start, usize index_end);
bool BitVector_Remove_All(BitVector* self);

void BitVector_Set_Bit(BitVector* self, usize index);
void BitVector_Set_Range(BitVector* self, usize index_start, usize index_end);
void BitVector_Set_All(BitVector* self);

void BitVector_Clear_Bit(BitVector* self, usize index);
void BitVector_Clear_Range(BitVector* self, usize index_start, usize index_end);
void BitVector_Clear_All(BitVector* self);

bool BitVector_IsBitSet(const BitVector* self, usize index);
bool BitVector_IsRangeSet(const BitVector* self, usize index_start, usize index_end);
bool BitVector_IsAllSet(const BitVector* self);

bool BitVector_IsBitClear(const BitVector* self, usize index);
bool BitVector_IsRangeClear(const BitVector* self, usize index_start, usize index_end);
bool BitVector_IsAllClear(const BitVector* self);

void BitVector_AND(BitVector* self, const BitVector* other);
void BitVector_NAND(BitVector* self, const BitVector* other);
void BitVector_OR(BitVector* self, const BitVector* other);
void BitVector_NOR(BitVector* self, const BitVector* other);
void BitVector_XOR(BitVector* self, const BitVector* other);
void BitVector_XNOR(BitVector* self, const BitVector* other);
void BitVector_NOT(BitVector* self);

void BitVector_ShiftLeft(BitVector* self, usize shift_amt);
void BitVector_ShiftRight(BitVector* self, usize shift_amt);
void BitVector_RotateRight(BitVector* self, usize rotate_amt);
void BitVector_RotateLeft(BitVector* self, usize rotate_amt);
void BitVector_Reverse(BitVector* self);

usize BitVector_CountLeadingZeros(const BitVector* self);
usize BitVector_CountTrailingZeros(const BitVector* self);
usize BitVector_FindFirstSet(const BitVector* self);
usize BitVector_FindLastSet(const BitVector* self);
usize BitVector_Popcount(const BitVector* self);
usize BitVector_Parity(const BitVector* self);

usize BitVector_Length(const BitVector* self);
