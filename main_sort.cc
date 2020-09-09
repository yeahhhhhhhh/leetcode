#include <iostream>
#include <vector>

using namespace std;

int partition(vector<int>& nums, int start, int end){
    int povit = nums[end];
    int j = start - 1;
    for(int i = start; i < end; i++){
        if(nums[i] < povit){
            j++;
            swap(nums[i], nums[j]);
        }
    }
    swap(nums[end], nums[j + 1]);
    return j + 1;
}

void qSort(vector<int>& nums, int start, int end){
    if(start < end){
        int mid = partition(nums, start, end);
        qSort(nums, start, mid - 1);
        qSort(nums, mid + 1, end);
    }
}

void qSort(vector<int>& nums){
    qSort(nums, 0, nums.size() - 1);
}