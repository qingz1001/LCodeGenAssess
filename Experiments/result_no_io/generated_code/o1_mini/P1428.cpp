#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int a[n];
    for(int i=0;i<n;i++) {
        scanf("%d", &a[i]);
    }
    for(int i=0;i<n;i++) {
        int count=0;
        for(int j=0;j<i;j++) {
            if(a[j]<a[i]) count++;
        }
        printf("%d%c", count, (i<n-1)?' ':'\n');
    }
    return 0;
}