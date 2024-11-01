#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    int index;
    int a;
} Inspector;

int cmp(const void* a, const void* b){
    Inspector* ia = (Inspector*)a;
    Inspector* ib = (Inspector*)b;
    if(ia->a != ib->a) return ia->a - ib->a;
    return ia->index - ib->index;
}

int main(){
    ll n;
    int k;
    scanf("%lld %d", &n, &k);
    int a[k];
    Inspector inspectors[k];
    for(int i=0;i<k;i++){
        scanf("%d", &a[i]);
        inspectors[i].a = a[i];
        inspectors[i].index = i;
    }
    ll left=1, right=1;
    for(int i=0;i<k;i++) {
        if(a[i]>right) right = a[i];
    }
    right *= n;
    ll M=right;
    while(left <= right){
        ll mid = left + (right - left)/2;
        ll total=0;
        for(int i=0;i<k;i++) total += mid / a[i];
        if(total >=n){
            M = mid;
            right = mid -1;
        }
        else{
            left = mid +1;
        }
    }
    ll total=0;
    for(int i=0;i<k;i++) total += M / a[i];
    ll delta = total - n;
    Inspector div_inspectors[k];
    int cnt=0;
    for(int i=0;i<k;i++) if(M % a[i]==0){
        div_inspectors[cnt++] = inspectors[i];
    }
    qsort(div_inspectors, cnt, sizeof(Inspector), cmp);
    ll last_command[k];
    for(int i=0;i<k;i++) last_command[i] = M / a[i];
    for(int i=0;i<cnt;i++) {
        if(i < delta){
            last_command[div_inspectors[i].index]--;
        }
    }
    for(int i=0;i<k;i++) printf("%lld ", last_command[i]);
}