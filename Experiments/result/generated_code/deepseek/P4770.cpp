#include <stdio.h>
#include <string.h>

#define MAXN 500005

char S[MAXN], T[MAXN];
int Q, l, r;

int count_unique_substrings(char *S, int lenS, char *T, int lenT) {
    int count = 0;
    for (int i = 0; i < lenT; i++) {
        for (int j = i; j < lenT; j++) {
            int valid = 1;
            for (int k = i; k <= j; k++) {
                if (k - i >= lenS || S[k - i] != T[k]) {
                    valid = 0;
                    break;
                }
            }
            if (valid) count++;
        }
    }
    return count;
}

int main() {
    scanf("%s", S);
    int lenS = strlen(S);
    scanf("%d", &Q);
    while (Q--) {
        scanf("%s %d %d", T, &l, &r);
        int lenT = strlen(T);
        char subS[MAXN];
        strncpy(subS, S + l - 1, r - l + 1);
        subS[r - l + 1] = '\0';
        int lenSubS = r - l + 1;
        int result = count_unique_substrings(subS, lenSubS, T, lenT);
        printf("%d\n", result);
    }
    return 0;
}