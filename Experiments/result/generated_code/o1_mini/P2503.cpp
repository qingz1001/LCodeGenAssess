#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long min_sum_sq = 1e18;
int n, m;
int a[20];
long long group_sums[6];
long long sum_a;

int cmp_desc(const void *x, const void *y){
    return (*(int*)y - *(int*)x);
}

void dfs(int index, long long current_sum_sq){
    if(index == n){
        if(current_sum_sq < min_sum_sq){
            min_sum_sq = current_sum_sq;
        }
        return;
    }
    int used = -1;
    for(int i=0;i<m;i++){
        if(group_sums[i] == used) continue;
        if(group_sums[i] + a[index] + (sum_a - a[index] - group_sums[i]) < 0) continue;
        group_sums[i] += a[index];
        long long new_sum_sq = current_sum_sq - (group_sums[i]-a[index])*(group_sums[i]-a[index]) + group_sums[i]*group_sums[i];
        if(new_sum_sq < min_sum_sq){
            dfs(index+1, new_sum_sq);
        }
        group_sums[i] -= a[index];
        used = group_sums[i];
        if(group_sums[i] == 0) break;
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=0;i<n;i++) {scanf("%d", &a[i]); sum_a += a[i];}
    qsort(a, n, sizeof(int), cmp_desc);
    for(int i=0;i<m;i++) group_sums[i] = 0;
    dfs(0, 0);
    double avg = (double)sum_a / m;
    double variance = ((double)min_sum_sq / m) - (avg * avg);
    if(variance < 0) variance = 0;
    printf("%.2lf\n", sqrt(variance));
    return 0;
}