/*洛谷题，区间最小值查询
算法：ST表*/
#include<iostream>
#include<cmath>
#include<vector>
using namespace std;
const int N=1e6+10;
const int DEP=17;
int st[DEP][N];
void build(int n){
    for(int i=1;i<=DEP;i++){
        for(int j=1;j+(1<<i)-1<=n;j++){//枚举区间起点,区间长度为2^i,区间终点为j+(1<<i)-1
            st[i][j]=min(st[i-1][j],st[i-1][j+(1<<i-1)]);
        }
    }
}
int query(int l,int r){
    int k=log2(r-l+1);
    return min(st[k][l],st[k][r-(1<<k)+1]);//查询区间[l,l+(1<<k)-1]和[r-(1<<k)+1,r]的最小值,两区间可能重叠，但不影响最值查询，且能刚好覆盖[l,r]区间
}   
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>st[0][i];
    build(n);
    vector<int> ans;
    while(m--){
        int l,r;
        cin>>l>>r;
        ans.push_back(query(l,r));
    }
    for(int i=0;i<ans.size();i++){
        cout<<ans[i]<<" ";
    }
    return 0;
}