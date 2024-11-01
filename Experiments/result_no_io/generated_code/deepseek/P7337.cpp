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
    
    int count_both = 0;
    for (int i = 0; i < n; i++) {
        if (t[i] == 1 && q[i] == 1) {
            count_both++;
        }
    }
    
    int total_sodas = n;
    if (count_both >= m) {
        total_sodas = n - count_both + m;
    }
    
    printf("%d\n", total_sodas);
    
    return 0;
}