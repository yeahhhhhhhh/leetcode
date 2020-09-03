#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// 通用数据结构
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 链表类练习
namespace listDemo{
    // 从尾到头打印链表——栈
    vector<int> reversePrint(ListNode* head) {
        if(head == NULL){
            return {};
        }
        vector<int> ret;
        stack<ListNode*> s;
        ListNode* cur = head;
        while(cur != NULL){
            s.push(cur);
            cur = cur->next;
        }
        while(!s.empty()){
            ret.push_back(s.top()->val);
            s.pop();
        }
        return ret;
    }

    // 从尾到头打印链表——递归
    vector<int> ret;
    vector<int> reversePrint2(ListNode* head){
        if(head == NULL){
            return {};
        }
        reversePrint2(head->next);
        ret.push_back(head->val);
        return ret;
    }

    // 删除链表中指定的节点
    ListNode* deleteNode(ListNode* head, int val) {
        if(head == NULL){
            return NULL;
        }
        if(head->val == val){
            return head->next;
        }
        ListNode* cur = head;
        ListNode* pre = head;
        while(cur != NULL){
            if(cur->val == val){
                pre->next = cur->next;
                break;
            }
            pre = cur;
            cur = cur->next;
        }
        return head;
    }

    // 删除链表中指定的节点——递归
    ListNode* deleteNode2(ListNode* head, int val){
        if(head == NULL){
            return head;
        }
        if(head->val == val){
            return head->next;
        }
        head->next = deleteNode2(head->next, val);
        return head;
    }

    // 链表中倒数第K个节点
    ListNode* getKthFromEnd(ListNode* head, int k) {
        if(head == NULL){
            return NULL;
        }
        ListNode* fast = head;
        ListNode* slow = head;
        while(k--){
            fast = fast->next;
        }
        while(fast){
            fast = fast->next;
            slow = slow->next;
        }
        return slow;
    }

    // 链表中倒数第K个节点——递归
    int size = 0;
    ListNode* getKthFromEnd2(ListNode* head, int k){
        if(head == NULL){
            return head;
        }
        ListNode* node = getKthFromEnd2(head->next, k);
        if(++size == k){
            return head;
        }
        return node;
    }

    // 反转链表
    ListNode* reverseList(ListNode* head) {
        if(head == NULL){
            return NULL;
        }
        ListNode* cur = head;
        ListNode* pre = NULL;
        while(cur){
            ListNode* next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        return pre;
    }

    // 反转链表——递归
    ListNode* reverseList2(ListNode* head){
        if(head == NULL || head->next == NULL){
            return head;
        }
        ListNode* ret = reverseList2(head->next);
        head->next->next = head;
        head->next = NULL;
        return ret;
    }

    // 合并两个有序链表
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        // 利用伪节点
        ListNode* dum = new ListNode(0);
        ListNode* cur = dum;
        while(l1 && l2){
            if(l1->val > l2->val){
                cur->next = l2;
                l2 = l2->next;
            }else{
                cur->next = l1;
                l1 = l1->next;
            }
            cur = cur->next;
        }
        cur->next = l1 == NULL ? l2 : l1;
        ListNode* ret = dum->next;
        delete dum;
        return ret;
    }
}