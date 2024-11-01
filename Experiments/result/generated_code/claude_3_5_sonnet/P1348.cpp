#include <stdio.h>
#include <math.h>

int isCouple(int n) {
    if (n <= 0) return 0;
    int x = (int)sqrt(n);
    for (int i = x; i > 0; i--) {
        int y = (int)sqrt(i * i - n);
        if (i * i - y * y == n) return 1;
    }
    return 0;
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    
    int count = 0;
    for (int i = a; i <= b; i++) {
        if (isCouple(i)) count++;
    }
    
    printf("%d\n", count);
    return 0;
}