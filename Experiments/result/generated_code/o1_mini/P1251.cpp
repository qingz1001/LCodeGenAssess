#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

long long min(long long a, long long b) {
    return a < b ? a : b;
}

int main(){
    int N;
    scanf("%d", &N);
    long long r[N+1];
    for(int i=1;i<=N;i++) scanf("%lld", &r[i]);
    long long p, m, f, n, s;
    scanf("%lld %lld %lld %lld %lld", &p, &m, &f, &n, &s);
    
    // Initialize arrays for fast and slow washing
    long long fast_ready[N+ m +2];
    long long slow_ready[N+ n +2];
    memset(fast_ready, 0, sizeof(fast_ready));
    memset(slow_ready, 0, sizeof(slow_ready));
    
    long long stored =0;
    long long total_cost =0;
    
    for(int day=1; day<=N; day++){
        // Add washed napkins available today
        long long available = fast_ready[day] + slow_ready[day] + stored;
        if(available >= r[day]){
            // Use slow_ready first (cheaper)
            long long use_slow = slow_ready[day] < r[day] ? slow_ready[day] : r[day];
            long long use_fast = (fast_ready[day] < (r[day] - use_slow)) ? fast_ready[day] : (r[day] - use_slow);
            long long use_store = r[day] - use_slow - use_fast;
            stored = available - r[day];
        }
        else{
            long long need = r[day] - available;
            total_cost += need * p;
            stored =0;
        }
        
        // Send dirty napkins to washing
        // Prefer slow washing if possible
        if(day + n <=N){
            slow_ready[day + n] += r[day];
            total_cost += r[day] * s;
        }
        else if(day + m <=N){
            fast_ready[day + m] += r[day];
            total_cost += r[day] * f;
        }
        else{
            // Cannot wash for future use, buy next time if needed
        }
    }
    
    printf("%lld\n", total_cost);
    return 0;
}