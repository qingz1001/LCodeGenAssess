#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int health = 10;
    int experience = 0;
    int level = 0;
    
    for (int i = 0; i < n; i++) {
        int x, a;
        scanf("%d %d", &x, &a);
        
        health -= x;
        if (health <= 0) {
            printf("0 0\n");
            return 0;
        }
        
        if (health > 10) {
            health = 10;
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