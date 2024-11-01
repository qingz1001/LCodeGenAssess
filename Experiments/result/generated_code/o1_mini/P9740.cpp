#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int a[7], b[7];
    for(int i=0;i<n;i++) {
        scanf("%d %d", &a[i], &b[i]);
    }
    int t;
    scanf("%d", &t);
    int total=0;
    for(int i=0;i<n;i++) {
        total += b[i]*(100/a[i]);
    }
    if(total >= t){
        printf("Already Au.\n");
        return 0;
    }
    for(int i=0;i<n;i++){
        int delta = t - total;
        int val = 100/a[i];
        int c = (delta + val -1) / val;
        if(c <= (a[i] - b[i]) && c >0){
            printf("%d\n", c);
        }
        else{
            printf("NaN\n");
        }
    }
}