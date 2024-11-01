#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LINES 50
#define MAX_VARS 26

typedef enum { HEAD, ASSIGNMENT, IF_STAT, ELSE_STAT, END_IF_STAT, RETURN_STAT } LineType;

typedef struct {
    int line_num;
    LineType type;
    // For HEAD
    int param_count;
    int params[MAX_VARS];
    // For ASSIGNMENT
    char lhs;
    char rvars[10];
    int rvar_count;
    // For IF
    char cond_var;
    char relation;
    int cond_val; // If comparing with integer
    char cond_var2; // If comparing with variable
    int has_var2;
    // For RETURN
    char ret_vars[10];
    int ret_var_count;
} Line;

Line lines[MAX_LINES];
int total_lines = 0;

// Mapping of IF to ELSE and END IF
int matching_else[MAX_LINES+1];
int matching_end_if[MAX_LINES+1];

// Warnings
int unreachable[MAX_LINES+1];
int warn_uninit[MAX_LINES+1][MAX_VARS];

// Parameters
int params_init[MAX_VARS];

// Function to trim newline
void trim_newline(char *s) {
    int len = strlen(s);
    if(len >0 && s[len-1]=='\n') s[len-1]='\0';
}

// Function to parse variables from a token
int parse_vars(char *token, char vars[]) {
    int count = 0;
    char *p = token;
    while(*p){
        if(*p >= 'A' && *p <= 'Z'){
            vars[count++] = *p;
        }
        p++;
    }
    return count;
}

// Function to parse a line into Line struct
void parse_line(char *s, Line *line, int line_num){
    line->line_num = line_num;
    if(strncmp(s, "PARAM", 5) == 0){
        line->type = HEAD;
        line->param_count = 0;
        char *token = strtok(s, " ");
        while(token != NULL){
            if(token[0] >= 'A' && token[0] <= 'Z'){
                line->params[line->param_count++] = token[0]-'A';
            }
            token = strtok(NULL, " ");
        }
    }
    else if(strncmp(s, "IF", 2) == 0){
        line->type = IF_STAT;
        // IF <variable> <relation> <value> THEN
        char var, rel;
        char val[20];
        sscanf(s, "IF %c %c %s THEN", &var, &rel, val);
        line->cond_var = var;
        line->relation = rel;
        if(isdigit(val[0]) || (val[0] == '-' && isdigit(val[1]))){
            line->cond_val = atoi(val);
            line->has_var2 = 0;
        }
        else{
            line->cond_val = 0;
            line->cond_var2 = val[0];
            line->has_var2 = 1;
        }
    }
    else if(strcmp(s, "ELSE") == 0){
        line->type = ELSE_STAT;
    }
    else if(strcmp(s, "END IF") == 0){
        line->type = END_IF_STAT;
    }
    else if(strncmp(s, "RETURN", 6) == 0){
        line->type = RETURN_STAT;
        line->ret_var_count = 0;
        char *token = strtok(s, " ");
        token = strtok(NULL, " ");
        while(token != NULL){
            if(token[0] >= 'A' && token[0] <= 'Z'){
                line->ret_vars[line->ret_var_count++] = token[0]-'A';
            }
            else{
                // It's a number, do nothing
            }
            token = strtok(NULL, " ");
        }
    }
    else{
        // Assume assignment
        line->type = ASSIGNMENT;
        // <variable> = <rvalue>
        char lhs;
        char expr[100];
        sscanf(s, "%c = %[^\n]", &lhs, expr);
        line->lhs = lhs - 'A';
        // Parse rvars
        line->rvar_count = 0;
        char *token = strtok(expr, " +-*/");
        while(token != NULL){
            if(token[0] >= 'A' && token[0] <= 'Z'){
                line->rvars[line->rvar_count++] = token[0]-'A';
            }
            token = strtok(NULL, " +-*/");
        }
    }
}

// Stack for IF matching
int stack[MAX_LINES];
int top = -1;

// Function to preprocess IF matching
void preprocess_matching(){
    for(int i=1;i<=total_lines;i++){
        if(lines[i].type == IF_STAT){
            stack[++top] = i;
        }
        else if(lines[i].type == END_IF_STAT){
            if(top >=0){
                int if_line = stack[top--];
                matching_end_if[if_line] = i;
                matching_end_if[i] = -1;
            }
        }
        else if(lines[i].type == ELSE_STAT){
            if(top >=0){
                int if_line = stack[top];
                matching_else[if_line] = i;
                matching_else[i] = -1;
            }
        }
    }
}

// Warnings list
typedef struct {
    int line;
    char var;
} Warning;

Warning warns_uninit[MAX_LINES * MAX_VARS];
int warn_uninit_count = 0;

Warning warns_unreachable[MAX_LINES];
int warn_unreachable_count = 0;

// Function to add uninit warning
void add_uninit(int line, char var){
    // Check if already added
    for(int i=0;i<warn_uninit_count;i++) {
        if(warns_uninit[i].line == line && warns_uninit[i].var == var) return;
    }
    warns_uninit[warn_uninit_count].line = line;
    warns_uninit[warn_uninit_count].var = var;
    warn_uninit_count++;
}

