#include <stdio.h>
#include <string.h>

#define MAX_LEN 105

int main() {
    char encrypted1[MAX_LEN], original1[MAX_LEN], encrypted2[MAX_LEN];
    int map[26][26] = {0};
    int visited[26] = {0};

    scanf("%s %s %s", encrypted1, original1, encrypted2);

    for (int i = 0; i < strlen(original1); i++) {
        int o = original1[i] - 'A';
        int e1 = encrypted1[i] - 'A';
        if (map[o][e1] == 0) {
            map[o][e1] = 1;
        } else {
            printf("Failed\n");
            return 0;
        }
        visited[o] = 1;
    }

    for (int i = 0; i < 26; i++) {
        if (!visited[i]) {
            printf("Failed\n");
            return 0;
        }
    }

    for (int i = 0; i < strlen(encrypted2); i++) {
        int e2 = encrypted2[i] - 'A';
        for (int j = 0; j < 26; j++) {
            if (map[j][e2] == 1) {
                printf("%c", j + 'A');
                break;
            }
        }
    }

    printf("\n");

    return 0;
}