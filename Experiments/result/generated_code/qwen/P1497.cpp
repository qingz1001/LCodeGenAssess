#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20

int factorial(int n) {
    if (n == 0 || n == 1) return 1;
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    int n, k, h;
    scanf("%d %d %d", &n, &k, &h);

    int colors[MAX_N];
    for (int i = 0; i < h; i++) {
        scanf("%d", &colors[i]);
    }

    int total_ways = 0;

    for (int i = 0; i < h; i++) {
        int remaining_k = k - colors[i];
        if (remaining_k < 0) break;
        for (int j = 0; j < h; j++) {
            if (i != j && remaining_k >= colors[j]) {
                int remaining_k2 = remaining_k - colors[j];
                if (remaining_k2 < 0) break;
                for (int l = 0; l < h; l++) {
                    if (i != l && j != l && remaining_k2 >= colors[l]) {
                        int remaining_k3 = remaining_k2 - colors[l];
                        if (remaining_k3 < 0) break;
                        for (int m = 0; m < h; m++) {
                            if (i != m && j != m && l != m && remaining_k3 >= colors[m]) {
                                int remaining_k4 = remaining_k3 - colors[m];
                                if (remaining_k4 < 0) break;
                                for (int o = 0; o < h; o++) {
                                    if (i != o && j != o && l != o && m != o && remaining_k4 >= colors[o]) {
                                        int remaining_k5 = remaining_k4 - colors[o];
                                        if (remaining_k5 < 0) break;
                                        for (int p = 0; p < h; p++) {
                                            if (i != p && j != p && l != p && m != p && o != p && remaining_k5 >= colors[p]) {
                                                int remaining_k6 = remaining_k5 - colors[p];
                                                if (remaining_k6 < 0) break;
                                                for (int q = 0; q < h; q++) {
                                                    if (i != q && j != q && l != q && m != q && o != q && p != q && remaining_k6 >= colors[q]) {
                                                        int remaining_k7 = remaining_k6 - colors[q];
                                                        if (remaining_k7 < 0) break;
                                                        for (int r = 0; r < h; r++) {
                                                            if (i != r && j != r && l != r && m != r && o != r && p != r && q != r && remaining_k7 >= colors[r]) {
                                                                int remaining_k8 = remaining_k7 - colors[r];
                                                                if (remaining_k8 < 0) break;
                                                                for (int s = 0; s < h; s++) {
                                                                    if (i != s && j != s && l != s && m != s && o != s && p != s && q != s && r != s && remaining_k8 >= colors[s]) {
                                                                        int remaining_k9 = remaining_k8 - colors[s];
                                                                        if (remaining_k9 < 0) break;
                                                                        for (int t = 0; t < h; t++) {
                                                                            if (i != t && j != t && l != t && m != t && o != t && p != t && q != t && r != t && s != t && remaining_k9 >= colors[t]) {
                                                                                int remaining_k10 = remaining_k9 - colors[t];
                                                                                if (remaining_k10 < 0) break;
                                                                                for (int u = 0; u < h; u++) {
                                                                                    if (i != u && j != u && l != u && m != u && o != u && p != u && q != u && r != u && s != u && t != u && remaining_k10 >= colors[u]) {
                                                                                        int remaining_k11 = remaining_k10 - colors[u];
                                                                                        if (remaining_k11 < 0) break;
                                                                                        for (int v = 0; v < h; v++) {
                                                                                            if (i != v && j != v && l != v && m != v && o != v && p != v && q != v && r != v && s != v && t != v && u != v && remaining_k11 >= colors[v]) {
                                                                                                int remaining_k12 = remaining_k11 - colors[v];
                                                                                                if (remaining_k12 < 0) break;
                                                                                                for (int w = 0; w < h; w++) {
                                                                                                    if (i != w && j != w && l != w && m != w && o != w && p != w && q != w && r != w && s != w && t != w && u != w && v != w && remaining_k12 >= colors[w]) {
                                                                                                        int remaining_k13 = remaining_k12 - colors[w];
                                                                                                        if (remaining_k13 < 0) break;
                                                                                                        for (int x = 0; x < h; x++) {
                                                                                                            if (i != x && j != x && l != x && m != x && o != x && p != x && q != x && r != x && s != x && t != x && u != x && v != x && w != x && remaining_k13 >= colors[x]) {
                                                                                                                int remaining_k14 = remaining_k13 - colors[x];
                                                                                                                if (remaining_k14 < 0) break;
                                                                                                                for (int y = 0; y < h; y++) {
                                                                                                                    if (i != y && j != y && l != y && m != y && o != y && p != y && q != y && r != y && s != y && t != y && u != y && v != y && w != y && x != y && remaining_k14 >= colors[y]) {
                                                                                                                        int remaining_k15 = remaining_k14 - colors[y];
                                                                                                                        if (remaining_k15 < 0) break;
                                                                                                                        for (int z = 0; z < h; z++) {
                                                                                                                            if (i != z && j != z && l != z && m != z && o != z && p != z && q != z && r != z && s != z && t != z && u != z && v != z && w != z && x != z && y != z && remaining_k15 >= colors[z]) {
                                                                                                                                int remaining_k16 = remaining_k15 - colors[z];
                                                                                                                                if (remaining_k16 < 0) break;
                                                                                                                                total_ways++;
                                                                                                                            }
                                                                                                                        }
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    printf("%d\n", total_ways);

    return 0;
}