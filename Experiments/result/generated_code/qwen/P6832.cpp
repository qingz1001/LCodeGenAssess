#include <stdio.h>
#include <string.h>

#define MAXN 10000005

int main() {
    char S[MAXN];
    scanf("%s", S);
    int n = strlen(S);

    int max_count = 0;
    for (int i = 0; i < n; i++) {
        int count = 1;
        for (int j = i + 1; j < n; j++) {
            if (S[j] == S[i]) {
                count++;
            } else {
                break;
            }
        }
        max_count = (count > max_count) ? count : max_count;
    }

    printf("%d\n", max_count);
    return 0;
}