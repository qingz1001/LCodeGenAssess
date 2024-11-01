#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    double total = 0.0;
    for (int i = 0; i < n; i++) {
        double price;
        int quantity;
        scanf("%lf %d", &price, &quantity);
        
        total += price * quantity;
    }
    
    total *= 0.85;
    int cents = (int)(total * 10) % 10;
    if (cents >= 5) {
        total += 0.1 - (total - (int)total) % 0.1;
    }
    
    printf("%.1f\n", total);
    
    return 0;
}