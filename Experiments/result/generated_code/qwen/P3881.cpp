#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 20
#define MAXLEN 20

int n;
char S[MAXN][MAXLEN];
char T[MAXLEN * MAXN];

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

void findShortestString() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                int len1 = strlen(S[i]);
                int len2 = strlen(S[j]);
                int len = len1 + len2;
                memcpy(T, S[i], len1);
                memcpy(T + len1, S[j], len2);
                T[len] = '\0';

                // Check if we can decompose T into two different Si's
                int found = 0;
                for (int k = 0; k < n && !found; k++) {
                    if (k != i && k != j) {
                        int len3 = strlen(S[k]);
                        if (len % len3 == 0) {
                            int count = len / len3;
                            int pos = 0;
                            for (int l = 0; l < count; l++) {
                                if (strncmp(T + pos, S[k], len3) != 0) {
                                    break;
                                }
                                pos += len3;
                            }
                            if (pos == len) {
                                printf("%d\n", len);
                                printf("%s\n", T);
                                exit(0);
                            }
                        }
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", S[i]);
    }

    // Sort the strings to ensure lexicographical order
    qsort(S, n, sizeof(char *), compare);

    findShortestString();

    return 0;
}