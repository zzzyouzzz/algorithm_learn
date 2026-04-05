#include <iostream>
#include <queue>
using namespace std;
const int N = 1e5+10;
struct Edge{
    int to,next;
}e[N<<1];
int head[N],cnt;
bool vis[N];
queue<pair<int,int>> q;
void add(int u,int v){
    e[++cnt].to=v;
    e[cnt].next=head[u];
    head[u]=cnt;
}
void bfs(int u,int d){
    q.push({u,0});
    vis[u]=1;
    int res=0;
    while(!q.empty()){
        int u=q.front().first,step=q.front().second;
        q.pop();
        for(int i=head[u];i;i=e[i].next){
            if(e[i].to==0)continue;
            if(vis[e[i].to])continue;
            vis[e[i].to]=1;
            if(step+1>d)continue;
            res++;
            q.push({e[i].to,step+1});
        }
    }
    cout<<res<<endl;
}
int main(){
    int n,d;
    cin>>n>>d;
    for(int i=1;i<n;i++){
        int u,c;
        cin>>u>>c;
        add(u,c);
        add(c,u);
    }
    bfs(1,d);
    return 0;
}
