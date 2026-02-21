// ============================================================
// Client Application
// Purpose : Connect to server and download requested file
// Usage   : ./client <IP> <Port> <ServerFile> <NewFile>
//
// Example : ./client 127.0.0.1 9000 Demo.txt A.txt
// ============================================================

#include<stdio.h>      // printf(), sscanf()
#include<stdlib.h>     // atoi()
#include<string.h>     // memset(), strlen()
#include<unistd.h>     // read(), write(), close()
#include<fcntl.h>      // open()
#include<sys/socket.h> // socket(), connect()
#include<sys/stat.h>   // File permission flags
#include<netinet/in.h> // sockaddr_in
#include<arpa/inet.h>  // inet_pton()

// ============================================================
// Function : ReadLine
// Purpose  : Read data from socket until newline '\n'
// Used to read header from server (Example: "OK 1700\n")
// ============================================================
int ReadLine(int Sock, char *line, int max)
{
    int i = 0;
    char ch = '\0';
    int n = 0;

    // Read one byte at a time
    while(i < max - 1)
    {
        n = read(Sock, &ch, 1);

        if(n <= 0)        // Connection closed or error
            break;

        line[i++] = ch;

        if(ch == '\n')    // Stop when newline found
            break;
    }

    line[i] = '\0';       // Null terminate string
    return i;             // Return number of bytes read
}

// ============================================================
// Main Function
// ============================================================
int main(int argc, char *argv[])
{
    int Sock = 0;
    int Port = 0;
    int iRet = 0;

    char *ip = NULL;
    char *Filename = NULL;
    char *OutFilename = NULL;

    struct sockaddr_in ServerAddr;
    char Header[64] = {'\0'};

    // --------------------------------------------------------
    // Step 0 : Validate Command Line Arguments
    // --------------------------------------------------------
    if(argc != 5)
    {
        printf("Invalid number of arguments\n");
        printf("Usage : ./client <IP> <Port> <ServerFile> <NewFile>\n");
        return -1;
    }

    // Store arguments
    ip = argv[1];                // Server IP address
    Port = atoi(argv[2]);        // Convert port string to integer
    Filename = argv[3];          // File to download from server
    OutFilename = argv[4];       // Name of new downloaded file

    // --------------------------------------------------------
    // Step 1 : Create TCP Socket
    // AF_INET     -> IPv4
    // SOCK_STREAM -> TCP
    // --------------------------------------------------------
    Sock = socket(AF_INET, SOCK_STREAM, 0);

    if(Sock < 0)
    {
        printf("Unable to create client socket\n");
        return -1;
    }

    // --------------------------------------------------------
    // Step 2 : Connect to Server
    // --------------------------------------------------------
    memset(&ServerAddr, 0, sizeof(ServerAddr));

    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(Port);  // Convert port to network byte order

    // Convert IP string to binary format
    inet_pton(AF_INET, ip, &ServerAddr.sin_addr);

    iRet = connect(Sock, (struct sockaddr*)&ServerAddr, sizeof(ServerAddr));

    if(iRet == -1)
    {
        printf("Unable to connect with server\n");
        close(Sock);
        return -1;
    }

    // --------------------------------------------------------
    // Step 3 : Send Requested File Name to Server
    // --------------------------------------------------------
    write(Sock, Filename, strlen(Filename));
    write(Sock, "\n", 1);  // Send newline to mark end of filename

    // --------------------------------------------------------
    // Step 4 : Read Header from Server
    // Header Format : "OK <FileSize>\n"
    // --------------------------------------------------------
    iRet = ReadLine(Sock, Header, sizeof(Header));

    if(iRet <= 0)
    {
        printf("Server disconnected unexpectedly\n");
        close(Sock);
        return -1;
    }

    printf("Header received : %s\n", Header);

    long FileSize = 0;
    sscanf(Header, "OK %ld", &FileSize);

    printf("File size : %ld bytes\n", FileSize);

    // --------------------------------------------------------
    // Step 5 : Create Output File
    // O_CREAT  -> Create file if not exists
    // O_WRONLY -> Write only
    // O_TRUNC  -> Clear file if already exists
    // 0777     -> File permissions
    // --------------------------------------------------------
    int outfd = open(OutFilename, O_CREAT | O_WRONLY | O_TRUNC, 0777);

    if(outfd < 0)
    {
        printf("Unable to create output file\n");
        close(Sock);
        return -1;
    }

    // --------------------------------------------------------
    // Step 6 : Receive File Data from Server
    // --------------------------------------------------------
    char Buffer[1024];
    long received = 0;
    long remaining = 0;
    int n = 0;
    int toRead = 0;

    while(received < FileSize)
    {
        remaining = FileSize - received;

        // Read either 1024 bytes or remaining bytes
        if(remaining > 1024)
            toRead = 1024;
        else
            toRead = remaining;

        n = read(Sock, Buffer, toRead);

        if(n <= 0)
            break;

        write(outfd, Buffer, n);

        received += n;
    }

    // --------------------------------------------------------
    // Step 7 : Close File and Socket
    // --------------------------------------------------------
    close(outfd);
    close(Sock);

    // --------------------------------------------------------
    // Step 8 : Final Status Check
    // --------------------------------------------------------
    if(received == FileSize)
    {
        printf("Download complete...\n");
        return 0;
    }
    else
    {
        printf("Download failed...\n");
        return -1;
    }
}
