#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int main(){
    int n;
    scanf("%d", &n);
    ll a[n];
    for(int i=0;i<n;i++) scanf("%lld", &a[i]);
    int changes =0;
    ll sum =0;
    ll last = -1e12;
    for(int i=0;i<n;i++){
        if(a[i] > last){
            last = a[i];
        }
        else{
            last +=1;
            changes++;
            sum += (last - a[i]);
        }
    }
    printf("%d\n%lld\n", changes, sum);
    return 0;
}