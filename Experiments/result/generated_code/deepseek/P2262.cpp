#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_SERVER_FLUX 10000000
#define MAX_USER_FLUX 1000000
#define MAX_FILE_SIZE 100000
#define MAX_FOLDER_SIZE 100000000

typedef enum {
    UPLOAD_USER,
    DOWNLOAD_USER,
    GUEST
} UserType;

typedef enum {
    SCAN,
    DOWNLOAD,
    UPLOAD
} UserState;

typedef enum {
    NORMAL,
    UPLOADING
} FileState;

typedef struct {
    char name[50];
    int size;
    FileState state;
} File;

typedef struct Folder {
    char name[50];
    int size;
    FileState state;
    struct Folder *parent;
    struct Folder *subfolders[100];
    File *files[100];
    int subfolder_count;
    int file_count;
} Folder;

typedef struct {
    char name[50];
    UserType type;
    UserState state;
    Folder *position;
    int flux;
    int remaining_size;
} User;

typedef struct {
    int max_user_number;
    int max_server_flux;
    int max_user_flux;
    Folder *root;
    User *users[MAX_USERS];
    int user_count;
    int current_server_flux;
} Server;

Folder* create_folder(char *name, Folder *parent) {
    Folder *folder = (Folder*)malloc(sizeof(Folder));
    strcpy(folder->name, name);
    folder->size = 0;
    folder->state = NORMAL;
    folder->parent = parent;
    folder->subfolder_count = 0;
    folder->file_count = 0;
    return folder;
}

File* create_file(char *name, int size) {
    File *file = (File*)malloc(sizeof(File));
    strcpy(file->name, name);
    file->size = size;
    file->state = NORMAL;
    return file;
}

User* create_user(char *name, UserType type) {
    User *user = (User*)malloc(sizeof(User));
    strcpy(user->name, name);
    user->type = type;
    user->state = SCAN;
    user->position = NULL;
    user->flux = 0;
    user->remaining_size = 0;
    return user;
}

Server* create_server(int max_user_number, int max_server_flux, int max_user_flux) {
    Server *server = (Server*)malloc(sizeof(Server));
    server->max_user_number = max_user_number;
    server->max_server_flux = max_server_flux;
    server->max_user_flux = max_user_flux;
    server->root = create_folder("root", NULL);
    server->user_count = 0;
    server->current_server_flux = 0;
    return server;
}

void add_file_to_folder(Folder *folder, File *file) {
    folder->files[folder->file_count++] = file;
    folder->size += file->size;
}

void add_folder_to_folder(Folder *parent, Folder *child) {
    parent->subfolders[parent->subfolder_count++] = child;
    parent->size += child->size;
}

int find_user(Server *server, char *name) {
    for (int i = 0; i < server->user_count; i++) {
        if (strcmp(server->users[i]->name, name) == 0) {
            return i;
        }
    }
    return -1;
}

Folder* find_folder(Folder *current, char *name) {
    if (strcmp(current->name, name) == 0) {
        return current;
    }
    for (int i = 0; i < current->subfolder_count; i++) {
        Folder *found = find_folder(current->subfolders[i], name);
        if (found) {
            return found;
        }
    }
    return NULL;
}

File* find_file(Folder *current, char *name) {
    for (int i = 0; i < current->file_count; i++) {
        if (strcmp(current->files[i]->name, name) == 0) {
            return current->files[i];
        }
    }
    for (int i = 0; i < current->subfolder_count; i++) {
        File *found = find_file(current->subfolders[i], name);
        if (found) {
            return found;
        }
    }
    return NULL;
}

void connect_user(Server *server, char *name, int type) {
    if (server->user_count >= server->max_user_number) {
        printf("unsuccess\n");
        return;
    }
    User *user = create_user(name, type == 1 ? UPLOAD_USER : (type == 2 ? DOWNLOAD_USER : GUEST));
    user->position = server->root;
    server->users[server->user_count++] = user;
    printf("success\n");
}

