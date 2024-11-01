#include <stdio.h>
#include <stdlib.h>

int magic(int n) {
    if (n < 10) return n;
    int next = 0;
    while (n >= 10) {
        int last = n % 10;
        n /= 10;
        next = (next * 10) + abs(last - (n % 10));
    }
    return magic(next);
}

int is_lucky(int n) {
    return magic(n) == 7;
}

int count_lucky_numbers(int A, int B) {
    int count = 0;
    for (int i = A; i <= B; i++) {
        if (is_lucky(i)) {
            count++;
        }
    }
    return count;
}

int main() {
    int A, B;
    scanf("%d", &A);
    scanf("%d", &B);
    printf("%d\n", count_lucky_numbers(A, B));
    return 0;
}