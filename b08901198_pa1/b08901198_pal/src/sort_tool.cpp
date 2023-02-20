// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    int key;
    int i;
    int j;
    for (j=1;j<data.size();j++){
        key=data[j];
        i=j-1;
        while(i>=0 && data[i]>key){//前項大
            data[i+1]=data[i];//往後一格
            i=i-1;
        }
        data[i+1]=key;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    int k;
    if (low<high){
       k=Partition(data,low,high);
       QuickSortSubVector(data,low,k);
       QuickSortSubVector(data,k+1,high);
    }

}

int SortTool::Partition(vector<int>& data, int low, int high) {
    int x;
    int i;
    int j;
    x=data[high];
    i=low-1;
    for(j=low;j<high;j++){
        if (data[j]<=x){
            i=i+1;
            swap(data[i],data[j]);
        }
    }
    swap(data[i+1],data[high]);
    return i;

}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    if(low<high){
        int middle1=(low+high)/2;
        int middle2=(low+high)/2+1;
        MergeSortSubVector(data,low,middle1);
        MergeSortSubVector(data,middle2,high);
        Merge(data,low,middle1,middle2,high);

    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    int n1;
    int n2;
    int m;
    n1=(middle1-low+1);
    n2=(high-middle2+1);
    m=1000001;
    vector<int>L(n1+1);
    vector<int>R(n2+1);
    for (int i=0;i<L.size()-1;i++){
        L[i]=data[low+i];
    }
    for (int j=0;j<R.size()-1;j++){
        R[j]=data[middle2+j];
    }
    L[n1]=m;
    R[n2]=m;
    int l=0;
    int r=0;

    for(int k=low;k<=high;k++){
        if (L[l]>R[r]){
            data[k]=R[r];
            r++;}
        else{
            data[k]=L[l];
            l++;
        }

    }




    
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    int l_child;
    int r_child;
    l_child=2*(root+1)-1;
    r_child=2*(root+1); 
    int max=root;
    if (l_child <= heapSize-1 && data[l_child]>data[root]){
            max=l_child;}
    if(r_child <= heapSize-1 && data[r_child]>data[max]){
            max=r_child;
    }
    if(max!=root){
        swap(data[root],data[max]);
        MaxHeapify(data,max);
    }
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); 
    for(int i =(data.size()/2)-1;i>=0;i--){
        MaxHeapify(data,i);
    }


}
