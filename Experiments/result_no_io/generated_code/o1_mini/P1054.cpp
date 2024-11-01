#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef long long ll;

typedef struct {
    char s[60];
    int pos;
} Parser;

ll a_val_global;

char current_char(Parser* p) {
    while (p->s[p->pos] == ' ') p->pos++;
    return p->s[p->pos];
}

ll power_func(ll base, ll exp) {
    ll res = 1;
    for(int i=0;i<exp;i++) res *= base;
    return res;
}

ll parseExpr(Parser* p);
ll parseTerm(Parser* p);
ll parseFactor(Parser* p);
ll parsePower(Parser* p);

ll parseExpr(Parser* p) {
    ll res = parseTerm(p);
    while(1){
        char c = current_char(p);
        if(c == '+' || c == '-'){
            p->pos++;
            ll tmp = parseTerm(p);
            if(c == '+') res += tmp;
            else res -= tmp;
        }
        else break;
    }
    return res;
}

ll parseTerm(Parser* p) {
    ll res = parseFactor(p);
    while(1){
        char c = current_char(p);
        if(c == '*'){
            p->pos++;
            ll tmp = parseFactor(p);
            res *= tmp;
        }
        else break;
    }
    return res;
}

ll parseFactor(Parser* p) {
    ll res = parsePower(p);
    while(1){
        char c = current_char(p);
        if(c == '^'){
            p->pos++;
            ll tmp = parsePower(p);
            res = power_func(res, tmp);
        }
        else break;
    }
    return res;
}

ll parsePower(Parser* p) {
    char c = current_char(p);
    if(c == 'a'){
        p->pos++;
        return a_val_global;
    }
    else if(c == '('){
        p->pos++;
        ll tmp = parseExpr(p);
        if(current_char(p) == ')') p->pos++;
        return tmp;
    }
    else{
        ll num = 0;
        while(isdigit(current_char(p))){
            num = num *10 + (current_char(p) - '0');
            p->pos++;
        }
        return num;
    }
}

ll evaluate(char* expr, int a_val){
    Parser p;
    strcpy(p.s, expr);
    p.pos = 0;
    a_val_global = a_val;
    return parseExpr(&p);
}

int main(){
    char main_expr[60];
    fgets(main_expr, sizeof(main_expr), stdin);
    int len = strlen(main_expr);
    if(main_expr[len-1]=='\n') main_expr[len-1]='\0';

    int n;
    scanf("%d", &n);
    char options[26][60];
    for(int i=0;i<n;i++) {
        scanf(" %[^\n]", options[i]);
    }

    int a_set[] = {1,2,3,4,5,6,7,8,9,10};
    int a_size = 10;
    ll main_vals[a_size];
    for(int i=0;i<a_size;i++) main_vals[i] = evaluate(main_expr, a_set[i]);

    char result[27];
    int res_len = 0;
    for(int i=0;i<n;i++){
        int same = 1;
        for(int j=0;j<a_size;j++) {
            if(evaluate(options[i], a_set[j]) != main_vals[j]){
                same = 0;
                break;
            }
        }
        if(same){
            result[res_len++] = 'A' + i;
        }
    }
    result[res_len] = '\0';
    printf("%s", result);
}