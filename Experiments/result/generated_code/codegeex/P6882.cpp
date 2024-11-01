#include <stdio.h>
#include <string.h>

int main() {
    int N;
    scanf("%d", &N);
    char sentences[6][1001];

    for (int i = 0; i < N; i++) {
        scanf(" %1000[^\n]", sentences[i]);
    }

    for (int i = 0; i < N; i++) {
        int nameCount = 0;
        int len = strlen(sentences[i]);
        bool isName = false;

        for (int j = 0; j < len; j++) {
            if (isupper(sentences[i][j]) && (j == 0 || !isalpha(sentences[i][j - 1]))) {
                isName = true;
            } else if (sentences[i][j] == '.' || sentences[i][j] == '?' || sentences[i][j] == '!') {
                if (isName) {
                    nameCount++;
                    isName = false;
                }
            } else {
                isName = false;
            }
        }

        printf("%d\n", nameCount);
    }

    return 0;
}