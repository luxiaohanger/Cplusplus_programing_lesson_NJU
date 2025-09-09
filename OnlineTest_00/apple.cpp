#include <iostream>

using namespace std;

int count(int M, int N) {
    // 创建dp表，大小至少为[M+1][N+1]
    int dp[M+1][N+1];

    // 初始化
    for (int j = 0; j <= N; j++) {
        dp[0][j] = 1;
    }
    for (int i = 1; i <= M; i++) {
        dp[i][0] = 0;
    }

    // 动态规划
    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= N; j++) {
            if (i >= j) {
                dp[i][j] = dp[i][j-1] + dp[i-j][j];
            } else {
                dp[i][j] = dp[i][j-1];
            }
        }
    }
    return dp[M][N];
}

int main() {
    int M, N;
    cin >> M >> N;
    cout << count(M, N);
    return 0;
}