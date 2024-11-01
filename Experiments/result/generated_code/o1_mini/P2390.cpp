#include <stdio.h>
#include <stdlib.h>

int cmp_int(const void* a, const void* b){
    int ia = *(int*)a;
    int ib = *(int*)b;
    return ia - ib;
}

int main(){
    long long T;
    int n;
    scanf("%lld %d", &T, &n);
    int *neg = (int*)malloc(n * sizeof(int));
    int *pos = (int*)malloc(n * sizeof(int));
    int neg_cnt =0, pos_cnt=0;
    for(int i=0;i<n;i++){
        int x;
        scanf("%d", &x);
        if(x <0){
            neg[neg_cnt++] = -x;
        }
        else{
            pos[pos_cnt++] = x;
        }
    }
    qsort(neg, neg_cnt, sizeof(int), cmp_int);
    qsort(pos, pos_cnt, sizeof(int), cmp_int);
    long long max_landmarks =0;
    // Iterate over neg
    for(int i=0;i<=neg_cnt;i++){
        if(i >0 && neg[i-1] > T) break;
        long long remaining = T - (i >0 ? (long long)neg[i-1] : 0);
        if(remaining <0) continue;
        // Binary search on pos
        int left =0, right = pos_cnt;
        while(left < right){
            int mid = left + (right - left)/2;
            if(pos[mid] <= remaining){
                left = mid +1;
            }
            else{
                right = mid;
            }
        }
        if(i + left > max_landmarks){
            max_landmarks = i + left;
        }
    }
    // Iterate over pos
    for(int i=0;i<=pos_cnt;i++){
        if(i >0 && pos[i-1] > T) break;
        long long remaining = T - (i >0 ? (long long)pos[i-1] : 0);
        if(remaining <0) continue;
        // Binary search on neg
        int left =0, right = neg_cnt;
        while(left < right){
            int mid = left + (right - left)/2;
            if(neg[mid] <= remaining){
                left = mid +1;
            }
            else{
                right = mid;
            }
        }
        if(i + left > max_landmarks){
            max_landmarks = i + left;
        }
    }
    printf("%lld\n", max_landmarks);
    free(neg);
    free(pos);
    return 0;
}