#include<stdint.h>

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


