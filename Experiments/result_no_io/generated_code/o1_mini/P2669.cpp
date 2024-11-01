#include <stdio.h>

int main(){
    int k;
    scanf("%d", &k);
    int total = 0;
    int current_num = 1;
    int days_processed = 0;
    while(days_processed < k){
        for(int i=0;i<current_num && days_processed <k;i++){
            total += current_num;
            days_processed++;
        }
        current_num++;
    }
    printf("%d\n", total);
    return 0;
}