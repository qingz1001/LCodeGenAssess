#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_EXP 1000

typedef struct {
    int coeff[MAX_EXP+1];
    int degree;
} Polynomial;

char expr_str[100];
int pos;

// Function prototypes
void poly_init(Polynomial* p);
void poly_add(Polynomial* a, Polynomial* b, Polynomial* res);
void poly_subtract(Polynomial* a, Polynomial* b, Polynomial* res);
void poly_multiply(Polynomial* a, Polynomial* b, Polynomial* res);
void poly_power(Polynomial* a, int exponent, Polynomial* res);
void skip_spaces();
int get_constant(Polynomial* p);
void parse_expression(Polynomial* p);
void parse_term(Polynomial* p);
void parse_factor(Polynomial* p);
void parse_primary(Polynomial* p);
int poly_equal(Polynomial* a, Polynomial* b);

// Initialize polynomial
void poly_init(Polynomial* p){
    memset(p->coeff, 0, sizeof(p->coeff));
    p->degree = 0;
}

// Add two polynomials
void poly_add(Polynomial* a, Polynomial* b, Polynomial* res){
    poly_init(res);
    res->degree = (a->degree > b->degree) ? a->degree : b->degree;
    for(int i=0;i<=res->degree;i++) {
        res->coeff[i] = a->coeff[i] + b->coeff[i];
    }
}

// Subtract polynomial b from a
void poly_subtract(Polynomial* a, Polynomial* b, Polynomial* res){
    poly_init(res);
    res->degree = (a->degree > b->degree) ? a->degree : b->degree;
    for(int i=0;i<=res->degree;i++) {
        res->coeff[i] = a->coeff[i] - b->coeff[i];
    }
}

// Multiply two polynomials
void poly_multiply(Polynomial* a, Polynomial* b, Polynomial* res){
    poly_init(res);
    for(int i=0;i<=a->degree;i++) {
        for(int j=0;j<=b->degree;j++) {
            if(i + j > MAX_EXP) continue;
            res->coeff[i+j] += a->coeff[i] * b->coeff[j];
            if(i +j > res->degree) res->degree = i +j;
        }
    }
}

// Raise a polynomial to an integer power
void poly_power(Polynomial* a, int exponent, Polynomial* res){
    poly_init(res);
    res->coeff[0] = 1;
    res->degree = 0;
    for(int i=0;i<exponent;i++) {
        Polynomial tmp;
        poly_multiply(res, a, &tmp);
        *res = tmp;
    }
}

// Skip spaces in the expression
void skip_spaces(){
    while(expr_str[pos] == ' ') pos++;
}

// Get constant value from a polynomial
int get_constant(Polynomial* p){
    if(p->degree != 0){
        return -1;
    }
    return p->coeff[0];
}

// Compare two polynomials for equality
int poly_equal(Polynomial* a, Polynomial* b){
    if(a->degree != b->degree){
        return 0;
    }
    for(int i=0;i<=a->degree;i++) {
        if(a->coeff[i] != b->coeff[i]) return 0;
    }
    return 1;
}

// Parse primary expressions: numbers, 'a', or expressions in parentheses
void parse_primary(Polynomial* p){
    poly_init(p);
    skip_spaces();
    if(expr_str[pos] == '('){
        pos++;
        parse_expression(p);
        if(expr_str[pos] == ')') pos++;
    }
    else if(isdigit(expr_str[pos])){
        int num =0;
        while(isdigit(expr_str[pos])){
            num = num *10 + (expr_str[pos] - '0');
            pos++;
        }
        poly_init(p);
        p->coeff[0] = num;
        p->degree =0;
    }
    else if(expr_str[pos] == 'a'){
        pos++;
        poly_init(p);
        p->coeff[1] = 1;
        p->degree =1;
    }
}

// Parse factors handling exponentiation
void parse_factor(Polynomial* p){
    parse_primary(p);
    while(1){
        skip_spaces();
        if(expr_str[pos] == '^'){
            pos++;
            Polynomial exponent_poly;
            parse_primary(&exponent_poly);
            int exponent = get_constant(&exponent_poly);
            Polynomial res;
            poly_power(p, exponent, &res);
            *p = res;
        }
        else{
            break;
        }
    }
}

// Parse terms handling multiplication
void parse_term(Polynomial* p){
    parse_factor(p);
    while(1){
        skip_spaces();
        if(expr_str[pos] == '*'){
            pos++;
            Polynomial q;
            parse_factor(&q);
            Polynomial tmp;
            poly_multiply(p, &q, &tmp);
            *p = tmp;
        }
        else{
            break;
        }
    }
}

// Parse expressions handling addition and subtraction
void parse_expression(Polynomial* p){
    parse_term(p);
    while(1){
        skip_spaces();
        if(expr_str[pos] == '+'){
            pos++;
            Polynomial q;
            parse_term(&q);
            Polynomial tmp;
            poly_add(p, &q, &tmp);
            *p = tmp;
        }
        else if(expr_str[pos] == '-'){
            pos++;
            Polynomial q;
            parse_term(&q);
            Polynomial tmp;
            poly_subtract(p, &q, &tmp);
            *p = tmp;
        }
        else{
            break;
        }
    }
}

int main(){
    char buffer1[100];
    // Read main expression
    if(fgets(buffer1, sizeof(buffer1), stdin) == NULL){
        return 0;
    }
    // Remove trailing newline
    int len = strlen(buffer1);
    if(len >0 && buffer1[len-1] == '\n') buffer1[len-1] = '\0';
    strcpy(expr_str, buffer1);
    pos =0;
    Polynomial main_p;
    parse_expression(&main_p);

    // Read number of options
    int n;
    if(scanf("%d", &n) !=1){
        return 0;
    }
    getchar(); // consume newline after number
    char buffer[100];
    char result[27];
    int res_len =0;
    for(int i=0;i<n;i++){
        if(fgets(buffer, sizeof(buffer), stdin) == NULL){
            break;
        }
        len = strlen(buffer);
        if(len >0 && buffer[len-1] == '\n') buffer[len-1] = '\0';
        strcpy(expr_str, buffer);
        pos =0;
        Polynomial option_p;
        parse_expression(&option_p);
        if(poly_equal(&main_p, &option_p)){
            result[res_len++] = 'A' + i;
        }
    }
    result[res_len] = '\0';
    printf("%s\n", result);
    return 0;
}