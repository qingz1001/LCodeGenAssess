#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int cmp(const void *a, const void *b){
    int64_t x = *(int64_t*)a;
    int64_t y = *(int64_t*)b;
    if(x < y) return -1;
    if(x > y) return 1;
    return 0;
}

int main(){
    int n;
    int64_t m;
    scanf("%d %lld", &n, &m);
    int64_t *a = malloc(n * sizeof(int64_t));
    for(int i=0;i<n;i++) scanf("%lld", &a[i]);
    qsort(a, n, sizeof(int64_t), cmp);
    int64_t sum=0;
    for(int i=0;i<n;i++) sum += a[i];
    int64_t min_val = a[0];
    int count_min =1;
    int i=1;
    while(i<n && a[i]==min_val) {count_min++; i++;}
    while(i<n && m >0){
        if(i == n){
            // All elements are same, distribute m
            min_val += m / count_min;
            m =0;
            break;
        }
        int64_t next_val = a[i];
        int64_t diff = next_val - min_val;
        int64_t required = diff * count_min;
        if(m >= required){
            min_val = next_val;
            sum += required;
            m -= required;
            while(i<n && a[i]==min_val){
                count_min++;
                i++;
            }
        }
        else{
            min_val += m / count_min;
            sum += (m / count_min) * count_min;
            m %= count_min;
            break;
        }
    }
    if(m >0){
        min_val += m / count_min;
        sum += (m / count_min) * count_min;
        m %= count_min;
    }
    // The max remains a[n-1]
    printf("%lld\n", sum + m - min_val - a[n-1]);
    free(a);
    return 0;
}