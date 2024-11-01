#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    double health = 10.0;
    int experience = 0;
    int level = 0;
    
    for (int i = 0; i < n; i++) {
        double x;
        int a;
        scanf("%lf %d", &x, &a);
        
        health -= x;
        if (health <= 0) {
            break;
        }
        
        if (health > 10.0) {
            health = 10.0;
        }
        
        experience += a;
    }
    
    while (experience >= (1 << level)) {
        experience -= (1 << level);
        level++;
    }
    
    printf("%d %d\n", level, experience);
    
    return 0;
}