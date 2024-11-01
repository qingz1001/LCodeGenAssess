#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct FileNode {
    char name[51];
    long size;
    int is_folder;
    char state[11];
    struct FileNode *parent;
    struct FileNode *children;
    struct FileNode *next;
} FileNode;

typedef struct User {
    char name[51];
    int type;
    int connected;
    FileNode *position;
    struct User *next;
} User;

typedef struct Operation {
    char user_name[51];
    int type; // 1: download, 2: upload
    FileNode *target;
    long remaining;
    struct Operation *next;
} Operation;

FileNode *root = NULL;
User *users = NULL;
Operation *operations = NULL;
int maxUserNumber, maxServerFlux, maxUserFlux;
long current_flux = 0;
int current_users = 0;

FileNode* create_filenode(char *name, long size, FileNode *parent) {
    FileNode *node = (FileNode*)malloc(sizeof(FileNode));
    strcpy(node->name, name);
    node->size = size;
    node->is_folder = (size == 0) ? 1 : 0;
    strcpy(node->state, "normal");
    node->parent = parent;
    node->children = NULL;
    node->next = NULL;
    return node;
}

void add_child(FileNode *parent, FileNode *child) {
    if (!parent->children) {
        parent->children = child;
    }
    else {
        FileNode *temp = parent->children;
        while (temp->next) temp = temp->next;
        temp->next = child;
    }
}

FileNode* parse_files(FILE *fp, FileNode *parent) {
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        if (strcmp(line, "-\n") == 0)
            return parent;
        char name[51];
        long size;
        sscanf(line, "%s %ld", name, &size);
        FileNode *node = create_filenode(name, size, parent);
        add_child(parent, node);
        if (node->is_folder) {
            parse_files(fp, node);
        }
    }
    return parent;
}

User* find_user(char *name) {
    User *temp = users;
    while (temp) {
        if (strcmp(temp->name, name) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

FileNode* find_in_folder(FileNode *folder, char *name) {
    FileNode *temp = folder->children;
    while (temp) {
        if (strcmp(temp->name, name) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

int main(){
    // Read initial server info
    scanf("%d %d %d", &maxUserNumber, &maxServerFlux, &maxUserFlux);
    // Read file system
    root = create_filenode("root", 0, NULL);
    parse_files(stdin, root);
    // Read commands
    char cmd_line[256];
    struct {
        int time;
        char user[51];
        char command[20];
        char arg1[51];
        char arg2[51];
    } commands[10000];
    int cmd_cnt = 0;
    while (fgets(cmd_line, sizeof(cmd_line), stdin)) {
        if (strcmp(cmd_line, "down\n") == 0)
            break;
        int time;
        char user[51], command[20], arg1[51], arg2[51];
        int num = sscanf(cmd_line, "%d %s %s %s", &time, user, command, arg1);
        if (num < 3) {
            sscanf(cmd_line, "%d %s %s", &time, user, command);
            arg1[0] = '\0';
            arg2[0] = '\0';
        }
        else {
            if (strcmp(command, "upload") == 0) {
                sscanf(cmd_line, "%d %s %s %s %s", &time, user, command, arg1, arg2);
            }
            else {
                arg2[0] = '\0';
            }
        }
        strcpy(commands[cmd_cnt].user, user);
        strcpy(commands[cmd_cnt].command, command);
        strcpy(commands[cmd_cnt].arg1, arg1);
        strcpy(commands[cmd_cnt].arg2, arg2);
        commands[cmd_cnt].time = time;
        cmd_cnt++;
    }
    // Process commands
    int current_time = 0;
    for(int i=0;i<cmd_cnt;i++){
        // Advance time and process operations
        while(current_time < commands[i].time){
            current_time++;
            // Process operations
            Operation *op = operations, *prev = NULL;
            while(op){
                long flux = (current_users >0) ? (maxServerFlux / current_users) : maxUserFlux;
                if(flux > maxUserFlux) flux = maxUserFlux;
                long transfer = (flux > op->remaining) ? 1 : 1;
                op->remaining -= flux;
                if(op->remaining <=0){
                    // Operation complete
                    if(op->type ==2){
                        // Upload
                        strcpy(op->target->state, "normal");
                    }
                    // Remove operation
                    if(prev){
                        prev->next = op->next;
                        free(op);
                        op = prev->next;
                    }
                    else{
                        operations = op->next;
                        free(op);
                        op = operations;
                    }
                    current_users--;
                }
                else{
                    prev = op;
                    op = op->next;
                }
            }
        }
        current_time = commands[i].time;
        // Execute command
        char *user = commands[i].user;
        char *command = commands[i].command;
        char *arg1 = commands[i].arg1;
        char *arg2 = commands[i].arg2;
        if(strcmp(command, "connect")==0){
            int type = atoi(arg1);
            User *u = find_user(user);
            if(!u && current_users < maxUserNumber){
                // Connect
                User *newu = (User*)malloc(sizeof(User));
                strcpy(newu->name, user);
                newu->type = type;
                newu->connected = 1;
                newu->position = root;
                newu->next = users;
                users = newu;
                current_users++;
                printf("success\n");
            }
            else{
                printf("unsuccess\n");
            }
        }
        else if(strcmp(command, "quit")==0){
            User *u = find_user(user);
            if(u){
                // Remove user
                User *temp = users, *prevu = NULL;
                while(temp){
                    if(strcmp(temp->name, user)==0){
                        if(prevu){
                            prevu->next = temp->next;
                        }
                        else{
                            users = temp->next;
                        }
                        free(temp);
                        current_users--;
                        break;
                    }
                    prevu = temp;
                    temp = temp->next;
                }
                printf("success\n");
            }
            else{
                printf("unsuccess\n");
            }
        }
        else if(strcmp(command, "cd")==0){
            User *u = find_user(user);
            if(u){
                FileNode *target = find_in_folder(u->position, arg1);
                if(target && target->is_folder && strcmp(target->state, "normal")==0){
                    u->position = target;
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
        else if(strcmp(command, "cd..")==0 || strcmp(command, "cd..!") ==0){
            User *u = find_user(user);
            if(u && u->position->parent){
                u->position = u->position->parent;
                printf("success\n");
            }
            else{
                printf("unsuccess\n");
            }
        }
        else if(strcmp(command, "download")==0){
            User *u = find_user(user);
            if(u && u->type !=1){
                FileNode *target = find_in_folder(u->position, arg1);
                if(target && strcmp(target->state, "normal")==0){
                    // Start download
                    Operation *newop = (Operation*)malloc(sizeof(Operation));
                    strcpy(newop->user_name, user);
                    newop->type =1;
                    newop->target = target;
                    newop->remaining = target->size;
                    newop->next = operations;
                    operations = newop;
                    current_users++;
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
        else if(strcmp(command, "upload")==0){
            User *u = find_user(user);
            if(u && u->type ==1){
                FileNode *existing = find_in_folder(u->position, arg1);
                if(!existing){
                    // Create new file
                    FileNode *newf = create_filenode(arg1, atol(arg2), u->position);
                    strcpy(newf->state, "uploading");
                    add_child(u->position, newf);
                    // Start upload
                    Operation *newop = (Operation*)malloc(sizeof(Operation));
                    strcpy(newop->user_name, user);
                    newop->type =2;
                    newop->target = newf;
                    newop->remaining = newf->size;
                    newop->next = operations;
                    operations = newop;
                    current_users++;
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
        else{
            printf("unsuccess\n");
        }
    }
    return 0;
}