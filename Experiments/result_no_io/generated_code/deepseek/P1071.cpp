#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 101

int main() {
    char encrypted[MAX_LEN], original[MAX_LEN], to_translate[MAX_LEN];
    char mapping[26] = {0};
    bool used[26] = {false};

    scanf("%s", encrypted);
    scanf("%s", original);
    scanf("%s", to_translate);

    int len1 = strlen(encrypted);
    int len2 = strlen(original);

    if (len1 != len2) {
        printf("Failed\n");
        return 0;
    }

    for (int i = 0; i < len1; i++) {
        int enc_char = encrypted[i] - 'A';
        int org_char = original[i] - 'A';

        if (mapping[enc_char] == 0) {
            if (used[org_char]) {
                printf("Failed\n");
                return 0;
            }
            mapping[enc_char] = original[i];
            used[org_char] = true;
        } else if (mapping[enc_char] != original[i]) {
            printf("Failed\n");
            return 0;
        }
    }

    for (int i = 0; i < 26; i++) {
        if (mapping[i] == 0) {
            printf("Failed\n");
            return 0;
        }
    }

    int len3 = strlen(to_translate);
    for (int i = 0; i < len3; i++) {
        int enc_char = to_translate[i] - 'A';
        printf("%c", mapping[enc_char]);
    }
    printf("\n");

    return 0;
}