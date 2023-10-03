#include <Windows.h>
#include <iostream>
#include <cstring>
#include "console_name.h"

static b32 GlobalRunning;
#define MAX_PATH_APP 260

b32 IsFolderEmpty(char *FolderPath) {
    b32 Result = false;

    char FolderPathWithStar[MAX_PATH_APP];
    sprintf(FolderPathWithStar, "%s\\*", FolderPath);

    WIN32_FIND_DATA FolderData;
    HANDLE FileHandle = FindFirstFile(FolderPath, &FolderData);

    if (FileHandle) 
    {
        if (!(FolderData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) 
        {
            printf("%s wasn't a directory\n", FolderPath);
            return Result;
        }
        
        WIN32_FIND_DATA FileData;
        HANDLE AnyFileHandle;
        AnyFileHandle = FindFirstFileA(FolderPathWithStar, &FileData);
        while(FindNextFileA(AnyFileHandle, &FileData))
        {
        }

        FindClose(AnyFileHandle);    
        
        // NOTE: There is always a '.' and '..' file
        if(FileData.cFileName[0] == '.')
        {
            Result = true;
        }

    } 
    else 
    {
        Result = true; 
    }

    FindClose(FileHandle);
    return Result;
}

inline void str_concat(size_t SourceACount, char *SourceA,
                       size_t SourceBCount, char *SourceB,
                       size_t DestCount, char *Dest)
{
    
    for(int Index = 0;
        Index < SourceACount;
        ++Index)
    {
        *Dest++ = *SourceA++;
    }

    for(int Index = 0;
        Index < SourceBCount;
        ++Index)
    {
        *Dest++ = *SourceB++;
    }

    *Dest = 0;
}

inline int str_len(char *String)
{
    int Count = 0;
    while(*String++)
    {
        ++Count;
    }
    return(Count);
}

int main(int ArgCount, char **Args) {
    GlobalRunning = true;

    if(ArgCount < 2)
    {
        printf("[folder path]");
    }
    else
    {
        char *FolderPlatforms = Args[1];
        WIN32_FIND_DATA FileData = {};
            
        char FolderPlatformsWithStart[MAX_PATH_APP];
        str_concat(str_len(FolderPlatforms), FolderPlatforms,
            str_len("\\*"), "\\*",
            str_len(FolderPlatformsWithStart), FolderPlatformsWithStart);
        HANDLE FileHandle = FindFirstFileA(FolderPlatformsWithStart, &FileData);

        if(FileHandle)
        {
            while(GlobalRunning)
            {        
                while(FindNextFileA(FileHandle, &FileData))
                {
                    
                    char GamesFolder[MAX_PATH_APP];
                    sprintf(GamesFolder, "%s\\%s", FolderPlatforms, FileData.cFileName);

                    if(strstr(GamesFolder, "\\..")) continue;                    

                    char GamesFolderWithStar[MAX_PATH_APP];
                    sprintf(GamesFolderWithStar, "%s\\%s\\*", FolderPlatforms, FileData.cFileName);
                    
                    HANDLE GamesFolderHandle = FindFirstFileA(GamesFolderWithStar, &FileData);
                    
                    if(GamesFolderHandle)
                    {
                        while(FindNextFileA(GamesFolderHandle, &FileData))
                        {                               
                            char RomPath[MAX_PATH_APP];
                            sprintf(RomPath, "%s\\%s", GamesFolder, FileData.cFileName);

                             wchar_t RomPathW[MAX_PATH_APP];
                            MultiByteToWideChar(CP_UTF8, 0, RomPath, -1, RomPathW, MAX_PATH_APP);

                            if(strstr(RomPath, "\\..")) continue;

                            if (IsFolderEmpty(RomPath)) 
                            {
                                
                                if(SetFileAttributesW(RomPathW, GetFileAttributesW(RomPathW) & ~FILE_ATTRIBUTE_READONLY) == 0)
                                {
                                    printf("ERROR: couln't unset READ_ONLY\n");
                                }
                                else
                                {
                                    printf("READ_ONLY Set\n");
                                }
                                

                                if(RemoveDirectoryA(RomPath))
                                {
                                    printf("Deletion succeed: %s\n", RomPath);
                                }
                                else
                                {
                                    DWORD ErrorCode = GetLastError();
                                    if(ErrorCode == ERROR_ACCESS_DENIED)
                                    {
                                        printf("Deletion failed: %s -> %d\n", RomPath, ErrorCode);
                                    }
                                }
                            } 
                            else 
                            {
                                
                            }
                            
                        }
                    }
                }
                GlobalRunning=false;
               
            }
        }
        else
        {
            printf("no folder find inside the folder specified\n");
            GlobalRunning = false;
        }
    }    

    return 0;
}