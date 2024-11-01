#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long long ll;

ll abs_ll(ll x) { return x < 0 ? -x : x; }

int find_set(int *parent, int x){
    if(parent[x] != x){
        parent[x] = find_set(parent, parent[x]);
    }
    return parent[x];
}

void union_set(int *parent, int x, int y){
    int fx = find_set(parent, x);
    int fy = find_set(parent, y);
    if(fx != fy){
        parent[fx] = fy;
    }
}

int connected(int n, ll **dist, ll t){
    int parent[50];
    for(int i=0;i<n;i++) parent[i] = i;
    for(int i=0;i<n;i++) {
        for(int j=i+1;j<n;j++) {
            if(dist[i][j] <= 2*t){
                union_set(parent, i, j);
            }
        }
    }
    int root = find_set(parent, 0);
    for(int i=1;i<n;i++) {
        if(find_set(parent, i) != root) return 0;
    }
    return 1;
}

int main(){
    int n;
    scanf("%d", &n);
    ll x[n], y[n];
    for(int i=0;i<n;i++) scanf("%lld %lld", &x[i], &y[i]);
    ll **dist = (ll **)malloc(n * sizeof(ll *));
    for(int i=0;i<n;i++){
        dist[i] = (ll *)malloc(n * sizeof(ll));
        for(int j=0;j<n;j++) {
            dist[i][j] = abs_ll(x[i]-x[j]) + abs_ll(y[i]-y[j]);
        }
    }
    ll left=0, right=2000000000, ans=right;
    while(left <= right){
        ll mid = left + (right - left)/2;
        if(connected(n, dist, mid)){
            ans = mid;
            right = mid -1;
        }
        else{
            left = mid +1;
        }
    }
    printf("%lld", ans);
    for(int i=0;i<n;i++) free(dist[i]);
    free(dist);
}