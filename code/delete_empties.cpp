
#include "shared.h"

static b32 GlobalRunning;

int main(int ArgCount, char **Args) {
    GlobalRunning = true;

    if(ArgCount < 2)
    {
        printf("[folder path]");
    }
    else
    {
        //TODO: make generic names, remove all game assumption
        char *FolderPlatforms = Args[1];
        WIN32_FIND_DATA FileData = {};
            
        char FolderPlatformsWithStar[MAX_PATH_APP];
        str_concat(str_len(FolderPlatforms), FolderPlatforms,
            str_len("\\*"), "\\*",
            str_len(FolderPlatformsWithStar), FolderPlatformsWithStar);
        HANDLE FileHandle = FindFirstFileA(FolderPlatformsWithStar, &FileData);

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
                            if(strstr(RomPath, "\\..")) continue;

                            wchar_t RomPathW[MAX_PATH_APP];
                            MultiByteToWideChar(CP_UTF8, 0, RomPath, -1, RomPathW, MAX_PATH_APP);


                            if (win32_is_folder_empty(RomPath)) 
                            {
                                
                                if(SetFileAttributesW(RomPathW, GetFileAttributesW(RomPathW) & ~FILE_ATTRIBUTE_READONLY) == 0)
                                {
                                    printf("ERROR: couln't unset READ_ONLY\n");
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
    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.get();
    return 0;
}