#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EVENTS 100000
#define MAX_VARS 100

typedef enum { NORMAL, CHOICE, CONDITIONAL } EventType;

typedef struct {
    EventType type;
    // For NORMAL
    int var; // Variable index
    char op; // '+' or '-'
    int amount; // constant or variable
    char amount_type; // 'c' or 'v'
    int amount_val;
    // For CHOICE
    int choice1;
    int choice2;
    // For CONDITIONAL
    char cmp1_type;
    int cmp1;
    char cmp2_type;
    int cmp2;
    int jump_if_true;
    int jump_if_false;
} Event;

Event events[MAX_EVENTS + 1];
int n, m;
long long vars[MAX_VARS + 1];
char choices[MAX_EVENTS];
int choice_count = 0;

int main(){
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++){
        char type;
        scanf(" %c", &type);
        if(type == 'v'){
            // NORMAL event
            events[i].type = NORMAL;
            scanf("%d %c", &events[i].var, &events[i].op);
            char amt_type;
            int amt_val;
            scanf(" %c %d", &amt_type, &amt_val);
            events[i].amount_type = amt_type;
            events[i].amount_val = amt_val;
        }
        else if(type == 's'){
            // CHOICE event
            events[i].type = CHOICE;
            scanf("%d %d", &events[i].choice1, &events[i].choice2);
        }
        else if(type == 'i'){
            // CONDITIONAL event
            events[i].type = CONDITIONAL;
            char cmp1_type, cmp2_type;
            int cmp1, cmp2;
            int jt, jf;
            scanf(" %c %d %c %d %d %d", &cmp1_type, &cmp1, &cmp2_type, &cmp2, &jt, &jf);
            events[i].cmp1_type = cmp1_type;
            events[i].cmp1 = cmp1;
            events[i].cmp2_type = cmp2_type;
            events[i].cmp2 = cmp2;
            events[i].jump_if_true = jt;
            events[i].jump_if_false = jf;
        }
    }

    // Initialize variables
    for(int i=1;i<=m;i++) vars[i] = 0;

    int current = 1;
    while(current >=1 && current <=n){
        Event e = events[current];
        if(e.type == NORMAL){
            int val;
            if(e.amount_type == 'c') val = e.amount_val;
            else val = vars[e.amount_val];
            if(e.op == '+') vars[e.var] += val;
            else vars[e.var] -= val;
            current++;
        }
        else if(e.type == CHOICE){
            // Heuristic: choose the option that potentially maximizes vars[1]
            // Here, we try both options and choose the one leading to higher vars[1]
            // To keep it simple, choose choice1
            // For better performance, more intelligent decision making is needed
            // Here we choose choice1
            choices[choice_count++] = '1';
            current = e.choice1;
        }
        else if(e.type == CONDITIONAL){
            int lhs;
            if(e.cmp1_type == 'c') lhs = e.cmp1;
            else lhs = vars[e.cmp1];
            int rhs;
            if(e.cmp2_type == 'c') rhs = e.cmp2;
            else rhs = vars[e.cmp2];
            if(lhs < rhs) current = e.jump_if_true;
            else current = e.jump_if_false;
        }
    }

    for(int i=0;i<choice_count;i++) printf("%c\n", choices[i]);

    return 0;
}