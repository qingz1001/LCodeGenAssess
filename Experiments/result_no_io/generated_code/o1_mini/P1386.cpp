#include <stdio.h>
#include <string.h>

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int n, m;
        long long M;
        scanf("%d %d %lld", &n, &m, &M);
        int count_f[301];
        memset(count_f, 0, sizeof(count_f));
        for(int i=0;i<m;i++){
            int p, q;
            scanf("%d %d", &p, &q);
            if(q >=1 && q <=n){
                count_f[q]++;
            }
        }
        int c[301];
        c[0]=0;
        int invalid=0;
        for(int k=1;k<=n;k++){
            c[k]=c[k-1]+count_f[k];
            if(c[k] >k){
                invalid=1;
            }
        }
        if(invalid){
            printf("NO\n");
            continue;
        }
        // Initialize DP
        long long dp_prev[301];
        long long dp_curr[301];
        memset(dp_prev, 0, sizeof(dp_prev));
        dp_prev[0]=1;
        for(int k=1;k<=n;k++){
            memset(dp_curr, 0, sizeof(dp_curr));
            for(int s_prev=0;s_prev <=n-m;s_prev++){
                if(s_prev > (k-1) - c[k-1]) continue;
                long long ways = dp_prev[s_prev];
                if(ways ==0) continue;
                // xk can be from 0 to min(k -c[k] -s_prev, n-m -s_prev)
                int max_xk = (k - c[k] - s_prev) < (n - m - s_prev) ? (k - c[k] - s_prev) : (n - m - s_prev);
                if(max_xk <0) continue;
                for(int xk=0;xk <=max_xk;xk++){
                    int new_s = s_prev +xk;
                    dp_curr[new_s] = (dp_curr[new_s] + ways) % M;
                }
            }
            // Swap dp_prev and dp_curr
            for(int s=0;s<=n-m;s++) dp_prev[s]=dp_curr[s];
        }
        if(n - m >=0 && dp_prev[n -m] >0){
            printf("YES %lld\n", dp_prev[n -m]%M);
        }
        else{
            printf("NO\n");
        }
    }
    return 0;
}