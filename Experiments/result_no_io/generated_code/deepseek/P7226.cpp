#include <stdio.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int X = 0;
    for (int i = 0; i < n; i++) {
        int q;
        scanf("%d", &q);
        
        int num = q / 10;
        int p = q % 10;
        
        X += pow(num, p);
    }
    
    printf("%d\n", X);
    
    return 0;
}