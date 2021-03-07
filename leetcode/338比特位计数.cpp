class Solution {
public:
    vector<int> countBits(int num) {
    	vector<int>v(num+1,0);
    	for(int i=0;i<=num;i++)
    		v[i]=v[(i&(i-1))]+1;//去掉最右边一位1,0不符合
    	return v;
    }
};
class Solution {
public:
    vector<int> countBits(int num) {
    	vector<int>v(num+1,0);
    	for(int i=0;i<=num;i++)
    		v[i]=v[i>>1]+(i&1);
    	return v;
    }
};