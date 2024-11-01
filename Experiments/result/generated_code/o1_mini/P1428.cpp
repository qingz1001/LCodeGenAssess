#include <stdio.h>

int main(){
    int n, a[101];
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for(int i = 0; i < n; i++) {
        int count = 0;
        for(int j = 0; j < i; j++) {
            if(a[j] < a[i]) count++;
        }
        if(i < n-1) printf("%d ", count);
        else printf("%d\n", count);
    }
    return 0;
}