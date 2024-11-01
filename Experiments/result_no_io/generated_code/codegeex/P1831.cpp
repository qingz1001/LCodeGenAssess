#include <stdio.h>

long long x, y;

bool isLeverageNumber(long long num) {
    char numStr[20];
    sprintf(numStr, "%lld", num);
    int len = strlen(numStr);
    for (int i = 1; i < len; i++) {
        int leftSum = 0, rightSum = 0;
        for (int j = 0; j < i; j++) {
            leftSum += (numStr[j] - '0') * (i - j);
        }
        for (int j = i; j < len; j++) {
            rightSum += (numStr[j] - '0') * (j - i);
        }
        if (leftSum != rightSum) {
            return false;
        }
    }
    return true;
}

int main() {
    scanf("%lld%lld", &x, &y);
    int count = 0;
    for (long long i = x; i <= y; i++) {
        if (isLeverageNumber(i)) {
            count++;
        }
    }
    printf("%d\n", count);
    return 0;
}