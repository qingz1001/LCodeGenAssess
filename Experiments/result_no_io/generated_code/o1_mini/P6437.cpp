#include <stdio.h>

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int a[n];
    for(int i=0;i<n;i++) scanf("%d", &a[i]);
    int max = -1;
    for(int i=0;i<n-2;i++) {
        for(int j=i+1;j<n-1;j++) {
            for(int k=j+1;k<n;k++) {
                int s = a[i] + a[j] + a[k];
                if(s <= m && s > max) max = s;
            }
        }
    }
    printf("%d\n", max);
    return 0;
}