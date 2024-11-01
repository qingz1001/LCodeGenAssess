#include <stdio.h>
#include <string.h>

#define MAX_LEN 101

int main() {
    char encrypted[MAX_LEN], original[MAX_LEN], to_translate[MAX_LEN];
    char mapping[26] = {0}; // To store the mapping from encrypted to original
    int used[26] = {0}; // To check if all letters are used
    int i, len;

    scanf("%s", encrypted);
    scanf("%s", original);
    scanf("%s", to_translate);

    len = strlen(encrypted);

    // Build the mapping
    for (i = 0; i < len; i++) {
        int enc_index = encrypted[i] - 'A';
        int orig_index = original[i] - 'A';

        if (mapping[enc_index] == 0) {
            if (used[orig_index]) {
                printf("Failed\n");
                return 0;
            }
            mapping[enc_index] = original[i];
            used[orig_index] = 1;
        } else if (mapping[enc_index] != original[i]) {
            printf("Failed\n");
            return 0;
        }
    }

    // Check if all letters are mapped
    for (i = 0; i < 26; i++) {
        if (mapping[i] == 0) {
            printf("Failed\n");
            return 0;
        }
    }

    // Translate the message
    len = strlen(to_translate);
    for (i = 0; i < len; i++) {
        int index = to_translate[i] - 'A';
        printf("%c", mapping[index]);
    }
    printf("\n");

    return 0;
}