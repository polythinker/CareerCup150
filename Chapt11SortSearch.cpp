/*
 * Chapt11SortSearch.cpp
 *	Solutions to question of Chapter 11 of CareerCup150 (5th ed.)
 * 	Created on: May 1, 2013
 *      Author: Vincent
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// Exercise 11.1
// Merge two sorted arrays (leetcode)

// Exercise 11.2
// Sort an array of strings so that all the anagrams are next to each other
void sortAnagrams(vector<string>& sVec) {
	map<string, vector<string> > myMap;

	// construct the hash table
	for (vector<string>::iterator it=sVec.begin(); it!=sVec.end(); ++it) {
		string strKey(*it);
		sort(strKey.begin(), strKey.end());
		if (myMap.find(strKey) == myMap.end()) {
			vector<string> tmp;
			myMap[strKey] = tmp;
		}
		myMap[strKey].push_back(*it);
	}

	// iterate all string vectors and record each string in the original sVec
	int index = 0;
	for (map<string, vector<string> >::iterator it=myMap.begin(); it!=myMap.end(); ++it) {
		for (vector<string>::iterator it2=it->second.begin(); it2!=it->second.end(); ++it2) {
			sVec[index] = *it2;
			++index;
		}
	}
}

// test function sortAnagrams(vector<string>& sVec)
void testSortAnagrams() {
	string s[] = {"acre", "bob", "race", "obb", "care"};
	int nSize = 5;
	vector<string> vStr;
	for (int i=0; i<nSize; ++i) {
		vStr.push_back(s[i]);
	}

	sortAnagrams(vStr);

	for (int i=0; i<nSize; ++i)
		cout << vStr[i] << " ";
	cout << endl;
}

// Exercise 11.3
// Find an element k in a rotated array A[] from left to right
// You can assume that A[] was original sorted in ascending order
// e.g., A[] = {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14};
int findInRotatedArray(int A[], int left, int right, int k) {
	if (left > right) return -1;
	else {
		int mid = (left + right)/2;
		if (A[mid] == k) return mid;
		else if (k < A[mid]) {
			if ((A[mid] >= A[left] && k >= A[left]) || (A[mid] < A[left]))
				return findInRotatedArray(A, left, mid-1, k);
			else
				return findInRotatedArray(A, mid+1, right, k);
		} else {
			if ((A[mid] <= A[right] && k <= A[right]) || (A[mid] > A[right]))
				return findInRotatedArray(A, mid+1, right, k);
			else
				return findInRotatedArray(A, left, mid-1, k);
		}
	}
}
// The wrapper function for findInRotatedArray
int findInRotatedArray(int A[], int n, int k) {
	return findInRotatedArray(A, 0, n-1, k);
}

void testFindInRotatedArray() {
	int rotatedArray[] = {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14};
	int rotArrSize = 12;
	for (int i=0; i<rotArrSize; ++i) {
		int elem = rotatedArray[i];
		cout << "find element " << elem << " at " << findInRotatedArray(rotatedArray, rotArrSize, elem) << endl;
	}
	cout << "find element 24 at " << findInRotatedArray(rotatedArray, rotArrSize, 24) << endl;
}

// Exercise 11.4
// external sort

// Exercise 11.5
// Find the location of a given string in a sorted array of string which is
//     interspersed with empty strings
// e.g., find "ball" in {"at", "", "", "", "ball", "", "", "car", "", "", "dad", "", ""};
//       output 4
int findStringInterEmpty(string sArr[], int left, int right, string s) {
	if (left > right) return -1;
	else {
		int mid = (left + right) / 2;
		if (sArr[mid] == s) return mid;
		else {
			int index = mid-1;
			if (sArr[mid] == "") {
				while (index >= left && sArr[index] == "")
					--index;
			}
			if (index < left) return -1;
			else if (s == sArr[index]) return index;
			else if (s < sArr[index])
				return findStringInterEmpty(sArr, left, index-1, s);
			else
				return findStringInterEmpty(sArr, mid+1, right, s);
		}
	}
}
// The wapper function of findStringInterEmpty
int findStringInterEmpty(string sArr[], int n, string s) {
	return findStringInterEmpty(sArr, 0, n-1, s);
}

void testFindStringInterEmpty() {
	string sArr[] = {"at", "", "", "", "ball", "", "", "car", "", "", "dad", "", ""};
	int sSize = 13;
	for (int i=0; i<sSize; ++i) {
		cout << "find the " << i << "th element at ";
		cout << findStringInterEmpty(sArr, 13, sArr[i]) << endl;
	}
	cout << "find \"top\" at ";
	cout << findStringInterEmpty(sArr, 13, "top") << endl;
}

// Exercise 11.6
// Find an element in an M*N matrix in which each row and each column is sorted in ascending order
bool findInMatrix(vector<vector<int> >A, int& m, int& n, int& x, int& i, int& j) {
	// start from the upper right corner and travel in zig-zag manner
	while (i<m && j>=0) {//
		if (A[i][j] == x) return true;
		else if (A[i][j] < x)
			++i;
		else
			--j;
	}
	return false;
}

void testFindInMatrix() {
	int a1[] = {15, 20, 40, 85};  int a2[] = {20, 35, 8, 95};
	int a3[] = {30, 55, 95, 105}; int a4[] ={40, 80, 100, 120};
	vector<vector<int> > A;
	A.push_back(vector<int>(a1, a1+4));
	A.push_back(vector<int>(a2, a2+4));
	A.push_back(vector<int>(a3, a3+4));
	A.push_back(vector<int>(a4, a4+4));
	int m = 4, n = 4, x = 55, i = 0, j = 3;
	bool found = findInMatrix(A, m, n, x, i, j);
	if (found)
		cout << A[i][j] << endl;
}




// Exercise 11.7 largest tower of people
// This question can be abstracted as "find the longest subsequences pairs"
// Given a set of rectangles defined by (length, width),
//     find the largest possible number of rectangles that can be overlaid on one another
//     so that each rectangle must be both (strictly) shorter and narrower than the one below it
// e.g., (5, 5) (7, 10) (10, 15) is OK, (7, 10) (5, 20) is not

struct Pair {
	int length;
	int width;
	Pair(int l, int w):length(l), width(w) {}
};

bool isNarrower(Pair A, Pair B) {
	return A.width < B.width;
}

bool isShorter(Pair A, Pair B) {
	return A.length < B.length;
}
// find the longest increasing sequence
// check Algorithm repository for more comments
void findLIS (vector<int>& seq, vector<int>& lis) {
	// lis temporarily serves as vector M
	// P array stores the position of the predecessor of X[k] in the longest increasing subsequence ending at X[k]
	if (seq.empty()) return;
	vector<int> P(seq.size());
	int left, right;
	lis.push_back(0);
	for (size_t i=1; i<seq.size(); ++i) {
		if (seq[lis.back()] < seq[i]) { // if the next element is larger
			P[i] = lis.back(); // record the predecessor of seq[i]
			lis.push_back(i);  // store the larger element into M
			continue;
		}
		left = 0;
		right = lis.size()-1;
		while (left < right) {
			int mid = (left + right) / 2;
			if (seq[lis[mid]] < seq[i])
				left = mid+1;
			else
				right = mid;
		}
		// Update b if new value is smaller then previously referenced value
		if (seq[i] < seq[lis[left]]) {
			if (left > 0)
				P[i] = lis[left-1];
			lis[left] = i;
		}
	}
	// backtrack P and put the true LIS into lis
	int n = lis.size();
	int current = lis.back();
	while (n) {
		lis[n-1] = current;
		current = P[current];
		--n;
	}
}

// Sort pair on length first, and then find the longest increasing subsequence on width
void maxNumOfOverlaid(vector<Pair>& rects) {
	// std::sort does not guarantees that equivalent elements keep their original order
	// for that purpose, use stable_sort instead
	// but here, that is unnecessary. The findLIS algorithm will take care of it.
	sort(rects.begin(), rects.end(), isShorter);
	vector<int> widthVec;
	for (vector<Pair>::iterator it = rects.begin(); it !=rects.end(); ++it)
		widthVec.push_back(it->width);
	vector<int> lis;
	findLIS(widthVec, lis);
	// this is only for printing the rectangles
	for (size_t pos = 0; pos<lis.size(); ++pos)
		cout << "(" << rects[lis[pos]].length << ", "<< rects[lis[pos]].width << ")" << endl;
	}

void testMaxNumOfOverlaid() {
	vector<Pair> rectVec;
	Pair rect3(56, 90);
	rectVec.push_back(rect3);
	Pair rect52(60, 110);
	rectVec.push_back(rect52);
	Pair rect5(60, 95);
	rectVec.push_back(rect5);
	Pair rect12(65, 110);
	rectVec.push_back(rect12);
	Pair rect1(65, 100);
	rectVec.push_back(rect1);
	Pair rect2(70, 150);
	rectVec.push_back(rect2);
	Pair rect4(75, 190);
	rectVec.push_back(rect4);
	Pair rect6(68, 110);
	rectVec.push_back(rect6);
	maxNumOfOverlaid(rectVec);
}

// Exercise 11.8
// Imagine you are reading in a stream of integers. Periodically, you wish to be able to look up
// 	the rank of a number x (the number of values less than or equal to x).
// Implement the data structures and algorithms to support these operations. That is, implement
// 	the method track(int x), which is called when each numbre is generated, and the method
// 	getRankOfNumber(int x), which returns the number of values less than or equal to x (exclusively)

// A tree node class that records the size of its left subtree by leftSize
struct TreeNodeL {
	int value;
	int leftSize;
	TreeNodeL* left;
	TreeNodeL* right;
	// constructor
	TreeNodeL(int v):value(v), leftSize(0), left(NULL), right(NULL) {}
};

class IntStreamProcessor {
	TreeNodeL* root;
public:
	// constructor
	IntStreamProcessor():root(NULL){}

	// insert a new node of value v into the binary search tree
	// note to update the leftSize for a node that branches on left
	void insert(int v) {
		if (!root) root = new TreeNodeL(v);
		else {
			TreeNodeL* p = root;
			TreeNodeL* parent = NULL;
			while (p) {
				if (v <= p->value) {
					parent = p;
					(p->leftSize)++;
					p = p->left;
				}
				else {
					parent = p;
					p = p->right;
				}
			}
			if (v < parent->value) {
				parent->left = new TreeNodeL(v);
			} else  {
				parent->right = new TreeNodeL(v);
			}
		}
	}
	// track the newly input value x
	void track(int x) {
		insert(x);
	}
	// get the rank of number x
	int getRankOfNumber(int x) {
		return getRank(root, x);
	}
	// get the rank of value x in the subtree rooted at TreeNodeL* p
	int getRank(TreeNodeL* p, int x) {
		if (!p) return -1;
		else if (x == p->value) return p->leftSize;
		else if (x < p->value) return getRank(p->left, x);
		// note if x is not found in the right subtree, return -1
		else {
			int rightSize = getRank(p->right, x);
			if (rightSize == -1) return -1;
			else return p->leftSize + 1 + rightSize;
		}
	}
};

void testIntStreamProcessor() {
	IntStreamProcessor case1;
	int A[] = {5, 1, 4, 4, 5, 9, 7, 13, 3};
	int ASize = 9;
	for (int i=0; i<ASize; ++i)
		case1.track(A[i]);
	cout << "The rank of 1 is " << case1.getRankOfNumber(1) << endl;
	cout << "The rank of 3 is " << case1.getRankOfNumber(3) << endl;
	cout << "The rank of 4 is " << case1.getRankOfNumber(4) << endl;
	cout << "The rank of 7 is " << case1.getRankOfNumber(7) << endl;
	cout << "The rank of 9 is " << case1.getRankOfNumber(9) << endl;
	cout << "The rank of 13 is " << case1.getRankOfNumber(13) << endl;
}

int main() {
	testSortAnagrams();
	testFindInRotatedArray();
	testFindStringInterEmpty();
	testFindInMatrix();
	testMaxNumOfOverlaid();
	testIntStreamProcessor();
   	return 0;
}


