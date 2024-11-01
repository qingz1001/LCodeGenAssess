#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EVENTS 100000
#define MAX_VARS 100
#define MAX_CHOICES 1000000

typedef enum { NORMAL, SELECT, CONDITIONAL } EventType;

typedef struct {
    EventType type;
    // For NORMAL
    int var;
    char op;
    int amount_type; // 0 for constant, 1 for variable
    int amount;
    // For SELECT
    int select1;
    int select2;
    // For CONDITIONAL
    int cmp1_type;
    int cmp1;
    int cmp2_type;
    int cmp2;
    int cond1;
    int cond2;
} Event;

Event events[MAX_EVENTS + 1];
int n, m;
long long vars[MAX_VARS + 1];
long long a1 = 0;
int choices[MAX_CHOICES];
int choice_cnt = 0;

int main(){
    scanf("%d %d", &n, &m);
    char type[2];
    for(int i=1;i<=n;i++){
        scanf("%s", type);
        if(type[0] == 'v' || type[0] == 'c'){
            // Could be NORMAL event
            char op;
            int amt_type, amt;
            scanf("%d %c", &amt_type, &op);
            if(op == '+' || op == '-'){
                // Read amount
                scanf("%d", &amt);
                events[i].type = NORMAL;
                events[i].var = amt_type;
                events[i].op = op;
                // Determine if amount is constant or variable
                // Here assuming amount is constant
                events[i].amount_type = 0;
                events[i].amount = amt;
            }
        }
        else if(type[0] == 's'){
            // SELECT
            int x, y;
            scanf("%d %d", &x, &y);
            events[i].type = SELECT;
            events[i].select1 = x;
            events[i].select2 = y;
        }
        else if(type[0] == 'i'){
            // CONDITIONAL
            char cmp1_type_char, cmp2_type_char;
            int cmp1_val, cmp2_val, x, y;
            scanf(" %c %d %c %d %d %d", &cmp1_type_char, &cmp1_val, &cmp2_type_char, &cmp2_val, &x, &y);
            events[i].type = CONDITIONAL;
            events[i].cmp1_type = (cmp1_type_char == 'v') ? 1 : 0;
            events[i].cmp1 = cmp1_val;
            events[i].cmp2_type = (cmp2_type_char == 'v') ? 1 : 0;
            events[i].cmp2 = cmp2_val;
            events[i].cond1 = x;
            events[i].cond2 = y;
        }
    }
    // Initialize variables
    for(int i=1;i<=m;i++) vars[i] = 0;
    int current = 1;
    while(current >=1 && current <=n && choice_cnt < MAX_CHOICES){
        Event e = events[current];
        if(e.type == NORMAL){
            long long val = (e.amount_type == 0) ? e.amount : vars[e.amount];
            if(e.op == '+') vars[e.var] += val;
            else vars[e.var] -= val;
            current++;
        }
        else if(e.type == SELECT){
            // Simple heuristic: choose the path with higher potential
            // Here, just choose the first option
            choices[choice_cnt++] = 1;
            current = e.select1;
        }
        else if(e.type == CONDITIONAL){
            long long left = (e.cmp1_type == 0) ? e.cmp1 : vars[e.cmp1];
            long long right = (e.cmp2_type == 0) ? e.cmp2 : vars[e.cmp2];
            if(left < right){
                current = e.cond1;
            }
            else{
                current = e.cond2;
            }
        }
    }
    for(int i=0;i<choice_cnt;i++) printf("%d\n", choices[i]);
    return 0;
}