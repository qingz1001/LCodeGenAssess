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
    
    total *= 0.85;  // 打八五折
    total = (int)(total * 10) / 10.0;  // 去除小于一角的零头
    
    printf("%.1lf\n", total);
    
    return 0;
}