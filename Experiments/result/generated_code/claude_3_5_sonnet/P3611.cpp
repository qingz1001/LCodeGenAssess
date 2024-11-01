#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000

int N, Tmax;
int durations[MAX_N];

int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int simulate(int K) {
    int stage[MAX_N] = {0};
    int next_cow = K;
    int time = 0;
    
    for (int i = 0; i < K; i++) {
        stage[i] = durations[i];
    }
    
    while (1) {
        int min_time = stage[0];
        for (int i = 1; i < K; i++) {
            if (stage[i] < min_time) {
                min_time = stage[i];
            }
        }
        
        time += min_time;
        
        if (time > Tmax) return 0;
        
        int finished = 0;
        for (int i = 0; i < K; i++) {
            stage[i] -= min_time;
            if (stage[i] == 0) {
                if (next_cow < N) {
                    stage[i] = durations[next_cow++];
                } else {
                    finished++;
                }
            }
        }
        
        if (finished == K) return 1;
    }
}

int binary_search() {
    int left = 1, right = N;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (simulate(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int main() {
    scanf("%d %d", &N, &Tmax);
    for (int i = 0; i < N; i++) {
        scanf("%d", &durations[i]);
    }
    
    qsort(durations, N, sizeof(int), compare);
    
    printf("%d\n", binary_search());
    
    return 0;
}