#include <stdio.h>
#include <string.h>

int isLeverNumber(long long num) {
    char str[20];
    sprintf(str, "%lld", num);
    int len = strlen(str);
    
    for (int pivot = 0; pivot < len; pivot++) {
        long long left_moment = 0, right_moment = 0;
        
        for (int i = 0; i < pivot; i++) {
            left_moment += (str[i] - '0') * (pivot - i);
        }
        
        for (int i = pivot + 1; i < len; i++) {
            right_moment += (str[i] - '0') * (i - pivot);
        }
        
        if (left_moment == right_moment) {
            return 1;
        }
    }
    
    return 0;
}

int countLeverNumbers(long long x, long long y) {
    int count = 0;
    for (long long num = x; num <= y; num++) {
        if (isLeverNumber(num)) {
            count++;
        }
    }
    return count;
}

int main() {
    long long x, y;
    scanf("%lld %lld", &x, &y);
    printf("%d\n", countLeverNumbers(x, y));
    return 0;
}