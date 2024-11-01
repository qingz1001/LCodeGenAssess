#include <stdio.h>

int main(){
    int n, m, type;
    scanf("%d %d %d", &n, &m, &type);
    int t[n], q[n];
    for(int i=0;i<n;i++) scanf("%d", &t[i]);
    for(int i=0;i<n;i++) scanf("%d", &q[i]);
    int k=0;
    for(int i=0;i<n;i++) if(t[i]==1 && q[i]==1) k++;
    int total;
    if(k >= m) total = n - k + m;
    else total = n;
    printf("%d", total);
    return 0;
}