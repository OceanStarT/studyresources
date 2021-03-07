#include <cstring>
class Solution {
public:
	#define inf 0x3f3f3f3f3f//一定要足够大
	#define mod 1000000007
	vector<pair<int,int>> v[20005];
	vector<pair<int,int>>pointnum;
	int vis[20004],mark[20005],dis[20004],val[20005];
	void priority_dijkstra(int n){
		priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >que;
		for(int i=0;i<=n;i++){
			dis[i]=inf;
			vis[i]=0;
		}
		vis[n]=1;dis[n]=0;
		que.push(make_pair(0,n));
		while(!que.empty()){
			pair<int,int> p = que.top();
			que.pop();
			if(dis[p.second]<p.first) continue;
			for(int i=0;i<v[p.second].size();i++){
				if(dis[v[p.second][i].first]>dis[p.second]+v[p.second][i].second){
					dis[v[p.second][i].first]=dis[p.second]+v[p.second][i].second;
					que.push(make_pair(dis[v[p.second][i].first],v[p.second][i].first));
				}
			}
		}
	}
	void bfs(int k){//注意距离相等的点
		int now = pointnum[k].second;
		if(now==1) return;
		for(int i=0;i<v[now].size();i++){
			if(mark[v[now][i].first] && pointnum[k].first!=dis[v[now][i].first]){
				val[v[now][i].first]=(val[v[now][i].first]+val[now])%mod;
			}
		}
		mark[now]=0;
		bfs(k+1);
	}
    int countRestrictedPaths(int n, vector<vector<int>>& edges) {
    	for(int i=0;i<edges.size();i++){
    		v[edges[i][0]].push_back(make_pair(edges[i][1],edges[i][2]));
    		v[edges[i][1]].push_back(make_pair(edges[i][0],edges[i][2]));
    	}
    	priority_dijkstra(n);//nlog(n)
    	for(int i=1;i<=n;i++)
    		pointnum.push_back(make_pair(dis[i],i));
    	//按照路径从小到大排序
    	sort(pointnum.begin(),pointnum.end(),[]
    		(const pair<int,int>&a,const pair<int,int>& b){
    			return a.first==b.first?a.second<b.second:a.first<b.first;
    	});
    	for(int i=0;i<=n;i++){
    		val[i]=0;
    		mark[i]=0;
    	}
    	val[n]=1;
    	for(int i=0;i<n;i++)
    		mark[pointnum[i].second]=1;
    	bfs(0);
    	return val[1];
    }
};
/*
10
[[9,10,8],[9,6,5],[1,5,9],[6,8,10],[1,8,1],[8,10,7],[10,7,9],[5,7,3],[4,2,9],[2,3,9],[3,10,4],[1,4,7],[7,6,1],[3,9,8],[9,1,6],[4,7,10],[9,4,9]]
*/