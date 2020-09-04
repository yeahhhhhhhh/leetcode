#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;

// 通用数据结构
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

namespace TreeDemo{
    TreeNode* buildTree(int preRoot, int inorderStart, int inorderEnd, unordered_map<int, int>& indexMap, vector<int>& preorder, vector<int>& inorder){
        if(inorderStart > inorderEnd){
            return NULL;
        }
        // 根节点
        TreeNode* root = new TreeNode(preorder[preRoot]);
        // 找到根节点在中序的位置
        int index = indexMap[preorder[preRoot]];
        // 左孩子
        root->left = buildTree(preRoot + 1, inorderStart, index - 1, indexMap, preorder, inorder);
        // 右孩子, 先序位置为当前位置加上中序中左孩子个数+1
        root->right = buildTree(preRoot + index - inorderStart + 1, index + 1, inorderEnd, indexMap, preorder, inorder);
        return root;
    }

    // 输入前序和中序遍历结果，重建二叉树
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.size() == 0){
            return NULL;
        }
        // 将中序遍历的值与索引存入map，方便查找
        unordered_map<int, int> indexMap;
        for(int i = 0; i < inorder.size(); i++){
            indexMap.insert(make_pair(inorder[i], i));
        }
        return buildTree(0, 0, inorder.size() - 1, indexMap, preorder, inorder);
    }

    bool helper(TreeNode* A, TreeNode* B){
        if(B == NULL){
            return true;
        }
        if(A == NULL || A->val != B->val){
            return false;
        }
        return helper(A->left, B->left) && helper(A->right, B->right);
    }

    // 树的子结构
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        if(A == NULL || B == NULL){
            return false;
        }
        if(A->val == B->val && helper(A, B)){
            return true;
        }
        return isSubStructure(A->left, B) || isSubStructure(A->right, B);
    }

    // 二叉树的镜像
    TreeNode* mirrorTree(TreeNode* root) {
        if(root == NULL){
            return NULL;
        }
        TreeNode* tmp = root->left;
        root->left = root->right;
        root->right = tmp;
        mirrorTree(root->left);
        mirrorTree(root->right);
        return root;
    }

    bool recur(TreeNode* left, TreeNode* right){
        if(left == NULL && right == NULL){
            return true;
        }
        if(left == NULL || right == NULL || left->val != right->val){
            return false;
        }
        return recur(left->left, right->right) && recur(left->right, right->left);
    }

    // 对称二叉树
    bool isSymmetric(TreeNode* root) {
        if(root == NULL){
            return true;
        }
        return recur(root->left, root->right);
    }
}