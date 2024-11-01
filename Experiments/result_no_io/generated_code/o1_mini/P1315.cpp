#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int index;
    int D;
    int c;
} station;

typedef struct {
    int T;
    int A;
    int B;
} passenger;

int cmp(const void *a, const void *b){
    station *sa = (station*)a;
    station *sb = (station*)b;
    if(sb->c != sa->c)
        return sb->c - sa->c;
    else
        return sa->index - sb->index;
}

int main(){
    int n, m;
    long long k;
    scanf("%d %d %lld", &n, &m, &k);
    
    int D[1001];
    for(int i=1;i<=n-1;i++) {
        scanf("%d", &D[i]);
    }
    
    passenger *passengers = (passenger*)malloc(sizeof(passenger)*m);
    int c[1001];
    for(int i=1;i<=n;i++) c[i] = 0;
    int max_T[1001];
    for(int i=1;i<=n;i++) max_T[i] = 0;
    
    for(int i=0;i<m;i++){
        int T, A, B;
        scanf("%d %d %d", &T, &A, &B);
        passengers[i].T = T;
        passengers[i].A = A;
        passengers[i].B = B;
        if(T > max_T[A]){
            max_T[A] = T;
        }
        for(int j=A; j<B; j++){
            c[j]++;
        }
    }
    
    station *stations = (station*)malloc(sizeof(station)*(n-1));
    for(int i=1;i<=n-1;i++){
        stations[i-1].index = i;
        stations[i-1].D = D[i];
        stations[i-1].c = c[i];
    }
    
    qsort(stations, n-1, sizeof(station), cmp);
    
    int D_new[1001];
    for(int i=1;i<=n-1;i++) D_new[i] = D[i];
    
    for(int i=0;i<n-1;i++){
        if(k ==0) break;
        int idx = stations[i].index;
        if(D_new[idx] ==0) continue;
        long long x = D_new[idx] < k ? D_new[idx] : k;
        D_new[idx] -= x;
        k -= x;
    }
    
    int t_arr[1001];
    int t_depart_time[1001];
    for(int j=1; j<=n; j++){
        if(j ==1){
            t_arr[j] =0;
        }
        else{
            t_arr[j] = t_depart_time[j-1] + D_new[j-1];
        }
        if(t_arr[j] > max_T[j]){
            t_depart_time[j] = t_arr[j];
        }
        else{
            t_depart_time[j] = max_T[j];
        }
    }
    
    long long total =0;
    for(int i=0;i<m;i++){
        total += (long long)(t_arr[passengers[i].B] - passengers[i].T);
    }
    
    printf("%lld\n", total);
    
    free(passengers);
    free(stations);
    return 0;
}