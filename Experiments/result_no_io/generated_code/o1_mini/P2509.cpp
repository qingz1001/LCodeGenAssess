#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LINES 50
#define MAX_TOKENS 10
#define MAX_TOKEN_LEN 20
#define VAR_COUNT 26

typedef struct Line {
    int number;
    char type; // 'H', 'A', 'I', 'E', 'F', 'R'
    char tokens[MAX_TOKENS][MAX_TOKEN_LEN];
    int token_count;
    int else_line;
    int end_if_line;
    int successors[MAX_LINES];
    int succ_count;
    unsigned int used_vars;
} Line;

int main(){
    Line lines[MAX_LINES];
    int n = 0;
    char buffer[256];
    while(fgets(buffer, sizeof(buffer), stdin) && n < MAX_LINES){
        buffer[strcspn(buffer, "\n")] = 0;
        lines[n].number = n+1;
        lines[n].succ_count = 0;
        lines[n].else_line = -1;
        lines[n].end_if_line = -1;
        lines[n].used_vars = 0;
        // Tokenize
        lines[n].token_count = 0;
        char *token = strtok(buffer, " ");
        while(token && lines[n].token_count < MAX_TOKENS){
            strcpy(lines[n].tokens[lines[n].token_count++], token);
            token = strtok(NULL, " ");
        }
        // Determine type
        if(strcmp(lines[n].tokens[0], "PARAM")==0){
            lines[n].type = 'H';
        }
        else if(strcmp(lines[n].tokens[0], "IF")==0){
            lines[n].type = 'I';
        }
        else if(strcmp(lines[n].tokens[0], "ELSE")==0){
            lines[n].type = 'E';
        }
        else if(strcmp(lines[n].tokens[0], "END") ==0 && strcmp(lines[n].tokens[1], "IF")==0){
            lines[n].type = 'F';
        }
        else if(strcmp(lines[n].tokens[0], "RETURN")==0){
            lines[n].type = 'R';
        }
        else{
            lines[n].type = 'A';
        }
        n++;
    }
    // Match IF, ELSE, END IF
    int stack[MAX_LINES];
    int top = -1;
    for(int i=0;i<n;i++){
        if(lines[i].type == 'I'){
            stack[++top] = i;
        }
        else if(lines[i].type == 'E'){
            if(top >=0){
                int if_idx = stack[top--];
                lines[if_idx].else_line = i;
                stack[++top] = i;
            }
        }
        else if(lines[i].type == 'F'){
            if(top >=0){
                int last = stack[top--];
                if(lines[last].type == 'E'){
                    int if_idx = stack[top--];
                    lines[if_idx].end_if_line = i;
                }
                else{
                    int if_idx = last;
                    lines[if_idx].end_if_line = i;
                }
            }
        }
    }
    // Build successors
    for(int i=0;i<n;i++){
        if(lines[i].type == 'I'){
            if(lines[i].else_line != -1){
                // IF -> then branch and else branch
                if(i+1 < n) lines[i].successors[lines[i].succ_count++] = i+1;
                if(lines[lines[i].else_line +1].type != 'E' && lines[i].else_line +1 < n)
                    lines[i].successors[lines[i].succ_count++] = lines[i].else_line +1;
            }
            else{
                // IF -> then branch and after END IF
                if(i+1 < n) lines[i].successors[lines[i].succ_count++] = i+1;
                if(lines[i].end_if_line +1 < n)
                    lines[i].successors[lines[i].succ_count++] = lines[i].end_if_line +1;
            }
        }
        else if(lines[i].type == 'E'){
            if(lines[i].end_if_line +1 < n)
                lines[i].successors[lines[i].succ_count++] = lines[i].end_if_line +1;
        }
        else if(lines[i].type == 'F'){
            // END IF -> next line
            if(i+1 < n)
                lines[i].successors[lines[i].succ_count++] = i+1;
        }
        else if(lines[i].type == 'R'){
            // No successors
        }
        else{
            // Assign, Head, Return
            if(i+1 < n)
                lines[i].successors[lines[i].succ_count++] = i+1;
        }
    }
    // Find reachable lines
    int reachable[MAX_LINES] = {0};
    reachable[0] = 1;
    int queue[MAX_LINES];
    int front=0, back=0;
    queue[back++] = 0;
    while(front < back){
        int current = queue[front++];
        for(int j=0;j<lines[current].succ_count;j++){
            int succ = lines[current].successors[j];
            if(!reachable[succ]){
                reachable[succ] = 1;
                queue[back++] = succ;
            }
        }
    }
    // Collect unreachable warnings
    int warnings_line[MAX_LINES];
    char warnings_vars[MAX_LINES][VAR_COUNT+1];
    int warnings_count[MAX_LINES];
    for(int i=0;i<n;i++) {
        warnings_count[i]=0;
        warnings_vars[i][0]=0;
    }
    for(int i=0;i<n;i++){
        if(!reachable[i] && lines[i].type != 'E' && lines[i].type != 'F'){
            // printf("Warning: Line %d is unreachable.\n", lines[i].number);
            // Collect as special warnings, handle later
        }
    }
    // Data-flow analysis for initialized variables
    unsigned int in_set[MAX_LINES];
    unsigned int out_set[MAX_LINES];
    for(int i=0;i<n;i++) { in_set[i] = 0; out_set[i] = 0; }
    // Initialize parameters
    for(int i=0;i<n;i++) {
        if(lines[i].type == 'H'){
            for(int j=1;j<lines[i].token_count;j++){
                char var = lines[i].tokens[j][0];
                if(var >= 'A' && var <= 'Z'){
                    in_set[i] |= (1U << (var - 'A'));
                }
            }
            break;
        }
    }
    // Initialize queue for worklist
    int worklist[MAX_LINES];
    int wl_front=0, wl_back=0;
    worklist[wl_back++] = 0;
    while(wl_front < wl_back){
        int current = worklist[wl_front++];
        unsigned int in = 0xFFFFFFFF;
        // Find predecessors
        for(int i=0;i<n;i++){
            for(int j=0;j<lines[i].succ_count;j++){
                if(lines[i].successors[j] == current){
                    in &= out_set[i];
                }
            }
        }
        if(current ==0){
            // For first line, in_set already has parameters
            // Do nothing
        }
        else{
            in_set[current] = in;
        }
        // Compute out_set
        unsigned int out = in_set[current];
        if(lines[current].type == 'A'){
            // Assignment: add the variable
            char var = lines[current].tokens[0][0];
            if(var >= 'A' && var <= 'Z'){
                out |= (1U << (var - 'A'));
            }
        }
        out_set[current] = out;
        // Check successors
        for(int j=0;j<lines[current].succ_count;j++){
            int succ = lines[current].succ_count < n ? lines[current].successors[j] : -1;
            if(succ != -1){
                worklist[wl_back++] = succ;
            }
        }
    }
    // Now check for used variables
    for(int i=0;i<n;i++){
        if(reachable[i] && lines[i].type != 'E' && lines[i].type != 'F'){
            unsigned int in = in_set[i];
            // Find used variables in this line
            unsigned int used = 0;
            if(lines[i].type == 'A'){
                // Assignment: RHS
                for(int j=2;j<lines[i].token_count;j++){
                    char c = lines[i].tokens[j][0];
                    if(c >= 'A' && c <= 'Z'){
                        used |= (1U << (c - 'A'));
                    }
                }
            }
            else if(lines[i].type == 'I'){
                // IF variable relation value
                char c = lines[i].tokens[1][0];
                if(c >= 'A' && c <= 'Z') used |= (1U << (c - 'A'));
                c = lines[i].tokens[3][0];
                if(c >= 'A' && c <= 'Z') used |= (1U << (c - 'A'));
            }
            else if(lines[i].type == 'R'){
                // RETURN value
                for(int j=1;j<lines[i].token_count;j++){
                    char c = lines[i].tokens[j][0];
                    if(c >= 'A' && c <= 'Z'){
                        used |= (1U << (c - 'A'));
                    }
                }
            }
            // Check used variables
            for(int v=0;v<VAR_COUNT;v++){
                if(used & (1U << v)){
                    if(!(in_set[i] & (1U << v))){
                        warnings_vars[i][warnings_count[i]++] = 'A' + v;
                        warnings_vars[i][warnings_count[i]] = '\0';
                    }
                }
            }
        }
    }
    // Print warnings
    for(int i=0;i<n;i++){
        if(!reachable[i] && lines[i].type != 'E' && lines[i].type != 'F'){
            printf("Warning: Line %d is unreachable.\n", lines[i].number);
        }
    }
    for(int i=0;i<n;i++){
        if(reachable[i] && lines[i].type != 'E' && lines[i].type != 'F' && warnings_count[i] >0){
            printf("Warning: %s used before initialized in line %d.\n", warnings_vars[i], lines[i].number);
        }
    }
    return 0;
}