#include <stdio.h>
#include <stdbool.h>

#define N 1337

bool contains7(int num) {
    while (num > 0) {
        if (num % 10 == 7) return true;
        num /= 10;
    }
    return false;
}

int main() {
    int X;
    scanf("%d", &X);

    int current = 1;
    int direction = 1;
    int num = 1;

    while (num < X) {
        if (num % 7 == 0 || contains7(num)) {
            direction *= -1;
        }
        
        current += direction;
        if (current == 0) current = N;
        if (current > N) current = 1;
        
        num++;
    }

    printf("%d\n", current);
    return 0;
}