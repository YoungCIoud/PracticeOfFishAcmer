a, b = map(int, input().split())
MOD = 998244353
print(a * pow(a + b, -1, MOD) % MOD, b * pow(a + b, -1, MOD) % MOD)