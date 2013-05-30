/*
 * Chapt1StringArray.cpp
 * Solutions to question of Chapter 1 of CareerCup150 (5th ed.)
 * Created on: May 29, 2013
 * Author: Vincent Yun
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// Q1. determine whether a string has unique characters
// hashtable (vector)
bool uniqueChar1(const string& str) {
	if (str.length() > 256)
		return false;
	vector<int> carray(256, 0);
	for (int i = 0; i < str.length(); ++i) {
		int val = str[i];
		if (carray[val] == 1)
			return false;
		else
			carray[val] = 1;
	}
	return true;
}

// hashtable (bit-vector)
bool isUniqueChar2(const string& str) {
	if (str.length() > 256)
		return false;
	vector<int> iarray(8, 0);
	for (int i = 0; i < str.length(); ++i) {
		int val = str[i];
		if (iarray[val / 32] & (1 << (val % 32)) > 0)
			return false;
		else
			iarray[val / 32] |= (1 << (val % 32));
	}
	return true;
}

// sort first
bool isUniqueChars3(const string& str) {
	if (str.length() > 256)
		return false;
	if (str.length() == 1)
		return false;
	else {
		string s(str.begin(), str.end());
		sort(s.begin(), s.end());
		string::iterator iter;
		for (iter = s.begin(); iter != (s.end() - 1); ++iter) {
			if (*iter == *(iter + 1))
				return false;
		}
		return true;
	}
}

// Q2. reverse a null-terminated string

void revStr(char *s) {
	// former for non-determined s, latter for str = ""
	if (!s || *s == '\0')
		return;
	char *p = s;
	while (*(p + 1))
		p++;
	while (s < p) {
		swap(*s, *p);
		s++;
		p--;
	}
}

// Q3. decide is a string is a permutation of another
// use sort
bool isPerm1(string str1, string str2) {
	if (str1.length() != str2.length()) {
		return false;
	} else {
		sort(str1.begin(), str1.end());
		sort(str2.begin(), str2.end());
		return 1 - str1.compare(str2);
	}
}

// do not use sort; use hash table, similar to isUnique
// bool isPerm2(string str1, string str2);

// Q4. Replace all spaces with %20
void repSpaces(string& str, int n) { // n must be passed as parameter
	int nspace = 0;
	for (int i = 0; i < n; i++) {
		if (str[i] == ' ')
			nspace++;
	}
	int back = n + 2 * nspace - 1;
	for (int front = n - 1; front >= 0; front--) {
		if (str[front] == ' ') {
			str[back--] = '0';
			str[back--] = '2';
			str[back--] = '%';
		} else {
			str[back--] = str[front];
		}
	}
}

// Q5. Compress string by counting repeated chars
// compress without ordering
void stringCompression1(string& str) {
	vector<int> charCount(256, 0);
	string::iterator iter;
	for (iter = str.begin(); iter != str.end(); ++iter) {
		int val = *iter;
		charCount[val]++;
	}
	int newLength = 0, i;
	for (i = 0; i < 256; ++i) {
		if (charCount[i] > 0)
			newLength += 2;
	}
	if (newLength < str.length()) {
		iter = str.begin();
		for (i = 0; i < 256; ++i) {
			if (charCount[i] > 0) {
				*iter++ = (char) i;
				*iter++ = charCount[i] + '0';
			}
		}
		str.resize(newLength);
	}
}

// compress in original order
void stringCompression2(string& str) {
	string newStr("");
	char prevChar;
	int charCount = 0;
	string::iterator iter;
	for (iter = str.begin(); iter != str.end(); ++iter) {
		if (iter == str.begin()) {
			newStr.insert(newStr.end(), *iter);
			prevChar = *iter;
			charCount++;
		} else if (*iter == prevChar) {
			charCount++;
		} else {
			newStr.insert(newStr.end(), charCount + '0');
			newStr.insert(newStr.end(), *iter);
			charCount = 1;
			prevChar = *iter;
		}
	}
	newStr.insert(newStr.end(), charCount + '0');

	if (newStr.length() < str.length()) {
		for (int i = 0; i < newStr.length(); ++i)
			str[i] = newStr[i];
		str.resize(newStr.length());
	}
}

// Q6 rotate matrix
// CC150 version
void rotate90(int** array, const int n) {
	if (n < 1) {
		cerr << "Error: array size < 1!\n";
	} else if (n > 1) {
		int tmp, layerNum = n / 2;

		for (int layer = 0; layer < layerNum; layer++) {
			int length = n - layer * 2 - 1;
			for (int id = 0; id < length; id++) {
				tmp = array[layer + length - id][layer];
				array[layer + length - id][layer] = array[layer + length][layer
						+ length - id];
				array[layer + length][layer + length - id] =
						array[layer + id][layer + length];
				array[layer + id][layer + length] = array[layer][layer + id];
				array[layer][layer + id] = tmp;
			}
		}
	}
}
// leetcode version
void rotate(vector<vector<int> > &matrix) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    assert(matrix.size() == matrix[0].size());
    int n = matrix.size();
    for (int i=0; i<n/2; ++i) {
        int tmp = 0;
        int m = n - 1 - 2*i;
        for (int j=0; j<m; ++j) {
            tmp = matrix[i][i+j];
            matrix[i][i+j] = matrix[n-1-i-j][i];
            matrix[n-1-i-j][i] = matrix[n-1-i][n-1-i-j];
            matrix[n-1-i][n-1-i-j] = matrix[i+j][n-1-i];
            matrix[i+j][n-1-i] = tmp;
        }
    }
}

void print2d(int** array, const int n) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)
			cout << array[i][j] << " ";
		cout << endl;
	}
}

// Q7 set matrix zeroes
void print2d(int** array, const int rowMax, const int colMax) {
	int i, j;
	for (i = 0; i < rowMax; ++i) {
		for (j = 0; j < colMax; ++j) {
			cout << array[i][j] << " ";
		}
		cout << endl;
	}
}

// space complexity O(M + N)
void setzeros1(int** array, const int rowMax, const int colMax) {
	int i, j;
	int* zeroRows = new int[rowMax];
	int* zeroCols = new int[colMax];
	//record row and col that contains zero
	for (i = 0; i < rowMax; ++i)
		for (j = 0; j < colMax; ++j)
			if (array[i][j] == 0) {
				zeroRows[i]++;
				zeroCols[j]++;
			}
	// set zero rows
	for (i = 0; i < rowMax; ++i) {
		if (zeroRows[i] > 0)
			for (j = 0; j < colMax; ++j)
				array[i][j] = 0;
	}
	// set zero cols
	for (j = 0; j < colMax; ++j) {
		if (zeroCols[j] > 0)
			for (i = 0; i < rowMax; ++i)
				array[i][j] = 0;
	}
}

// space complexity O(1)
// function interface for leetcode OJ
// Tips: problem requires constant space can be solved by
// 	(1) a few number of extra variables, or (2) the problem has provide enough space itself
// large test set 396 milli
void setZeroes2(vector<vector<int> > &matrix) {
	// boundary
	if (matrix.size() == 0 || matrix[0].size() == 0)
		return;
	// whether need to set first row
	bool setFirstRow = false;
	for (int i = 0; i < matrix[0].size(); i++) {
		if (matrix[0][i] == 0) {
			setFirstRow = true;
			break; // bug1: left this line outside if {}
		}
	}
	// whether need to set first column
	bool setFirstCol = false;
	for (int i = 0; i < matrix.size(); i++) {
		if (matrix[i][0] == 0) {
			setFirstCol = true;
			break;
		}
	}
	// record zeros in first row and first column
	for (int i = 1; i < matrix.size(); i++) {
		for (int j = 1; j < matrix[0].size(); j++) {
			if (matrix[i][j] == 0) {
				matrix[0][j] = 0;
				matrix[i][0] = 0;
			}
		}
	}
	// set columns
	for (int j = 1; j < matrix[0].size(); j++) { // bug2: start from j=0 (think about matrix[0][0] = 0)
		if (matrix[0][j] == 0) {
			for (int i = 1; i < matrix.size(); i++)
				matrix[i][j] = 0;
		}
	}
	// set rows
	for (int i = 1; i < matrix.size(); i++) {
		if (matrix[i][0] == 0) {
			for (int j = 1; j < matrix[0].size(); j++)
				matrix[i][j] = 0;
		}
	}
	// set first row if necessary
	if (setFirstRow) {
		for (int j = 0; j < matrix[0].size(); j++)
			matrix[0][j] = 0;
	}
	// set second row if necessary
	if (setFirstCol) {
		for (int i = 0; i < matrix.size(); i++)
			matrix[i][0] = 0;
	}
}

int main() {
	// test revStr
	char str1[] = "";
	char str2[] = "s";
	char str3[] = "string to reverse";
	// revStr(str1);
	cout << str1 << endl;
	revStr(str2);
	cout << str2 << endl;
	revStr(str3);
	cout << str3 << endl;

	// test isPerm
	string permStr1("Asimplestring");
	string permStr2("simpleAstring");
	cout << isPerm1(permStr1, permStr2) << endl;

	// test repSpaces
	string strToRep("Mr John Smith        ");
	repSpaces(strToRep, 13);
	cout << strToRep << endl;

	// test compress
	string strToCompress("Compress me, if you can!");
	stringCompression1(strToCompress);
	cout << strToCompress << endl;
	string str2ToCompress("aabccccaaa");
	stringCompression2(str2ToCompress);
	cout << str2ToCompress << endl;

	// test rotate90

	const int N = 10;
	int** image = new int*[N];

	int i, j;
	for (i = 0; i < N; ++i) {
		image[i] = new int[N];
		for (j = 0; j < N; ++j)
			image[i][j] = j;
	}

	print2d(image, N);
	cout << endl;
	rotate90(image, N);
	print2d(image, N);

	cout << endl;
	rotate90(image, N);
	print2d(image, N);

	for (i = 0; i < N; ++i) {
		delete[] image[i];
	}
	delete[] image;

	// test set matrix zeroes
	const int rowMax = 5, colMax = 9;
	int** iarray = new int*[rowMax];
	int i, j;
	for (i = 0; i < rowMax; ++i) {
		iarray[i] = new int[colMax];
		for (j = 0; j < colMax; ++j) {
			iarray[i][j] = rand() % 10;
		}
	}
	print2d(iarray, rowMax, colMax);
	cout << endl;

	setzeros1(iarray, rowMax, colMax);
	print2d(iarray, rowMax, colMax);
	cout << endl;
	return 0;
}
