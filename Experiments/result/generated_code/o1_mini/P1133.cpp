#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

int main(){
    int n;
    scanf("%d", &n);
    ll *a = (ll*)malloc((n+1)*sizeof(ll));
    ll *b = (ll*)malloc((n+1)*sizeof(ll));
    ll *c = (ll*)malloc((n+1)*sizeof(ll));
    for(int i=1;i<=n;i++) {
        scanf("%lld %lld %lld", &a[i], &b[i], &c[i]);
    }
    // Option 1: Peaks on odd positions
    // Heights: 20 and 30
    // Map heights: 20 ->1, 30->2
    ll dp1_prev[3];
    memset(dp1_prev, -1, sizeof(dp1_prev));
    // Initialize first peak
    // Position 1 as peak
    for(int h=1; h<=2; h++){
        ll val;
        if(h ==1) val = b[1];
        else val = c[1];
        dp1_prev[h] = val;
    }
    for(int i=3;i<=n;i+=2){
        ll dp1_curr[3];
        memset(dp1_curr, -1, sizeof(dp1_curr));
        for(int prev_h=1; prev_h<=2; prev_h++) {
            if(dp1_prev[prev_h]==-1) continue;
            for(int curr_h=1; curr_h<=2; curr_h++){
                ll valley_val;
                if(i-2 >=1){
                    // Valley between prev peak and current peak is at i-1
                    // min(prev_h, curr_h) corresponds to heights 20 or 30
                    // If min=20, valley can only be 10
                    // If min=30, valley can be 10 or 20
                    int min_h = (prev_h < curr_h) ? prev_h : curr_h;
                    if(min_h ==1){
                        // Valley height =10
                        valley_val = a[i-1];
                    }
                    else{
                        // min_h ==2
                        // Choose max between a[i-1] and b[i-1]
                        ll choice1 = a[i-1];
                        ll choice2 = b[i-1];
                        valley_val = (choice1 > choice2) ? choice1 : choice2;
                    }
                }
                ll curr_sum;
                if(curr_h ==1) curr_sum = b[i];
                else curr_sum = c[i];
                if(i-2 >=1){
                    curr_sum += valley_val;
                }
                if(dp1_prev[curr_h] < dp1_prev[prev_h] + curr_sum){
                    dp1_prev[curr_h] = dp1_prev[prev_h] + curr_sum;
                }
            }
        }
    }
    // Handle last valley between last peak and first peak
    ll option1 = -1;
    for(int last_h=1; last_h<=2; last_h++){
        if(dp1_prev[last_h]==-1) continue;
        // First peak height
        for(int first_h=1; first_h<=2; first_h++){
            // Valley at position 2n or between last peak and first peak
            int min_h = (last_h < first_h) ? last_h : first_h;
            ll valley_val;
            if(min_h ==1){
                valley_val = a[2];
            }
            else{
                ll choice1_val = a[2];
                ll choice2_val = b[2];
                valley_val = (choice1_val > choice2_val) ? choice1_val : choice2_val;
            }
            ll total = dp1_prev[last_h] + valley_val;
            if(option1 < total){
                option1 = total;
            }
        }
    }
    // Option 2: Peaks on even positions
    ll dp2_prev[3];
    memset(dp2_prev, -1, sizeof(dp2_prev));
    // Initialize first peak at position 2
    for(int h=1; h<=2; h++){
        ll val;
        if(h ==1) val = b[2];
        else val = c[2];
        dp2_prev[h] = val;
    }
    for(int i=4;i<=n;i+=2){
        ll dp2_curr[3];
        memset(dp2_curr, -1, sizeof(dp2_curr));
        for(int prev_h=1; prev_h<=2; prev_h++) {
            if(dp2_prev[prev_h]==-1) continue;
            for(int curr_h=1; curr_h<=2; curr_h++){
                ll valley_val;
                if(i-2 >=2){
                    // Valley between prev peak and current peak is at i-1
                    // min(prev_h, curr_h)
                    int min_h = (prev_h < curr_h) ? prev_h : curr_h;
                    if(min_h ==1){
                        // Valley height =10
                        valley_val = a[i-1];
                    }
                    else{
                        // min_h ==2
                        // Choose max between a[i-1] and b[i-1]
                        ll choice1 = a[i-1];
                        ll choice2 = b[i-1];
                        valley_val = (choice1 > choice2) ? choice1 : choice2;
                    }
                }
                ll curr_sum;
                if(curr_h ==1) curr_sum = b[i];
                else curr_sum = c[i];
                if(i-2 >=2){
                    curr_sum += valley_val;
                }
                if(dp2_prev[curr_h] < dp2_prev[prev_h] + curr_sum){
                    dp2_prev[curr_h] = dp2_prev[prev_h] + curr_sum;
                }
            }
        }
    }
    // Handle last valley between last peak and first peak
    ll option2 = -1;
    for(int last_h=1; last_h<=2; last_h++){
        if(dp2_prev[last_h]==-1) continue;
        // First peak height
        for(int first_h=1; first_h<=2; first_h++){
            // Valley between last peak and first peak
            int min_h = (last_h < first_h) ? last_h : first_h;
            ll valley_val;
            if(min_h ==1){
                valley_val = a[1];
            }
            else{
                ll choice1_val = a[1];
                ll choice2_val = b[1];
                valley_val = (choice1_val > choice2_val) ? choice1_val : choice2_val;
            }
            ll total = dp2_prev[last_h] + valley_val;
            if(option2 < total){
                option2 = total;
            }
        }
    }
    ll result = (option1 > option2) ? option1 : option2;
    printf("%lld\n", result);
    free(a);
    free(b);
    free(c);
    return 0;
}