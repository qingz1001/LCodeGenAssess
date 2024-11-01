#include <stdio.h>

int main(){
    int n;
    long long k;
    scanf("%d %lld", &n, &k);
    long long a[n];
    for(int i =0;i<n;i++) scanf("%lld", &a[i]);
    long long count =0;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(a[i] * a[j] <=k) count++;
        }
    }
    printf("%lld\n", count);
    return 0;
}