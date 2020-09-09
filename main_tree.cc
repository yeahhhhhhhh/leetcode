#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <stack>
#include <queue>

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

    // 层次遍历，不打印层数
    vector<int> levelorder(TreeNode* root){
        if(root == NULL){
            return {};
        }
        queue<TreeNode*> q;
        q.push(root);
        vector<int> ret;
        while(q.size() > 0){
            TreeNode* tmp = q.front();
            q.pop();
            ret.push_back(tmp->val);
            if(tmp->left != NULL){
                q.push(tmp->left);
            }
            if(tmp->right != NULL){
                q.push(tmp->right);
            }
        }
        return ret;
    }

    // 层次遍历，打印层数
    vector<vector<int> > levelorder2(TreeNode* root){
        if(root == NULL){
            return {};
        }
        vector<vector<int> > ret;
        queue<TreeNode*> q;
        q.push(root);
        while(q.size() > 0){
            int size = q.size();
            vector<int> subRet;
            for(int i = 0; i < size; i++){
                TreeNode* tmp = q.front();
                q.pop();
                subRet.push_back(tmp->val);
                if(tmp->left != NULL){
                    q.push(tmp->left);
                }
                if(tmp->right != NULL){
                    q.push(tmp->right);
                }
            }
            ret.push_back(subRet);
        }
        return ret;
    }

    // 层次遍历，按“之”字形打印
    vector<vector<int> > levelorder3(TreeNode* root){
        if(root == NULL){
            return {};
        }
        vector<vector<int> > ret;
        stack<TreeNode*> s1;
        stack<TreeNode*> s2;
        s1.push(root);
        while(s1.size() > 0 || s2.size() > 0){
            vector<int> subRet;
            if(s1.size() > 0){
                int size = s1.size();
                for(int i = 0; i < size; i++){
                    TreeNode* tmp = s1.top();
                    s1.pop();
                    subRet.push_back(tmp->val);
                    if(tmp->left != NULL){
                        s2.push(tmp->left);
                    }
                    if(tmp->right != NULL){
                        s2.push(tmp->right);
                    }
                }
                ret.push_back(subRet);
                continue;
            }
            if(s2.size() > 0){
                int size = s2.size();
                for(int i = 0; i < size; i++){
                    TreeNode* tmp = s2.top();
                    s2.pop();
                    subRet.push_back(tmp->val);
                    if(tmp->right != NULL){
                        s1.push(tmp->right);
                    }
                    if(tmp->left != NULL){
                        s1.push(tmp->left);
                    }
                }
            }
            ret.push_back(subRet);
        }
        return ret;
    }
    
    int maxx = 0;
    void dfs(TreeNode* root, int deep){
        if(root == NULL){
            return;
        }
        deep++;
        if(root->left == NULL && root->right == NULL){
            maxx = maxx > deep ? maxx : deep;
        }
        dfs(root->left, deep);
        dfs(root->right, deep);
        deep--;
    }
    // 二叉树的深度
    int maxDepth(TreeNode* root) {
        dfs(root, 0);
        return maxx;
    }

    // 二叉树的深度
    int depth(TreeNode* root){
        if(root == NULL){
            return 0;
        }
        return max(depth(root->left), depth(root->right)) + 1;
    }

    // 判断是否是平衡二叉树——自顶向下(先序+递归)
    bool isBalanced(TreeNode* root) {
        if(root == NULL){
            return true;
        }
        return abs(depth(root->left) - depth(root->right)) < 2 && isBalanced(root->left) && isBalanced(root->right);
    }

    int recur(TreeNode* root){
        if(root == NULL){
            return 0;
        }
        int left = recur(root->left);
        if(left == -1){
            return -1;
        }
        int right = recur(root->right);
        if(right == -1){
            return -1;
        }
        return abs(left - right) < 2 ? max(left, right) + 1 : -1;
    }

    // 判断是否是平衡二叉树——自底向上(后序+递归)
    bool isBalanced(TreeNode* root){
        return recur(root) == -1 ? false : true;
    }

    // 二叉搜索树的最近公共父节点——迭代
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        while(root){
            if(root->val > p->val && root->val > q->val){
                root = root->left;
            }else if(root->val < p->val && root->val < q->val){
                root = root->right;
            }else{
                break;
            }
        }
        return root;
    }

    // 二叉搜索树的最近公共父节点——递归
    TreeNode* lowestCommonAncestor2(TreeNode* root, TreeNode* p, TreeNode* q){
        if(root->val > p->val && root->val > q->val){
            return lowestCommonAncestor2(root->left, p, q);
        }
        if(root->val < p->val && root->val < q->val){
            return lowestCommonAncestor2(root->right, p, q);
        }
        return root;
    }
}