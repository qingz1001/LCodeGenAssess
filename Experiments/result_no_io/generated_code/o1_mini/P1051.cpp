#include <stdio.h>
#include <string.h>

typedef struct {
    char name[21];
    int avg;
    int cls;
    char is_leader;
    char is_west;
    int paper;
    long long total;
} Student;

int main(){
    int N;
    scanf("%d", &N);
    Student students[N];
    long long total_sum = 0;
    long long max_total = -1;
    int max_index = 0;
    for(int i=0;i<N;i++){
        scanf("%s %d %d %c %c %d", students[i].name, &students[i].avg, &students[i].cls, &students[i].is_leader, &students[i].is_west, &students[i].paper);
        students[i].total = 0;
        // Academician Scholarship
        if(students[i].avg > 80 && students[i].paper >=1){
            students[i].total += 8000;
        }
        // May Fourth Scholarship
        if(students[i].avg >85 && students[i].cls >80){
            students[i].total +=4000;
        }
        // Excellence Scholarship
        if(students[i].avg >90){
            students[i].total +=2000;
        }
        // Western Scholarship
        if(students[i].avg >85 && students[i].is_west == 'Y'){
            students[i].total +=1000;
        }
        // Class Contribution Scholarship
        if(students[i].cls >80 && students[i].is_leader == 'Y'){
            students[i].total +=850;
        }
        total_sum += students[i].total;
        if(students[i].total > max_total){
            max_total = students[i].total;
            max_index = i;
        }
    }
    printf("%s\n%lld\n%lld\n", students[max_index].name, students[max_index].total, total_sum);
    return 0;
}