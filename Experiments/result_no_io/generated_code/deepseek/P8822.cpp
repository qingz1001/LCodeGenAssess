#include <stdio.h>

int main() {
    int n, v, m, a;
    scanf("%d %d %d %d", &n, &v, &m, &a);
    
    int total_tuition = 0;
    int current_price = v;
    
    for (int i = 1; i <= n; i++) {
        total_tuition += current_price;
        if (i % m == 0) {
            current_price += a;
        }
    }
    
    printf("%d\n", total_tuition);
    return 0;
}