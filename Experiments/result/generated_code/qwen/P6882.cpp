#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    int N;
    scanf("%d", &N);
    getchar(); // consume the newline character after the integer input

    for (int i = 0; i < N; i++) {
        char sentence[1001];
        fgets(sentence, sizeof(sentence), stdin);

        int nameCount = 0;
        int inName = 0;

        for (int j = 0; sentence[j] != '\0'; j++) {
            if (isalpha(sentence[j])) {
                if (!inName && isupper(sentence[j])) {
                    inName = 1;
                }
            } else {
                if (inName) {
                    if (sentence[j] == '.' || sentence[j] == '?' || sentence[j] == '!') {
                        nameCount++;
                    }
                    inName = 0;
                }
            }
        }

        if (inName) {
            nameCount++;
        }

        printf("%d\n", nameCount);
    }

    return 0;
}