#include <bits/stdc++.h>
using namespace std;

#define fast_io() ios::sync_with_stdio(false); cin.tie(nullptr)
#define ll long long
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define vi vector<int>
#define vll vector<ll>
#define vpii vector<pii>
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
#define MOD 1000000007

void solve() 
{
    ll n;
    cin>>n;
    ll ans=(n/5)+(n%5)/4+(((n%5)/4)%4)/3+ ((((n%5)/4)%4)%3)/2 +((((n%5)/4)%4)%3)%2;
}

int main() {
    fast_io();
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}