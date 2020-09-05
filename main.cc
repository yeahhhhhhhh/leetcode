#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <queue>
#include <deque>

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

    // 二叉树层次遍历，“之”字形打印
    vector<vector<int>> levelOrder(TreeNode* root) {
        if(root == NULL){
            return {};
        }
        vector<vector<int> > ret;
        deque<TreeNode*> q;
        bool flag = true;
        q.push_front(root);
        while(q.size() > 0){
            int size = q.size();
            vector<int> subRet;
            for(int i = 0; i < size; i++){
                TreeNode* tmp = NULL;
                if(flag){
                    tmp = q.front();
                    q.pop_front();
                    subRet.push_back(tmp->val);
                    if(tmp->left != NULL){
                        q.push_back(tmp->left);
                    }
                    if(tmp->right != NULL){
                        q.push_back(tmp->right);
                    }
                }else{
                    tmp = q.back();
                    q.pop_back();
                    subRet.push_back(tmp->val);
                    if(tmp->right != NULL){
                        q.push_front(tmp->right);
                    }
                    if(tmp->left != NULL){
                        q.push_front(tmp->left);
                    }
                }
            }
            flag = !flag;
            ret.push_back(subRet);
        }
        return ret;
    }

    bool recur(vector<int>& postorder, int i, int j){
        if(i >= j){
            return true;
        }
        int p = i;
        while(postorder[p] < postorder[j]){
            p++;
        }
        int m = p;
        while(postorder[p] > postorder[j]){
            p++;
        }
        return (p == j) && recur(postorder, i, m - 1) && recur(postorder, m, j - 1);
    }

    // 利用二叉树的后序遍历判断是否是二叉搜索树——暴力递归n2
    bool verifyPostorder(vector<int>& postorder) {
        if(postorder.size() == 0){
            return true;
        }
        return recur(postorder, 0, postorder.size() - 1);
    }

    void recur(TreeNode* root, int target, vector<int>& path, vector<vector<int> >& ret){
        if(root == NULL){
            return;
        }
        target -= root->val;
        path.push_back(root->val);
        if(target == 0 && root->left == NULL && root->right == NULL){
            ret.push_back(path);
        }
        recur(root->left, target, path, ret);
        recur(root->right, target, path, ret);
        path.pop_back();
    }

    // 二叉树中和为某一值的路径
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        if(root == NULL){
            return {};
        }
        vector<vector<int> > ret;
        vector<int> path;
        recur(root, sum, path, ret);
        return ret; 
    }
}