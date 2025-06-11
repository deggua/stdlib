#ifndef T
# error "Vector type `T` must be defined before `vector.h` is included"
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <deggua/macros.h>

#ifndef CONCAT2_
# define CONCAT2_(x, y) x ## _ ## y
#endif

#ifndef CONCAT2
# define CONCAT2(x, y) CONCAT2_(x, y)
#endif

#define Vector(T)                       CONCAT2(Vector, T)

#define Vector_New(T)                   CONCAT2(Vector_New, T)
#define Vector_New_Copy(T)              CONCAT2(Vector_New_Copy, T)
#define Vector_Delete(T)                CONCAT2(Vector_Delete, T)

#define Vector_Reserve(T)               CONCAT2(Vector_Reserve, T)
#define Vector_Resize(T)                CONCAT2(Vector_Resize, T)
#define Vector_FitToLength(T)           CONCAT2(Vector_FitToLength, T)
#define Vector_Clear(T)                 CONCAT2(Vector_Clear, T)

#define Vector_Append(T)                CONCAT2(Vector_Append, T)
#define Vector_AppendMany(T)            CONCAT2(Vector_AppendMany, T)
#define Vector_Insert(T)                CONCAT2(Vector_Insert, T)
#define Vector_InsertMany(T)            CONCAT2(Vector_InsertMany, T)

#define Vector_Remove(T)                CONCAT2(Vector_Remove, T)
#define Vector_Remove_Unordered(T)      CONCAT2(Vector_Remove_Unordered, T)
#define Vector_RemoveRange(T)           CONCAT2(Vector_RemoveRange, T)
#define Vector_RemoveRange_Unordered(T) CONCAT2(Vector_RemoveRange_Unordered, T)

#define Vector_PopRight(T)              CONCAT2(Vector_PopRight, T)
#define Vector_PopRightMany(T)          CONCAT2(Vector_PopRightMany, T)
#define Vector_PopLeft(T)               CONCAT2(Vector_PopLeft, T)
#define Vector_PopLeftMany(T)           CONCAT2(Vector_PopLeftMany, T)

typedef struct {
    size_t capacity;
    size_t len;
    T*     at;
} Vector(T);

SYM_WEAK
bool Vector_New(T)(Vector(T)* this, size_t init_capacity)
{
    init_capacity = max(1, init_capacity);

    T* alloc = malloc(init_capacity * sizeof(T));
    if (!alloc) return false;

    this->capacity = init_capacity;
    this->len      = 0;
    this->at       = alloc;

    return true;
}

SYM_WEAK
bool Vector_New_Copy(T)(Vector(T)* this, const Vector(T)* restrict src)
{
    T* alloc = malloc(src->capacity * sizeof(T));
    if (!alloc) return false;

    memcpy(alloc, src->at, src->capacity * sizeof(T));

    this->capacity = src->capacity;
    this->len      = src->len;
    this->at       = alloc;

    return true;
}

SYM_WEAK
void Vector_Delete(T)(Vector(T)* this)
{
    free(this->at);
}

#define Vector__ChangeCapacity(T) CONCAT2(Vector__ChangeCapacity, T)

SYM_WEAK
bool Vector__ChangeCapacity(T)(Vector(T)* this, size_t capacity)
{
    capacity = max(1, capacity);

    T* new_alloc = realloc(this->at, capacity * sizeof(T));
    if (!new_alloc) return false;

    this->at       = new_alloc;
    this->capacity = capacity;

    return true;
}

SYM_WEAK
bool Vector_Reserve(T)(Vector(T)* this, size_t capacity)
{
    if (capacity <= this->capacity) return true;

    if (!Vector__ChangeCapacity(T)(this, capacity)) return false;

    return true;
}

SYM_WEAK
bool Vector_Resize(T)(Vector(T)* this, size_t length)
{
    if (length == this->len) return true;

    if (this->capacity < length) {
        if (!Vector__ChangeCapacity(T)(this, length)) return false;
    }

    if (length > this->len) {
        memset(&this->at[this->len], 0x00, length - this->len);
    }

    this->len = length;

    return true;
}

