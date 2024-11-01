#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

#define MAXN 1000005
#define MAXBUF 1<<24

char input_buf[MAXBUF];
int input_pos = 0, input_len = 0;

char output_buf[MAXBUF];
int output_pos = 0;

inline char get_char() {
    if (input_pos == input_len) {
        input_len = fread(input_buf, 1, MAXBUF, stdin);
        if (input_len == 0) return EOF;
        input_pos = 0;
    }
    return input_buf[input_pos++];
}

inline int read_int(int *x) {
    char c;
    *x = 0;
    int sign = 1;
    while ((c = get_char()) != EOF && (c < '0' || c > '9') && c != '-');
    if (c == '-') { sign = -1; c = get_char(); }
    if (c == EOF) return 0;
    do {
        *x = (*x) * 10 + (c - '0');
    } while ((c = get_char()) >= '0' && c <= '9');
    *x *= sign;
    return 1;
}

inline void flush_output() {
    fwrite(output_buf, 1, output_pos, stdout);
    output_pos = 0;
}

inline void write_int(int x) {
    if (output_pos + 12 >= MAXBUF) flush_output();
    if (x == 0) {
        output_buf[output_pos++] = '0';
        output_buf[output_pos++] = '\n';
        return;
    }
    if (x < 0) {
        output_buf[output_pos++] = '-';
        x = -x;
    }
    char tmp[12];
    int cnt = 0;
    while (x > 0) {
        tmp[cnt++] = '0' + (x % 10);
        x /= 10;
    }
    for(int i = cnt-1;i >=0;i--) output_buf[output_pos++] = tmp[i];
    output_buf[output_pos++] = '\n';
}

ll fenwick[MAXN];
int n, opt, mod, mn, mx;

// Add value to index idx
void add_fenwick(int idx, ll val){
    while(idx <= n){
        fenwick[idx] += val;
        idx += idx & -idx;
    }
}

// Get prefix sum up to idx
ll get_fenwick(int idx){
    ll res = 0;
    while(idx > 0){
        res += fenwick[idx];
        idx -= idx & -idx;
    }
    return res;
}

int main(){
    // Fast IO setup
    // Read n, opt, mod, min, max
    read_int(&n);
    read_int(&opt);
    read_int(&mod);
    read_int(&mn);
    read_int(&mx);
    
    char op_type;
    int L, R, X;
    for(int i = 0; i < opt; i++){
        // Read operation type
        // Skip any non-letter characters
        do{
            op_type = get_char();
            if(op_type == EOF) break;
        } while((op_type != 'A') && (op_type != 'Q'));
        if(op_type == 'A'){
            // Read L, R, X
            read_int(&L);
            read_int(&R);
            read_int(&X);
            add_fenwick(L, X);
            add_fenwick(R+1, -X);
        }
        else if(op_type == 'Q'){
            // Read L, R
            read_int(&L);
            read_int(&R);
            int cnt = 0;
            for(int j = L; j <= R; j++){
                ll A = get_fenwick(j);
                ll T = (A * (ll)j) % mod;
                if(T < 0) T += mod;
                if(T >= mn && T <= mx) cnt++;
            }
            write_int(cnt);
        }
    }
    // Read Final
    int Final;
    read_int(&Final);
    // Compute final A[i]
    ll *A = (ll*)malloc((n+2)*sizeof(ll));
    for(int i =1;i<=n;i++) A[i] = get_fenwick(i);
    // Compute C[i] and prefix sum P[i]
    char *C = (char*)malloc((n+2)*sizeof(char));
    int *P = (int*)malloc((n+2)*sizeof(int));
    P[0] = 0;
    for(int i=1;i<=n;i++){
        ll T = (A[i] * (ll)i) % mod;
        if(T < 0) T += mod;
        C[i] = (T >= mn && T <= mx) ? 1 : 0;
        P[i] = P[i-1] + C[i];
    }
    free(A);
    free(C);
    // Process Final queries
    for(int i=0;i<Final;i++){
        read_int(&L);
        read_int(&R);
        if(L > R){
            write_int(0);
            continue;
        }
        if(L <1) L =1;
        if(R >n) R =n;
        if(L > R){
            write_int(0);
            continue;
        }
        write_int(P[R] - P[L-1]);
    }
    free(P);
    flush_output();
    return 0;
}