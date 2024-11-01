#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    
    double *ropes = (double *)malloc(N * sizeof(double));
    for (int i = 0; i < N; i++) {
        scanf("%lf", &ropes[i]);
    }
    
    double max_length = 0.0;
    for (int i = 0; i < N; i++) {
        max_length = (ropes[i] > max_length) ? ropes[i] : max_length;
    }
    
    double min_length = max_length;
    for (int i = 0; i < N; i++) {
        if (ropes[i] / K > min_length) {
            min_length = ropes[i] / K;
        }
    }
    
    int count = 0;
    for (int i = 0; i < N; i++) {
        count += (int)(ropes[i] / min_length);
    }
    
    if (count >= K) {
        printf("%.2lf\n", min_length);
    } else {
        printf("0.00\n");
    }
    
    free(ropes);
    return 0;
}