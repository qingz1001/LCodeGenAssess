#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    int index;
    int c;
    int D;
} Segment;

int cmp(const void *a, const void *b){
    Segment *sa = (Segment*)a;
    Segment *sb = (Segment*)b;
    if(sa->c != sb->c){
        return sb->c - sa->c;
    }
    return sb->D - sa->D;
}

int main(){
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    
    int *D_org = (int*)malloc((n-1) * sizeof(int));
    for(int i=0;i<n-1;i++) scanf("%d", &D_org[i]);
    
    int *c = (int*)calloc(n, sizeof(int));
    int *max_T = (int*)calloc(n+1, sizeof(int));
    int *count_B = (int*)calloc(n+1, sizeof(int));
    ll sum_T_p = 0;
    
    for(int i=0;i<m;i++){
        int T, A, B;
        scanf("%d %d %d", &T, &A, &B);
        sum_T_p += T;
        c[A] +=1;
        if(B <= n-1){
            c[B] -=1;
        }
        if(T > max_T[A]) max_T[A] = T;
        count_B[B] +=1;
    }
    
    for(int i=1;i<n;i++) c[i] += c[i-1];
    
    Segment *segments = (Segment*)malloc((n-1) * sizeof(Segment));
    for(int i=0;i<n-1;i++){
        segments[i].index = i;
        segments[i].c = c[i+1];
        segments[i].D = D_org[i];
    }
    
    qsort(segments, n-1, sizeof(Segment), cmp);
    
    int *x = (int*)calloc(n-1, sizeof(int));
    for(int i=0;i<n-1 && k>0;i++){
        int idx = segments[i].index;
        if(segments[i].c ==0) break;
        int assign = D_org[idx] < k ? D_org[idx] : k;
        x[idx] = assign;
        k -= assign;
    }
    
    // Compute D_new
    int *D_new = (int*)malloc((n-1) * sizeof(int));
    for(int i=0;i<n-1;i++) D_new[i] = D_org[i] - x[i];
    
    // Simulate
    ll sum_arrival = 0;
    ll t =0;
    for(int j=1; j<=n; j++){
        ll arrival = t;
        if(j <=n){
            int dep = arrival < max_T[j] ? max_T[j] : arrival;
            sum_arrival += ((ll)arrival) * count_B[j];
            if(j <n){
                t = dep + D_new[j-1];
            }
        }
    }
    
    ll result = sum_arrival - sum_T_p;
    printf("%lld\n", result);
    
    // Free memory
    free(D_org);
    free(c);
    free(max_T);
    free(count_B);
    free(segments);
    free(x);
    free(D_new);
    
    return 0;
}