#include <stdio.h>

int main() {
    int n, k;
    while (scanf("%d %d", &n, &k) != EOF) {
        int total = n;
        int butts = n;
        
        while (butts >= k) {
            int new_cigarettes = butts / k;
            total += new_cigarettes;
            butts = butts % k + new_cigarettes;
        }
        
        printf("%d\n", total);
    }
    return 0;
}