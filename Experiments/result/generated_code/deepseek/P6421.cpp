#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    
    bool is_deleted[1001] = {false};
    int deleted_count = 0;
    
    for (int p = 2; p <= n; p++) {
        if (!is_deleted[p]) {
            for (int multiple = p; multiple <= n; multiple += p) {
                if (!is_deleted[multiple]) {
                    is_deleted[multiple] = true;
                    deleted_count++;
                    if (deleted_count == k) {
                        printf("%d\n", multiple);
                        return 0;
                    }
                }
            }
        }
    }
    
    return 0;
}