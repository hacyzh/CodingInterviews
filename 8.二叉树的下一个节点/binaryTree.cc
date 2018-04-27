 ///
 /// @file    binaryTree.cc
 /// @author  haiy(hacyzh@163.com)
 /// @date    2018-04-27 20:29:33
 ///
 
#include <iostream>
#include <stdio.h>
using std::cout;
using std::endl;
using std::cin;

typedef struct TreeNode
{
	int Value;
	struct TreeNode*LTreeNode;
	struct TreeNode*RTreeNode;
} BinaryTreeNode;

class BinaryTree
{
public:
	BinaryTree()
	:_root(NULL)
	{}
	~BinaryTree()
	{}

	TreeNode *constructCore(int *start_preorder,int *end_preorder,
			int *start_inorder,int *end_inorder);
	TreeNode * construct(int *preorder,int *inorder,int lenth);
private:
	TreeNode *_root;	
};
TreeNode * BinaryTree::constructCore(int *start_preorder,int *end_preorder,
		int *start_inorder,int *end_inorder)
{
	cout << "constructCore " <<endl;
	TreeNode * root = new TreeNode();
	root->Value = start_preorder[0];
	root->LTreeNode = root->RTreeNode = nullptr;
	if(start_preorder==end_preorder)
	{
		if(start_inorder==end_inorder)
			return root;
		else
			std::cout <<"Invalid input"<<endl;
			return nullptr;
	}

	int *rootInorder = start_inorder;
	while(rootInorder <= end_inorder && *rootInorder != root->Value)
		++rootInorder;

	if(rootInorder == end_inorder && *rootInorder != root->Value)
		std::cout <<"Invalide input"<<endl;

	int leftLength = rootInorder - start_inorder;
	if(leftLength > 0)
	{
		root ->LTreeNode = constructCore(start_preorder+1,start_preorder+leftLength-1,
				start_inorder,start_inorder+leftLength-1);
	}
	if((end_inorder-rootInorder)>0)
	{
		root ->RTreeNode = constructCore(start_preorder+leftLength+1,end_preorder,
				rootInorder,end_inorder);
	}
	return root;
}
TreeNode * BinaryTree::construct(int *preorder,int *inorder,int lenth)
{
	cout << "Now consturc" << endl;
	if(preorder==nullptr||inorder==nullptr||lenth<=0)
		return nullptr;
	return constructCore(preorder,preorder+lenth-1,inorder,inorder+lenth-1);
}
int main()
{
	BinaryTree myTree;
	cout << "输入序列长度:";
	fflush(stdin);
	int n,preorder[64]={0},inorder[64]={0};
	cin >> n;

	cout << "输入前序遍历序列:" ;
	fflush(stdin);
	for(int index=0;index != n ;++index)
	{
		cin >> preorder[index];
	}
	cout << "输入中序遍历序列:" ;
	fflush(stdin);
	for(int index=0;index != n ;++index)
	{
		cin >> inorder[index];
	}
	
	BinaryTreeNode *pNode = myTree.construct(preorder,inorder,n);
	cout << pNode->Value << endl;
	cout << "二叉树构建成功" << endl;
	
}
