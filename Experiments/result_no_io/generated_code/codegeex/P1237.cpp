#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FD 100
#define MAX_DOMAIN 10
#define MAX_SEQ 100

typedef struct {
    char left[MAX_DOMAIN];
    char right[MAX_DOMAIN];
} FD;

FD fds[MAX_FD];
int n;

void parseFD(char *line, FD *fd) {
    char *left, *right;
    left = strtok(line, "->");
    right = strtok(NULL, "->");
    strcpy(fd->left, left);
    strcpy(fd->right, right);
}

int isRedundant(int fdIndex) {
    FD fd = fds[fdIndex];
    char domain[MAX_DOMAIN];
    strcpy(domain, fd.left);
    strcat(domain, fd.right);
    for (int i = 0; i < n; i++) {
        if (i == fdIndex) continue;
        FD otherFD = fds[i];
        if (strstr(domain, otherFD.left) != NULL) {
            char newDomain[MAX_DOMAIN];
            strcpy(newDomain, domain);
            strreplace(newDomain, otherFD.left, otherFD.right);
            if (strstr(newDomain, fd.right) != NULL) {
                printf("FD %d is redundant using FDs: ", fdIndex + 1);
                for (int j = 0; j < n; j++) {
                    if (j == i) {
                        printf("%d ", j + 1);
                    } else if (strstr(newDomain, fds[j].left) != NULL) {
                        printf("%d ", j + 1);
                    }
                }
                printf("\n");
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        char line[100];
        scanf("%s", line);
        parseFD(line, &fds[i]);
    }

    int foundRedundant = 0;
    for (int i = 0; i < n; i++) {
        if (isRedundant(i)) {
            foundRedundant = 1;
        }
    }

    if (!foundRedundant) {
        printf("No redundant FDs\n");
    }

    return 0;
}

void strreplace(char *str, const char *oldSubstr, const char *newSubstr) {
    char buffer[256];
    const char *p = str;
    char *q = buffer;
    while (1) {
        const char *r = strstr(p, oldSubstr);
        if (r == NULL) {
            strcpy(q, p);
            break;
        }
        strncpy(q, p, r - p);
        q += r - p;
        strcpy(q, newSubstr);
        q += strlen(newSubstr);
        p = r + strlen(oldSubstr);
    }
    strcpy(str, buffer);
}