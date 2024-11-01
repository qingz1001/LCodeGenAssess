#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 500005
#define OFFSET 500000
#define INF 1000000000

typedef long long ll;

ll min(ll a, ll b) { return a < b ? a : b; }

ll min_seg(ll a, ll b) { return a < b ? a : b; }

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    int *s = (int*)malloc((N+1)*sizeof(int));
    for(int i=1;i<=N;i++) scanf("%d", &s[i]);
    // Initialize prefix D
    int *D = (int*)malloc((N+1)*sizeof(int));
    D[0]=0;
    for(int i=1;i<=N;i++) D[i] = D[i-1] + (s[i]==1 ? 1 : -1);
    // Initialize dp
    int *dp = (int*)malloc((N+1)*sizeof(int));
    dp[0]=0;
    // Initialize segment tree
    int size = 1;
    while(size < 1000001) size <<=1;
    int *seg = (int*)malloc(2*size*sizeof(int));
    for(int i=0;i<2*size;i++) seg[i] = INF;
    // Update function
    auto update = [&](int pos, int val) -> void {
        pos += size;
        if(seg[pos] > val) seg[pos] = val;
        else return;
        pos >>=1;
        while(pos >=1){
            int new_val = min(seg[2*pos], seg[2*pos+1]);
            if(seg[pos] > new_val){
                seg[pos] = new_val;
                pos >>=1;
            }
            else break;
        }
    };
    // Query function
    auto query = [&](int l, int r) -> int {
        int res = INF;
        l += size;
        r += size;
        while(l <= r){
            if(l%2 ==1){
                if(seg[l] < res) res = seg[l];
                l++;
            }
            if(r%2 ==0){
                if(seg[r] < res) res = seg[r];
                r--;
            }
            l >>=1;
            r >>=1;
        }
        return res;
    };
    // Initially, set D[0]
    update(D[0] + OFFSET, dp[0]);
    // Maintain last_non1 and last_non2
    int last_non1 =0, last_non2=0;
    for(int i=1;i<=N;i++){
        if(s[i] !=1){
            last_non1 = i-1;
        }
        if(s[i] !=2){
            last_non2 = i-1;
        }
        // min_case1 and min_case2
        int min1 = dp[last_non1] +1;
        int min2 = dp[last_non2] +1;
        // Query segment tree
        int lower = D[i] - M;
        if(lower < -OFFSET) lower = -OFFSET;
        int upper = D[i] + M;
        if(upper > OFFSET) upper = OFFSET;
        int q = query(lower + OFFSET, upper + OFFSET);
        int min3 = q +1;
        // dp[i]
        dp[i] = min(min(min1, min2), min3);
        // Update segment tree
        if(seg[size + D[i] + OFFSET] > dp[i]) update(D[i] + OFFSET, dp[i]);
    }
    printf("%d\n", dp[N]);
    free(s);
    free(D);
    free(dp);
    free(seg);
    return 0;
}