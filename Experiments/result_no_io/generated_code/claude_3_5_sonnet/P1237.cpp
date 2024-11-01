#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_FDS 100
#define MAX_DOMAINS 26

typedef struct {
    bool left[MAX_DOMAINS];
    bool right[MAX_DOMAINS];
} FunctionalDependency;

FunctionalDependency fds[MAX_FDS];
int n;

void parse_fd(char* line, FunctionalDependency* fd) {
    memset(fd->left, 0, sizeof(fd->left));
    memset(fd->right, 0, sizeof(fd->right));
    
    char* token = strtok(line, "->");
    for (int i = 0; token[i]; i++) {
        if (token[i] >= 'A' && token[i] <= 'Z') {
            fd->left[token[i] - 'A'] = true;
        }
    }
    
    token = strtok(NULL, "->");
    for (int i = 0; token[i]; i++) {
        if (token[i] >= 'A' && token[i] <= 'Z') {
            fd->right[token[i] - 'A'] = true;
        }
    }
}

bool closure(bool* attrs, int fd_count) {
    bool changed = true;
    while (changed) {
        changed = false;
        for (int i = 0; i < fd_count; i++) {
            bool applicable = true;
            for (int j = 0; j < MAX_DOMAINS; j++) {
                if (fds[i].left[j] && !attrs[j]) {
                    applicable = false;
                    break;
                }
            }
            if (applicable) {
                for (int j = 0; j < MAX_DOMAINS; j++) {
                    if (fds[i].right[j] && !attrs[j]) {
                        attrs[j] = true;
                        changed = true;
                    }
                }
            }
        }
    }
    return changed;
}

void find_redundant_fds() {
    bool redundant_found = false;
    
    for (int i = 0; i < n; i++) {
        bool attrs[MAX_DOMAINS] = {0};
        for (int j = 0; j < MAX_DOMAINS; j++) {
            attrs[j] = fds[i].left[j];
        }
        
        closure(attrs, i);
        closure(attrs, n);
        
        bool is_redundant = true;
        for (int j = 0; j < MAX_DOMAINS; j++) {
            if (fds[i].right[j] && !attrs[j]) {
                is_redundant = false;
                break;
            }
        }
        
        if (is_redundant) {
            redundant_found = true;
            printf("FD %d is redundant using FDs:", i + 1);
            for (int j = 0; j < i; j++) {
                bool applicable = true;
                for (int k = 0; k < MAX_DOMAINS; k++) {
                    if (fds[j].left[k] && !attrs[k]) {
                        applicable = false;
                        break;
                    }
                }
                if (applicable) {
                    printf(" %d", j + 1);
                }
            }
            printf("\n");
        }
    }
    
    if (!redundant_found) {
        printf("No redundant FDs\n");
    }
}

int main() {
    scanf("%d", &n);
    getchar();  // Consume newline
    
    char line[100];
    for (int i = 0; i < n; i++) {
        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\n")] = 0;  // Remove newline
        parse_fd(line, &fds[i]);
    }
    
    find_redundant_fds();
    
    return 0;
}