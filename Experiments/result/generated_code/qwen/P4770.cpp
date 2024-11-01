#include <stdio.h>
#include <string.h>

#define MAXN 500010

int main() {
    char S[MAXN];
    int Q;
    scanf("%s", S);
    scanf("%d", &Q);

    for (int i = 0; i < Q; i++) {
        char T[MAXN];
        int l, r;
        scanf("%s %d %d", T, &l, &r);

        int len_S = strlen(S);
        int len_T = strlen(T);

        if (len_T > len_S) {
            printf("0\n");
            continue;
        }

        int count = 0;
        for (int j = 0; j <= len_S - len_T; j++) {
            int valid = 1;
            for (int k = 0; k < len_T; k++) {
                if (S[j + k] != T[k]) {
                    valid = 0;
                    break;
                }
            }
            if (valid) {
                count++;
            }
        }

        printf("%d\n", count);
    }

    return 0;
}