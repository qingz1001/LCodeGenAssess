#include <stdio.h>

int is_valid(int num, int length, int allowed[]) {
    for(int i=0;i<length;i++) {
        if(num == 0) return 0;
        int d = num % 10;
        if(!allowed[d]) return 0;
        num /=10;
    }
    if(num !=0) return 0;
    return 1;
}

int main(){
    int n;
    scanf("%d", &n);
    int allowed[10] = {0};
    for(int i=0;i<n;i++){
        int d;
        scanf("%d", &d);
        allowed[d]=1;
    }
    int count=0;
    for(int ABC=100; ABC<=999; ABC++){
        // Check ABC digits
        int tmp = ABC;
        int valid = 1;
        for(int i=0;i<3;i++){
            int d = tmp%10;
            if(!allowed[d]){
                valid =0;
                break;
            }
            tmp /=10;
        }
        if(!valid) continue;
        for(int DE=10; DE<=99; DE++){
            // Check DE digits
            int tmpDE = DE;
            valid =1;
            for(int i=0;i<2;i++){
                int d = tmpDE%10;
                if(!allowed[d]){
                    valid=0;
                    break;
                }
                tmpDE /=10;
            }
            if(!valid) continue;
            int D = DE /10;
            int E = DE %10;
            int partial1 = ABC * E;
            if(partial1 <100 || partial1 >999 || !is_valid(partial1,3,allowed)) continue;
            int partial2 = ABC * D;
            if(partial2 <100 || partial2 >999 || !is_valid(partial2,3,allowed)) continue;
            int product = ABC * DE;
            if(product <1000 || product >9999 || !is_valid(product,4,allowed)) continue;
            count++;
        }
    }
    printf("%d\n", count);
}