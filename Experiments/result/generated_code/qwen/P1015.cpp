#include <stdio.h>
#include <string.h>

int isPalindrome(char *num) {
    int len = strlen(num);
    for (int i = 0; i < len / 2; i++) {
        if (num[i] != num[len - i - 1]) return 0;
    }
    return 1;
}

void addStrings(char *a, char *b, char *result, int base) {
    int carry = 0;
    int lenA = strlen(a), lenB = strlen(b);
    int maxLen = lenA > lenB ? lenA : lenB;
    result[maxLen + 1] = '\0';

    for (int i = 0; i < maxLen; i++) {
        int digitA = i < lenA ? a[lenA - i - 1] - '0' : 0;
        int digitB = i < lenB ? b[lenB - i - 1] - '0' : 0;
        int sum = digitA + digitB + carry;
        result[maxLen - i] = (sum % base) + '0';
        carry = sum / base;
    }

    if (carry) {
        result[0] = carry + '0';
    } else {
        memmove(result, result + 1, maxLen + 1);
    }
}

int main() {
    int base;
    char num[105];
    scanf("%d %s", &base, num);

    char reversedNum[105];
    strcpy(reversedNum, num);
    strrev(reversedNum);

    int steps = 0;
    while (steps <= 30 && !isPalindrome(num)) {
        char temp[105];
        addStrings(num, reversedNum, temp, base);
        strcpy(num, temp);
        strcpy(reversedNum, num);
        strrev(reversedNum);
        steps++;
    }

    if (steps <= 30) {
        printf("STEP=%d\n", steps);
    } else {
        printf("Impossible!\n");
    }

    return 0;
}