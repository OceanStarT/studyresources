// https://leetcode-cn.com/problems/sudoku-solver/
#include <bits/stdc++.h>
class Solution {
public:
	int row[9][10],col[9][10],sudoku[9][10],a[9][9],x,y,ans=0;
	vector<pair<int,int>> v;
	int boardNum(int i,int j){
		return i/3*3 + j/3;
	}
	int dfs(int index){
		if(index>=ans) return 1;
		int i=v[index].first,j=v[index].second;
		for(int k=1;k<=9;k++){
			if(!row[i][k] && !col[j][k] && !sudoku[boardNum(i,j)][k]){
				row[i][k]=1;col[j][k]=1;sudoku[boardNum(i,j)][k]=1;a[i][j]=k;
				if(dfs(index+1)) return 1;
				row[i][k]=0;col[j][k]=0;sudoku[boardNum(i,j)][k]=0;a[i][j]=0;
			}
		}
		return 0;
	}
    void solveSudoku(vector<vector<char>>& board) {
    	memset(row,0,sizeof(row));
    	memset(col,0,sizeof(col));
    	memset(sudoku,0,sizeof(sudoku));
    	for(int i=0;i<9;i++){
    		for(int j=0;j<9;j++){
    			if(board[i][j]=='.'){
    				a[i][j]=0;
    				v.push_back(make_pair(i,j));
    				ans++;
    			}
    			else {
    				a[i][j]=(int)(board[i][j]-'0');
    				row[i][a[i][j]]=1;
    				col[j][a[i][j]]=1;
    				sudoku[boardNum(i,j)][a[i][j]]=1;
    			}
    		}
    	}
    	dfs(0);
    	for(int i=0;i<9;i++)
    		for(int j=0;j<9;j++)
    			board[i][j]=(char)a[i][j]+'0';
    }
};