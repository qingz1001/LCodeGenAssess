#include <stdio.h>
#include <string.h>

int main(){
    int x, y, z;
    scanf("%d %d %d", &x, &y, &z);
    int A, B, C;
    if(x <= y && x <= z){
        A = x;
        if(y <= z){
            B = y;
            C = z;
        }
        else{
            B = z;
            C = y;
        }
    }
    else if(y <= x && y <= z){
        A = y;
        if(x <= z){
            B = x;
            C = z;
        }
        else{
            B = z;
            C = x;
        }
    }
    else{
        A = z;
        if(x <= y){
            B = x;
            C = y;
        }
        else{
            B = y;
            C = x;
        }
    }
    char order[4];
    scanf("%s", order);
    for(int i=0;i<3;i++){
        if(order[i]=='A') printf("%d", A);
        else if(order[i]=='B') printf("%d", B);
        else printf("%d", C);
        if(i<2) printf(" ");
    }
    return 0;
}