void quit_user(Server *server, char *name) {
    int index = find_user(server, name);
    if (index == -1) {
        printf("unsuccess\n");
        return;
    }
    free(server->users[index]);
    for (int i = index; i < server->user_count - 1; i++) {
        server->users[i] = server->users[i + 1];
    }
    server->user_count--;
    printf("success\n");
}

void cd_folder(Server *server, char *name, char *folder_name) {
    int index = find_user(server, name);
    if (index == -1) {
        printf("unsuccess\n");
        return;
    }
    Folder *current = server->users[index]->position;
    Folder *target = find_folder(current, folder_name);
    if (!target || target->state == UPLOADING) {
        printf("unsuccess\n");
        return;
    }
    server->users[index]->position = target;
    printf("success\n");
}

void cd_parent(Server *server, char *name) {
    int index = find_user(server, name);
    if (index == -1) {
        printf("unsuccess\n");
        return;
    }
    Folder *current = server->users[index]->position;
    if (!current->parent) {
        printf("unsuccess\n");
        return;
    }
    server->users[index]->position = current->parent;
    printf("success\n");
}

void download_file(Server *server, char *name, char *file_name) {
    int index = find_user(server, name);
    if (index == -1) {
        printf("unsuccess\n");
        return;
    }
    User *user = server->users[index];
    if (user->type != DOWNLOAD_USER) {
        printf("unsuccess\n");
        return;
    }
    Folder *current = user->position;
    File *file = find_file(current, file_name);
    if (!file || file->state == UPLOADING) {
        printf("unsuccess\n");
        return;
    }
    user->state = DOWNLOAD;
    user->remaining_size = file->size;
    printf("success\n");
}

void upload_file(Server *server, char *name, char *file_name, int size) {
    int index = find_user(server, name);
    if (index == -1) {
        printf("unsuccess\n");
        return;
    }
    User *user = server->users[index];
    if (user->type != UPLOAD_USER) {
        printf("unsuccess\n");
        return;
    }
    Folder *current = user->position;
    if (find_file(current, file_name) || find_folder(current, file_name)) {
        printf("unsuccess\n");
        return;
    }
    if (size > 0) {
        File *file = create_file(file_name, size);
        add_file_to_folder(current, file);
    } else {
        Folder *folder = create_folder(file_name, current);
        add_folder_to_folder(current, folder);
    }
    user->state = UPLOAD;
    user->remaining_size = size;
    printf("success\n");
}

void process_command(Server *server, int time, char *command) {
    char name[50], action[10], param1[50], param2[50];
    int type, size;
    if (sscanf(command, "%s %s %s %s", name, action, param1, param2) == 4) {
        size = atoi(param2);
        upload_file(server, name, param1, size);
    } else if (sscanf(command, "%s %s %s", name, action, param1) == 3) {
        if (strcmp(action, "connect") == 0) {
            type = atoi(param1);
            connect_user(server, name, type);
        } else if (strcmp(action, "download") == 0) {
            download_file(server, name, param1);
        } else if (strcmp(action, "cd") == 0) {
            cd_folder(server, name, param1);
        } else if (strcmp(action, "cd..") == 0) {
            cd_parent(server, name);
        }
    } else if (sscanf(command, "%s %s", name, action) == 2) {
        if (strcmp(action, "quit") == 0) {
            quit_user(server, name);
        }
    }
}

int main() {
    int max_user_number, max_server_flux, max_user_flux;
    scanf("%d %d %d", &max_user_number, &max_server_flux, &max_user_flux);
    Server *server = create_server(max_user_number, max_server_flux, max_user_flux);

    char line[200];
    while (1) {
        scanf("%s", line);
        if (strcmp(line, "down") == 0) break;
        int time = atoi(line);
        scanf("%s", line);
        process_command(server, time, line);
    }

    return 0;
}