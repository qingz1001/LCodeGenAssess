#include <stdio.h>

int apply(int x, int op, int y) {
    switch(op){
        case 0: return x + y;
        case 1: return x - y;
        case 2: return x * y;
    }
    return 0;
}

int main(){
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    int found = 0;
    for(int op1=0; op1<3 && !found; op1++){
        for(int op2=0; op2<3 && !found; op2++){
            int res = apply(apply(a, op1, b), op2, c);
            if(res == d){
                found = 1;
            }
        }
    }
    if(found){
        printf("Yes\n");
    } else{
        printf("No\n");
    }
    return 0;
}