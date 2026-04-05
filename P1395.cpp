#include <iostream>
#include <cstring>
using namespace std;
const int N = 1e5+10;
struct Edge{
    int to,next;
}e[N];
int head[N<<1],cnt;
int si[N],val[N];
bool vis[N];
void add(int u,int v){
    e[++cnt].to=v;
    e[cnt].next=head[u];
    head[u]=cnt;
}
void dfs1(int u){
    vis[u]=1;
    for(int i=head[u];i;i=e[i].next){
        if(e[i].to==0)continue;
        if(vis[e[i].to])continue;
        dfs1(e[i].to);
        si[u]+=si[e[i].to];
        val[u]+=val[e[i].to]+si[e[i].to];
    }
    si[u]+=1;
}
void dfs2(int u){
    vis[u]=1;
    for(int i=head[u];i;i=e[i].next){
        if(e[i].to==0)continue;
        if(vis[e[i].to])continue;   
        val[e[i].to]=val[u]+si[1]-si[e[i].to]*2;
        dfs2(e[i].to);
    }
}
int main(){
    int n;
    cin>>n;
    for(int i=1;i<n;i++){
        int u,c;
        cin>>u>>c;
        add(u,c);
        add(c,u);
    }
    dfs1(1);//根不一定是1，因为输入是一张图；
    memset(vis,0,sizeof(vis));
    dfs2(1);
    int minn=1e9,k;
    for(int i=1;i<=n;i++){
        //cout<<val[i]<<endl;
        if(val[i]<minn){
            minn=val[i];
            k=i;
        }
    }
    cout<<k<<" "<<minn<<endl;   
    return 0;
}
