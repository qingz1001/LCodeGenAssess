#include <stdio.h>
#include <string.h>

#define MAX_LEN 101

int main() {
    char encrypted1[MAX_LEN], original1[MAX_LEN], encrypted2[MAX_LEN];
    int map[26][26] = {0};
    int used[26] = {0};

    scanf("%s %s %s", encrypted1, original1, encrypted2);

    for (int i = 0; i < strlen(original1); i++) {
        int o_index = original1[i] - 'A';
        int e1_index = encrypted1[i] - 'A';
        int e2_index = encrypted2[i] - 'A';

        if (map[o_index][e1_index] == 0) {
            map[o_index][e1_index] = 1;
            used[e1_index] = 1;
        } else if (map[o_index][e1_index] != 1) {
            printf("Failed\n");
            return 0;
        }

        if (map[o_index][e2_index] == 0) {
            map[o_index][e2_index] = 2;
        } else if (map[o_index][e2_index] != 2) {
            printf("Failed\n");
            return 0;
        }
    }

    for (int i = 0; i < 26; i++) {
        if (!used[i]) {
            printf("Failed\n");
            return 0;
        }
    }

    char decrypted2[MAX_LEN];
    for (int i = 0; i < strlen(encrypted2); i++) {
        int e2_index = encrypted2[i] - 'A';
        for (int j = 0; j < 26; j++) {
            if (map[j][e2_index] == 1) {
                decrypted2[i] = j + 'A';
                break;
            }
        }
    }
    decrypted2[strlen(encrypted2)] = '\0';

    printf("%s\n", decrypted2);

    return 0;
}