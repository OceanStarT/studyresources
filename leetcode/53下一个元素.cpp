// https://leetcode-cn.com/problems/next-greater-element-ii/
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
    	int n=nums.size(),pos=0;
    	pair<int,int> p[n<<1|1];
    	vector<int> v(n,-1);
    	for(int i=0;i <(n<<1);i++){
    		while(pos && p[pos].first < nums[i%n]){
    			v[p[pos].second]=nums[i%n];
    			--pos;
    		}
    		p[++pos]=make_pair(nums[i%n],i%n);
    	}
    	return v;
    }
};