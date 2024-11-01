#include <stdio.h>

int matchsticks[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
int count = 0;

int calculate_matchsticks(int num) {
    if (num == 0) return 6;
    int sum = 0;
    while (num > 0) {
        sum += matchsticks[num % 10];
        num /= 10;
    }
    return sum;
}

void find_equations(int n) {
    for (int a = 0; a <= 1111; a++) {
        for (int b = 0; b <= 1111; b++) {
            int c = a + b;
            int total = calculate_matchsticks(a) + calculate_matchsticks(b) + calculate_matchsticks(c) + 4;
            if (total == n) {
                count++;
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    
    find_equations(n);
    
    printf("%d\n", count);
    
    return 0;
}