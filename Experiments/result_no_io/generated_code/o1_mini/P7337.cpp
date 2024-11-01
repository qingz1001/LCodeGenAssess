#include <stdio.h>

int main(){
    int n, m, type;
    scanf("%d %d %d", &n, &m, &type);
    int t[n];
    for(int i=0;i<n;i++) scanf("%d", &t[i]);
    int q[n];
    for(int i=0;i<n;i++) scanf("%d", &q[i]);
    int count_k=0;
    for(int i=0;i<n;i++) if(t[i]==1 && q[i]==1) count_k++;
    int total;
    if(count_k >=m) total = n - count_k + m;
    else total =n;
    printf("%d", total);
    return 0;
}