#include <stdio.h>

int main(){
    int n;
    long long k;
    scanf("%d %lld", &n, &k);
    int a[n];
    for(int i=0;i<n;i++) scanf("%d", &a[i]);
    long long count = 0;
    for(int i=0;i<n;i++) {
        for(int j=i+1;j<n;j++) {
            long long prod = (long long)a[i] * a[j];
            if(prod <= k) count++;
        }
    }
    printf("%lld", count);
    return 0;
}