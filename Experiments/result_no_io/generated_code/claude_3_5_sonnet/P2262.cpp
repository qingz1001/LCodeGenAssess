#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME 100
#define MAX_PATH 1000
#define MAX_USERS 100
#define MAX_FILES 1000

typedef struct File {
    char name[MAX_NAME];
    long long size;
    int is_folder;
    int state; // 0: normal, 1: uploading
    struct File* parent;
    struct File* children[MAX_FILES];
    int child_count;
} File;

typedef struct User {
    char name[MAX_NAME];
    int type; // 1: upload, 2: download, 3: guest
    int state; // 0: idle, 1: downloading, 2: uploading
    File* position;
    long long remaining_size;
    File* target_file;
} User;

File* root;
User users[MAX_USERS];
int user_count = 0;
int max_user_number, max_server_flux, max_user_flux;

File* create_file(char* name, long long size, int is_folder, File* parent) {
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

void read_file_structure(File* current) {
    char name[MAX_NAME];
    long long size;
    while (1) {
        if (scanf("%s", name) == EOF || strcmp(name, "-") == 0) {
            return;
        }
        scanf("%lld", &size);
        File* new_file = create_file(name, size, size == 0, current);
        add_child(current, new_file);
        if (size == 0) {
            read_file_structure(new_file);
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
    if (user_count >= max_user_number || find_user(name) != NULL) {
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
    user->remaining_size = file->size;
    user->target_file = file;
    printf("success\n");
}

void upload(char* name, char* file_name, long long size) {
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
    if (size > 0) {
        user->state = 2;
        user->remaining_size = size;
        user->target_file = new_file;
        new_file->state = 1;
    }
    printf("success\n");
}

void process_command(char* name, char* command, char* arg1, char* arg2) {
    if (strcmp(command, "connect") == 0) {
        connect(name, atoi(arg1));
    } else if (strcmp(command, "quit") == 0) {
        quit(name);
    } else if (strcmp(command, "cd") == 0) {
        if (strcmp(arg1, "..") == 0) {
            cd_parent(name);
        } else {
            cd(name, arg1);
        }
    } else if (strcmp(command, "download") == 0) {
        download(name, arg1);
    } else if (strcmp(command, "upload") == 0) {
        upload(name, arg1, atoll(arg2));
    }
}

int main() {
    scanf("%d %d %d", &max_user_number, &max_server_flux, &max_user_flux);
    root = create_file("/", 0, 1, NULL);
    read_file_structure(root);

    int time;
    char name[MAX_NAME], command[MAX_NAME], arg1[MAX_NAME], arg2[MAX_NAME];
    while (1) {
        if (scanf("%d", &time) == EOF) break;
        scanf("%s %s", name, command);
        if (strcmp(command, "quit") == 0 || strcmp(command, "cd..") == 0) {
            process_command(name, command, NULL, NULL);
        } else if (strcmp(command, "connect") == 0 || strcmp(command, "cd") == 0 || strcmp(command, "download") == 0) {
            scanf("%s", arg1);
            process_command(name, command, arg1, NULL);
        } else if (strcmp(command, "upload") == 0) {
            scanf("%s %s", arg1, arg2);
            process_command(name, command, arg1, arg2);
        }
    }

    return 0;
}