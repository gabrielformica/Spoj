#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<int> vi;

// T is the type of input array elements
// V is the type of required aggregate statistic

struct SegmentTreeNode {
    int uo, uc;

    void merge(const SegmentTreeNode &left, const SegmentTreeNode &right) {
        int x = left.uo - right.uc;
        uo = right.uo + (x > 0 ? x : 0);
        uc = left.uc + (x > 0 ? 0 : -1 * x);
    }

    bool getValue() {
        return uo == 0 && uc == 0;
    }

    void assignLeaf(char value) {
        uo = uc = 0;
        if (value == '(') uo = 1;
        else uc = 1; 
    }
};

template<class T, class V>
class SegmentTree {
  SegmentTreeNode* nodes;
  int N;

public:
  SegmentTree(T arr[], int N) {
    this->N = N;
    nodes = new SegmentTreeNode[4 * N];
    buildTree(arr, 1, 0, N-1);
  }
  
  ~SegmentTree() {
    delete[] nodes;
  }
  
  V getValue(int lo, int hi) {
    SegmentTreeNode result = getValue(1, 0, N-1, lo, hi);
    return result.getValue();
  }
  
  void update(int index, T value) {
    update(1, 0, N-1, index, value);
  }
  
  private:  
  void buildTree(T arr[], int stIndex, int lo, int hi) {
    if (lo == hi) {
      nodes[stIndex].assignLeaf(arr[lo]);
      return;
    }
    
    int left = 2 * stIndex, right = left + 1, mid = (lo + hi) / 2;
    buildTree(arr, left, lo, mid);
    buildTree(arr, right, mid + 1, hi);
    nodes[stIndex].merge(nodes[left], nodes[right]);
  }
  
  SegmentTreeNode getValue(int stIndex, int left, int right, int lo, int hi) {
    if (left == lo && right == hi)
      return nodes[stIndex];
        
    int mid = (left + right) / 2;
    if (lo > mid)
      return getValue(2*stIndex+1, mid+1, right, lo, hi);
    if (hi <= mid)
      return getValue(2*stIndex, left, mid, lo, hi);
        
    SegmentTreeNode leftResult = getValue(2*stIndex, left, mid, lo, mid);
    SegmentTreeNode rightResult = getValue(2*stIndex+1, mid+1, right, mid+1, hi);
    SegmentTreeNode result;
    result.merge(leftResult, rightResult);
    return result;
  }
  
  int getSegmentTreeSize(int N) {
    int size = 1;
    for (; size < N; size <<= 1);
    return size << 1;
  }
  
  void update(int stIndex, int lo, int hi, int index, T value) {
    if (lo == hi) {
        nodes[stIndex].assignLeaf(value);
        return;
    }
    
    int left = 2 * stIndex, right = left + 1, mid = (lo + hi) / 2;
    if (index <= mid)
      update(left, lo, mid, index, value);
    else
      update(right, mid+1, hi, index, value);
    
    nodes[stIndex].merge(nodes[left], nodes[right]);
  }
};

int N, M, o;
char arr[30005];
int main(void) {
    for (int test = 1; test <= 10; test++) {
        scanf("%d", &N);
        scanf("%s", arr);
        SegmentTree<char, bool> st(arr, N);

        scanf("%d", &M);
        printf("Test %d:\n", test);
        for (int i = 0; i < M; i++) {
            scanf("%d", &o);
            if (o != 0) {
                o--;
                if (arr[o] == '(') arr[o] = ')';
                else arr[o] = '(';
                st.update(o, arr[o]);
            } 
            else printf("%s\n", (st.getValue(0, N-1) ? "YES" : "NO"));
        }
    }
    
    return 0;
}
