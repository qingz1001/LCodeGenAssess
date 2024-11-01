#include <stdio.h>
#include <string.h>

int main(){
    int n;
    scanf("%d", &n);
    char x[105], y[105], z[105];
    scanf("%s", x);
    scanf("%s", y);
    for(int i=0;i<n;i++){
        if(x[i] < y[i]){
            printf("-1");
            return 0;
        }
        z[i] = y[i];
    }
    z[n] = '\0';
    printf("%s", z);
    return 0;
}