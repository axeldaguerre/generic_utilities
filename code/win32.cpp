#include"shared.h"


inline b32 Win32IsFolderEmpty(char *FolderPath) {
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

inline b32 CreateEmptyFolder(char *FolderName)
{
    b32 Result;
    if(CreateDirectoryA(FolderName, 0))
    {
        Result = true;
    }
    else
    {
        printf("Folder with path: %s could not be created\n", FolderName);
        Result = true;
    }
}

inline b32 win32_move_file(thread_context *Thread, char *FilePath, char *NewFilePath)
{
    b32 Result = true;

    if(MoveFile(FilePath, NewFilePath))
    {
    }
    else
    {
        Result = false;
    }
    
    return Result;
}

inline b32 win32_create_folder(thread_context *Thread, app_state *AppState, char *FolderPath)
{             
    b32 Result = false;
    if(CreateDirectory(FolderPath, 0))
    {
        Result = true;
    }
    else
    {
        
        if(GetLastError() == ERROR_PATH_NOT_FOUND)
        {
            MessageBox( NULL, "Couldn't create the directory\n Path doesn't exists",
                        "Error Movie File Folder Creation", MB_OK);
            
            Result = false;
        }
        else
        {
            Result = true;
        }
    }

    return Result;   
}

inline b32 win32_free_memory(thread_context *Thread, void *Memory)
{
    if(Memory)
    {   
        VirtualFree(Memory, 0, MEM_RELEASE);
    }
}

inline b32 win32_write_entire_file(thread_context *Thread, char *FileName, u32 MemorySize, void *Memory)
{
    b32 Result = false;
    
    HANDLE FileHandle = CreateFileA(FileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
    if(FileHandle != INVALID_HANDLE_VALUE)
    {
        DWORD BytesWritten;
        if(WriteFile(FileHandle, Memory, MemorySize, &BytesWritten, 0))
        {
            // NOTE(casey): File read successfully
            Result = (BytesWritten == MemorySize);
        }
        else
        {
            // TODO(casey): Logging
        }

        CloseHandle(FileHandle);
    }
    else
    {
        // TODO(casey): Logging
    }

    return(Result);
}

inline debug_read_file_result win32_read_entire_file (thread_context *Thread, char *FileName)
{
    // STUDY(Axel): Use HeapAlloc()?     
    debug_read_file_result Result = {};
    
    HANDLE FileHandle = CreateFileA(FileName, GENERIC_READ,
                                    FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
    if(FileHandle != INVALID_HANDLE_VALUE)
    {
        LARGE_INTEGER FileSize;
        if(GetFileSizeEx(FileHandle, &FileSize))
        {
            u32 FileSize32 = safe_truncate_u64(FileSize.QuadPart);
            Result.Contents = VirtualAlloc(0, FileSize32, MEM_RESERVE|MEM_COMMIT,
                                           PAGE_READWRITE);
            if(Result.Contents)
            {
                DWORD BytesRead;
                if(ReadFile(FileHandle, Result.Contents, FileSize32, &BytesRead, 0) &&
                   (FileSize32 == BytesRead))
                {
                    Result.ContentsSize = FileSize32;
                }
                else
                {
                    win32_free_memory(Thread, Result.Contents);
                    Result.Contents = 0;
                }
            }
            else
            {
            }
        }
        else
        {

        }
        CloseHandle(FileHandle);
    }
    else
    {
    }
    return Result;
}

inline b32 win32_free_memory(thread_context *Thread, char *FileName, u32 MemorySize, void *Memory)
{
    b32 Result = false;

    HANDLE FileHandle = CreateFileA(FileName, FILE_APPEND_DATA, 0, 0, OPEN_ALWAYS, 0, 0);

    if(FileHandle != INVALID_HANDLE_VALUE)
    {
        DWORD BytesWritten;
        
        if(WriteFile(FileHandle, Memory, MemorySize, &BytesWritten, 0))
        {
            Result = (BytesWritten == MemorySize);
        }
    }
    else
    {            
    }
    // STUDY(Axel): Does keeping the FILEHANDLE gives better perf?
    CloseHandle(FileHandle);
    
    return(Result);
}

inline b32 win32_copy_file(char *InFilePath, char *OutFilePath)
{
	b32 Result = false;
	

	if(CopyFile(InFilePath, OutFilePath, false))
	{
		Result = true;
	}
	else
	{
		DWORD Error = GetLastError();
		printf("ERROR: while copying file -> %d\n", Error);
	}
	
	return Result;
}

b32 FolderExists(char *FolderPath)
{
	b32 Result = false;
	DWORD fileAttributes = GetFileAttributes(FolderPath);

	if(fileAttributes != INVALID_FILE_ATTRIBUTES && 
		(fileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	{
		Result = true;
	}
	return Result;
}


inline bool win32_is_folder(char *path)
{
    DWORD fileAttributes = GetFileAttributes(path);

    if (fileAttributes != INVALID_FILE_ATTRIBUTES)
    {
        return (fileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
    }
    else
    {
        return false;
    }
}

