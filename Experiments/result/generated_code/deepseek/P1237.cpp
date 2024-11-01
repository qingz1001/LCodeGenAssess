#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_DEPENDENCIES 100
#define MAX_DOMAIN_LENGTH 10

typedef struct {
    char lhs[MAX_DOMAIN_LENGTH];
    char rhs[MAX_DOMAIN_LENGTH];
} Dependency;

Dependency dependencies[MAX_DEPENDENCIES];
int n;

bool is_redundant(int idx, bool used[MAX_DEPENDENCIES], int path[MAX_DEPENDENCIES], int path_len) {
    char target[MAX_DOMAIN_LENGTH];
    strcpy(target, dependencies[idx].rhs);
    char current[MAX_DOMAIN_LENGTH];
    strcpy(current, dependencies[idx].lhs);

    for (int i = 0; i < n; i++) {
        if (used[i]) continue;
        if (strcmp(dependencies[i].lhs, current) == 0) {
            strcpy(current, dependencies[i].rhs);
            used[i] = true;
            path[path_len++] = i + 1;
            if (strcmp(current, target) == 0) {
                return true;
            }
            if (is_redundant(idx, used, path, path_len)) {
                return true;
            }
            used[i] = false;
            path_len--;
            strcpy(current, dependencies[idx].lhs);
        }
    }
    return false;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s->%s", dependencies[i].lhs, dependencies[i].rhs);
    }

    bool found_redundant = false;
    for (int i = 0; i < n; i++) {
        bool used[MAX_DEPENDENCIES] = {false};
        int path[MAX_DEPENDENCIES];
        int path_len = 0;
        if (is_redundant(i, used, path, path_len)) {
            found_redundant = true;
            printf("FD %d is redundant using FDs:", i + 1);
            for (int j = 0; j < path_len; j++) {
                printf(" %d", path[j]);
            }
            printf("\n");
        }
    }

    if (!found_redundant) {
        printf("No redundant FDs\n");
    }

    return 0;
}