#include <stdio.h>
#include <string.h>

#define MAX_N 501

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int N, K;
    char s[MAX_N];
    int j_count = 0, z_count = 0;
    
    scanf("%d %d", &N, &K);
    scanf("%s", s);
    
    for (int i = 0; i < N; i++) {
        if (s[i] == 'j') j_count++;
        else z_count++;
    }
    
    int max_pairs = min(j_count, z_count);
    int current_pairs = 0;
    
    for (int i = 0; i < N - 1; i++) {
        if (s[i] == 'j' && s[i+1] == 'z') {
            current_pairs++;
            i++;
        }
    }
    
    int additional_pairs = max_pairs - current_pairs;
    int swaps_needed = additional_pairs * 2;
    
    printf("%d\n", current_pairs + min(K, swaps_needed) / 2);
    
    return 0;
}