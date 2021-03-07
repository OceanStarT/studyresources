// https://leetcode-cn.com/problems/russian-doll-envelopes/
// 排序后跑上升子序列
# include <bits/stdc++.h>
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
    	int n=envelopes.size();
    	sort(envelopes.begin(),envelopes.end(),
    		[](const vector<int>& a, const vector<int>& b){
    			return a[0]==b[0]?a[1]>b[1]:a[0]<b[0];
    		});
    	int dp[n+2],len=0;
    	dp[0]=0;
    	for(int i=0;i<n;i++){
    		if(dp[len] < envelopes[i][1]) dp[++len]=envelopes[i][1];
    		else{
    			int k=lower_bound(dp,dp+len+1,envelopes[i][1])-dp;
    			dp[k]=envelopes[i][1];
    		}
    	}
    	return len;
    }
};
/*
[[4,5],[4,6],[6,7],[2,3],[1,1]]
[[2,100],[3,200],[4,300],[5,500],[5,400],[5,250],[6,370],[6,360],[7,380]]
[[30,50],[12,2],[3,4],[12,15]]
[[5,4],[6,4],[6,7],[2,3]]
[[1,1],[1,1],[1,1]]
*/