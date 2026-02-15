///////////////////////////////////////////////////////////////////////////////
//
//  Header File Inclusion
//
///////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

///////////////////////////////////////////////////////////////////////////////
//
//  User Defined Macros
//
///////////////////////////////////////////////////////////////////////////////

// Maximum file size that we allow in the project
#define MAXFILESIZE 50

#define MAXOPENFILES 20

#define MAXINODE 5

#define READ 1
#define WRITE 2
#define EXECUTE 4

#define START 0
#define CURRENT 1
#define END 2

#define EXECUTE_SUCCESS 0

#define REGULARFILE 1
#define SPECIALFILE 2

///////////////////////////////////////////////////////////////////////////////
//
//  User Defined Macros for error handling
//
///////////////////////////////////////////////////////////////////////////////

#define ERR_INVALID_PARAMETER -1

#define ERR_NO_INODES -2

#define ERR_FILE_ALREADY_EXIST -3
#define ERR_FILE_NOT_EXIST -4

#define ERR_PERMISSION_DENIED -5

#define ERR_INSUFFICIENT_SPACE -6
#define ERR_INSUFFICIENT_DATA -7

#define ERR_MAX_FILES_OPEN -8

///////////////////////////////////////////////////////////////////////////////
//
//  User Defined Structures
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
//  Structure Name : BootBlock
//  Description    : Holds the information to boot the OS
//
///////////////////////////////////////////////////////////////////////////////

struct BootBlock
{
    char Information[100];
};

///////////////////////////////////////////////////////////////////////////////
//
//  Structure Name : SuperBlock
//  Description    : Holds the information about the file system
//
///////////////////////////////////////////////////////////////////////////////

struct SuperBlock
{
    int TotalInodes;
    int FreeInodes;
};

///////////////////////////////////////////////////////////////////////////////
//
//  Structure Name : Inode
//  Description    : Holds the information about the file
//
///////////////////////////////////////////////////////////////////////////////

#pragma pack(1)
struct Inode
{
    char FileName[20];
    int InodeNumber;
    int FileSize;
    int ActualFileSize;
    int FileType;
    int ReferenceCount;     
    int Permission;
    char *Buffer;               // for data block-cr
    struct Inode *next;
};

typedef struct Inode INODE;
typedef struct Inode * PINODE;
typedef struct Inode ** PPINODE;

///////////////////////////////////////////////////////////////////////////////
//
//  Structure Name : FileTable
//  Description    : Holds the information about opened file
//
///////////////////////////////////////////////////////////////////////////////

struct FileTable
{
    int ReadOffset;
    int WriteOffSet;
    int Mode;
    PINODE ptrinode;
};

typedef FileTable FILETABLE;
typedef FileTable * PFILETABLE;

///////////////////////////////////////////////////////////////////////////////
//
//  Structure Name : UAREA
//  Description    : Holds the information about the process file
//
///////////////////////////////////////////////////////////////////////////////

struct UAREA
{
    char ProcessName[20];
    PFILETABLE UFDT[MAXOPENFILES];
};

///////////////////////////////////////////////////////////////////////////////
//
//  Structure Name : Global variables or objects used in the project
//
///////////////////////////////////////////////////////////////////////////////

BootBlock bootobj;              // auxillary data
SuperBlock superobj;            // auxillary data
UAREA uareaobj;                 // auxillary data

PINODE head = NULL;

///////////////////////////////////////////////////////////////////////////////
//
//  Function Name : InitialiseUAREA
//  Description   : It is used to initialise UAREA members
//  Author        : Chakradhar Rawaji Dugade
//  Date          : 13/01/2026
//
///////////////////////////////////////////////////////////////////////////////

void InitialiseUAREA()
{
    strcpy(uareaobj.ProcessName, "Myexe");

    int i = 0;

    for(i = 0; i < MAXOPENFILES; i++)
    {
        uareaobj.UFDT[i] = NULL;
    }
    printf("Marvellous CVFS : UAREA gets initialised successfully\n");
}

///////////////////////////////////////////////////////////////////////////////
//
//  Function Name : InitialiseSuperBlock
//  Description   : It is used to initialise Super Block members
//  Author        : Chakradhar Rawaji Dugade
//  Date          : 13/01/2026
//
///////////////////////////////////////////////////////////////////////////////

void InitialiseSuperBlock()
{
    superobj.TotalInodes = MAXINODE;
    superobj.FreeInodes = MAXINODE;

    printf("\nMarvellous CVFS : Super block gets initialised successfully\n");
}

