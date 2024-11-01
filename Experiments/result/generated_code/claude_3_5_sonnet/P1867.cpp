#include <stdio.h>
#include <math.h>

int main() {
    int n, level = 0;
    double health = 10.0, exp = 0.0, x, a;
    
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &x, &a);
        
        health -= x;
        if (health <= 0) break;
        if (health > 10) health = 10;
        
        exp += a;
    }
    
    while (exp >= pow(2, level)) {
        exp -= pow(2, level);
        level++;
    }
    
    printf("%d %.0f\n", level, exp);
    
    return 0;
}