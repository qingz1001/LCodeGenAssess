#include <stdio.h>

int main() {
    int n, x, a;
    int life = 10;
    int exp = 0;
    int level = 0;
    
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x, &a);
        
        life -= x;
        if (life <= 0) break;
        if (life > 10) life = 10;
        
        exp += a;
        
        while (exp >= (1 << level)) {
            exp -= (1 << level);
            level++;
        }
    }
    
    printf("%d %d\n", level, exp);
    
    return 0;
}