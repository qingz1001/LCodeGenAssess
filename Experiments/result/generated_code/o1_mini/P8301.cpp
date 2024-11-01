#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    int n;
    scanf("%d", &n);
    char a[n+1], b[n+1];
    scanf("%s", a);
    scanf("%s", b);
    int count_a0=0, count_b0=0;
    for(int i=0;i<n;i++){
        if(a[i]=='0') count_a0++;
        if(b[i]=='0') count_b0++;
    }
    int diff = count_a0 > count_b0 ? count_a0 - count_b0 : count_b0 - count_a0;
    printf("%d\n", diff);
    return 0;
}