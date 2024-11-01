#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int n;
char A[27], B[27], C_str[27];
int mapping[26];
bool used_digit[26];
bool found = false;

bool solve(int pos, int carry) {
    if (found) return false;
    if (pos < 0) {
        if (carry == 0) {
            found = true;
            return true;
        }
        return false;
    }
    char la = A[pos] - 'A';
    char lb = B[pos] - 'A';
    char lc = C_str[pos] - 'A';
    int da = mapping[la];
    int db = mapping[lb];
    int dc = mapping[lc];
    
    if (da != -1 && db != -1 && dc != -1) {
        int total = da + db + carry;
        if ((total % n) == dc) {
            return solve(pos - 1, total / n);
        }
        return false;
    }
    else if (da != -1 && db != -1 && dc == -1) {
        int total = da + db + carry;
        int dc_try = total % n;
        int carry_out = total / n;
        if (!used_digit[dc_try]) {
            mapping[lc] = dc_try;
            used_digit[dc_try] = true;
            if (solve(pos - 1, carry_out)) return true;
            mapping[lc] = -1;
            used_digit[dc_try] = false;
        }
        return false;
    }
    else if (da != -1 && db == -1 && dc != -1) {
        for(int carry_out = 0; carry_out <=1; carry_out++) {
            int db_try = lc + carry_out * n - da - carry;
            if(db_try >=0 && db_try < n && !used_digit[db_try]) {
                mapping[lb] = db_try;
                used_digit[db_try] = true;
                if (solve(pos - 1, carry_out)) return true;
                mapping[lb] = -1;
                used_digit[db_try] = false;
            }
        }
        return false;
    }
    else if (da == -1 && db != -1 && dc != -1) {
        for(int carry_out = 0; carry_out <=1; carry_out++) {
            int da_try = lc + carry_out * n - db - carry;
            if(da_try >=0 && da_try < n && !used_digit[da_try]) {
                mapping[la] = da_try;
                used_digit[da_try] = true;
                if (solve(pos - 1, carry_out)) return true;
                mapping[la] = -1;
                used_digit[da_try] = false;
            }
        }
        return false;
    }
    else if (da != -1 && db == -1 && dc == -1) {
        for(int carry_out = 0; carry_out <=1; carry_out++) {
            int sum = da + carry;
            for(int db_try = 0; db_try < n; db_try++) {
                if(!used_digit[db_try]) {
                    int dc_try = (da + db_try + carry) % n;
                    int new_carry = (da + db_try + carry) / n;
                    if(new_carry != carry_out) continue;
                    if(!used_digit[dc_try]) {
                        mapping[lb] = db_try;
                        mapping[lc] = dc_try;
                        used_digit[db_try] = true;
                        used_digit[dc_try] = true;
                        if (solve(pos - 1, carry_out)) return true;
                        mapping[lb] = -1;
                        mapping[lc] = -1;
                        used_digit[db_try] = false;
                        used_digit[dc_try] = false;
                    }
                }
            }
        }
        return false;
    }
    else if (da == -1 && db != -1 && dc == -1) {
        for(int carry_out = 0; carry_out <=1; carry_out++) {
            int sum = db + carry;
            for(int da_try = 0; da_try < n; da_try++) {
                if(!used_digit[da_try]) {
                    int dc_try = (da_try + db + carry) % n;
                    int new_carry = (da_try + db + carry) / n;
                    if(new_carry != carry_out) continue;
                    if(!used_digit[dc_try]) {
                        mapping[la] = da_try;
                        mapping[lc] = dc_try;
                        used_digit[da_try] = true;
                        used_digit[dc_try] = true;
                        if (solve(pos - 1, carry_out)) return true;
                        mapping[la] = -1;
                        mapping[lc] = -1;
                        used_digit[da_try] = false;
                        used_digit[dc_try] = false;
                    }
                }
            }
        }
        return false;
    }
    else if (da == -1 && db == -1 && dc != -1) {
        for(int carry_out = 0; carry_out <=1; carry_out++) {
            for(int da_try = 0; da_try < n; da_try++) {
                if(!used_digit[da_try]) {
                    for(int db_try = 0; db_try < n; db_try++) {
                        if(!used_digit[db_try] && db_try != da_try) {
                            int dc_calc = (da_try + db_try + carry) % n;
                            int new_carry = (da_try + db_try + carry) / n;
                            if(new_carry == carry_out && dc_calc == lc && !used_digit[dc_calc]) {
                                mapping[la] = da_try;
                                mapping[lb] = db_try;
                                used_digit[da_try] = true;
                                used_digit[db_try] = true;
                                used_digit[dc_calc] = true;
                                if (solve(pos - 1, carry_out)) return true;
                                mapping[la] = -1;
                                mapping[lb] = -1;
                                used_digit[da_try] = false;
                                used_digit[db_try] = false;
                                used_digit[dc_calc] = false;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }
    else if (da == -1 && db == -1 && dc == -1) {
        for(int carry_out = 0; carry_out <=1; carry_out++) {
            for(int da_try = 0; da_try < n; da_try++) {
                if(!used_digit[da_try]) {
                    for(int db_try = 0; db_try < n; db_try++) {
                        if(!used_digit[db_try] && db_try != da_try) {
                            int dc_try = (da_try + db_try + carry) % n;
                            int new_carry = (da_try + db_try + carry) / n;
                            if(new_carry == carry_out && !used_digit[dc_try]) {
                                mapping[la] = da_try;
                                mapping[lb] = db_try;
                                mapping[lc] = dc_try;
                                used_digit[da_try] = true;
                                used_digit[db_try] = true;
                                used_digit[dc_try] = true;
                                if (solve(pos - 1, carry_out)) return true;
                                mapping[la] = -1;
                                mapping[lb] = -1;
                                mapping[lc] = -1;
                                used_digit[da_try] = false;
                                used_digit[db_try] = false;
                                used_digit[dc_try] = false;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }
    return false;
}

int main(){
    scanf("%d", &n);
    scanf("%s", A);
    scanf("%s", B);
    scanf("%s", C_str);
    for(int i=0;i<26;i++) mapping[i]=-1;
    memset(used_digit, 0, sizeof(used_digit));
    solve(n-1, 0);
    for(int i=0;i<n;i++){
        printf("%d%c", mapping['A' + i], (i<n-1)?' ':'\n');
    }
    return 0;
}