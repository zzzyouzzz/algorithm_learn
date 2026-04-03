#include<iostream>
#include<algorithm>
#include<set>
using namespace std;
const int N=40000+5;
const int M=100000+5;
struct node{
    int a,b,w;
    bool operator<(const node &x)const{
        return w>x.w;
    }
}edge[M];
int father[N];
int opp[N];
int find(int x){
    if(father[x]==x) return x;
    else return father[x]=find(father[x]);
}
void merge(int a,int b){
    int fa=find(a);
    int fb=find(b);
    if(fa!=fb) father[fa]=fb;
}
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n*2;i++) father[i]=i;
    for(int i=1;i<=m;i++){
        int a,b;
        char opt;
        cin>>opt>>a>>b;
        if(opt=='F'){
            merge(a,b);
        }else{
            merge(b+n,a);
            merge(a+n,b);
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(find(i)==i)ans++;
    }
    cout<<ans<<endl;
    return 0;
}
