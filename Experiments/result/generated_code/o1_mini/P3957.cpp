#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

typedef long long ll;

// Function to perform binary search
int main(){
    int n;
    ll d, k;
    scanf("%d %lld %lld", &n, &d, &k);
    // Allocate n+1 for start
    ll *x = (ll*)malloc((n+1) * sizeof(ll));
    ll *s = (ll*)malloc((n+1) * sizeof(ll));
    x[0] = 0;
    s[0] = 0;
    for(int i=1;i<=n;i++) {
        scanf("%lld %lld", &x[i], &s[i]);
    }
    // Binary search
    ll left =0, right=2000000, answer=-1;
    while(left <=right){
        ll mid = left + (right -left)/2;
        // Initialize DP and deque
        ll *dp = (ll*)malloc((n+1)*sizeof(ll));
        for(int i=0;i<=n;i++) dp[i] = LLONG_MIN;
        dp[0] =0;
        // Initialize deque
        int *deque = (int*)malloc((n+1)*sizeof(int));
        int head =0, tail =0;
        deque[tail++] =0;
        ll max_sum = LLONG_MIN;
        // Set jump limits
        ll min_jump = (mid <d) ? ((d - mid) >=1 ? (d - mid) : 1) : 1;
        ll max_jump = d + mid;
        int l =0, r=0;
        for(int i=1;i<=n;i++){
            ll required_min_x = x[i] - max_jump;
            ll required_max_x = x[i] - min_jump;
            // Advance l to first j where x[j] >= required_min_x
            while(l <=n && x[l] < required_min_x){
                if(head < tail && deque[head] == l){
                    head++;
                }
                l++;
            }
            // Advance r to include j where x[j] <= required_max_x
            while(r <=n && x[r] <= required_max_x){
                while(head < tail && dp[r] >= dp[deque[tail-1]]){
                    tail--;
                }
                deque[tail++] = r;
                r++;
            }
            // Remove deque elements out of window
            while(head < tail && deque[head] < l){
                head++;
            }
            // Set dp[i]
            if(head < tail && dp[deque[head]] != LLONG_MIN){
                dp[i] = dp[deque[head]] + s[i];
            }
            // Update max_sum
            if(dp[i] > max_sum){
                max_sum = dp[i];
            }
            // Maintain deque for next iterations
            if(dp[i] != LLONG_MIN){
                while(head < tail && dp[i] >= dp[deque[tail-1]]){
                    tail--;
                }
                deque[tail++] = i;
            }
        }
        free(deque);
        // Check if max_sum >=k
        if(max_sum >=k){
            answer = mid;
            right = mid -1;
        }
        else{
            left = mid +1;
        }
        free(dp);
    }
    // After binary search, check if answer is set
    // To confirm, if answer was not found in the loop, check for right boundary
    // But since we set right=2000000, which should be sufficient
    // Alternatively, perform a final check
    // To handle if answer was never updated
    // Maximum possible g is 2e6
    // If answer was never set, it remains -1
    // Additionally, check if answer was found
    // If answer is still greater than 2e6, set to -1
    if(answer <=2000000){
        // Now, double check if answer actually allows reaching >=k
        // Since binary search stops at the minimal g, it's already correct
        printf("%lld\n", answer);
    }
    else{
        printf("-1\n");
    }
    free(x);
    free(s);
    return 0;
}