#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USER_NUMBER 100
#define MAX_SERVER_FLUX 10000000
#define MAX_USER_FLUX 1000000

typedef enum {
    NORMAL,
    UPLOADING
} State;

typedef struct FileOrFolder {
    char name[100];
    int size;
    State state;
    struct FileOrFolder *children[MAX_USER_NUMBER];
    int childCount;
} FileOrFolder;

typedef struct User {
    char name[100];
    int userType;
    int userState;
    FileOrFolder *userPosition;
} User;

FileOrFolder root;
User users[MAX_USER_NUMBER];
int userCount = 0;

void initRoot() {
    strcpy(root.name, "/");
    root.size = 0;
    root.state = NORMAL;
    root.childCount = 0;
}

void addFileOrFolder(FileOrFolder *parent, const char *name, int size) {
    for (int i = 0; i < parent->childCount; i++) {
        if (strcmp(parent->children[i]->name, name) == 0) {
            return;
        }
    }
    FileOrFolder *newItem = (FileOrFolder *)malloc(sizeof(FileOrFolder));
    strcpy(newItem->name, name);
    newItem->size = size;
    newItem->state = NORMAL;
    newItem->childCount = 0;
    parent->children[parent->childCount++] = newItem;
}

void parseInput() {
    scanf("%d %d %d", &root.maxUserNumber, &root.maxServerFlux, &root.maxUserFlux);

    char line[1000];
    fgets(line, sizeof(line), stdin);
    while (fgets(line, sizeof(line), stdin)) {
        if (line[0] == '-') break;
        char *token = strtok(line, " ");
        char *name = token;
        token = strtok(NULL, " ");
        int size = atoi(token);
        addFileOrFolder(&root, name, size);
    }

    int time;
    char order[100];
    while (scanf("%d %s", &time, order) != EOF) {
        if (strcmp(order, "down") == 0) break;
        // Process the command here
    }
}

int main() {
    initRoot();
    parseInput();
    return 0;
}