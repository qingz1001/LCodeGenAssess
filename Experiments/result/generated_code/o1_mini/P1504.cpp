#include <stdio.h>
#include <string.h>

#define MAX_H 10000

int main(){
    int n;
    scanf("%d", &n);
    int possible[MAX_H+1];
    memset(possible, 1, sizeof(possible));
    for(int c=0;c<n;c++){
        int temp[MAX_H+1];
        memset(temp, 0, sizeof(temp));
        int x;
        int sum=0;
        while(1){
            scanf("%d", &x);
            if(x == -1) break;
            sum += x;
            if(sum <= MAX_H){
                temp[sum] = 1;
            }
        }
        if(c ==0){
            for(int i=0;i<=MAX_H;i++) possible[i] = temp[i];
        }
        else{
            for(int i=0;i<=MAX_H;i++) possible[i] = possible[i] && temp[i];
        }
    }
    int H=0;
    for(int i=MAX_H;i>=0;i--){
        if(possible[i]){
            H = i;
            break;
        }
    }
    printf("%d\n", H);
    return 0;
}