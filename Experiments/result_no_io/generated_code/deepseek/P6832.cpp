#include <stdio.h>
#include <string.h>

#define MAX_LEN 10000000

int main() {
    char S[MAX_LEN + 1];
    scanf("%s", S);
    int len = strlen(S);

    int count[26] = {0};
    for (int i = 0; i < len; i++) {
        count[S[i] - 'a']++;
    }

    int max_count = 0;
    for (int i = 0; i < 26; i++) {
        if (count[i] > max_count) {
            max_count = count[i];
        }
    }

    printf("%d\n", max_count);
    return 0;
}