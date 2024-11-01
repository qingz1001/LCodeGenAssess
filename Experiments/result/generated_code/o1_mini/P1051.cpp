#include <stdio.h>
#include <string.h>

int main(){
    int N;
    scanf("%d", &N);
    char name[21];
    int final, class_eval, num_papers;
    char is_cadre, is_west;
    long long total_sum=0;
    long long max_total=-1;
    char max_name[21];
    for(int i=0;i<N;i++){
        scanf("%s %d %d %c %c %d", name, &final, &class_eval, &is_cadre, &is_west, &num_papers);
        long long total=0;
        if(final >80 && num_papers >=1){
            total +=8000;
        }
        if(final >85 && class_eval >80){
            total +=4000;
        }
        if(final >90){
            total +=2000;
        }
        if(final >85 && is_west == 'Y'){
            total +=1000;
        }
        if(class_eval >80 && is_cadre == 'Y'){
            total +=850;
        }
        total_sum += total;
        if(total > max_total){
            max_total = total;
            strcpy(max_name, name);
        }
    }
    printf("%s\n%lld\n%lld", max_name, max_total, total_sum);
    return 0;
}