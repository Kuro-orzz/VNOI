const int base = 331;

ll hashS[maxn], hashX[maxn], p[maxn];

void calc(int n, string &s, string &x){
    p[0] = 1;
    for(int i = 1; i <= n; i++)
        p[i] = (p[i-1] * base) % MOD;
    s = ' ' + s;
    x = ' ' + x;
    hashS[0] = 0;
    for(int i = 1; i <= n; i++)
        hashS[i] = (hashS[i-1] * base + s[i] - 'a' + 1) % MOD;
    hashX[0] = 0;
    for(int i = 1; i <= n; i++)
        hashX[i] = (hashX[i-1] * base + x[i] - 'a' + 1) % MOD;
}

ll getHash(int i, int j, ll hash[]){
    return (hash[j]-hash[i-1]*p[j-i+1]+MOD*MOD)%MOD;
}

bool check_even(int n, int m){
    for(int i = 1; i <= n-m+1; i++){
        int j = i+m-1;
        int k = i+m/2;
        if(getHash(i, k-1, hashS) == getHash(n-j+1, n-k+1, hashX))
            return true;
    }
    return false;
}

bool check_odd(int n, int m){
    for(int i = 1; i <= n-m+1; i++){
        int j = i+m-1;
        int k = i+m/2;
        if(getHash(i, k-1, hashS) == getHash(n-j+1, n-k, hashX))
            return true;
    }
    return false;
}

ll bin_even(int n){
    int res = 0;
    int l = 1, r = n/2;
    while(l <= r){
        int m = (l + r) / 2;
        if(check_even(n, 2*m)){
            res = max(res, 2*m);
            l = m+1;
        }
        else
            r = m-1;
    }
    return res;
}

ll bin_odd(int n){
    int res = 0;
    int l = 1, r = n/2;
    while(l <= r){
        int m = (l + r) / 2;
        if(check_odd(n, 2*m+1)){
            res = max(res, 2*m+1);
            l = m+1;
        }
        else
            r = m-1;
    }
    return res;
}

void solve(){
    int n; cin >> n;
    string s; cin >> s;
    string x = s;
    reverse(all(x));
    calc(n, s, x);
    int ans1 = bin_odd(n), ans2 = bin_even(n);
    cout << max(ans1, ans2);
}
