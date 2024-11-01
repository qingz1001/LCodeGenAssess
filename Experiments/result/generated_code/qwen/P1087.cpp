#include <stdio.h>
#include <string.h>

#define MAX_LEN 1024

void constructAndTraverse(char *s, int start, int end, char *result, int *index) {
    if (start > end) return;

    int mid = (start + end) / 2;
    char type = s[start];

    for (int i = start; i <= end; i++) {
        if (s[i] != type) {
            type = 'F';
            break;
        }
    }

    result[(*index)++] = type;

    if (type == 'F') {
        constructAndTraverse(s, start, mid, result, index);
        constructAndTraverse(s, mid + 1, end, result, index);
    }
}

int main() {
    int N;
    scanf("%d", &N);
    char S[MAX_LEN];
    scanf("%s", S);

    int len = 1 << N;
    char result[MAX_LEN];
    int index = 0;

    constructAndTraverse(S, 0, len - 1, result, &index);

    printf("%s\n", result);

    return 0;
}