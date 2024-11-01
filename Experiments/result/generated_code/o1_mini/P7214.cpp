#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Treatment {
    long long T;
    long long L;
    long long R;
    long long C;
} Treatment;

typedef struct Point {
    long long x;
} Point;

int cmp_treatment(const void *a, const void *b) {
    Treatment *ta = (Treatment *)a;
    Treatment *tb = (Treatment *)b;
    if (ta->R != tb->R)
        return ta->R < tb->R ? -1 : 1;
    return 0;
}

int cmp_point(const void *a, const void *b) {
    long long xa = ((Point*)a)->x;
    long long xb = ((Point*)b)->x;
    if (xa < xb) return -1;
    if (xa > xb) return 1;
    return 0;
}

typedef struct DPEntry {
    long long pos;
    long long cost;
} DPEntry;

int main(){
    long long N, M;
    scanf("%lld %lld", &N, &M);
    Treatment *treatments = (Treatment*)malloc(M * sizeof(Treatment));
    Point *points = (Point*)malloc(2*M +1 * sizeof(Point));
    long long cnt =0;
    for(long long i=0;i<M;i++){
        scanf("%lld %lld %lld %lld", &treatments[i].T, &treatments[i].L, &treatments[i].R, &treatments[i].C);
        points[cnt++].x = treatments[i].L-1;
        points[cnt++].x = treatments[i].R;
    }
    points[cnt++].x = N;
    qsort(points, cnt, sizeof(Point), cmp_point);
    long long unique_cnt=0;
    for(long long i=0;i<cnt;i++){
        if(unique_cnt ==0 || points[i].x != points[unique_cnt-1].x){
            points[unique_cnt++] = points[i];
        }
    }
    // Map function
    long long *map = (long long*)malloc(unique_cnt * sizeof(long long));
    for(long long i=0;i<unique_cnt;i++) map[i] = points[i].x;
    qsort(treatments, M, sizeof(Treatment), cmp_treatment);
    // Initialize DP
    DPEntry *dp = (DPEntry*)malloc((unique_cnt+1) * sizeof(DPEntry));
    long long dp_size =1;
    dp[0].pos =0;
    dp[0].cost =0;
    for(long long i=0;i<M;i++){
        // Binary search for L_i-1
        long long L = treatments[i].L-1;
        // Find the rightmost position <= L
        long long left =0, right=unique_cnt-1, best = -1;
        while(left <= right){
            long long mid = left + (right - left)/2;
            if(map[mid] <= L){
                best = mid;
                left = mid +1;
            }
            else{
                right = mid -1;
            }
        }
        if(best == -1) continue;
        long long prev_cost = dp[best].cost;
        long long current_cost = prev_cost + treatments[i].C;
        // Find R_i in map
        long long R = treatments[i].R;
        // Binary search for R
        left =0; right=unique_cnt-1; long long r_idx = -1;
        while(left <= right){
            long long mid = left + (right - left)/2;
            if(map[mid] == R){
                r_idx = mid;
                break;
            }
            else if(map[mid] < R){
                left = mid +1;
            }
            else{
                right = mid -1;
            }
        }
        if(r_idx == -1) continue;
        // Update dp[r_idx]
        // Find if there's already a dp entry at r_idx
        // If yes, take min
        // Else, add new
        // Binary search in dp
        left =0; right=dp_size-1; long long insert = -1;
        while(left <= right){
            long long mid = left + (right - left)/2;
            if(dp[mid].pos == R){
                if(current_cost < dp[mid].cost){
                    dp[mid].cost = current_cost;
                }
                break;
            }
            else if(dp[mid].pos < R){
                left = mid +1;
            }
            else{
                right = mid -1;
            }
        }
        if(left > right){
            // Insert at position left
            dp[dp_size].pos = R;
            dp[dp_size].cost = current_cost;
            // Maintain the dp array sorted and keep min cost
            if(dp_size >0){
                if(current_cost < dp[dp_size-1].cost){
                    dp_size++;
                }
                else{
                    dp[dp_size].cost = dp[dp_size-1].cost;
                    dp_size++;
                }
            }
            else{
                dp_size++;
            }
        }
    }
    // Find the minimal cost covering N
    // Binary search for N
    long long answer = -1;
    long long left =0, right=dp_size-1;
    while(left <= right){
        long long mid = left + (right - left)/2;
        if(dp[mid].pos >= N){
            if(answer == -1 || dp[mid].cost < answer){
                answer = dp[mid].cost;
            }
            right = mid -1;
        }
        else{
            left = mid +1;
        }
    }
    printf("%lld\n", answer);
    free(treatments);
    free(points);
    free(map);
    free(dp);
    return 0;
}