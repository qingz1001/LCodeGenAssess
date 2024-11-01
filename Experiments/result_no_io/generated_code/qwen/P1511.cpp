#include <stdio.h>
#include <string.h>

int main() {
    char A[201];
    scanf("%s", A);
    int len_A = strlen(A);
    long long k = 0;
    long long pos = 0;

    while (pos < len_A) {
        for (int i = 1; ; i++) {
            if (pos + i > len_A) break;
            char str_i[20];
            sprintf(str_i, "%d", i);
            if (strncmp(A + pos, str_i, i) == 0) {
                pos += i;
                k++;
                break;
            }
        }
    }

    printf("%lld\n", k);
    return 0;
}