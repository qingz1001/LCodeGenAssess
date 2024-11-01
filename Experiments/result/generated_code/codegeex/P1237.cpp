#include <stdio.h>
#include <string.h>

#define MAX_LEN 100
#define MAX_FD 100

typedef struct {
    char left[MAX_LEN];
    char right[MAX_LEN];
} FD;

FD fds[MAX_FD];
int n;

void parse_input() {
    char line[MAX_LEN];
    fgets(line, MAX_LEN, stdin);
    sscanf(line, "%d", &n);
    for (int i = 0; i < n; i++) {
        fgets(line, MAX_LEN, stdin);
        sscanf(line, "%[^->]->%s", fds[i].left, fds[i].right);
    }
}

int is_redundant(int fd_index) {
    char left[MAX_LEN];
    strcpy(left, fds[fd_index].left);
    char right[MAX_LEN];
    strcpy(right, fds[fd_index].right);
    
    for (int i = 0; i < n; i++) {
        if (i == fd_index) continue;
        char temp_left[MAX_LEN];
        strcpy(temp_left, left);
        char temp_right[MAX_LEN];
        strcpy(temp_right, fds[i].right);
        
        if (strstr(temp_left, temp_right) != NULL) {
            char *ptr = strtok(temp_left, temp_right);
            if (ptr == NULL) {
                strcpy(left, temp_right);
            } else {
                strcpy(left, ptr);
            }
            strcat(left, fds[i].left);
        }
    }
    
    if (strstr(left, right) != NULL) {
        return 1;
    }
    return 0;
}

void find_redundant_fds() {
    for (int i = 0; i < n; i++) {
        if (is_redundant(i)) {
            printf("FD %d is redundant using FDs: ", i + 1);
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                if (strstr(fds[j].right, fds[i].right) != NULL) {
                    printf("%d ", j + 1);
                }
            }
            printf("\n");
        }
    }
    
    if (n > 0 && is_redundant(0) == 0) {
        printf("No redundant FDs\n");
    }
}

int main() {
    parse_input();
    find_redundant_fds();
    return 0;
}