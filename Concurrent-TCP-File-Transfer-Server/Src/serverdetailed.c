// ===============================
// Required Header Files
// ===============================
#include<stdio.h>      // printf(), snprintf()
#include<stdlib.h>     // atoi(), exit()
#include<string.h>     // memset(), strlen(), strcspn()
#include<unistd.h>     // read(), write(), close(), fork()
#include<fcntl.h>      // open()
#include<sys/socket.h> // socket(), bind(), listen(), accept()
#include<sys/stat.h>   // stat() - to get file size
#include<netinet/in.h> // sockaddr_in structure
#include<arpa/inet.h>  // inet_ntoa()
#include<stdbool.h>

// ==========================================================
// Function : SendFileToClient()
// Purpose  : Opens requested file and sends it to client
// ==========================================================
void SendFileToClient(int ClientSocket, char * Filename)
{
    int fd = 0;                 // File descriptor
    struct stat sobj;           // Structure to store file information
    char Buffer[1024];          // Buffer to send file data
    int BytesRead = 0;
    char Header[64] = {'\0'};   // Header to send status and file size

    printf("File name is : %s : %lu\n", Filename, strlen(Filename));

    // Open the file in read-only mode
    fd = open(Filename, O_RDONLY);

    // If file cannot be opened
    if(fd < 0)
    {
        printf("Unable to open file\n");

        // Send error message to client
        write(ClientSocket, "ERR\n", 4);
        return;
    }

    // Get file information (mainly size)
    stat(Filename, &sobj);

    // Prepare header : "OK <filesize>\n"
    snprintf(Header, sizeof(Header), "OK %ld\n", (long)sobj.st_size);

    // Send header to client
    write(ClientSocket, Header, strlen(Header));

    // Read file data and send to client
    while((BytesRead = read(fd, Buffer, sizeof(Buffer))) > 0)
    {
        write(ClientSocket, Buffer, BytesRead);
    }

    close(fd);  // Close file
}

// ==========================================================
// Main Function
// Usage : ./server <port>
// Example : ./server 9000
// ==========================================================
int main(int argc, char *argv[])
{
    int ServerSocket = 0;
    int ClientSocket = 0;
    int Port = 0;
    int iRet = 0;

    char FileName[50] = {'\0'};
    pid_t pid = 0;

    struct sockaddr_in ServerAddr;
    struct sockaddr_in ClientAddr;
    socklen_t AddrLen = sizeof(ClientAddr);

    // Check command line argument count
    if((argc < 2) || (argc > 2))
    {
        printf("Invalid arguments. Provide port number\n");
        return -1;
    }

    // Convert port number from string to integer
    Port = atoi(argv[1]);

    // ==================================================
    // Step 1 : Create TCP Socket
    // socket(AF_INET, SOCK_STREAM, 0)
    // AF_INET      -> IPv4
    // SOCK_STREAM  -> TCP
    // ==================================================
    ServerSocket = socket(AF_INET, SOCK_STREAM, 0);

    if(ServerSocket < 0)
    {
        printf("Unable to create server socket\n");
        return -1;
    }

    // ==================================================
    // Step 2 : Bind socket to IP and Port
    // ==================================================

    // Clear the ServerAddr structure by setting all bytes to 0
    // This avoids garbage values inside the structure
    // Must be done before assigning sin_family, sin_port, etc.
    memset(&ServerAddr, 0, sizeof(ServerAddr));
    
    ServerAddr.sin_family = AF_INET;          // IPv4
    ServerAddr.sin_port = htons(Port);        // Convert port to network byte order
    ServerAddr.sin_addr.s_addr = INADDR_ANY;  // Accept connections from any IP

    iRet = bind(ServerSocket, 
                (struct sockaddr *)&ServerAddr, 
                sizeof(ServerAddr));

    if(iRet == -1)
    {
        printf("Unable to bind\n");
        close(ServerSocket);
        return -1;
    }

    // ==================================================
    // Step 3 : Listen for client connections
    // 11 = backlog (max pending connections)
    // ==================================================
    iRet = listen(ServerSocket, 11);

    if(iRet == -1)
    {
        printf("Server unable to listen\n");
        close(ServerSocket);
        return -1;
    }

    printf("Server is running on port : %d\n", Port);

    // ==================================================
    // Step 4 : Infinite loop to accept multiple clients
    // ==================================================
    while(1)
    {
        memset(&ClientAddr, 0, sizeof(ClientAddr));

        printf("Waiting for client request...\n");

        // Accept client connection
        ClientSocket = accept(ServerSocket, 
                              (struct sockaddr *)&ClientAddr, 
                              &AddrLen);

        if(ClientSocket < 0)
        {
            printf("Unable to accept client\n");
            continue;
        }

        printf("Client connected : %s\n", inet_ntoa(ClientAddr.sin_addr));

        // ==================================================
        // Step 5 : Create new process using fork()
        // Purpose : Handle multiple clients concurrently
        // ==================================================
        pid = fork();

        if(pid < 0)
        {
            printf("Fork failed\n");
            close(ClientSocket);
            continue;
        }

        // ===============================
        // Child Process
        // ===============================
        if(pid == 0)
        {
            printf("Child process created for client\n");

            close(ServerSocket); // Child does not need server socket

            // Read requested file name from client
            iRet = read(ClientSocket, FileName, sizeof(FileName));

            printf("Requested file : %s\n", FileName);

            // Remove newline characters
            FileName[strcspn(FileName, "\r\n")] = '\0';

            // Send file to client
            SendFileToClient(ClientSocket, FileName);

            close(ClientSocket);

            printf("File sent. Client disconnected\n");

            exit(0);  // Terminate child process
        }
        // ===============================
        // Parent Process
        // ===============================
        else
        {
            // Parent closes client socket and continues accepting others
            close(ClientSocket);
        }
    }

    close(ServerSocket);
    return 0;
}
