#include <stdio.h>

int main() {
    int N, S;
    scanf("%d%d", &N, &S);
    
    int C[N], Y[N];
    for (int i = 0; i < N; i++) {
        scanf("%d%d", &C[i], &Y[i]);
    }
    
    long long cost = 0;
    for (int i = 0; i < N; i++) {
        // Calculate the cost of producing machines in the current week
        long long current_cost = 0;
        for (int j = 0; j < Y[i]; j++) {
            current_cost += C[i];
        }
        
        // Calculate the cost of holding machines from previous weeks
        long long hold_cost = 0;
        for (int j = 0; j < i; j++) {
            for (int k = 0; k < Y[j]; k++) {
                hold_cost += S;
            }
        }
        
        // Add the minimum of current_cost and hold_cost to the total cost
        cost += (current_cost < hold_cost) ? current_cost : hold_cost;
    }
    
    printf("%lld\n", cost);
    return 0;
}