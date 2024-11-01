#include<stdio.h>
#include<stdlib.h>

typedef long long ll;

int cmp(const void *a, const void *b){
    ll x = *(ll*)a;
    ll y = *(ll*)b;
    if(x < y) return -1;
    if(x > y) return 1;
    return 0;
}

int main(){
    int n, k;
    ll r, L;
    scanf("%d %d %lld %lld", &n, &k, &r, &L);
    ll *p = (ll*)malloc(sizeof(ll)*n);
    for(int i=0;i<n;i++) scanf("%lld", &p[i]);
    qsort(p, n, sizeof(ll), cmp);
    // Duplicate for circularity
    ll *pp = (ll*)malloc(sizeof(ll)*(2*n));
    for(int i=0;i<2*n;i++) pp[i] = p[i%n] + (i>=n ? L : 0);
    // Binary search
    double left=0, right=L, mid;
    for(int it=0; it<50; it++){
        mid = (left + right)/2;
        int cnt=1;
        ll last = pp[0];
        for(int i=1;i<2*n;i++){
            if(pp[i] - last >= mid){
                cnt++;
                last = pp[i];
                if(cnt >=k) break;
            }
        }
        if(cnt >=k) left = mid;
        else right = mid;
    }
    // Now select the points
    double d = left;
    int selected=0;
    int *indices = (int*)malloc(sizeof(int)*k);
    ll start = pp[0];
    for(int i=0;i<n && selected<k;i++){
        if(pp[i] - start >=d || selected==0){
            indices[selected++] = i+1;
            start = pp[i];
        }
    }
    // If not enough, wrap around
    if(selected <k){
        for(int i=0;i<n && selected<k;i++){
            if(pp[i+n] - start >=d){
                indices[selected++] = i+1;
                start = pp[i+n];
            }
        }
    }
    // If still not enough, fill the rest
    for(int i=0;i<n && selected<k;i++) if(selected <k){
        indices[selected++] = i+1;
    }
    // Sort indices
    for(int i=0;i<k-1;i++) for(int j=i+1;j<k;j++) if(indices[i]>indices[j]){
        int tmp = indices[i];
        indices[i] = indices[j];
        indices[j] = tmp;
    }
    for(int i=0;i<k;i++) printf("%d%c", indices[i], i<k-1?' ':'\n');
    free(p); free(pp); free(indices);
    return 0;
}