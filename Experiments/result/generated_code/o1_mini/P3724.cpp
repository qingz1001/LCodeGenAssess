#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Define a struct for storing F and steps
typedef struct {
    int f;
    int steps;
} FStep;

#define MAX_F 100000000
#define MAX_F_STEPS 100

int main(){
    int n, m;
    long long mc;
    scanf("%d %d %lld", &n, &m, &mc);
    int a[100];
    for(int i=0;i<n;i++) scanf("%d", &a[i]);
    int w[100];
    for(int i=0;i<n;i++) scanf("%d", &w[i]);
    long long Ck[20];
    for(int i=0;i<m;i++) scanf("%lld", &Ck[i]);
    
    // Precompute all possible F with steps
    // Since F can be up to 1e8 and n=100, we limit F to 1e8
    // Use BFS approach
    // To store minimum steps to reach each F
    // Initialize
    int max_F = 100000000;
    int *min_steps = (int*)malloc((max_F+1)*sizeof(int));
    for(int i=0;i<=max_F;i++) min_steps[i] = n+1;
    // Starting from L=0, F=1
    // To perform actions to build F
    // We use a queue
    typedef struct {
        int L;
        int F;
        int steps;
    } State;
    State queue[1000000];
    int front = 0, rear = 0;
    // Initial state: L=0, F=1, steps=0
    queue[rear++] = (State){0, 1, 0};
    if(1 <= max_F) { min_steps[1] = 0; }
    while(front < rear){
        State current = queue[front++];
        if(current.steps >= n) continue;
        // Action3: L +=1
        State next = current;
        next.L +=1;
        next.steps +=1;
        if(next.F <= max_F && next.steps < min_steps[next.F]){
            min_steps[next.F] = next.steps;
            queue[rear++] = next;
        }
        // Action4: F *= L (only if L >=1)
        if(current.L >=1){
            next = current;
            next.F = current.F * current.L;
            if(next.F > max_F) next.F = max_F+1;
            if(next.F <= max_F && current.steps +1 < min_steps[next.F]){
                min_steps[next.F] = current.steps +1;
                queue[rear++] = next;
            }
        }
    }
    // Collect all possible F with their steps
    FStep FList[200];
    int FCount = 0;
    for(int f=1; f<=max_F && FCount < 1000; f++) {
        if(min_steps[f] <= n){
            FList[FCount].f = f;
            FList[FCount].steps = min_steps[f];
            FCount++;
        }
    }
    // Now, for single action5
    // action5 takes 1 day
    // So total steps for one action5: F.steps +1
    // Collect possible F1
    // Similarly for two action5
    // Precompute possible single and double F reductions
    // To avoid duplicates, use an array
    int singleF_steps[1000];
    int singleF_val[1000];
    int singleF_total = 0;
    for(int i=0;i<FCount;i++){
        singleF_val[singleF_total] = FList[i].f;
        singleF_steps[singleF_total++] = FList[i].steps +1;
    }
    // For two action5
    int doubleF_steps[100000];
    int doubleF_val[100000];
    int doubleF_total = 0;
    for(int i=0;i<FCount;i++){
        for(int j=i;j<FCount;j++){
            long long sumF = (long long)FList[i].f + (long long)FList[j].f;
            if(sumF > max_F) continue;
            int total_steps = FList[i].steps + FList[j].steps +2;
            if(total_steps > n) continue;
            doubleF_val[doubleF_total] = FList[i].f + FList[j].f;
            doubleF_steps[doubleF_total++] = total_steps;
        }
    }
    // Now for each Ck, check possibilities
    for(int i=0;i<m;i++){
        long long C = Ck[i];
        int possible = 0;
        // Option 0 action5
        if(C <= n){
            possible =1;
        }
        // Option 1 action5
        if(!possible){
            for(int s=0;s<singleF_total;s++){
                if(singleF_val[s] > C) continue;
                if(C - singleF_val[s] <= n - singleF_steps[s]){
                    possible =1;
                    break;
                }
            }
        }
        // Option 2 action5
        if(!possible){
            for(int s=0;s<doubleF_total;s++){
                if(doubleF_val[s] > C) continue;
                if(C - doubleF_val[s] <= n - doubleF_steps[s]){
                    possible =1;
                    break;
                }
            }
        }
        printf("%d\n", possible ? 1 : 0);
    }
    free(min_steps);
    return 0;
}