///////////////////////////////////////////////////////////////////////////////
//
//  Function Name : CreateDILB
//  Description   : It is used to create linked list of inodes
//  Author        : Chakradhar Rawaji Dugade
//  Date          : 13/01/2026
//
///////////////////////////////////////////////////////////////////////////////

void CreateDILB()
{
    int i = 1;
    PINODE newn = NULL;
    PINODE temp = head;

    for(i = 1; i <= MAXINODE; i++)
    {
        newn = (PINODE)malloc(sizeof(INODE));

        strcpy(newn->FileName,"\0");
        newn->InodeNumber = i;
        newn->FileSize = 0;
        newn->ActualFileSize = 0;
        newn->FileType = 0;
        newn->ReferenceCount = 0;
        newn->Permission = 0;
        newn->Buffer = NULL;
        newn->next = NULL;

        if(temp == NULL)    // LL is empty
        {
            head = newn;
            temp = head;
        }
        else                // LL contains atleast 1 node
        {
            temp->next = newn;
            temp = temp->next;
        }
    }
    
    printf("Marvellous CVFS : DILB created successfully\n");
}

///////////////////////////////////////////////////////////////////////////////
//
//  Function Name : StartAuxillaryDataInitialisation
//  Description   : It is used to call all such functions which are used
//                  to initialise auxillary data
//  Author        : Chakradhar Rawaji Dugade
//  Date          : 13/01/2026
//
///////////////////////////////////////////////////////////////////////////////

void StartAuxillaryDataInitialisation()
{
    strcpy(bootobj.Information,"Booting process of Marvellous CVFS is done");

    printf("%s", bootobj.Information);

    InitialiseSuperBlock();

    CreateDILB();

    InitialiseUAREA();

    printf("Marvellous CVFS : Auxillary data initialised successfully\n");
}

///////////////////////////////////////////////////////////////////////////////
//
//  Function Name : DisplayHelp
//  Description   : It is used to display the help page
//  Author        : Chakradhar Rawaji Dugade
//  Date          : 14/01/2026
//
///////////////////////////////////////////////////////////////////////////////

void DisplayHelp()
{
    printf("--------------------------------------------------------\n");
    printf("--------------  Marvellous CVFS Help Page  -------------\n");
    printf("--------------------------------------------------------\n");

    printf("man    : It is used to display manual page\n");
    printf("clear  : It is used to clear the terminal\n");
    printf("creat  : It is used to create new file\n");
    printf("write  : It is used to write the data into the file\n");
    printf("read   : It is used to read the data from the file\n");
    printf("stat   : It is used to display statistical information\n");
    printf("unlink : It is used to delete the fiel\n");
    printf("exit   : It is used to terminate Marvellous CVFS\n");

    printf("--------------------------------------------------------\n");
}

///////////////////////////////////////////////////////////////////////////////
//
//  Function Name : ManPageDisplay
//  Description   : It is used to display the man page
//  Author        : Chakradhar Rawaji Dugade
//  Date          : 14/01/2026
//
///////////////////////////////////////////////////////////////////////////////

void ManPageDisplay(char Name[])
{
    if(strcmp("ls",Name) == 0)
    {
        printf("About : It is used to list the name of all files\n");
        printf("Usage : ls\n");
    }
    else if (strcmp("man",Name) == 0)
    {
        printf("About : It is used to display manual page\n");
        printf("Usage : man command_name\n");
        printf("command_name : It is the name of command\n");
    }
    else if(strcmp("clear",Name) == 0)
    {
        printf("About : It is used to clear the shell\n");
        printf("Usage : clear\n");
    }
    else if(strcmp("creat",Name) == 0)
    {
        printf("About : It is used to create a new file\n");
        printf("Usage : creat FileName Permission\n");
        printf("Permission : 1 = Read, 2 = Write, 3 = Read & Write\n");
    }
    else if(strcmp("write",Name) == 0)
    {
        printf("About : It is used to write data into the file\n");
        printf("Usage : write FileDescriptor\n");
    }
    else if(strcmp("read",Name) == 0)
    {
        printf("About : It is used to read data from the file\n");
        printf("Usage : read FileDescriptor Size\n");
    }
    else if(strcmp("stat",Name) == 0)
    {
        printf("About : It is used to display statistical information of a file\n");
        printf("Usage : stat FileName\n");
    }
    else if(strcmp("unlink",Name) == 0)
    {
        printf("About : It is used to delete a file\n");
        printf("Usage : unlink FileName\n");
    }
    else if(strcmp("exit",Name) == 0)
    {
        printf("About : It is used to terminate the shell\n");
        printf("Usage : exit\n");
    }
    else
    {
        printf("No manual entry for %s\n",Name);
    }   
}

