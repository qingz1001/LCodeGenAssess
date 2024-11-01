#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    ll x;
    ll y;
    ll l;
} Star;

int cmp_x(const void *a, const void *b){
    Star *sa = (Star*)a;
    Star *sb = (Star*)b;
    if(sa->x != sb->x) return (sa->x < sb->x) ? -1 : 1;
    return 0;
}

int cmp_y(const void *a, const void *b){
    ll ya = *(ll*)a;
    ll yb = *(ll*)b;
    if(ya != yb) return (ya < yb) ? -1 : 1;
    return 0;
}

int main(){
    int T;
    if(scanf("%d", &T)!=1) return 0;
    while(T--){
        int n;
        ll W, H;
        if(scanf("%d %lld %lld", &n, &W, &H)!=3) break;
        Star stars[n];
        for(int i=0;i<n;i++) scanf("%lld %lld %lld", &stars[i].x, &stars[i].y, &stars[i].l);
        qsort(stars, n, sizeof(Star), cmp_x);
        // Initialize y_sorted
        ll y_sorted_y[n];
        ll y_sorted_l[n];
        int y_size = 0;
        ll max_sum = 0;
        int left = 0;
        for(int right=0; right<n; right++){
            // Move left pointer
            while(left <= right && stars[right].x - stars[left].x >= W){
                // Remove stars[left] from y_sorted
                // Binary search to find y
                int lo = 0, hi = y_size-1, pos = -1;
                while(lo <= hi){
                    int mid = lo + (hi - lo)/2;
                    if(y_sorted_y[mid] == stars[left].y){
                        pos = mid;
                        break;
                    }
                    else if(y_sorted_y[mid] < stars[left].y) lo = mid +1;
                    else hi = mid -1;
                }
                if(pos != -1){
                    for(int k=pos; k<y_size-1; k++){
                        y_sorted_y[k] = y_sorted_y[k+1];
                        y_sorted_l[k] = y_sorted_l[k+1];
                    }
                    y_size--;
                }
                left++;
            }
            // Insert stars[right] into y_sorted
            // Find insert position
            int insert_pos = 0;
            int lo = 0, hi = y_size;
            while(lo < hi){
                int mid = lo + (hi - lo)/2;
                if(y_sorted_y[mid] < stars[right].y) lo = mid +1;
                else hi = mid;
            }
            insert_pos = lo;
            for(int k=y_size; k>insert_pos; k--){
                y_sorted_y[k] = y_sorted_y[k-1];
                y_sorted_l[k] = y_sorted_l[k-1];
            }
            y_sorted_y[insert_pos] = stars[right].y;
            y_sorted_l[insert_pos] = stars[right].l;
            y_size++;
            // Now find max sum in y window of height H
            ll current_sum = 0;
            ll local_max = 0;
            int start = 0, end = 0;
            while(start < y_size){
                while(end < y_size && y_sorted_y[end] < y_sorted_y[start] + H){
                    current_sum += y_sorted_l[end];
                    end++;
                }
                if(current_sum > local_max) local_max = current_sum;
                current_sum -= y_sorted_l[start];
                start++;
            }
            if(local_max > max_sum) max_sum = local_max;
        }
        printf("%lld\n", max_sum);
    }
    return 0;
}