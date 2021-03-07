// https://leetcode-cn.com/problems/trapping-rain-water/
class Solution {
public:
    int trap(vector<int>& height) {
    	int n=height.size();
    	int left[n+2],right[n+2],i,ans=0;
    	memset(right,0,sizeof(right));
    	for(left[0]=0,i=1;i<n;++i)
    		left[i]=max(left[i-1],height[i-1]);
    	for(i=n-2;i>=0;--i)//数组越界
    		right[i]=max(right[i+1],height[i+1]);
    	for(int i=1;i<n-1;i++){
    		int leavl=min(right[i],left[i]);
    		ans+=(leavl-height[i]>0?leavl-height[i]:0);
    	}
    	return ans;
    }
};
//[]