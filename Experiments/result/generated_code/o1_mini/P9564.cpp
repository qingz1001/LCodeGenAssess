#include <stdio.h>

int main(){
    int A, B;
    scanf("%d %d", &A, &B);
    for(int d1 =1; d1<=6; d1++){
        for(int d2 =1; d2<=6; d2++){
            for(int d3 =1; d3<=6; d3++){
                int red_sum = 0, black_sum =0;
                int faces[3] = {d1, d2, d3};
                for(int i=0;i<3;i++){
                    if(faces[i]==1){
                        red_sum +=1;
                    }
                    else if(faces[i]==4){
                        red_sum +=4;
                    }
                    if(faces[i]==2 || faces[i]==3 || faces[i]==5 || faces[i]==6){
                        black_sum += faces[i];
                    }
                }
                if(red_sum == A && black_sum == B){
                    printf("Yes");
                    return 0;
                }
            }
        }
    }
    printf("No");
    return 0;
}