SYM_WEAK
bool Vector_FitToLength(T)(Vector(T)* this)
{
    if (this->capacity == this->len) return true;

    if (!Vector__ChangeCapacity(T)(this, this->len)) return false;

    return true;
}

SYM_WEAK
bool Vector_Clear(T)(Vector(T)* this)
{
    this->len = 0;

    return true;
}

#define Vector__MaybeGrow(T) CONCAT2(Vector__MaybeGrow, T)

SYM_WEAK
bool Vector__MaybeGrow(T)(Vector(T)* this, size_t min_capacity)
{
    if (this->capacity >= min_capacity) return true;

    size_t new_capacity = max(min_capacity, this->capacity * 3 / 2);
    return Vector__ChangeCapacity(T)(this, new_capacity);
}

SYM_WEAK
bool Vector_AppendMany(T)(Vector(T)* this, const T* restrict elems, size_t count)
{
    if (!count) return true;
    if (!Vector__MaybeGrow(T)(this, this->len + count)) return false;

    memcpy(&this->at[this->len], elems, count * sizeof(T));

    this->len += count;

    return true;
}

SYM_WEAK
bool Vector_Append(T)(Vector(T)* this, const T* restrict elem)
{
    return Vector_AppendMany(T)(this, elem, 1);
}

SYM_WEAK
bool Vector_InsertMany(T)(Vector(T)* this, size_t index, const T* restrict elems, size_t count)
{
    if (!count) return true;
    if (!Vector__MaybeGrow(T)(this, this->len + count)) return false;

    memmove(&this->at[index + count], &this->at[index], count * sizeof(T));
    memcpy(&this->at[index], elems, count * sizeof(T));

    this->len += count;

    return true;
}

SYM_WEAK
bool Vector_Insert(T)(Vector(T)* this, size_t index, const T* restrict elem)
{
    return Vector_InsertMany(T)(this, index, elem, 1);
}

SYM_WEAK
bool Vector_RemoveRange(T)(Vector(T)* this, size_t index, size_t count)
{
    if (!count) return true;
    if (count == this->len) return Vector_Clear(T)(this);

    size_t nafter = this->len - index - count;
    memmove(&this->at[index], &this->at[index + count], nafter * sizeof(T));

    this->len -= count;

    return true;
}

SYM_WEAK
bool Vector_Remove(T)(Vector(T)* this, size_t index)
{
    return Vector_RemoveRange(T)(this, index, 1);
}

SYM_WEAK
bool Vector_RemoveRange_Unordered(T)(Vector(T)* this, size_t index, size_t count)
{
    if (!count) return true;
    if (count == this->len) return Vector_Clear(T)(this);

    size_t nrem = min(this->len - index - count, count);
    memcpy(&this->at[index], &this->at[this->len - nrem], nrem * sizeof(T));

    this->len -= count;

    return true;
}

SYM_WEAK
bool Vector_Remove_Unordered(T)(Vector(T)* this, size_t index)
{
    return Vector_RemoveRange_Unordered(T)(this, index, 1);
}

SYM_WEAK
bool Vector_PopRightMany(T)(Vector(T)* this, T* restrict elems, size_t count)
{
    for (size_t ii = 0; ii < count; ii++) {
        elems[count - 1 - ii] = this->at[this->len - count + ii];
    }

    this->len -= count;

    return true;
}

SYM_WEAK
bool Vector_PopRight(T)(Vector(T)* this, T* restrict elem)
{
    return Vector_PopRightMany(T)(this, elem, 1);
}

SYM_WEAK
bool Vector_PopLeftMany(T)(Vector(T)* this, T* restrict elems, size_t count)
{
    memcpy(elems, &this->at[0], count * sizeof(T));

    this->len -= 1;

    return true;
}

#undef Vector__ChangeCapacity
#undef Vector__MaybeGrow

#undef T
