#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_NAME_LEN 50
#define MAX_COMMAND_LEN 100

typedef struct {
    char name[MAX_NAME_LEN];
    int type; // 1: uploadUser, 2: downloadUser, 3: guest
    int state; // 0: idle, 1: scanning, 2: downloading, 3: uploading
    char position[MAX_NAME_LEN];
    int flux;
} User;

typedef struct {
    char name[MAX_NAME_LEN];
    int size;
    int state; // 0: normal, 1: uploading
    struct Node* children;
    struct Node* parent;
} Node;

typedef struct {
    int maxUserNumber;
    int maxServerFlux;
    int maxUserFlux;
    int currentFlux;
    int userCount;
    User users[MAX_USERS];
    Node* root;
} Server;

Server server;

Node* createNode(char* name, int size, Node* parent) {
    Node* node = (Node*)malloc(sizeof(Node));
    strcpy(node->name, name);
    node->size = size;
    node->state = 0;
    node->children = NULL;
    node->parent = parent;
    return node;
}

void addChild(Node* parent, Node* child) {
    if (parent->children == NULL) {
        parent->children = child;
    } else {
        Node* temp = parent->children;
        while (temp->children != NULL) {
            temp = temp->children;
        }
        temp->children = child;
    }
}

User* findUser(char* name) {
    for (int i = 0; i < server.userCount; i++) {
        if (strcmp(server.users[i].name, name) == 0) {
            return &server.users[i];
        }
    }
    return NULL;
}

Node* findNode(Node* current, char* name) {
    if (current == NULL) return NULL;
    if (strcmp(current->name, name) == 0) return current;
    Node* temp = current->children;
    while (temp != NULL) {
        Node* result = findNode(temp, name);
        if (result != NULL) return result;
        temp = temp->children;
    }
    return NULL;
}

void connectUser(char* name, int type) {
    if (server.userCount >= server.maxUserNumber) {
        printf("unsuccess\n");
        return;
    }
    User* user = findUser(name);
    if (user != NULL) {
        printf("unsuccess\n");
        return;
    }
    User newUser;
    strcpy(newUser.name, name);
    newUser.type = type;
    newUser.state = 0;
    strcpy(newUser.position, "/");
    newUser.flux = 0;
    server.users[server.userCount++] = newUser;
    printf("success\n");
}

void quitUser(char* name) {
    User* user = findUser(name);
    if (user == NULL) {
        printf("unsuccess\n");
        return;
    }
    for (int i = 0; i < server.userCount; i++) {
        if (strcmp(server.users[i].name, name) == 0) {
            for (int j = i; j < server.userCount - 1; j++) {
                server.users[j] = server.users[j + 1];
            }
            server.userCount--;
            break;
        }
    }
    printf("success\n");
}

void cd(char* name, char* folderName) {
    User* user = findUser(name);
    if (user == NULL) {
        printf("unsuccess\n");
        return;
    }
    Node* current = findNode(server.root, user->position);
    Node* target = findNode(current, folderName);
    if (target == NULL || target->size != 0 || target->state != 0) {
        printf("unsuccess\n");
        return;
    }
    strcpy(user->position, target->name);
    printf("success\n");
}

void cdParent(char* name) {
    User* user = findUser(name);
    if (user == NULL) {
        printf("unsuccess\n");
        return;
    }
    Node* current = findNode(server.root, user->position);
    if (current == NULL || current->parent == NULL) {
        printf("unsuccess\n");
        return;
    }
    strcpy(user->position, current->parent->name);
    printf("success\n");
}

void download(char* name, char* fileName) {
    User* user = findUser(name);
    if (user == NULL || user->type != 2) {
        printf("unsuccess\n");
        return;
    }
    Node* current = findNode(server.root, user->position);
    Node* target = findNode(current, fileName);
    if (target == NULL || target->state != 0) {
        printf("unsuccess\n");
        return;
    }
    user->state = 2;
    user->flux = target->size;
    printf("success\n");
}

void upload(char* name, char* fileName, int size) {
    User* user = findUser(name);
    if (user == NULL || user->type != 1) {
        printf("unsuccess\n");
        return;
    }
    Node* current = findNode(server.root, user->position);
    Node* target = findNode(current, fileName);
    if (target != NULL) {
        printf("unsuccess\n");
        return;
    }
    Node* newNode = createNode(fileName, size, current);
    addChild(current, newNode);
    user->state = 3;
    user->flux = size;
    printf("success\n");
}

void processCommand(int time, char* command) {
    char name[MAX_NAME_LEN], action[MAX_COMMAND_LEN], arg1[MAX_NAME_LEN], arg2[MAX_NAME_LEN];
    int type, size;
    if (sscanf(command, "%s %s %s %s", name, action, arg1, arg2) == 4) {
        size = atoi(arg2);
        if (strcmp(action, "upload") == 0) {
            upload(name, arg1, size);
        }
    } else if (sscanf(command, "%s %s %s", name, action, arg1) == 3) {
        if (strcmp(action, "connect") == 0) {
            type = atoi(arg1);
            connectUser(name, type);
        } else if (strcmp(action, "download") == 0) {
            download(name, arg1);
        } else if (strcmp(action, "cd") == 0) {
            cd(name, arg1);
        }
    } else if (sscanf(command, "%s %s", name, action) == 2) {
        if (strcmp(action, "quit") == 0) {
            quitUser(name);
        } else if (strcmp(action, "cd..") == 0) {
            cdParent(name);
        }
    }
}

void readServerInfo() {
    scanf("%d %d %d", &server.maxUserNumber, &server.maxServerFlux, &server.maxUserFlux);
    server.currentFlux = 0;
    server.userCount = 0;
    server.root = createNode("/", 0, NULL);

    char line[MAX_COMMAND_LEN];
    while (fgets(line, sizeof(line), stdin)) {
        if (strcmp(line, "-\n") == 0) break;
        char name[MAX_NAME_LEN];
        int size;
        sscanf(line, "%s %d", name, &size);
        Node* newNode = createNode(name, size, server.root);
        addChild(server.root, newNode);
    }
}

void readCommands() {
    char line[MAX_COMMAND_LEN];
    while (fgets(line, sizeof(line), stdin)) {
        if (strcmp(line, "down\n") == 0) break;
        int time;
        char command[MAX_COMMAND_LEN];
        sscanf(line, "%d %[^\n]", &time, command);
        processCommand(time, command);
    }
}

int main() {
    readServerInfo();
    readCommands();
    return 0;
}