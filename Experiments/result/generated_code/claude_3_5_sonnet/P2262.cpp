#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME 100
#define MAX_USERS 100
#define MAX_FILES 1000

typedef struct {
    char name[MAX_NAME];
    int size;
    int is_folder;
    int state; // 0: normal, 1: uploading
    struct File* parent;
    struct File* children[MAX_FILES];
    int child_count;
} File;

typedef struct {
    char name[MAX_NAME];
    int type; // 1: upload, 2: download, 3: guest
    int state; // 0: idle, 1: downloading, 2: uploading
    File* position;
} User;

int maxUserNumber, maxServerFlux, maxUserFlux;
User users[MAX_USERS];
int user_count = 0;
File* root;

File* create_file(char* name, int size, int is_folder, File* parent) {
    File* file = (File*)malloc(sizeof(File));
    strcpy(file->name, name);
    file->size = size;
    file->is_folder = is_folder;
    file->state = 0;
    file->parent = parent;
    file->child_count = 0;
    return file;
}

void add_child(File* parent, File* child) {
    parent->children[parent->child_count++] = child;
}

File* find_child(File* folder, char* name) {
    for (int i = 0; i < folder->child_count; i++) {
        if (strcmp(folder->children[i]->name, name) == 0) {
            return folder->children[i];
        }
    }
    return NULL;
}

void read_file_structure() {
    char name[MAX_NAME];
    int size;
    root = create_file("root", 0, 1, NULL);
    File* current = root;

    while (1) {
        if (scanf("%s", name) == EOF || strcmp(name, "-") == 0) {
            if (current == root) break;
            current = current->parent;
            continue;
        }

        scanf("%d", &size);
        File* new_file = create_file(name, size, size == 0, current);
        add_child(current, new_file);

        if (size == 0) {
            current = new_file;
        }
    }
}

User* find_user(char* name) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].name, name) == 0) {
            return &users[i];
        }
    }
    return NULL;
}

void connect(char* name, int type) {
    if (user_count >= maxUserNumber || find_user(name) != NULL) {
        printf("unsuccess\n");
        return;
    }

    User new_user;
    strcpy(new_user.name, name);
    new_user.type = type;
    new_user.state = 0;
    new_user.position = root;
    users[user_count++] = new_user;
    printf("success\n");
}

void quit(char* name) {
    User* user = find_user(name);
    if (user == NULL) {
        printf("unsuccess\n");
        return;
    }

    *user = users[--user_count];
    printf("success\n");
}

void cd(char* name, char* folder_name) {
    User* user = find_user(name);
    if (user == NULL) {
        printf("unsuccess\n");
        return;
    }

    File* folder = find_child(user->position, folder_name);
    if (folder == NULL || !folder->is_folder || folder->state == 1) {
        printf("unsuccess\n");
        return;
    }

    user->position = folder;
    printf("success\n");
}

void cd_parent(char* name) {
    User* user = find_user(name);
    if (user == NULL || user->position == root) {
        printf("unsuccess\n");
        return;
    }

    user->position = user->position->parent;
    printf("success\n");
}

void download(char* name, char* file_name) {
    User* user = find_user(name);
    if (user == NULL || user->type == 3) {
        printf("unsuccess\n");
        return;
    }

    File* file = find_child(user->position, file_name);
    if (file == NULL || file->state == 1) {
        printf("unsuccess\n");
        return;
    }

    user->state = 1;
    printf("success\n");
}

void upload(char* name, char* file_name, int size) {
    User* user = find_user(name);
    if (user == NULL || user->type != 1) {
        printf("unsuccess\n");
        return;
    }

    if (find_child(user->position, file_name) != NULL) {
        printf("unsuccess\n");
        return;
    }

    File* new_file = create_file(file_name, size, size == 0, user->position);
    add_child(user->position, new_file);
    user->state = 2;
    printf("success\n");
}

int main() {
    scanf("%d %d %d", &maxUserNumber, &maxServerFlux, &maxUserFlux);
    read_file_structure();

    int time;
    char command[MAX_NAME], name[MAX_NAME], param[MAX_NAME];
    int size;

    while (1) {
        scanf("%d", &time);
        scanf("%s %s", name, command);

        if (strcmp(command, "connect") == 0) {
            scanf("%d", &size);
            connect(name, size);
        } else if (strcmp(command, "quit") == 0) {
            quit(name);
        } else if (strcmp(command, "cd") == 0) {
            scanf("%s", param);
            if (strcmp(param, "..") == 0) {
                cd_parent(name);
            } else {
                cd(name, param);
            }
        } else if (strcmp(command, "download") == 0) {
            scanf("%s", param);
            download(name, param);
        } else if (strcmp(command, "upload") == 0) {
            scanf("%s %d", param, &size);
            upload(name, param, size);
        } else if (strcmp(command, "down") == 0) {
            break;
        }
    }

    return 0;
}