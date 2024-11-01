#include <stdio.h>
#include <string.h>

typedef struct {
    char name[21];
    int count;
} Child;

int find_child(Child children[], int num_children, char *name) {
    for(int i=0;i<num_children;i++) {
        if(strcmp(children[i].name, name) == 0)
            return i;
    }
    return -1;
}

int main(){
    int n;
    scanf("%d", &n);
    Child children[100];
    int num_children =0;
    int total_taken =0;
    int reminders =0;
    char s[21];
    for(int i=0;i<n;i++){
        scanf("%s", s);
        int idx = find_child(children, num_children, s);
        if(idx == -1){
            strcpy(children[num_children].name, s);
            children[num_children].count =0;
            idx = num_children;
            num_children++;
        }
        int count_before = children[idx].count;
        int sum_other = total_taken - count_before;
        if(count_before > sum_other){
            reminders++;
        }
        children[idx].count++;
        total_taken++;
    }
    printf("%d\n", reminders);
    return 0;
}