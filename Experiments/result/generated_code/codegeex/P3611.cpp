#include <stdio.h>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, T_max;
    scanf("%d %d", &N, &T_max);
    
    vector<int> durations(N);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &durations[i]);
    }
    
    int left = 1, right = N;
    while (left < right) {
        int K = (left + right) / 2;
        priority_queue<int> pq;
        int currentTime = 0;
        
        for (int i = 0; i < K; ++i) {
            pq.push(durations[i]);
        }
        
        for (int i = K; i < N; ++i) {
            currentTime += pq.top();
            pq.pop();
            pq.push(durations[i]);
            if (currentTime > T_max) {
                break;
            }
        }
        
        currentTime += pq.top();
        if (currentTime <= T_max) {
            right = K;
        } else {
            left = K + 1;
        }
    }
    
    printf("%d\n", left);
    return 0;
}