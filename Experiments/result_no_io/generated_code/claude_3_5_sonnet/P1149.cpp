#include <stdio.h>

int matchsticks[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
long long count = 0;

void dfs(int n, int a, int b, int c) {
    if (n == 0) {
        if (a + b == c) {
            count++;
        }
        return;
    }
    
    for (int i = 0; i <= 9; i++) {
        if (n >= matchsticks[i]) {
            if (a == 0) {
                dfs(n - matchsticks[i], i, b, c);
            } else if (b == 0) {
                dfs(n - matchsticks[i], a, i, c);
            } else {
                dfs(n - matchsticks[i], a, b, c * 10 + i);
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    
    n -= 4;  // 减去加号和等号所需的4根火柴棒
    
    for (int a = 0; a <= 1000; a++) {
        for (int b = 0; b <= 1000; b++) {
            int c = a + b;
            int total = 0;
            int temp_a = a, temp_b = b, temp_c = c;
            
            while (temp_a) {
                total += matchsticks[temp_a % 10];
                temp_a /= 10;
            }
            while (temp_b) {
                total += matchsticks[temp_b % 10];
                temp_b /= 10;
            }
            while (temp_c) {
                total += matchsticks[temp_c % 10];
                temp_c /= 10;
            }
            
            if (total == n) {
                if (a == 0 || b == 0 || c == 0) {
                    if (a == 0 && b != 0) count++;
                    if (b == 0 && a != 0) count++;
                    if (c == 0) count++;
                } else {
                    count++;
                }
            }
        }
    }
    
    printf("%lld\n", count);
    return 0;
}