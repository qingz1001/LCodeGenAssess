#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USER_NUMBER 100
#define MAX_SERVER_FLUX 10000000
#define MAX_USER_FLUX 1000000
#define MAX_COMMAND_LENGTH 100

typedef struct User {
    char name[50];
    int userType;
    int userState;
    int userPosition;
} User;

typedef struct File {
    char fileName[50];
    int fileSize;
    int fileState;
} File;

typedef struct Folder {
    char folderName[50];
    int folderSize;
    int folderState;
    struct Folder *parent;
    struct File *files;
    struct Folder *folders;
} Folder;

typedef struct Command {
    int time;
    char name[50];
    char command[50];
    char parameter[50];
} Command;

int maxUserNumber, maxServerFlux, maxUserFlux;
int userTotal = 0;
User users[MAX_USER_NUMBER];
Folder *root;
Command commands[1000];
int commandCount = 0;

void parseInput() {
    int i;
    scanf("%d %d %d", &maxUserNumber, &maxServerFlux, &maxUserFlux);
    root = (Folder *)malloc(sizeof(Folder));
    root->parent = NULL;
    root->files = NULL;
    root->folders = NULL;
    root->folderSize = 0;
    root->folderState = 0;
    while (1) {
        char name[50];
        int size;
        scanf("%s %d", name, &size);
        if (size == 0) {
            Folder *newFolder = (Folder *)malloc(sizeof(Folder));
            strcpy(newFolder->folderName, name);
            newFolder->folderSize = 0;
            newFolder->folderState = 0;
            newFolder->parent = root;
            newFolder->files = NULL;
            newFolder->folders = NULL;
            root->folders = newFolder;
        } else {
            File *newFile = (File *)malloc(sizeof(File));
            strcpy(newFile->fileName, name);
            newFile->fileSize = size;
            newFile->fileState = 0;
            root->files = newFile;
        }
        char line[100];
        fgets(line, 100, stdin);
        if (line[0] == '-') {
            break;
        }
    }
    while (1) {
        Command newCommand;
        scanf("%d %s %s %s", &newCommand.time, newCommand.name, newCommand.command, newCommand.parameter);
        if (strcmp(newCommand.command, "down") == 0) {
            break;
        }
        commands[commandCount++] = newCommand;
    }
}

int main() {
    parseInput();
    for (int i = 0; i < commandCount; i++) {
        Command currentCommand = commands[i];
        if (strcmp(currentCommand.command, "connect") == 0) {
            if (userTotal < maxUserNumber) {
                User newUser;
                strcpy(newUser.name, currentCommand.name);
                newUser.userType = atoi(currentCommand.parameter);
                newUser.userState = 0;
                newUser.userPosition = 0;
                users[userTotal++] = newUser;
                printf("success\n");
            } else {
                printf("unsuccess\n");
            }
        } else if (strcmp(currentCommand.command, "quit") == 0) {
            int userIndex = -1;
            for (int j = 0; j < userTotal; j++) {
                if (strcmp(users[j].name, currentCommand.name) == 0) {
                    userIndex = j;
                    break;
                }
            }
            if (userIndex != -1) {
                userTotal--;
                for (int j = userIndex; j < userTotal; j++) {
                    users[j] = users[j + 1];
                }
                printf("success\n");
            } else {
                printf("unsuccess\n");
            }
        } else if (strcmp(currentCommand.command, "cd") == 0) {
            // TODO: Implement cd command
        } else if (strcmp(currentCommand.command, "cd..") == 0) {
            // TODO: Implement cd.. command
        } else if (strcmp(currentCommand.command, "download") == 0) {
            // TODO: Implement download command
        } else if (strcmp(currentCommand.command, "upload") == 0) {
            // TODO: Implement upload command
        }
    }
    return 0;
}