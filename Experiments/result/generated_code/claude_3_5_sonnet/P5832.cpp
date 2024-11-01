#include <stdio.h>
#include <string.h>

#define MAX_N 101

int is_unique(char *str, int len, int k) {
    for (int i = 0; i <= len - k; i++) {
        for (int j = i + 1; j <= len - k; j++) {
            if (strncmp(str + i, str + j, k) == 0) {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    int N;
    char mailboxes[MAX_N];

    scanf("%d", &N);
    scanf("%s", mailboxes);

    for (int k = 1; k <= N; k++) {
        if (is_unique(mailboxes, N, k)) {
            printf("%d\n", k);
            break;
        }
    }

    return 0;
}