#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int cmp_desc(const void *a, const void *b){
    return (*(int*)b - *(int*)a);
}

double min_sum_q;
int n, m;
int a[20];
int group_sums[6];

void backtrack(int idx, double current_sum_q){
    if(idx == n){
        if(current_sum_q < min_sum_q){
            min_sum_q = current_sum_q;
        }
        return;
    }
    for(int i=0; i<m; i++){
        if(group_sums[i] == 0){
            if(i > 0 && group_sums[i-1] == 0){
                continue;
            }
        }
        group_sums[i] += a[idx];
        double new_sum_q = current_sum_q + 2.0 * a[idx] * (group_sums[i] - a[idx]) + (double)(a[idx]) * a[idx];
        if(new_sum_q < min_sum_q){
            backtrack(idx+1, new_sum_q);
        }
        group_sums[i] -= a[idx];
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=0;i<n;i++) scanf("%d", &a[i]);
    qsort(a, n, sizeof(int), cmp_desc);
    min_sum_q = 1e18;
    backtrack(0, 0.0);
    double total = 0.0;
    for(int i=0;i<n;i++) total += a[i];
    double avg = total / m;
    double variance = (min_sum_q / m) - (avg * avg);
    if(variance < 0) variance = 0;
    double sigma = sqrt(variance);
    printf("%.2lf\n", sigma);
    return 0;
}