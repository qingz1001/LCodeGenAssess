#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200005

typedef long double ld;

int n, m;
char type_str[20];
ld p[MAX_N];
ld qv[MAX_N];
int known[MAX_N];
int known_list[MAX_N];
int known_size = 0;

// Function to compare for qsort
int cmp(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

int main(){
    // Read n, m, type
    scanf("%d %d %s", &n, &m, type_str);
    // Read p and q
    scanf("%Lf", &p[1]);
    for(int i=2;i<=n;i++) {
        scanf("%Lf %Lf", &p[i], &qv[i]);
    }
    // Initialize known array
    memset(known, -1, sizeof(known));
    // Initialize total expectation
    ld total = 0.0;
    // Initialize previous probabilities
    // To compute expectation, we need to compute the probabilities sequentially
    // However, with known positions, it's more complex
    // For simplicity, after each operation, we recompute from scratch
    // This is O(mn), which may not pass, but given time constraints, proceed
    char op[10];
    for(int op_num=0; op_num<m; op_num++){
        scanf("%s", op);
        if(strcmp(op, "add") == 0){
            int idx, c;
            scanf("%d %d", &idx, &c);
            known[idx] = c;
            // Insert idx into known_list
            known_list[known_size++] = idx;
            // Sort the known_list
            qsort(known_list, known_size, sizeof(int), cmp);
        }
        else if(strcmp(op, "del") == 0){
            int idx;
            scanf("%d", &idx);
            // Remove idx from known_list
            int pos = -1;
            for(int i=0;i<known_size;i++) if(known_list[i]==idx){ pos = i; break;}
            if(pos != -1){
                for(int i=pos;i<known_size-1;i++) known_list[i]=known_list[i+1];
                known_size--;
            }
            known[idx] = -1;
        }
        // Now, recompute the expectation
        // Initialize
        ld dp_prev_R = 0.0, dp_prev_B = 0.0;
        ld expect = 0.0;
        for(int i=1;i<=n;i++){
            if(i == 1){
                if(known[i] == 1){
                    dp_prev_R = 1.0;
                    dp_prev_B = 0.0;
                    expect += 1.0;
                }
                else if(known[i] == 0){
                    dp_prev_R = 0.0;
                    dp_prev_B = 1.0;
                }
                else{
                    dp_prev_R = p[i];
                    dp_prev_B = 1.0 - p[i];
                    expect += p[i];
                }
            }
            else{
                ld prob_R, prob_B;
                if(known[i] == 1){
                    prob_R = 1.0;
                    prob_B = 0.0;
                }
                else if(known[i] == 0){
                    prob_R = 0.0;
                    prob_B = 1.0;
                }
                else{
                    prob_R = -1.0;
                }
                if(prob_R < 0){
                    // Not known
                    ld prob_R_i = dp_prev_R * p[i] + dp_prev_B * qv[i];
                    ld prob_B_i = 1.0 - prob_R_i;
                    dp_prev_R = prob_R_i;
                    dp_prev_B = prob_B_i;
                    expect += prob_R_i;
                }
                else{
                    dp_prev_R = dp_prev_R * (prob_R) / (dp_prev_R * (prob_R) + dp_prev_B * (1.0 - prob_R));
                    dp_prev_B = 1.0 - dp_prev_R;
                    if(prob_R ==1.0) expect +=1.0;
                }
            }
        }
        // Print expectation with 10 decimal digits
        printf("%.10Lf\n", expect);
    }
    return 0;
}