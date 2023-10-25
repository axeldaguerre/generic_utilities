#include <iostream>
#include <stdint.h>
#include <iostream>
#include <cstring>
#include <Windows.h>

#define MAX_PATH_APP 260
#define internal static 

#define Kilobytes(Value) ((Value)*1024LL)
#define Megabytes(Value) (Kilobytes(Value)*1024LL)
#define Gigabytes(Value) (Megabytes(Value)*1024LL)
#define Terabytes(Value) (Gigabytes(Value)*1024LL)

#define ArrayCount(Array) (sizeof(Array)/sizeof(Array[0]))
#define Assert(Expression) if(!(Expression)) {*(int *)0 = 0;}

typedef double f64;

typedef uint8_t u8;

typedef int16_t s16;
typedef uint16_t u16;
typedef int8_t s8;
typedef uint64_t u64;
typedef int64_t s64;
typedef uint32_t u32;
typedef uint32_t b32;
typedef int32_t s32;

struct buffer
{
    void *Data;
    size_t Count;
};

struct app_state
{
    void *DisplayBuffer;
};

typedef struct thread_context
{
    int Placeholder;
} thread_context;

typedef struct debug_read_file_result
{
    u32 ContentsSize;
    void *Contents;
} debug_read_file_result;

inline u32 safe_truncate_u64(u64 Value)
{
    Assert(Value <= 0xFFFFFFFF);
    u32 Result = (u32)Value;
    return Result;
}

#include "string.h"
#include"win32_file.cpp"

char* win32_wchar_to_char(WCHAR *wideStr) {
    int requiredSize = WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, nullptr, 0, NULL, NULL);
    if (requiredSize == 0) {
        // Handle the error here
        return nullptr;
    }

    char* charStr = new char[requiredSize];
    WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, charStr, requiredSize, NULL, NULL);

    return charStr;
}

WCHAR* win32_char_to_wchar(const char* charStr) {
    int requiredSize = MultiByteToWideChar(CP_UTF8, 0, charStr, -1, nullptr, 0);
    if (requiredSize == 0) {
        // Handle the error here
        return nullptr;
    }

    WCHAR* wideStr = new WCHAR[requiredSize];
    MultiByteToWideChar(CP_UTF8, 0, charStr, -1, wideStr, requiredSize);

    return wideStr;
}
