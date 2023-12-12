#include <string>
#include "driver.hpp"
#include "defs.h"
#include "spoofer.h"

#define FNAMEPOOL_OFFSET 0x118FF480

static std::string GetNameFromIndex(int key)
{
    SPOOF_FUNC;
    uint32_t ChunkOffset = (uint32_t)((int)(key) >> 16);
    uint16_t NameOffset = (uint16_t)key;
    uint64_t NamePoolChunk = driver_rq->read<uint64_t>(driver_rq->image_base + FNAMEPOOL_OFFSET + (8 * ChunkOffset) + 16) + (unsigned int)(2 * NameOffset);
    uint16_t nameEntry = driver_rq->read<uint16_t>(NamePoolChunk);
    int nameLength = nameEntry >> 6;
    char buff[1024] = {};

    char* v2 = buff; // rdi
    int v4 = nameLength; // ebx
    int v5; // edx
    int v6; // ecx
    int v7; // ecx
    __int16 v8; // ax
    __int16 v9; // ax

    v6 = 0;
    v7 = 42;
    if (v4)
    {
        driver_rq->read_physical(PVOID(NamePoolChunk + 2), (PVOID)buff, 2 * nameLength);
        do
        {
            v8 = v6++ | v7;
            v9 = v8;
            v7 = 2 * v8;
            *v2++ ^= ~v8;
        } while (v6 < v4);
        buff[nameLength] = '\0';
        return std::string(buff);
    }
    return std::string("");
}

static std::string GetNameFromFName(int key)
{
    SPOOF_FUNC;
    uint32_t ChunkOffset = (uint32_t)((int)(key) >> 16);
    uint16_t NameOffset = (uint16_t)key;

    uint64_t NamePoolChunk = driver_rq->read<uint64_t>(driver_rq->image_base + FNAMEPOOL_OFFSET + (8 * ChunkOffset) + 16) + (unsigned int)(2 * NameOffset); //((ChunkOffset + 2) * 8) ERROR_NAME_SIZE_EXCEEDED
    if (driver_rq->read<uint16_t>(NamePoolChunk) < 64)
    {
        auto a1 = driver_rq->read<DWORD>(NamePoolChunk + 2);
        return GetNameFromIndex(a1);
    }
    else
    {
        return GetNameFromIndex(key);
    }
}
