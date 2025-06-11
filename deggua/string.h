#pragma once

#include <deggua/types.h>

typedef struct {
    usize      len;
    const char at[];
} String;

typedef struct {
    usize       len;
    const char* at;
} StringView;

#define String(x) ((String*)&((struct {usize len; const char buf[sizeof(x)];}){.len = sizeof(x) - 1, .buf = x}))

bool String_New(String* self, usize len);
bool String_Copy(String* self);
bool String_Cast_CStr(String* self, const char* cstr);
bool String_Cast_Bytes(String* self, const u8* data, usize len);
bool String_Cast_StringView(String* self, const StringView* sv);
void String_Delete(String* self);

const char* String_CStr(String* self);

bool String_Append(String* self, const String* other);
bool String_Prepend(String* self, const String* other);

usize String_Find(const String* self, const String* substr);
usize String_FindFrom(const String* self, const String* substr, usize index);
usize String_ReverseFind(const String* self, const String* substr);
usize String_ReverseFindFrom(const String* self, const String* substr, usize index);

bool String_BeginsWith(const String* self, const String* substr);
bool String_EndsWith(const String* self, const String* substr);
bool String_Contains(const String* self, const String* substr);
isize String_Compare(const String* self, const String* other);
bool String_Equal(const String* self, const String* other);

#define STR_FMT    "%.*s"
#define STR_ARG(x) ((x)->len), ((x)->at)
