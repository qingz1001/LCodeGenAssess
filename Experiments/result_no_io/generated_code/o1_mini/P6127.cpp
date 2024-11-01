#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TERMS 64
#define MAX_PI 64
#define MAX_EXPR 256

typedef struct {
    unsigned int bits;
    unsigned int mask;
} implicant;

int n;
unsigned int minterms[MAX_TERMS];
int num_minterms = 0;
implicant prime_implicants[MAX_PI];
int num_pi = 0;
int covered[MAX_TERMS][MAX_PI];

int count_bits(unsigned int x) {
    int count=0;
    while(x){
        count += x &1;
        x >>=1;
    }
    return count;
}

int compare(const void *a, const void *b){
    return count_bits(*(unsigned int*)a) - count_bits(*(unsigned int*)b);
}

int is_mergeable(implicant a, implicant b){
    unsigned int diff = a.bits ^ b.bits;
    if(count_bits(diff) !=1) return 0;
    if(a.mask != b.mask) return 0;
    return (diff & ~a.mask) !=0;
}

implicant merge(implicant a, implicant b){
    implicant res;
    res.bits = a.bits & b.bits;
    res.mask = a.mask & b.mask;
    unsigned int diff = a.bits ^ b.bits;
    res.mask |= diff;
    return res;
}

int main(){
    scanf("%d", &n);
    int total = 1<<n;
    char s[n+2];
    for(int i=0;i<total;i++){
        scanf("%s", s);
        int val = 0;
        for(int j=0;j<n;j++) {
            if(s[j]=='T') val |= (1<<(n-1-j));
        }
        if(s[n]=='T'){
            minterms[num_minterms++] = val;
        }
    }
    // Initial implicants
    implicant implicants[MAX_TERMS];
    int count =0;
    for(int i=0;i<num_minterms;i++){
        implicants[count].bits = minterms[i];
        implicants[count].mask = 0;
        count++;
    }
    int new_count, used[MAX_TERMS] = {0};
    while(1){
        new_count =0;
        implicant next[MAX_TERMS];
        int marked[count];
        memset(marked, 0, sizeof(marked));
        for(int i=0;i<count;i++){
            for(int j=i+1;j<count;j++){
                if(is_mergeable(implicants[i], implicants[j])){
                    next[new_count++] = merge(implicants[i], implicants[j]);
                    marked[i]=marked[j]=1;
                }
            }
        }
        for(int i=0;i<count;i++) if(!marked[i]){
            prime_implicants[num_pi++] = implicants[i];
        }
        if(new_count ==0) break;
        // Remove duplicates
        count =0;
        for(int i=0;i<new_count;i++){
            int exists=0;
            for(int j=0;j<count;j++) if(next[i].bits == next[j].bits && next[i].mask == next[j].mask){exists=1; break;}
            if(!exists) implicants[count++] = next[i];
        }
    }
    // Build prime implicant chart
    for(int i=0;i<num_minterms;i++) {
        for(int j=0;j<num_pi;j++) {
            if( (prime_implicants[j].bits & ~prime_implicants[j].mask) == (minterms[i] & ~prime_implicants[j].mask)){
                covered[i][j]=1;
            }
            else covered[i][j]=0;
        }
    }
    // Essential prime implicants
    int essential[MAX_PI];
    memset(essential, 0, sizeof(essential));
    for(int i=0;i<num_minterms;i++){
        int count_p=0, last_p=-1;
        for(int j=0;j<num_pi;j++) if(covered[i][j]){
            count_p++;
            last_p =j;
        }
        if(count_p ==1){
            essential[last_p]=1;
        }
    }
    // Select essential PI
    int selected[MAX_PI];
    memset(selected, 0, sizeof(selected));
    for(int j=0;j<num_pi;j++) if(essential[j]) selected[j]=1;
    // Cover minterms with selected PI
    int covered_minterms[num_minterms];
    memset(covered_minterms, 0, sizeof(covered_minterms));
    for(int i=0;i<num_minterms;i++) {
        for(int j=0;j<num_pi;j++) if(selected[j] && covered[i][j]){
            covered_minterms[i]=1;
            break;
        }
    }
    // Greedy for remaining
    while(1){
        int all =1;
        for(int i=0;i<num_minterms;i++) if(!covered_minterms[i]) {all=0; break;}
        if(all) break;
        // Find PI that covers most uncovered
        int best =-1, best_count= -1;
        for(int j=0;j<num_pi;j++) if(!selected[j] && !essential[j]){
            int cnt=0;
            for(int i=0;i<num_minterms;i++) if(!covered_minterms[i] && covered[i][j]) cnt++;
            if(cnt > best_count){
                best_count=cnt;
                best =j;
            }
        }
        if(best==-1) break;
        selected[best]=1;
        for(int i=0;i<num_minterms;i++) if(covered[i][best]) covered_minterms[i]=1;
    }
    // Build expression
    char expr[MAX_EXPR] = "";
    for(int j=0;j<num_pi;j++) if(selected[j]){
        char term[32]="";
        for(int b=0;b<n;b++){
            unsigned int mask = 1<<(n-1-b);
            if(prime_implicants[j].mask & mask){
                strcat(term, "!");
            }
            if(!(prime_implicants[j].mask & mask)){
                char var[2] = { 'a' +b, '\0'};
                strcat(term, var);
            }
        }
        if(strlen(term)==0){
            strcpy(term, "T");
        }
        else{
            // Insert & between literals
            char temp[32]="";
            for(int k=0; k<strlen(term); ){
                if(term[k]=='!'){
                    temp[strlen(temp)] = '!';
                    k++;
                    temp[strlen(temp)] = 'a' + (__builtin_ctz(~0U ^ ((1<<n)-1)) ); // not accurate, fix below
                }
                else{
                    temp[strlen(temp)] = term[k];
                    k++;
                }
            }
            strcpy(term, "");
            int first=1;
            for(int k=0; k<n; k++){
                unsigned int mask = 1<<(n-1 -k);
                if(prime_implicants[j].mask & mask){
                    strcat(term, "!");
                }
                if(!(prime_implicants[j].mask & mask)){
                    char var[2] = { 'a' +k, '\0'};
                    strcat(term, var);
                }
                if(k !=n-1){
                    int next =0;
                    for(int m=k+1;m<n;m++) if(!(prime_implicants[j].mask & (1<<(n-1 -m)))){
                        next=1; break;
                    }
                    if(next) strcat(term, "&");
                }
            }
        }
        if(strlen(expr)!=0) strcat(expr, "|");
        strcat(expr, term);
    }
    if(strlen(expr)==0) printf("F");
    else printf("%s", expr);
}