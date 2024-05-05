const int base = 90;
ll POW[maxn], hashA[maxn];


int getHash(int i, int j){
    return (hashA[j] - hashA[i-1] * POW[j-i+1] + MOD*MOD) % MOD;
}

void solve(){ 
    string a, b; cin >> a >> b;
    int n = a.size();
    int m = b.size();
    a = " " + a;
    b = " " + b;
    POW[0] = 1;
    for(int i = 1; i <= n; i++)
        POW[i] = (POW[i-1]*base) % MOD;

    hashA[0] = 0;
    for(int i = 1; i <= n; i++)
        hashA[i] = (hashA[i-1] * base + a[i] - 'a' + 1) % MOD;

    ll hashB = 0;
    for(int i = 1; i <= m; i++)
        hashB = (hashB * base + b[i] - 'a' + 1) % MOD;

    for(int i = 1; i <= n-m+1; i++)
        if(hashB == getHash(i, i+m-1))
            cout << i << " ";

}
