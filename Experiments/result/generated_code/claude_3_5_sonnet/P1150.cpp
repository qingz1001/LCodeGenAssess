#include <stdio.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    
    int total = n;
    int butts = n;
    
    while (butts >= k) {
        int new_cigarettes = butts / k;
        total += new_cigarettes;
        butts = new_cigarettes + (butts % k);
    }
    
    printf("%d\n", total);
    
    return 0;
}