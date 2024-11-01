#include <stdio.h>

int count_twos(int num) {
    int count = 0;
    while (num) {
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
    
    int total_count = 0;
    for (int i = L; i <= R; i++) {
        total_count += count_twos(i);
    }
    
    printf("%d\n", total_count);
    
    return 0;
}