Data: Transaction database,min_sup,item_sum,faulat factor(g)
Result:All Fault Tolernt(FT) frequent itemsets
Procedure:FT-FP-Growth(Tree,a)
此处应该有个C为空集，用来合并模式串X的所有条件模式串
a为一个模式串
define b为一个空串用来保存找到的模式串，
if a==null then //初始条件下模式串为空
	for each itemsets X of length=|g+1| do 
		for each item i of X do 
			C=C U it is conditional pattern from tree;
			if itemsets-support(X)>=min_sup then
				output X as FT frequent itemsets;
				b=X;
				FT-FP-Tree(C,b);
else
	if Tree contains a single path P then
		for each item pi in the P do 
			X=a U pi
			if itemsets-support(X)>=min_sup and each item 
			i in X has item_support(i)>=item_sup then
				output X as a FT frequent itemsets;
	else
		for each header item hi in the header table of Tree do 
			generate itemsets X = a U hi;
			for each path P of Tree do 
				C=C U generate conditional pattern from P;
			if itemsets-support(X) in C >=min_sup and each
			item i of X in C has item_support(i)>=item_sup
			then 
				output X as a FT frequent itemsets;
				b=X;
				FT-FP-Tree(C,b);