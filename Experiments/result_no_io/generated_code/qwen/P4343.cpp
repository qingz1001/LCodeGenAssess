#include <stdio.h>
#include <stdlib.h>

int main() {
    int l, k;
    scanf("%d %d", &l, &k);
    
    long long *logs = (long long *)malloc(l * sizeof(long long));
    for (int i = 0; i < l; i++) {
        scanf("%lld", &logs[i]);
    }
    
    long long min_n = -1, max_n = -1;
    long long current_code = 0;
    int question_count = 0;
    
    for (int i = 0; i < l; i++) {
        current_code += logs[i];
        
        if (current_code >= 0) {
            question_count++;
            if (question_count == k + 1) {
                break;
            }
        }
        
        if (current_code < 0) {
            current_code = 0;
        }
    }
    
    if (question_count != k + 1) {
        printf("-1\n");
    } else {
        for (int i = l - 1; i >= 0; i--) {
            current_code += logs[i];
            
            if (current_code >= 0) {
                if (min_n == -1) {
                    min_n = current_code;
                }
                if (max_n == -1) {
                    max_n = current_code;
                }
                
                if (i > 0 && logs[i - 1] < 0) {
                    current_code -= logs[i - 1];
                }
            } else {
                current_code = 0;
            }
        }
        
        printf("%lld %lld\n", min_n, max_n);
    }
    
    free(logs);
    return 0;
}