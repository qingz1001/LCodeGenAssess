#include <stdio.h>
#include <string.h>

#define MAX_CHILDREN 100
#define MAX_NAME_LEN 21

typedef struct {
    char name[MAX_NAME_LEN];
    int count;
} Child;

int find_child(Child children[], int num, char *name) {
    for(int i = 0; i < num; i++) {
        if(strcmp(children[i].name, name) == 0)
            return i;
    }
    return -1;
}

int main(){
    int n;
    scanf("%d", &n);
    Child children[MAX_CHILDREN];
    int num_children = 0;
    int reminders = 0;
    int sum_before = 0;
    char buffer[MAX_NAME_LEN];
    for(int i = 0; i < n; i++){
        scanf("%s", buffer);
        int idx = find_child(children, num_children, buffer);
        if(idx == -1){
            strcpy(children[num_children].name, buffer);
            children[num_children].count = 0;
            idx = num_children;
            num_children++;
        }
        int c_i = children[idx].count;
        if(2 * c_i > sum_before){
            reminders++;
        }
        children[idx].count++;
        sum_before++;
    }
    printf("%d\n", reminders);
    return 0;
}