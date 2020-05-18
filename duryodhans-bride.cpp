#include <bits/stdtr1c++.h>
#define MAX 616
#define clr(ar) memset(ar, 0, sizeof(ar))
using namespace std;
const long long HMOD[] = {2078526727, 2117566807};
const long long BASE[] = {1572872831, 1971536491};
int n, m;
char str[2][MAX];
long long ar[4 * MAX * MAX];
long long P[2][MAX], H[2][2][MAX][MAX], R[2][2][MAX][MAX];
void generate(){
    int i, j, k, d;
    unsigned long long x;
    clr(H), clr(R);
    for (d = 0; d < 2; d++){
        for (P[d][0] = 1, i = 1; i < MAX; i++) P[d][i] = (P[d][i - 1] * BASE[d]) % HMOD[d];
    }
    for (d = 0; d < 2; d++){
        for (i = 0; i < 2; i++){
            for (j = 0; j < n; j++){
                for (k = j, x = 0; k < n; k++){
                    x = ((x * BASE[d]) + str[i][k] + 1007) % HMOD[d];
                    H[d][i][j][k] = x;
                }
            }
            for (j = n - 1; j >= 0; j--){
                for (k = j, x = 0; k >= 0; k--){
                    x = ((x * BASE[d]) + str[i][k] + 1007) % HMOD[d];
                    R[d][i][k][j] = x;
                }
            }
        }
    }
}
void simulate(){
    generate();
    long long val[2][2];
    int d, i, j, k, l, v;
    for (k = 0; k < 2; k++){
        for (i = 0; i < n; i++){
            val[0][0] = (R[0][k][0][i] * P[0][i + 1] + H[0][k ^ 1][0][i]) % HMOD[0];
            val[1][0] = (R[1][k][0][i] * P[1][i + 1] + H[1][k ^ 1][0][i]) % HMOD[1];
            for (j = i, d = k ^ 1; j < n; j++, d ^= 1){
                for (v = 0; v < 2; v++){
                    val[v][1] = ((val[v][0] * P[v][n - j - 1]) + H[v][d][j + 1][n - 1]) % HMOD[v];
                    val[v][1] = ((val[v][1] * P[v][n - j - 1]) + R[v][d ^ 1][j + 1][n - 1]) % HMOD[v];
                    val[v][0] = ((val[v][0] * BASE[v]) + str[d][j + 1] + 1007) % HMOD[v];
                    val[v][0] = ((val[v][0] * BASE[v]) + str[d ^ 1][j + 1] + 1007) % HMOD[v];
                }
                ar[m++] = (val[0][1] << 32) | val[1][1];
            }
        }
    }
}
int main(){
    int t, i, j, res;
    scanf("%d", &t);
    while (t--){
        m = 0;
        scanf("%d", &n);
        scanf("%s %s", str[0], str[1]);
        simulate();
        for (i = 0; i < 2; i++) reverse(str[i], str[i] + n);
        simulate();
        sort(ar, ar + m);
        res = 0, ar[m] = -1;
        for (i = 0; i < m; i++) res += (ar[i] != ar[i + 1]);
        printf("%d\n", res);
        ///fprintf(stderr, "%d = %d = %d\n", res, 2 * ((n * n) - n + 2), (2 * ((n * n) - n + 2)) - res);
    }
    return 0;
}
