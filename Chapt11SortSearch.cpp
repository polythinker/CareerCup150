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

// Exercise 11.6 largest tower of people
// This question can be abstracted as follows:
//     given a set of rectangles defined by (length, width),
//     find the largest possible number of rectangles that can be overlaid on one another
//     so that each rectangle must be both (strictly) shorter and narrower than the one below it
// e.g., (5, 5) (7, 10) (10, 15) is OK, (7, 10) (5, 20) is not

struct Rectangle {
	int length;
	int width;
	Rectangle(int l, int w):length(l), width(w) {}
};

bool isNarrower(Rectangle A, Rectangle B) {
	return A.width < B.width;
}

bool isShorter(Rectangle A, Rectangle B) {
	return A.length < B.length;
}

int maxNumOfOverlaid(vector<Rectangle>& rects) {
	// make sure whether std::sort keeps the order??
	sort(rects.begin(), rects.end(), isNarrower);
	sort(rects.begin(), rects.end(), isShorter);
	int prevLen = 0;
	int maxNum = 0;
	// this is only for printing the rectangles
	vector<Rectangle> rectOutput;
	for (vector<Rectangle>::iterator it = rects.begin(); it!=rects.end(); ++it) {
		if ((*it).length > prevLen) {
			prevLen = (*it).length;
			++maxNum;
			rectOutput.push_back(*it);
		}
	}
	for (vector<Rectangle>::iterator it = rectOutput.begin(); it!=rectOutput.end(); ++it) {
		cout << "(" << (*it).length << ", "<< (*it).width << ")" << endl;
	}
	return maxNum;
}

void testMaxNumOfOverlaid() {
	vector<Rectangle> rectVec;
	Rectangle rect1(65, 100);
	rectVec.push_back(rect1);
	Rectangle rect2(70, 150);
	rectVec.push_back(rect2);
	Rectangle rect3(56, 90);
	rectVec.push_back(rect3);
	Rectangle rect4(75, 190);
	rectVec.push_back(rect4);
	Rectangle rect5(60, 95);
	rectVec.push_back(rect5);
	Rectangle rect6(68, 110);
	rectVec.push_back(rect6);
	maxNumOfOverlaid(rectVec);
}

int main() {
	testSortAnagrams();
	testFindInRotatedArray();
	testFindStringInterEmpty();
	testMaxNumOfOverlaid();
   	return 0;
}