// Function to add unreachable warning
void add_unreachable(int line){
    // Check if already added
    for(int i=0;i<warn_unreachable_count;i++) {
        if(warns_unreachable[i].line == line) return;
    }
    warns_unreachable[warn_unreachable_count].line = line;
    warn_unreachable_count++;
}

// Recursive traversal
void traverse(int current_line, unsigned int init_vars, int visited[]){
    if(current_line > total_lines) return;
    if(visited[current_line]) return;
    visited[current_line] = 1;

    Line *line = &lines[current_line];
    // Mark reachable
    unreachable[current_line] = 1;

    switch(line->type){
        case HEAD:
            traverse(current_line+1, init_vars, visited);
            break;
        case ASSIGNMENT: {
            // Check used vars
            for(int i=0;i<line->rvar_count;i++){
                if( !(init_vars & (1<<line->rvars[i])) ){
                    add_uninit(line->line_num, 'A' + line->rvars[i]);
                }
            }
            // Mark lhs as initialized
            unsigned int new_init = init_vars | (1<<line->lhs);
            traverse(current_line+1, new_init, visited);
            break;
        }
        case IF_STAT: {
            int else_line = matching_else[current_line];
            int end_if = matching_end_if[current_line];
            if(else_line != 0){
                // True branch: current_line+1 to else_line-1
                traverse(current_line+1, init_vars, (int *)visited);
                // False branch: else_line+1 to end_if-1
                traverse(else_line+1, init_vars, (int *)visited);
            }
            else{
                // True branch: current_line+1 to end_if-1
                traverse(current_line+1, init_vars, (int *)visited);
                // False branch: skip to end_if+1
                traverse(end_if+1, init_vars, (int *)visited);
            }
            break;
        }
        case RETURN_STAT: {
            // Check used vars
            for(int i=0;i<line->ret_var_count;i++){
                if( !(init_vars & (1<<line->ret_vars[i])) ){
                    add_uninit(line->line_num, 'A' + line->ret_vars[i]);
                }
            }
            // Path terminates
            break;
        }
        case ELSE_STAT:
        case END_IF_STAT:
            traverse(current_line+1, init_vars, visited);
            break;
    }
}

int main(){
    char buffer[256];
    // Read lines
    while(fgets(buffer, sizeof(buffer), stdin) && total_lines < MAX_LINES){
        trim_newline(buffer);
        total_lines++;
        parse_line(buffer, &lines[total_lines], total_lines);
    }
    // Preprocess matching IFs
    preprocess_matching();

    // Initialize initialized variables with parameters
    unsigned int init_vars = 0;
    if(lines[1].type == HEAD){
        for(int i=0;i<lines[1].param_count;i++){
            init_vars |= (1<<lines[1].params[i]);
        }
    }

    // Traverse
    int visited[MAX_LINES+1] = {0};
    traverse(1, init_vars, visited);

    // Check unreachable lines
    for(int i=1;i<=total_lines;i++){
        if(!unreachable[i]){
            if(lines[i].type != ELSE_STAT && lines[i].type != END_IF_STAT){
                add_unreachable(i);
            }
        }
    }

    // Prepare warnings for uninitialized variables
    // Reset visited and traverse again to collect uninit warnings
    warn_uninit_count = 0;
    unsigned int init_vars2 = 0;
    if(lines[1].type == HEAD){
        for(int i=0;i<lines[1].param_count;i++){
            init_vars2 |= (1<<lines[1].params[i]);
        }
    }
    // Reset visited
    memset(visited, 0, sizeof(visited));
    // Traverse with warnings
    traverse(1, init_vars2, visited);

    // Sorting warnings
    // Sort unreachable warnings
    for(int i=1;i<=total_lines;i++){
        if(!unreachable[i]){
            if(lines[i].type != ELSE_STAT && lines[i].type != END_IF_STAT){
                add_unreachable(i);
            }
        }
    }

    // Print warnings in order
    // First collect uninit warnings and unreachable warnings
    // Then sort them
    // We'll use two separate lists

    // Sort uninit warnings
    // Simple bubble sort
    for(int i=0;i<warn_uninit_count-1;i++){
        for(int j=i+1;j<warn_uninit_count;j++){
            if(warns_uninit[i].line > warns_uninit[j].line ||
               (warns_uninit[i].line == warns_uninit[j].line && warns_uninit[i].var > warns_uninit[j].var)){
                Warning temp = warns_uninit[i];
                warns_uninit[i] = warns_uninit[j];
                warns_uninit[j] = temp;
            }
        }
    }

    // Sort unreachable warnings
    for(int i=0;i<warn_unreachable_count-1;i++){
        for(int j=i+1;j<warn_unreachable_count;j++){
            if(warns_unreachable[i].line > warns_unreachable[j].line){
                Warning temp = warns_unreachable[i];
                warns_unreachable[i] = warns_unreachable[j];
                warns_unreachable[j] = temp;
            }
        }
    }

    // Print uninit warnings
    for(int i=0;i<warn_uninit_count;i++){
        printf("Line %d: variable %c might not have been\n", warns_uninit[i].line, warns_uninit[i].var);
        printf("initialized\n");
    }
    // Print unreachable warnings
    for(int i=0;i<warn_unreachable_count;i++){
        printf("Line %d: unreachable code\n", warns_unreachable[i].line);
    }

    return 0;
}