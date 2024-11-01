#include <stdio.h>
#include <string.h>

int main() {
    char word[101];
    char result[101];
    int j = 0;
    char remove[] = "CAMBRIDGE";

    scanf("%s", word);

    for (int i = 0; i < strlen(word); i++) {
        int found = 0;
        for (int k = 0; k < strlen(remove); k++) {
            if (word[i] == remove[k]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            result[j] = word[i];
            j++;
        }
    }
    result[j] = '\0';

    printf("%s\n", result);

    return 0;
}