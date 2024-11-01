#include <stdio.h>

int main() {
    int n, m, type;
    scanf("%d %d %d", &n, &m, &type);
    
    int t[n], q[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &t[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &q[i]);
    }
    
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (t[i] == 1 && q[i] == 1) {
            k++;
        }
    }
    
    int total_bottles = n - k + (k >= m ? m : k);
    printf("%d\n", total_bottles);
    
    return 0;
}