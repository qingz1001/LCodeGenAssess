#include <stdio.h>
#include <string.h>

#define MAXN 500005

int main() {
    char S[MAXN];
    int Q;
    scanf("%s", S);
    scanf("%d", &Q);

    while (Q--) {
        char T[MAXN];
        int l, r;
        scanf("%s %d %d", T, &l, &r);

        int len = strlen(T);
        if (len > r - l + 1) {
            printf("0\n");
            continue;
        }

        int count = 0;
        for (int i = 0; i <= r - l + 1 - len; i++) {
            int match = 1;
            for (int j = 0; j < len; j++) {
                if (T[j] != S[l + i + j]) {
                    match = 0;
                    break;
                }
            }
            if (match) {
                count++;
            }
        }

        printf("%d\n", count);
    }

    return 0;
}