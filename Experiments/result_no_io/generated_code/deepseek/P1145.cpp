#include <stdio.h>

int josephus(int n, int k) {
    if (n == 1)
        return 0;
    else
        return (josephus(n - 1, k) + k) % n;
}

int main() {
    int k;
    scanf("%d", &k);
    
    int m = k + 1;
    while (1) {
        int good_position = josephus(2 * k, m);
        if (good_position >= k) {
            printf("%d\n", m);
            break;
        }
        m++;
    }
    
    return 0;
}