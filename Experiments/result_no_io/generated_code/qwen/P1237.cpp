#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DEPS 100
#define MAX_VARS 26
#define MAX_LEN 50

typedef struct {
    char vars[MAX_LEN];
} Dependency;

int is_redundant(Dependency deps[], int n, int i) {
    for (int j = 0; j < n; j++) {
        if (j != i && !strcmp(deps[j].vars, deps[i].vars)) {
            return 1;
        }
    }
    return 0;
}

void find_redundant_deps(Dependency deps[], int n) {
    int redundant[MAX_DEPS] = {0};
    int count = 0;

    for (int i = 0; i < n; i++) {
        if (!redundant[i] && is_redundant(deps, n, i)) {
            redundant[i] = 1;
            count++;
        }
    }

    if (count == 0) {
        printf("No redundant FDs\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        if (redundant[i]) {
            printf("FD %d is redundant using FDs: ", i + 1);
            for (int j = 0; j < n; j++) {
                if (i != j && !strcmp(deps[j].vars, deps[i].vars)) {
                    printf("%d ", j + 1);
                    break;
                }
            }
            printf("\n");
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    Dependency deps[MAX_DEPS];

    for (int i = 0; i < n; i++) {
        scanf("%s", deps[i].vars);
    }

    find_redundant_deps(deps, n);

    return 0;
}