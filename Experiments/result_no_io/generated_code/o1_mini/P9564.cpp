#include <stdio.h>

int main(){
    int A, B;
    scanf("%d %d", &A, &B);
    int flag = 0;
    for(int i=1;i<=6 && !flag;i++) {
        for(int j=1;j<=6 && !flag;j++) {
            for(int k=1;k<=6 && !flag;k++) {
                int sum_red=0, sum_black=0;
                // Die i
                if(i ==1 || i==4){
                    sum_red += i;
                }
                else{
                    sum_black += i;
                }
                // Die j
                if(j ==1 || j==4){
                    sum_red += j;
                }
                else{
                    sum_black += j;
                }
                // Die k
                if(k ==1 || k==4){
                    sum_red += k;
                }
                else{
                    sum_black += k;
                }
                if(sum_red == A && sum_black == B){
                    flag =1;
                }
            }
        }
    }
    if(flag){
        printf("Yes\n");
    }
    else{
        printf("No\n");
    }
    return 0;
}