///////////////////////////////////////////////////////////////////////////////
//
//  Function Name : IsFileExist
//  Description   : It is used to check whether file is already exist or not
//  Input         : It accepts file name 
//  Output        : It returns true or false (boolean)
//  Author        : Chakradhar Rawaji Dugade
//  Date          : 16/01/2026
//
///////////////////////////////////////////////////////////////////////////////

bool IsFileExist(
                    char *name          // File name
                )
{
    PINODE temp = head;
    bool bFlag = false;

    while(temp != NULL)
    {
        if((strcmp(name,temp->FileName) == 0) && (temp->FileType == REGULARFILE))
        {
            bFlag = true;
            break;
        }
        temp = temp->next;
    }

    return bFlag;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Function Name : CreateFile
//  Description   : It is used to create new regular file
//  Input         : It accepts file name and permission
//  Output        : It returns the file discriptor(fd)
//  Author        : Chakradhar Rawaji Dugade
//  Date          : 16/01/2026
//
///////////////////////////////////////////////////////////////////////////////

int CreateFile(
                    char *name,             // Name of new file
                    int permission         // Permission for that file
                )
{
    PINODE temp = head;
    int i = 0;

    // If name is missing
    if(name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    // If the permission value is wrong
    // permission -> 1 -> READ
    // permission -> 2 -> WRITE
    // permission -> 3 -> READ + WRITE
    if(permission < 1 || permission > 3)
    {
        return ERR_INVALID_PARAMETER;
    }

    // If the inodes are full
    if(superobj.FreeInodes == 0)
    {
        return ERR_NO_INODES;   
    }

    // If file is already present
    if(IsFileExist(name) == true)
    {
        return ERR_FILE_ALREADY_EXIST;
    }

    // Search empty Inode
    while(temp != NULL)
    {
        if(temp->FileType == 0)
        {
            break;
        }
        temp = temp->next;
    }

    if(temp == NULL)
    {
        printf("There is no Inode\n");
        return ERR_NO_INODES;
    }

    // Search for empty UFDT entry
    //Note : 0,1,2 are reserved  
    for(i = 3; i < MAXOPENFILES; i++)
    {
        if(uareaobj.UFDT[i] == NULL)
        {
            break;
        }
    }

    // UFDT is full
    if(i == MAXOPENFILES)
    {
        return ERR_MAX_FILES_OPEN;
    }

    // Allocate memory for file table
    uareaobj.UFDT[i] = (PFILETABLE)malloc(sizeof(FileTable));

    // Initialize File table
    uareaobj.UFDT[i]->ReadOffset = 0;
    uareaobj.UFDT[i]->WriteOffSet = 0;
    uareaobj.UFDT[i]->Mode = permission;
    
    // Connect File Table with Inode
    uareaobj.UFDT[i]->ptrinode = temp;

    // Initialise elements of Inode
    strcpy(uareaobj.UFDT[i]->ptrinode->FileName,name);
    uareaobj.UFDT[i]->ptrinode->FileSize = MAXFILESIZE;
    uareaobj.UFDT[i]->ptrinode->ActualFileSize = 0;
    uareaobj.UFDT[i]->ptrinode->FileType = REGULARFILE;
    uareaobj.UFDT[i]->ptrinode->ReferenceCount = 1;
    uareaobj.UFDT[i]->ptrinode->Permission = permission;

    // Allocate memory for files data
    uareaobj.UFDT[i]->ptrinode->Buffer = (char*)malloc(MAXFILESIZE);
    memset(uareaobj.UFDT[i]->ptrinode->Buffer, 0, MAXFILESIZE);

    superobj.FreeInodes--;

    printf("Total number of Inodes remaining : %d\n", superobj.FreeInodes);

    return i;       // File descriptor(fd)
}

///////////////////////////////////////////////////////////////////////////////
//
//  Function Name : LsFile
//  Description   : It is used to list all files
//  Input         : Nothing
//  Output        : Nothing
//  Author        : Chakradhar Rawaji Dugade
//  Date          : 16/01/2026
//
///////////////////////////////////////////////////////////////////////////////

// ls -l
void LsFile()
{
    PINODE temp = head;

    printf("--------------------------------------------------------\n");
    printf("----------- Marvellous CVFS files informantion ---------\n");
    printf("--------------------------------------------------------\n");

    while(temp != NULL)
    {
        if(temp->FileType != 0)
        {
            printf("%d\t%s\t%d\n",temp->InodeNumber,temp->FileName,temp->ActualFileSize);
        }
        temp = temp->next;
    }

    printf("--------------------------------------------------------\n");
}

///////////////////////////////////////////////////////////////////////////////
//
//  Function Name : UnlinkFile()
//  Description   : It is used to delete the file
//  Input         : File name
//  Output        : Nothing
//  Author        : Chakradhar Rawaji Dugade
//  Date          : 22/01/2026
//
///////////////////////////////////////////////////////////////////////////////

int UnlinkFile(
                    char *name
                )
{
    int i = 0;

    if(name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    if(IsFileExist(name) == false)
    {
        return ERR_FILE_NOT_EXIST;
    }

    // Travell the UFDT
    for(i = 0; i < MAXOPENFILES; i++)
    {
        if(uareaobj.UFDT[i] != NULL)
        {
            if(strcmp(uareaobj.UFDT[i]->ptrinode->FileName, name) == 0)
            {
                // Deallocate memory of Buffer
                free(uareaobj.UFDT[i]->ptrinode->Buffer);
                uareaobj.UFDT[i]->ptrinode->Buffer = NULL;
                
                // Reset all values of inode
                // Dont deallocate memory of inode
                uareaobj.UFDT[i]->ptrinode->FileSize = 0;
                uareaobj.UFDT[i]->ptrinode->ActualFileSize = 0;
                uareaobj.UFDT[i]->ptrinode->FileType = 0;
                uareaobj.UFDT[i]->ptrinode->ReferenceCount = 0;
                uareaobj.UFDT[i]->ptrinode->Permission = 0;

                memset(uareaobj.UFDT[i]->ptrinode->FileName, '\0', sizeof(uareaobj.UFDT[i]->ptrinode->FileName));

                // Deallocate the memory of file table
                free(uareaobj.UFDT[i]);

                // Set NULL to UFDT
                uareaobj.UFDT[i] = NULL;

                // Increament FreeInodes count
                superobj.FreeInodes++;

                break;          //imp
            }   // End of if
        }   // End of if
    }   // End of for

    return EXECUTE_SUCCESS;
}   // End of UnlinkFile()

///////////////////////////////////////////////////////////////////////////////
//
//  Function Name : WriteFile()
//  Description   : It is used to write the data into the file
//  Input         : File descriptor,
//                  Address of buffer which contains data,
//                  Size of data that we want to write
//  Output        : Number of bytes successfully written
//  Author        : Chakradhar Rawaji Dugade
//  Date          : 22/01/2026
//
///////////////////////////////////////////////////////////////////////////////

int WriteFile(
                    int fd,
                    char *data,
                    int size
            )
{
    printf("File descriptor : %d\n", fd);
    printf("Data that we want to write : %s\n", data);
    printf("The number of bytes that we want to write : %d\n",size);

    // Invalid fd
    if(fd < 0 || fd >= MAXOPENFILES)
    {
        return ERR_INVALID_PARAMETER;
    }

    // fd points to NULL
    if(uareaobj.UFDT[fd] == NULL)
    {
        return ERR_FILE_NOT_EXIST;
    }

    // There is no permission to write
    if(uareaobj.UFDT[fd]->ptrinode->Permission < WRITE)
    {
        return ERR_PERMISSION_DENIED;
    }

    // Insufficient space
    if((MAXFILESIZE - uareaobj.UFDT[fd]->WriteOffSet) < size)
    {
        return ERR_INSUFFICIENT_SPACE;
    }

    // Write the data in the file
    strncpy(uareaobj.UFDT[fd]->ptrinode->Buffer + uareaobj.UFDT[fd]->WriteOffSet, data, size); 

    // Update the writeoffset
    uareaobj.UFDT[fd]->WriteOffSet = uareaobj.UFDT[fd]->WriteOffSet + size;

    // Update the actual file size
    uareaobj.UFDT[fd]->ptrinode->ActualFileSize = uareaobj.UFDT[fd]->ptrinode->ActualFileSize + size;

    return size;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Function Name : ReadFile()
//  Description   : It is used to read the data from the file
//  Input         : File descriptor,
//                  Address of empty buffer,
//                  Size of data that we want to read
//  Output        : Number of bytes successfully read
//  Author        : Chakradhar Rawaji Dugade
//  Date          : 22/01/2026
//
///////////////////////////////////////////////////////////////////////////////

int ReadFile(
                int fd,
                char *data,
                int size
            )
{
    // Invalid fd
    if(fd < 0 || fd >= MAXOPENFILES)
    {
        return ERR_INVALID_PARAMETER;
    }

    // 
    if(data == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    //
    if(size <= 0)
    {
        return ERR_INVALID_PARAMETER;
    }

    //
    if(uareaobj.UFDT[fd] == NULL)
    {
        return ERR_FILE_NOT_EXIST;
    }

    // Filter for permission
    if(uareaobj.UFDT[fd]->ptrinode->Permission < READ)
    {
        return ERR_PERMISSION_DENIED;
    }

    // Insufficient data
    if((uareaobj.UFDT[fd]->ptrinode->ActualFileSize - uareaobj.UFDT[fd]->ReadOffset) < size)
    {
        return ERR_INSUFFICIENT_DATA;
    }

    // Read the data
    strncpy(data, uareaobj.UFDT[fd]->ptrinode->Buffer + uareaobj.UFDT[fd]->ReadOffset, size);

    // Update the read offset
    uareaobj.UFDT[fd]->ReadOffset = uareaobj.UFDT[fd]->ReadOffset + size;

    return size;
}      

// Updated-cr
///////////////////////////////////////////////////////////////////////////////
//
//  Function Name : StatFile
//  Description   : Displays information of the file using file name
//
///////////////////////////////////////////////////////////////////////////////

int StatFile(char *name)
{
    PINODE temp = head;

    if(name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    // Traverse inode list
    while(temp != NULL)
    {
        if((strcmp(name, temp->FileName) == 0) && (temp->FileType == REGULARFILE))
        {
            break;
        }
        temp = temp->next;
    }

    if(temp == NULL)
    {
        return ERR_FILE_NOT_EXIST;
    }

    printf("\n---------- File Statistics ----------\n");
    printf("File name        : %s\n", temp->FileName);
    printf("Inode number     : %d\n", temp->InodeNumber);
    printf("File size        : %d\n", temp->FileSize);
    printf("Actual file size : %d\n", temp->ActualFileSize);

    if(temp->FileType == REGULARFILE)
    {
        printf("File type        : Regular\n");
    }
    else
    {
        printf("File type        : Special\n");
    }

    printf("Reference count  : %d\n", temp->ReferenceCount);

    printf("Permission       : ");
    if(temp->Permission == 1)
    {
        printf("Read only\n");
    }
    else if(temp->Permission == 2)
    {
        printf("Write only\n");
    }
    else if(temp->Permission == 3)
    {
        printf("Read & Write\n");
    }

    printf("-------------------------------------\n");

    return EXECUTE_SUCCESS;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Entry point function of the project
//
///////////////////////////////////////////////////////////////////////////////

int main()
{
    char str[80] = {'\0'};
    char Command[5][20] = {{'\0'}};    
    char InputBuffer[MAXFILESIZE] ={'\0'};

    char *EmptyBuffer = NULL;

    int iCount = 0;
    int iRet = 0;

    StartAuxillaryDataInitialisation();

    printf("--------------------------------------------------------\n");
    printf("---------- Marvellous CVFS started successfully --------\n");
    printf("--------------------------------------------------------\n");

    // Infinite Listening Shell
    while(1)
    {
        strcpy(str,"");

        printf("\nMarvellous CVFS : > ");
        fgets(str,sizeof(str),stdin);

        // tokenisation or spliting of string-cr
        iCount = sscanf(str,"%s %s %s %s %s",Command[0],Command[1],Command[2],Command[3],Command[4]);

        if(iCount == 1)
        {
            // Marvellous CVFS : > exit
            if(strcmp("exit",Command[0]) == 0) // imp (== 0)-cr 
            {
                printf("Thank for using Marvellous CVFS\n");
                printf("Deallocating all the resources\n");

                break;
            }   
            // Marvellous CVFS : > ls
            else if(strcmp("ls",Command[0]) == 0)
            {
                LsFile();
            }
            // Marvellous CVFS : > help
            else if(strcmp("help",Command[0]) == 0)
            {
                DisplayHelp();
            }
            // Marvellous CVFS : > clear
            else if(strcmp("clear",Command[0]) == 0)
            {
                // conditional preprocessing
                #ifdef _WIN32
                    system("cls");
                #else
                    system("clear");
                #endif
            }
        } // End of else if 1
        else if(iCount == 2)
        {
            // Marvellous CVFS : > man command_name(ls)
            if(strcmp("man",Command[0]) == 0)
            {
                ManPageDisplay(Command[1]);
            }

            // Marvellous CVFS : > unlink FileName (Demo.txt)
            if(strcmp("unlink",Command[0]) == 0)
            {
                iRet = UnlinkFile(Command[1]);

                if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalid parameter\n");
                }

                if(iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Error : Unable to delete as there is no such file\n");
                }

                if(iRet == EXECUTE_SUCCESS)
                {
                    printf("File gets successfully deleted\n");
                }
            }
            // Marvellous CVFS : > write 2
            else if(strcmp("write",Command[0]) == 0)
            {
                printf("Enter the data that you want to write : \n");
                fgets(InputBuffer,MAXFILESIZE,stdin);

                iRet = WriteFile(atoi(Command[1]), InputBuffer, strlen(InputBuffer)-1);
            
                if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalid parameters \n");
                }
                else if(iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Error : There is no such file\n");
                }
                else if(iRet == ERR_PERMISSION_DENIED)
                {
                    printf("Error : Unable to write as there is no permission\n");
                }
                else if(iRet == ERR_INSUFFICIENT_SPACE)
                {
                    printf("Error : Unable to write as there is no space\n");
                }
                else
                {
                    printf("%d bytes gets succesfully written\n",iRet);
                }
            }
            // Marvellous CVFS : > stat filename
            else if(strcmp("stat",Command[0]) == 0)
            {
                iRet = StatFile(Command[1]);

                if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalid parameter\n");
                }
                else if(iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Error : File not found\n");
                }
            }
            else
            {
                printf("There is no such command\n");
            }

        } // End of else if 2
        else if(iCount == 3)
        {
            // Marvellous CVFS : > creat filename(Ganesh.txt) permission(3)
            if(strcmp("creat",Command[0]) == 0)
            {
                iRet = CreateFile(Command[1],atoi(Command[2]));

                if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("ERROR : Unable to create the file as the parameters are invalid\n");
                    printf("Please refer the man page\n");
                }

                if(iRet == ERR_NO_INODES)
                {
                    printf("ERROR : Unable to create the file as there is no inode\n");
                }

                if(iRet == ERR_FILE_ALREADY_EXIST)
                {
                    printf("ERROR : Unable to create the file because the file already present\n");
                }

                if(iRet == ERR_MAX_FILES_OPEN)
                {
                    printf("ERROR : Unable to create file\n");
                    printf("Max opened files limit reached\n");
                }

                if(iRet >= 3)
                {
                    printf("File gets successfully created with FD %d\n",iRet);
                }
            }
            // read 3(fd) 10(number of bytes)
            else if(strcmp("read",Command[0]) == 0)
            {
                int size = atoi(Command[2]);
                EmptyBuffer = (char *)malloc(size + 1);

                if(EmptyBuffer == NULL)
                {
                    printf("Memory allocation failed\n");
                    continue;
                }

                iRet = ReadFile(atoi(Command[1]), EmptyBuffer, atoi(Command[2]));

                if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalid parameter\n");
                    free(EmptyBuffer);
                }
                else if(iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Error : File not exist\n");
                }
                else if(iRet == ERR_PERMISSION_DENIED)
                {
                    printf("Error : Permission denied\n");
                }
                else if(iRet == ERR_INSUFFICIENT_DATA)
                {
                    printf("Error : Insufficient data\n");
                }
                else
                {
                    EmptyBuffer[iRet] = '\0';
                    printf("Read operation is succesful\n");
                    printf("Data from file is : %s\n",EmptyBuffer);

                    free(EmptyBuffer);
                }
            }
            else
            {
                printf("There is no such command\n");
            }
        } // End of else if 3
        else if(iCount == 4)
        {
            
        } // End of else if 4
        else
        {
            printf("Command not found\n");
            printf("Please refer to get more information\n");
        } // End of else
    } // End of while

    return 0;
}// End of main                                                              
