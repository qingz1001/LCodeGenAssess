#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

int R, C, A, B;
int grid[505][505];
ll prefix[505][505];

int can_split(ll s) {
    int count_a = 0;
    int last = 0;
    ll col_sum[505];
    memset(col_sum, 0, sizeof(col_sum));
    
    for(int i=1;i<=R;i++) {
        for(int j=1;j<=C;j++) {
            col_sum[j] += prefix[i][j] - prefix[i-1][j];
        }
        // Try to split vertically
        int count_b = 0;
        ll current = 0;
        for(int j=1;j<=C;j++) {
            current += col_sum[j];
            if(current >= s) {
                count_b++;
                current = 0;
            }
        }
        if(count_b >= B) {
            count_a++;
            memset(col_sum, 0, sizeof(col_sum));
        }
    }
    return count_a >= A;
}

int main(){
    scanf("%d %d %d %d", &R, &C, &A, &B);
    for(int i=1;i<=R;i++) {
        for(int j=1;j<=C;j++) {
            scanf("%d", &grid[i][j]);
            prefix[i][j] = prefix[i-1][j] + grid[i][j];
        }
    }
    ll total = 0;
    for(int i=1;i<=R;i++) {
        for(int j=1;j<=C;j++) {
            total += grid[i][j];
        }
    }
    ll low = 0, high = total, ans = 0;
    while(low <= high){
        ll mid = low + (high - low) / 2;
        if(can_split(mid)){
            ans = mid;
            low = mid + 1;
        }
        else{
            high = mid -1;
        }
    }
    printf("%lld\n", ans);
}