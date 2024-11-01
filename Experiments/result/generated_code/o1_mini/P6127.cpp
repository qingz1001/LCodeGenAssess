#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 6
#define MAX_TERMS 64
#define MAX_PI 64
#define MAX_COVER 64
#define INF 1000000

typedef struct {
    char pattern[MAX_N + 1];
    bool used;
    int minterms[MAX_TERMS];
    int count;
} Term;

typedef struct {
    char pattern[MAX_N + 1];
    int minterms[MAX_TERMS];
    int count;
} PrimeImplicant;

int n;
int total_minterms;
bool minterm_present[MAX_TERMS];
char var_names[MAX_N] = {'a','b','c','d','e','f'};
PrimeImplicant prime_implicants[MAX_PI];
int pi_count = 0;
int min_cover_size = INF;
PrimeImplicant best_cover[MAX_PI];
int best_cover_size = 0;

bool can_combine(char *p1, char *p2, char *combined) {
    int diff = 0;
    for(int i=0;i<n;i++) {
        if(p1[i] != p2[i]){
            if(p1[i] != '-' && p2[i] != '-')
                diff++;
            else
                return false;
            combined[i] = '-';
            if(diff >1) return false;
        }
        else combined[i] = p1[i];
    }
    combined[n] = '\0';
    return diff ==1;
}

void generate_prime_implicants(Term terms[], int term_count) {
    bool combined_flag;
    Term new_terms[MAX_TERMS];
    int new_count;
    do {
        combined_flag = false;
        new_count = 0;
        bool marked[term_count];
        for(int i=0;i<term_count;i++) marked[i]=false;
        for(int i=0;i<term_count;i++) {
            for(int j=i+1;j<term_count;j++) {
                char combined[MAX_N+1];
                if(can_combine(terms[i].pattern, terms[j].pattern, combined)) {
                    combined_flag = true;
                    marked[i]=marked[j]=true;
                    bool exists = false;
                    for(int k=0;k<new_count;k++) {
                        if(strcmp(new_terms[k].pattern, combined)==0){
                            exists = true;
                            break;
                        }
                    }
                    if(!exists){
                        strcpy(new_terms[new_count].pattern, combined);
                        new_terms[new_count].count = 0;
                        for(int m=0;m<terms[i].count;m++) {
                            new_terms[new_count].minterms[new_terms[new_count].count++] = terms[i].minterms[m];
                        }
                        for(int m=0;m<terms[j].count;m++) {
                            bool found = false;
                            for(int t=0;t<new_terms[new_count].count;t++) {
                                if(new_terms[new_count].minterms[t] == terms[j].minterms[m]){
                                    found = true;
                                    break;
                                }
                            }
                            if(!found){
                                new_terms[new_count].minterms[new_terms[new_count].count++] = terms[j].minterms[m];
                            }
                        }
                        new_terms[new_count].used = false;
                        new_count++;
                    }
                }
            }
        }
        // Mark prime implicants
        for(int i=0;i<term_count;i++) {
            if(!marked[i]){
                // Add to prime implicants
                strcpy(prime_implicants[pi_count].pattern, terms[i].pattern);
                prime_implicants[pi_count].count = terms[i].count;
                for(int m=0;m<terms[i].count;m++) {
                    prime_implicants[pi_count].minterms[m] = terms[i].minterms[m];
                }
                pi_count++;
            }
        }
        // Prepare for next iteration
        for(int i=0;i<new_count;i++) {
            strcpy(terms[i].pattern, new_terms[i].pattern);
            terms[i].count = new_terms[i].count;
            for(int m=0;m<new_terms[i].count;m++) {
                terms[i].minterms[m] = new_terms[i].minterms[m];
            }
            terms[i].used = false;
        }
        term_count = new_count;
    } while(combined_flag && term_count >0);
}

int cover_minterms[MAX_TERMS];
int coverage[MAX_PI][MAX_TERMS];
int coverage_count[MAX_PI];

