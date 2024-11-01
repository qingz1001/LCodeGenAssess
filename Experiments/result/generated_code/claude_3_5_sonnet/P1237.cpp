#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_FDS 100
#define MAX_CHARS 26

typedef struct {
    bool left[MAX_CHARS];
    bool right[MAX_CHARS];
} FunctionalDependency;

FunctionalDependency fds[MAX_FDS];
int n;

void parse_fd(char* line, FunctionalDependency* fd) {
    memset(fd->left, 0, sizeof(fd->left));
    memset(fd->right, 0, sizeof(fd->right));
    
    char* arrow = strstr(line, "->");
    *arrow = '\0';
    
    for (char* c = line; *c; c++) {
        fd->left[*c - 'A'] = true;
    }
    
    for (char* c = arrow + 2; *c; c++) {
        fd->right[*c - 'A'] = true;
    }
}

bool closure(bool* attrs) {
    bool changed = true;
    while (changed) {
        changed = false;
        for (int i = 0; i < n; i++) {
            bool applies = true;
            for (int j = 0; j < MAX_CHARS; j++) {
                if (fds[i].left[j] && !attrs[j]) {
                    applies = false;
                    break;
                }
            }
            if (applies) {
                for (int j = 0; j < MAX_CHARS; j++) {
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

void find_redundant() {
    bool found_redundant = false;
    
    for (int i = 0; i < n; i++) {
        bool attrs[MAX_CHARS] = {0};
        for (int j = 0; j < MAX_CHARS; j++) {
            attrs[j] = fds[i].left[j];
        }
        
        FunctionalDependency temp = fds[i];
        fds[i] = fds[n-1];
        
        closure(attrs);
        
        bool redundant = true;
        for (int j = 0; j < MAX_CHARS; j++) {
            if (temp.right[j] && !attrs[j]) {
                redundant = false;
                break;
            }
        }
        
        if (redundant) {
            found_redundant = true;
            printf("FD %d is redundant using FDs:", i + 1);
            for (int j = 0; j < n - 1; j++) {
                if (j != i) {
                    printf(" %d", j + 1);
                }
            }
            printf("\n");
        }
        
        fds[i] = temp;
    }
    
    if (!found_redundant) {
        printf("No redundant FDs\n");
    }
}

int main() {
    scanf("%d", &n);
    getchar();  // consume newline
    
    char line[100];
    for (int i = 0; i < n; i++) {
        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\n")] = 0;  // remove newline
        parse_fd(line, &fds[i]);
    }
    
    find_redundant();
    
    return 0;
}