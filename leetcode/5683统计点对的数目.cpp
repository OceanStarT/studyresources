class Solution {
public:
    static const int mod = 100000;
    int ans[mod<<1];
    int lowbit(int x){
        return x&(-x);
    }
    void update(int x,int value){
        for(int i=x;i< (mod<<1);i+=lowbit(i))
            ans[i]+=value;
    }
    int query(int x){
        int cnt=0;
        for(int i=x;i;i-=lowbit(i))
            cnt+=ans[i];
        return cnt;
    }
    vector<int> countPairs(int n, vector<vector<int>>& edges, vector<int>& queries) {
        vector<int> v[n+3];
        vector<int> pos(queries.size(),0);
        int dp[n+2],mark;
        memset(dp,0,sizeof(dp));
        memset(ans,0,sizeof(ans));
        for(int i=0;i<edges.size();i++){
            dp[edges[i][0]]++;
            dp[edges[i][1]]++;
            if(edges[i][0]<edges[i][1]) v[edges[i][0]].push_back(edges[i][1]);
            else v[edges[i][1]].push_back(edges[i][0]);
        }
        for(int i=1;i<=n;i++){
            update(dp[i]+mod,1);
            v[i].push_back(n+1);
        }
        for(int i=1;i<n;i++){
            update(dp[i]+mod,-1);
            sort(v[i].begin(),v[i].end());
            mark=1;
            for(int j=1;j<v[i].size();j++){
                if(v[i][j]==v[i][j-1]){
                    mark++;
                    continue;
                }
                update(dp[v[i][j-1]]+mod,-1);
                update(dp[v[i][j-1]]+mod-mark,1);
                mark=1;
            }
            for(int j=0;j<queries.size();j++){
                int k=queries[j]+mod-dp[i];
                pos[j]+=n-i-query(k);
            }
            mark=1;
            for(int j=1;j<v[i].size();j++){
                if(v[i][j]==v[i][j-1]){
                    mark++;
                    continue;
                }
                update(dp[v[i][j-1]]+mod,1);
                update(dp[v[i][j-1]]+mod-mark,-1);
                mark=1;
            }
        }
        return pos;
    }
};
/*
4
[[1,2],[2,4],[1,3],[2,3],[2,1]]
[2,3]
5
[[1,5],[1,5],[3,4],[2,5],[1,3],[5,1],[2,3],[2,5]]
[1,2,3,4,5]
6
[[5,2],[3,5],[4,5],[1,5],[1,4],[3,5],[2,6],[6,4],[5,6],[4,6],[6,2],[2,6],[5,4],[6,1],[6,1],[2,5],[1,3],[1,3],[4,5]]
[6,9,2,1,2,3,6,6,6,5,9,7,0,4,5,9,1,18,8,9]
*/