bool used_pi[MAX_PI];
int current_cover[MAX_PI];
int current_size =0;
int minimal_length = INF;
PrimeImplicant final_cover[MAX_PI];
int final_size =0;

int formula_length[MAX_PI];

void calculate_formula_length(){
    for(int i=0;i<pi_count;i++){
        int len =0;
        for(int j=0;j<n;j++) {
            if(prime_implicants[i].pattern[j] == '1'){
                len +=1;
                if(j !=0 && prime_implicants[i].pattern[j-1] != '-')
                    len +=1; // for &
            }
            else if(prime_implicants[i].pattern[j] == '0'){
                len +=2;
                if(j !=0 && prime_implicants[i].pattern[j-1] != '-')
                    len +=1; // for &
            }
        }
        // Count & operators
        int var_count =0;
        for(int j=0;j<n;j++) if(prime_implicants[i].pattern[j] != '-') var_count++;
        if(var_count >1){
            len += (var_count -1);
        }
        formula_length[i] = len;
    }
}

void find_minimal_cover(int start, int covered, int current_len){
    if(current_len >= minimal_length) return;
    if(covered == (1<<total_minterms)-1){
        if(current_len < minimal_length){
            minimal_length = current_len;
            final_size = current_size;
            for(int i=0;i<current_size;i++) final_cover[i] = prime_implicants[current_cover[i]];
        }
        return;
    }
    // Select the first uncovered minterm
    int first = -1;
    for(int i=0;i<total_minterms;i++) {
        if(!(covered & (1<<i))){
            first = i;
            break;
        }
    }
    if(first == -1) return;
    // Try all prime implicants that cover this minterm
    for(int i=0;i<pi_count;i++) {
        bool found = false;
        for(int m=0;m<prime_implicants[i].count;m++) {
            if(prime_implicants[i].minterms[m] == first){
                found = true;
                break;
            }
        }
        if(found){
            // Calculate new coverage
            int new_covered = covered;
            for(int m=0;m<prime_implicants[i].count;m++) {
                new_covered |= (1<<prime_implicants[i].minterms[m]);
            }
            current_cover[current_size] = i;
            current_size++;
            find_minimal_cover(i+1, new_covered, current_len + formula_length[i] + (current_size >1 ? 1 :0));
            current_size--;
        }
    }
}

