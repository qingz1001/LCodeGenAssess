#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 500005

char S[MAXN], T[MAXN];
int Q, l, r;

int count_unique_substrings(char *s, int len) {
    int count = 0;
    for (int i = 0; i < len; i++) {
        for (int j = 1; j <= len - i; j++) {
            count++;
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
        l--; r--; // Convert to 0-based index

        // Extract the substring from S
        char subS[MAXN];
        strncpy(subS, S + l, r - l + 1);
        subS[r - l + 1] = '\0';

        int lenSubS = strlen(subS);

        // Count unique substrings in T
        int unique_in_T = count_unique_substrings(T, lenT);

        // Count unique substrings in subS
        int unique_in_subS = count_unique_substrings(subS, lenSubS);

        // The answer is the difference between the two counts
        int result = unique_in_T - unique_in_subS;

        printf("%d\n", result);
    }

    return 0;
}