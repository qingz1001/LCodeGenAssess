#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FD 100
#define MAX_DOMAIN 26
#define MAX_DEPS 1000

typedef struct {
    char domains[MAX_DOMAIN];
} FD;

int find_domain_index(char *domain) {
    for (int i = 0; i < MAX_DOMAIN; i++) {
        if (domain[i] == '\0') return -1;
        if (domain[i] >= 'A' && domain[i] <= 'Z') return i;
    }
    return -1;
}

int contains_domain(char *domains, char target) {
    for (int i = 0; i < MAX_DOMAIN; i++) {
        if (domains[i] == target) return 1;
        if (domains[i] == '\0') break;
    }
    return 0;
}

void print_redundant_fds(FD fds[], int n) {
    int found = 0;
    for (int i = 0; i < n; i++) {
        int can_be_reduced = 1;
        for (int j = 0; j < n; j++) {
            if (i != j && contains_domain(fds[j].domains, fds[i].domains[0])) {
                can_be_reduced = 0;
                printf("FD %d is redundant using FDs: %d", i + 1, j + 1);
                for (int k = 0; k < n; k++) {
                    if (k != i && k != j && contains_domain(fds[k].domains, fds[j].domains[0])) {
                        printf(" %d", k + 1);
                    }
                }
                printf("\n");
                found = 1;
                break;
            }
        }
        if (!can_be_reduced) break;
    }
    if (!found) {
        printf("No redundant FDs\n");
    }
}

int main() {
    int n;
    scanf("%d", &n);
    FD fds[MAX_FD];
    for (int i = 0; i < n; i++) {
        scanf("%s", fds[i].domains);
    }
    print_redundant_fds(fds, n);
    return 0;
}