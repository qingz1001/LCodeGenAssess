#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int max_cost = 0;
    int current_max = 0;
    
    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);
        
        if (a > current_max) {
            max_cost += current_max;
            current_max = a;
        } else {
            max_cost += a;
        }
    }
    
    printf("%d\n", max_cost);
    return 0;
}