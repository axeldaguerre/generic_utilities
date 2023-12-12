#include"win32.cpp"
#include "shared.h"

int main(int ArgCount, char **Args) {
    if(ArgCount < 2)
    {
        printf("[folder path]");
    }
    else
    {
        char *FolderPath = Args[1];
        WIN32_FIND_DATA FileData = {};
            
        char FolderPathWithStar[MAX_PATH_APP];
        str_concat(str_len(FolderPath), FolderPath,
            str_len("\\*"), "\\*",
            str_len(FolderPathWithStar), FolderPathWithStar);
        HANDLE FileHandle = FindFirstFileA(FolderPathWithStar, &FileData);

        if(FileHandle)
        {
            while(FindNextFileA(FileHandle, &FileData))
            {                
                char NestedFolderName[MAX_PATH_APP];
                sprintf(NestedFolderName, "%s\\%s", FolderPath, FileData.cFileName);

                if(strstr(NestedFolderName, "\\..")) continue;

                char NestedFolderNameWithStar[MAX_PATH_APP];
                sprintf(NestedFolderNameWithStar, "%s\\%s\\*", FolderPath, FileData.cFileName);
                
                HANDLE NestedFolderHandle = FindFirstFileA(NestedFolderNameWithStar, &FileData);
                
                if(NestedFolderHandle)
                {
                    while(FindNextFileA(NestedFolderHandle, &FileData))
                    {                               
                        char FileName[MAX_PATH_APP];
                        sprintf(FileName, "%s\\%s", NestedFolderName, FileData.cFileName);
                        if(strstr(FileName, "\\..")) continue;

                        wchar_t RomPathW[MAX_PATH_APP];
                        MultiByteToWideChar(CP_UTF8, 0, FileName, -1, RomPathW, MAX_PATH_APP);

                        if (Win32IsFolderEmpty(FileName)) 
                        {
                            
                            if(SetFileAttributesW(RomPathW, GetFileAttributesW(RomPathW) & ~FILE_ATTRIBUTE_READONLY) == 0)
                            {
                                printf("ERROR: couln't unset READ_ONLY\n");
                            }
                            

                            if(RemoveDirectoryA(FileName))
                            {
                                printf("Deletion succeed: %s\n", FileName);
                            }
                            else
                            {
                                DWORD ErrorCode = GetLastError();
                                if(ErrorCode == ERROR_ACCESS_DENIED)
                                {
                                    printf("Deletion failed: %s -> %d\n", FileName, ErrorCode);
                                }
                            }
                        } 
                        else 
                        {
                            
                        }
                    }
                }
            }
        }
        else
        {
            printf("Can't find folder with path: %s", FolderPath);
        }
    }    

    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.get();

    return 0;
}