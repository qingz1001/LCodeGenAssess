#include <stdio.h>

int countTwos(int num) {
    int count = 0;
    while (num > 0) {
        if (num % 10 == 2) {
            count++;
        }
        num /= 10;
    }
    return count;
}

int main() {
    int L, R;
    scanf("%d %d", &L, &R);
    
    int totalCount = 0;
    for (int i = L; i <= R; i++) {
        totalCount += countTwos(i);
    }
    
    printf("%d\n", totalCount);
    
    return 0;
}