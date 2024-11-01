#include<stdio.h>
#include<string.h>

int main(){
    int n;
    scanf("%d", &n);
    char x[101], y[101], z[101];
    scanf("%s %s", x, y);
    int valid = 1;
    for(int i=0;i<n;i++){
        if(y[i] > x[i]){
            valid = 0;
            break;
        }
        if(y[i] == x[i]){
            z[i] = x[i];
        }
        else{
            z[i] = y[i];
        }
    }
    z[n] = '\0';
    if(valid){
        printf("%s", z);
    }
    else{
        printf("-1");
    }
    return 0;
}