#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    int *a = (int*)malloc((n+1)*sizeof(int));
    for(int i=1;i<=n;i++) scanf("%d", &a[i]);
    
    int low = 0, high = 0;
    for(int i=1;i<=n;i++) if(a[i] > high) high = a[i];
    int answer = 0;
    
    while(low <= high){
        int mid = low + (high - low)/2;
        // Compute prefix sums
        ll *pre = (ll*)malloc((n+1)*sizeof(ll));
        pre[0] = 0;
        for(int i=1;i<=n;i++) pre[i] = pre[i-1] + (a[i] >= mid ? 1 : 0);
        
        int operations = 0;
        int l =1;
        int possible_flag =1;
        while(l <=n){
            int left = l, right = n, res = l-1;
            while(left <= right){
                int m = left + (right - left)/2;
                ll required = pre[l-1] + ( (m - l +2)/2 );
                if(pre[m] >= required){
                    res = m;
                    left = m +1;
                }
                else{
                    right = m -1;
                }
            }
            if(res >= l){
                operations++;
                l = res +1;
            }
            else{
                possible_flag =0;
                break;
            }
        }
        free(pre);
        if(possible_flag && operations <=k){
            answer = mid;
            low = mid +1;
        }
        else{
            high = mid -1;
        }
    }
    printf("%d\n", answer);
    free(a);
    return 0;
}