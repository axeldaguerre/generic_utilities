#include <stdlib.h>
#include "shared.h"

static b32 GlobalRunning;
// NOTE: Does not check if the file archive already exists.

int main(int ArgCount, char **Args) 
{
	GlobalRunning = true;

	if(ArgCount < 3)
    {
        printf("[Source Folder] [Folder path 7zip]");
    }
	else
	{
	const char* SourceFolder = Args[1];
    const char* OutputFolder = Args[2];
    
    // Iterate through files in the source folder and create .7z archives.
    // Replace "7z.exe" with the full path to the 7-Zip executable if needed.

    //system("C:\\Users\\axeld\\Documents\\Projects\\Projects_Programming\\generic_utilities\\script_files\\create_separate_archive.bat");
    
	char command[512];
    sprintf(command, "for %%A in (\"%s\\*\") do ("
                     "set \"fileName=%%~nA\" "
                     "set \"fileExt=%%~xA\" "
                     "set \"archiveName=!fileName!!fileExt!.7z\" "
                     "\"C:\\Program Files\\7-Zip\\7z.exe\" a \"!%s\\!archiveName!\" \"%%A\""
                     ")", SourceFolder, OutputFolder);

    system(command);
	}
    return 0;	
}