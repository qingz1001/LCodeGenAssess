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
    
    // 打八五折
    total *= 0.85;
    
    // 去分化整
    total = (int)(total * 10) / 10.0;
    
    printf("%.1f\n", total);
    
    return 0;
}