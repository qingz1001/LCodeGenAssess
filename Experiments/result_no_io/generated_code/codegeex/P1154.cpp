#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    
    int max_mod = 0;
    int cow_ids[5000];
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &cow_ids[i]);
        max_mod = (max_mod > (cow_ids[i] % N)) ? max_mod : (cow_ids[i] % N);
    }
    
    int K = max_mod + 1;
    printf("%d\n", K);
    
    return 0;
}