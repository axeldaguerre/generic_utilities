#include "shared.h"
static b32 GlobalRunning;

inline void 
win32_copy_files_in_folder(char *FolderPath, WIN32_FIND_DATA FileData, char *FolderDestinationPath)
{
	
	char FolderPathWithStar[MAX_PATH_APP];
			str_concat(str_len(FolderPath), FolderPath,
				str_len("\\*"), "\\*",
				str_len(FolderPathWithStar), FolderPathWithStar);

	HANDLE FileHandle = FindFirstFileA(FolderPathWithStar, &FileData);

	if(FileHandle)
	{
		while(FindNextFileA(FileHandle, &FileData))
		{   
			if(strstr(FileData.cFileName, "..")) continue;

			char FilePath[MAX_PATH_APP];
			sprintf(FilePath, "%s\\%s", FolderPath, FileData.cFileName);
			
			if(win32_is_folder(FilePath))
			{
				win32_copy_files_in_folder(FilePath, FileData, FolderDestinationPath);
			}
			else
			{
				WCHAR *FilePathW = win32_char_to_wchar(FilePath);

				if(SetFileAttributesW(FilePathW, GetFileAttributesW(FilePathW) & 
										~FILE_ATTRIBUTE_READONLY) == 0)
				{
					printf("ERROR: couln't unset READ_ONLY\n");
				}

				char FilePathDestination[MAX_PATH_APP];
				sprintf(FilePathDestination, "%s\\%s", FolderDestinationPath, FileData.cFileName);

				if(!win32_copy_file(FilePath, FilePathDestination))
				{
					DWORD Error = GetLastError();
					printf("Couldn't copy %s\n", FilePath);
					break;
				}
				else
				{
					printf("File Copied successfully\n");
				}
			}
		}
	}
}
//NOTE: Only handle 2 level of folder currently
int main(int ArgCount, char **Args) 
{
	if(ArgCount < 3)
    {
        printf("[folder path] [path to move files]");
    }
	else
    {
		char *FolderPath = Args[1];
		char *FolderDestinationPath = Args[2];
		thread_context Thread = {};
        WIN32_FIND_DATA FileData = {};

		if(!FolderExists(FolderDestinationPath))
		{
			win32_create_folder(FolderDestinationPath);
		}

		win32_copy_files_in_folder(FolderPath, FileData, FolderDestinationPath);
        
	}
	return 0;
}