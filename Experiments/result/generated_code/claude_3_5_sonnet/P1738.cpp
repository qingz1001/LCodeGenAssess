#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 1000
#define MAX_LEN 101

char paths[MAX_N][MAX_LEN];
int folder_count = 0;

bool folder_exists(char *path) {
    for (int i = 0; i < folder_count; i++) {
        if (strcmp(paths[i], path) == 0) {
            return true;
        }
    }
    return false;
}

void add_folder(char *path) {
    strcpy(paths[folder_count], path);
    folder_count++;
}

int count_new_folders(char *path) {
    int new_folders = 0;
    char current_path[MAX_LEN] = "";
    char *token = strtok(path, "/");
    
    while (token != NULL) {
        strcat(current_path, "/");
        strcat(current_path, token);
        
        if (!folder_exists(current_path)) {
            add_folder(current_path);
            new_folders++;
        }
        
        token = strtok(NULL, "/");
    }
    
    return new_folders;
}

int main() {
    int N;
    scanf("%d", &N);
    
    for (int i = 0; i < N; i++) {
        char path[MAX_LEN];
        scanf("%s", path);
        printf("%d\n", count_new_folders(path));
    }
    
    return 0;
}