#include <stdio.h>

int apply_op(int x, int op, int y) {
    switch(op){
        case 0: return x + y;
        case 1: return x - y;
        case 2: return x * y;
        default: return 0;
    }
}

int main(){
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    for(int op1=0; op1<3; op1++){
        int temp = apply_op(a, op1, b);
        for(int op2=0; op2<3; op2++){
            int result = apply_op(temp, op2, c);
            if(result == d){
                printf("Yes\n");
                return 0;
            }
        }
    }
    printf("No\n");
    return 0;
}