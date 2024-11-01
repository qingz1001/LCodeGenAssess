#include <stdio.h>
#include <string.h>

#define MAX_LEN 200

int main() {
    char A[MAX_LEN + 1];
    scanf("%s", A);
    int lenA = strlen(A);

    char S[MAX_LEN * 10 + 1]; // 假设S的长度足够长
    int pos = 0;
    for (int i = 1; pos < lenA; i++) {
        int num = i;
        int digits[10], digitCount = 0;
        while (num > 0) {
            digits[digitCount++] = num % 10;
            num /= 10;
        }
        for (int j = digitCount - 1; j >= 0; j--) {
            S[pos++] = digits[j] + '0';
        }
    }
    S[pos] = '\0';

    for (int i = 0; i <= pos - lenA; i++) {
        int match = 1;
        for (int j = 0; j < lenA; j++) {
            if (S[i + j] != A[j]) {
                match = 0;
                break;
            }
        }
        if (match) {
            printf("%d\n", i + 1);
            return 0;
        }
    }

    return 0;
}