int main(){
    scanf("%d", &n);
    total_minterms =0;
    char s[MAX_N+2];
    Term initial_terms[MAX_TERMS];
    int initial_count =0;
    for(int i=0;i<(1<<n);i++){
        scanf("%s", s);
        bool A = (s[n] == 'T');
        if(A){
            initial_terms[initial_count].count =0;
            strcpy(initial_terms[initial_count].pattern, "");
            for(int j=0;j<n;j++) initial_terms[initial_count].pattern[j] = s[j];
            initial_terms[initial_count].pattern[n] = '\0';
            // Convert to pattern with '-'
            // Initially, each minterm is separate
            initial_terms[initial_count].count =1;
            initial_terms[initial_count].minterms[0] = i;
            initial_terms[initial_count].used = false;
            initial_count++;
            total_minterms++;
        }
    }
    if(total_minterms ==0){
        printf("F");
        return 0;
    }
    generate_prime_implicants(initial_terms, initial_count);
    calculate_formula_length();
    // Assign minterm indices
    // Assign each minterm to a unique index
    int minterm_indices[MAX_TERMS];
    int idx =0;
    for(int i=0;i<(1<<n);i++) {
        bool A = false;
        // Re-parse input to get A
        // Not efficient but n<=6
        // Reconstruct patterns
        // Here, we already have the minterms where A is true
        // So minterm_indices maps the actual minterm to 0..total_minterms-1
        // Use the order of prime implicants minterms
    }
    // Build coverage
    // Assign each minterm to 0..total_minterms-1
    int minterm_map[64];
    int map_count =0;
    for(int i=0;i<(1<<n);i++) {
        // Reconstruct which minterms are present
        // Not stored separately, but in initial_terms
        // Assign mapping
        // For simplicity, re-read the input
        // But since we have initial_terms with minterms
        // Assign unique index to each
        // So minterm_map[i] = index if present
        // Else -1
    }
    // Assign unique index to each minterm in prime implicants
    // Create a list of minterms
    int minterm_list[64];
    int list_count =0;
    for(int i=0;i<(1<<n);i++) {
        // Reconstruct if A is true for this minterm
        // Not stored directly, redo parsing
    }
    // Alternative approach:
    // Assign minterm indices based on prime implicants
    // and use bitmask for coverage
    // Implement the coverage as bitmask where each bit represents a minterm
    // from 0 to total_minterms-1
    // For simplicity, map minterms in the order they appear
    int minterm_order[64];
    int order =0;
    // Re-read input
    fseek(stdin, 0, SEEK_SET);
    scanf("%d", &n);
    for(int i=0;i<(1<<n);i++){
        scanf("%s", s);
        bool A = (s[n] == 'T');
        if(A){
            minterm_order[i] = order;
            order++;
        }
        else{
            minterm_order[i] = -1;
        }
    }
    total_minterms = order;
    // Now build coverage
    memset(coverage, 0, sizeof(coverage));
    memset(coverage_count, 0, sizeof(coverage_count));
    for(int i=0;i<pi_count;i++) {
        for(int m=0;m<prime_implicants[i].count;m++) {
            int mt = prime_implicants[i].minterms[m];
            if(minterm_order[mt] != -1){
                coverage[i][minterm_order[mt]] =1;
                coverage_count[i]++;
            }
        }
    }
    // Implement set cover via recursion
    // Represent coverage as bitmask
    // Implemented earlier find_minimal_cover
    minimal_length = INF;
    final_size =0;
    find_minimal_cover(0, 0, 0);
    // Now build the formula from final_cover
    // Convert each prime implicant to string
    // Then combine with '|'
    char formula[1000] = "";
    for(int i=0;i<final_size;i++) {
        char term_str[20] = "";
        bool first = true;
        for(int j=0;j<n;j++) {
            if(best_cover[i].pattern[j] == '1') {
                if(!first){
                    strcat(term_str, "&");
                }
                char var[2] = {var_names[j], '\0'};
                strcat(term_str, var);
                first = false;
            }
            else if(best_cover[i].pattern[j] == '0') {
                if(!first){
                    strcat(term_str, "&");
                }
                char var_not[3] = {'!', var_names[j], '\0'};
                strcat(term_str, var_not);
                first = false;
            }
        }
        if(final_size >1){
            // Add parentheses if necessary
            bool need_paren = false;
            for(int k=0;k<n;k++) {
                if(best_cover[i].pattern[k] == '&'){
                    need_paren = true;
                    break;
                }
            }
            // According to precedence, '&' has higher than '|', so no need
        }
        strcat(formula, term_str);
        if(i != final_size-1){
            strcat(formula, "|");
        }
    }
    // To handle the minimal_cover correctly, adjust the formula construction
    // Reconstruct the formula with correct best_cover
    // Reset formula
    strcpy(formula, "");
    for(int i=0;i<final_size;i++) {
        char term_str[20] = "";
        bool first = true;
        for(int j=0;j<n;j++) {
            if(best_cover[i].pattern[j] == '1') {
                if(!first){
                    strcat(term_str, "&");
                }
                char var[2] = {var_names[j], '\0'};
                strcat(term_str, var);
                first = false;
            }
            else if(best_cover[i].pattern[j] == '0') {
                if(!first){
                    strcat(term_str, "&");
                }
                char var_not[3] = {'!', var_names[j], '\0'};
                strcat(term_str, var_not);
                first = false;
            }
        }
        strcat(formula, term_str);
        if(i != final_size-1){
            strcat(formula, "|");
        }
    }
    printf("%s", formula);
}