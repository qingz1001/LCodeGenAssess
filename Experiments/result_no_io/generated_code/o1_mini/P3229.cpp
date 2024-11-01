#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long long ll;

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int *a = (int*)malloc((n+1)*sizeof(int));
    int *b = (int*)malloc((n+1)*sizeof(int));
    for(int i=1;i<=n;i++){
        scanf("%d %d", &a[i], &b[i]);
    }
    ll *pre_h = (ll*)malloc((n+1)*sizeof(ll));
    pre_h[0]=0;
    for(int i=1;i<=n;i++) pre_h[i] = pre_h[i-1] + b[i];
    // Binary search for c
    int low=0, high=n, c=0;
    while(low <= high){
        int mid = low + (high - low)/2;
        // Check possible with c=mid
        int splits=1;
        int pos=0;
        for(int j=1; j<=n; j++){
            ll h = pre_h[j] - pre_h[pos];
            ll d = llabs(2*h - (j - pos));
            if(d > mid){
                splits++;
                pos = j-1;
                h = pre_h[j] - pre_h[pos];
                d = llabs(2*h -1);
                if(d > mid){
                    splits = m +1;
                    break;
                }
            }
        }
        if(splits <= m){
            c = mid;
            high = mid -1;
        }
        else{
            low = mid +1;
        }
    }
    // Now c is determined. Find lex smallest partition.
    int *x = (int*)malloc((m+1)*sizeof(int));
    int pos_split=0;
    int current_j = pos_split +1;
    for(int i=1;i<=m-1;i++){
        int max_j = n - (m -i);
        // Find the smallest j from current_j to max_j such that |2*(pre_h[j]-pre_h[pos_split]) - (j - pos_split)| <=c
        int chosen = -1;
        while(current_j <= max_j){
            ll h = pre_h[current_j] - pre_h[pos_split];
            ll d = llabs(2*h - (current_j - pos_split));
            if(d <= c){
                chosen = current_j;
                break;
            }
            current_j++;
        }
        if(chosen == -1){
            // Should not happen
            chosen = max_j;
        }
        x[i] = chosen;
        pos_split = chosen;
        current_j = pos_split +1;
    }
    x[m] = n;
    // Print the result
    for(int i=1;i<=m;i++){
        printf("%d", a[x[i]]);
        if(i != m) printf(" ");
    }
    printf("\n");
    // Free memory
    free(a);
    free(b);
    free(pre_h);
    free(x);
    return 0;
}