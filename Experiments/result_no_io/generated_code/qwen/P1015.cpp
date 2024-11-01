#include <stdio.h>
#include <string.h>

int isPalindrome(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - i - 1]) {
            return 0;
        }
    }
    return 1;
}

void reverseString(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void addStrings(char *a, char *b, char *result, int base) {
    int carry = 0;
    int lenA = strlen(a);
    int lenB = strlen(b);
    int maxLen = (lenA > lenB) ? lenA : lenB;

    for (int i = 0; i < maxLen || carry; i++) {
        int digitA = (i < lenA) ? a[lenA - i - 1] - '0' : 0;
        int digitB = (i < lenB) ? b[lenB - i - 1] - '0' : 0;
        int sum = digitA + digitB + carry;
        result[maxLen - i] = (sum % base) + '0';
        carry = sum / base;
    }
    result[maxLen + 1] = '\0';
}

int main() {
    int N;
    char M[105];
    scanf("%d %s", &N, M);

    for (int step = 0; step <= 30; step++) {
        char reversedM[105];
        strcpy(reversedM, M);
        reverseString(reversedM);

        char result[105];
        addStrings(M, reversedM, result, N);

        if (isPalindrome(result)) {
            printf("STEP=%d\n", step + 1);
            return 0;
        }

        strcpy(M, result);
    }

    printf("Impossible!\n");
    return 0;
}