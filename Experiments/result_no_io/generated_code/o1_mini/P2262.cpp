#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_NAME 50
#define MAX_COMMANDS 10000

typedef enum {UPLOAD_USER, DOWNLOAD_USER, GUEST} UserType;
typedef enum {SCAN, DOWNLOAD, UPLOAD} UserStateType;
typedef enum {NORMAL, UPLOADING} FileState;
typedef enum {CONNECT, QUIT, CD, CD_BACK, DOWNLOAD_CMD, UPLOAD_CMD} CommandType;

typedef struct FileNode {
    char name[MAX_NAME];
    long size;
    FileState state;
    int is_folder;
    struct FileNode *parent;
    struct FileNode *child;
    struct FileNode *sibling;
} FileNode;

typedef struct User {
    char name[MAX_NAME];
    int is_connected;
    UserType type;
    UserStateType state;
    FileNode *position;
    long flux_remaining;
    long user_flux;
    int busy;
} User;

typedef struct Command {
    int time;
    char user_name[MAX_NAME];
    CommandType type;
    char param1[MAX_NAME];
    long param2;
} Command;

FileNode* create_file_node(char *name, long size, FileState state, int is_folder) {
    FileNode* node = (FileNode*)malloc(sizeof(FileNode));
    strcpy(node->name, name);
    node->size = size;
    node->state = state;
    node->is_folder = is_folder;
    node->parent = NULL;
    node->child = NULL;
    node->sibling = NULL;
    return node;
}

FileNode* build_file_system() {
    char name[MAX_NAME];
    long size;
    if (scanf("%s %ld", name, &size) != 2) return NULL;
    FileNode* root = create_file_node(name, size, NORMAL, size == 0 ? 1 : 0);
    if (root->is_folder) {
        FileNode* current = root;
        FileNode* stack[1000];
        int top = -1;
        while (1) {
            if (scanf("%s", name) != 1) break;
            if (strcmp(name, "-") == 0) {
                if (top >= 0) {
                    current = stack[top--];
                } else {
                    break;
                }
            } else {
                scanf("%ld", &size);
                int is_folder = size == 0 ? 1 : 0;
                FileNode* new_node = create_file_node(name, size, NORMAL, is_folder);
                new_node->parent = current;
                if (current->child == NULL) {
                    current->child = new_node;
                } else {
                    FileNode* tmp = current->child;
                    while (tmp->sibling) tmp = tmp->sibling;
                    tmp->sibling = new_node;
                }
                if (is_folder) {
                    stack[++top] = current;
                    current = new_node;
                }
            }
        }
    }
    return root;
}

int main(){
    int maxUserNumber, maxServerFlux, maxUserFlux;
    scanf("%d %d %d", &maxUserNumber, &maxServerFlux, &maxUserFlux);
    FileNode* root = build_file_system();
    Command commands[MAX_COMMANDS];
    int cmd_count = 0;
    while(1){
        char line[256];
        if (scanf("%s", line) != 1) break;
        if (strcmp(line, "down") == 0) break;
        commands[cmd_count].time = atoi(line);
        scanf("%s", commands[cmd_count].user_name);
        char cmd[20];
        scanf("%s", cmd);
        if(strcmp(cmd, "connect") == 0){
            commands[cmd_count].type = CONNECT;
            scanf("%s", commands[cmd_count].param1);
        }
        else if(strcmp(cmd, "quit") == 0){
            commands[cmd_count].type = QUIT;
        }
        else if(strcmp(cmd, "cd") == 0){
            scanf("%s", commands[cmd_count].param1);
            if(strcmp(commands[cmd_count].param1, "..") == 0){
                commands[cmd_count].type = CD_BACK;
            }
            else{
                commands[cmd_count].type = CD;
            }
        }
        else if(strcmp(cmd, "download") == 0){
            commands[cmd_count].type = DOWNLOAD_CMD;
            scanf("%s", commands[cmd_count].param1);
        }
        else if(strcmp(cmd, "upload") == 0){
            commands[cmd_count].type = UPLOAD_CMD;
            scanf("%s %ld", commands[cmd_count].param1, &commands[cmd_count].param2);
        }
        cmd_count++;
    }
    User users[MAX_USERS];
    int user_total = 0;
    for(int i=0;i<cmd_count;i++){
        Command cmd = commands[i];
        // Find user
        int user_idx = -1;
        for(int j=0;j<user_total;j++) if(strcmp(users[j].name, cmd.user_name)==0){user_idx=j; break;}
        if(cmd.type == CONNECT){
            if(user_idx == -1){
                if(user_total < maxUserNumber){
                    strcpy(users[user_total].name, cmd.user_name);
                    users[user_total].is_connected = 1;
                    int type = atoi(cmd.param1);
                    users[user_total].type = type == 1 ? UPLOAD_USER : (type ==2 ? DOWNLOAD_USER : GUEST);
                    users[user_total].position = root;
                    users[user_total].busy = 0;
                    users[user_total].flux_remaining = 0;
                    user_total++;
                    printf("success\n");
                }
                else{
                    printf("unsuccess\n");
                }
            }
            else{
                printf("unsuccess\n");
            }
        }
        else if(cmd.type == QUIT){
            if(user_idx == -1 || users[user_idx].is_connected == 0){
                printf("unsuccess\n");
            }
            else{
                users[user_idx].is_connected = 0;
                printf("success\n");
            }
        }
        else{
            if(user_idx == -1 || users[user_idx].is_connected == 0){
                printf("unsuccess\n");
                continue;
            }
            User* user = &users[user_idx];
            if(cmd.type == CD){
                FileNode* child = user->position->child;
                while(child){
                    if(strcmp(child->name, cmd.param1)==0 && child->is_folder && child->state == NORMAL){
                        user->position = child;
                        break;
                    }
                    child = child->sibling;
                }
                if(child){
                    printf("success\n");
                }
                else{
                    printf("unsuccess\n");
                }
            }
            else if(cmd.type == CD_BACK){
                if(user->position->parent){
                    user->position = user->position->parent;
                    printf("success\n");
                }
                else{
                    printf("unsuccess\n");
                }
            }
            else{
                if(cmd.type == DOWNLOAD_CMD){
                    // Not implemented
                    printf("unsuccess\n");
                }
                else if(cmd.type == UPLOAD_CMD){
                    // Not implemented
                    printf("unsuccess\n");
                }
            }
        }
    }
    return 0;
}