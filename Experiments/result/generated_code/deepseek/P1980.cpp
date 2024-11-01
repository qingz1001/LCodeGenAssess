#include <stdio.h>

int countOccurrences(int n, int x) {
    int count = 0;
    for (int i = 1; i <= n; i++) {
        int num = i;
        while (num > 0) {
            if (num % 10 == x) {
                count++;
            }
            num /= 10;
        }
    }
    return count;
}

int main() {
    int n, x;
    scanf("%d %d", &n, &x);
    printf("%d\n", countOccurrences(n, x));
    return 0;
}