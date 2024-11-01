#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1001

int n;
char words[MAX_WORDS][21];
int visited[MAX_WORDS];
int starts[MAX_WORDS];
int ends[MAX_WORDS];

void dfs(int current, char *result, int length) {
    if (current == n) {
        result[length-1] = '\0';
        printf("%s\n", result);
        exit(0);
    }
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (ends[current] == starts[i]) {
                visited[i] = 1;
                int j = 0;
                while (words[i][j] != '\0') {
                    result[length + j] = words[i][j];
                    j++;
                }
                result[length + j] = '.';
                dfs(i, result, length + j + 1);
                visited[i] = 0;
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", words[i]);
        starts[i] = words[i][0];
        ends[i] = words[i][strlen(words[i]) - 1];
    }

    char result[MAX_WORDS * 21];
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            visited[i] = 1;
            int j = 0;
            while (words[i][j] != '\0') {
                result[j] = words[i][j];
                j++;
            }
            result[j] = '.';
            dfs(i, result, j + 1);
            visited[i] = 0;
        }
    }

    printf("***\n");
    return 0;
}