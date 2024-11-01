#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    long long original_X = 0;
    
    for (int i = 0; i < n; i++) {
        int q;
        scanf("%d", &q);
        
        // Extract num and p from q
        int num = q / 10;
        int p = q % 10;
        
        // Calculate the original value of the term
        original_X += (long long)num * (long long)num * p;
    }
    
    printf("%lld\n", original_X);
    
    return 0;
}