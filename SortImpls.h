#include <iostream>
#include <vector>
#include <string>

using namespace std;

void BubbleSort(vector<int> &items, int start_index, int final_index);
void InsertionSort(vector<int> &items, int start_index, int final_index);
void Merge(vector<int> &items, int start_index, int middle_ind, int final_index);
void MergeSort(vector<int> &items, int start_index, int final_index);
void iterative_merge(vector<int> &items, int l, int m, int r);
void IterativeMergeSort(vector<int> &items, int start_index, int final_index);// needs fixing
void ShellSort(vector<int> &items, int start_index, int final_index);
void QuickSort(vector<int> &items, int start_index, int final_index);
int partition_quick(vector<int> &items, int start_index, int final_index);


void BubbleSort(vector<int> &items, int start_index, int final_index) {
	int temp = 0;
	bool flag = true;
	if (final_index < 1) return;
	for (int i = 0; flag == true && i < final_index; i++) {
		flag = false;
		for (int j = 0; j < final_index; j++) {
			if (items[j] > items[j + 1]) {// basically checks current item with next item, swaps if next item
				temp = items[j];// greater
				items[j] = items[j+1];// swap function used in switching integers
				items[j+1] = temp;
				flag = true;// setting flag so once vector sorted, no need to do unnecessary run throughs
			}
		}
	}
}

void InsertionSort(vector<int> &items, int start_index, int final_index) {
	int index = 0;
	int value = 0;
	for (int i = 1; i < (final_index + 1); i++) {
		value = items[i];
		index = i;
		while (index > 0 && items[index - 1] > value) {
			items[index] = items[index - 1];// if value is smaller it is moved to the left and vice versa
			index--;
		}
		items[index] = value;
	}
}

void ShellSort(vector<int> &items, int start_index, int final_index) {
	int temp = 0;
	for (int gap = (final_index / 2); gap > 0; gap /= 2) {//doing divide by 2 until it is 0
		for (int j = gap;j < (final_index+1);j++) {
			temp = items[j];
			int i = 0;
			for (i = j; i >= gap && items[i - gap] > temp; i -= gap) {
				items[i] = items[i-gap];// basically like a sliding window type approach
			}//compares the element of middle and the first, organize that window
			items[i] = temp;// then shrink/2 and eventually sorting every number
		}
	}
}

void QuickSort(vector<int> &items, int start_index, int final_index) {
	if (start_index < final_index) {
		int mid_index = partition_quick(items, start_index, final_index);
		QuickSort(items, start_index, mid_index - 1);
		QuickSort(items, mid_index + 1, final_index);
	}
}

int partition_quick(vector<int> &items, int start_index, int final_index) {
	int pivot = final_index;
	int index = start_index;
	int temp = 0;
	for (int i = start_index; i < final_index; i++) {
		if (items[i] < items[pivot]) {
			temp = items[i];
			items[i] = items[index];
			items[index] = temp;
			index++;
		}
	}
	temp = items[index];
	items[index] = items[final_index];
	items[final_index] = temp;
	return index;
}

void Merge(vector<int> &items, int start_index, int middle_ind, int final_index) {
	vector<int> temp;
	int start_ind = start_index;// example 3 6 2 1 4
	int last_pl = middle_ind+1;// first we split it so it would 5/2, 2.5 so 0 2 one array and 3 4 other
	while (start_ind <= middle_ind && last_pl <= final_index) {
		if (items[start_ind] < items[last_pl]) {//if the value in 0-2 array smaller than other array
			temp.push_back(items[start_ind]);// insert
			++start_ind;
		}
		else {
			temp.push_back(items[last_pl]);//else insert the other, index increment universally by push_back
			++last_pl;
		}
	}
	while (start_ind <= middle_ind) {
		temp.push_back(items[start_ind]);// whichever array has elements left insert it
		++start_ind;
	}
	while (last_pl <= final_index) {
		temp.push_back(items[last_pl]);
		++last_pl;
	}
	for (int j = start_index; j <= final_index; ++j) {
		items[j] = temp[j-start_index];// copy array
	}
}

void MergeSort(vector<int>& items, int start_index, int final_index) {
	if (start_index < final_index) {
		int mid = (start_index + final_index) / 2;
		MergeSort(items, start_index, mid);
		MergeSort(items, mid + 1, final_index);
		Merge(items, start_index, mid, final_index);
	}
}

void iterative_merge(vector<int> &Arr, int l, int m, int r) {
	int i = 0, j = 0, k = 0;
	int n1 = m - l + 1;
	int n2 = r - m;
	vector<int> L(n1);
	vector<int> R(n2);
	for (i = 0; i < n1; i++) {
		L[i] = Arr[l + i];
	}
	for (j = 0; j < n2; j++) {
		R[j] = Arr[m + 1 + j];
	}
	i = 0, j = 0, k = l;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			Arr[k] = L[i];
			i++;
		}
		else {
			Arr[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1) {
		Arr[k] = L[i];
		i++;
		k++;
	}
	while (j < n2) {
		Arr[k] = R[j];
		j++;
		k++;
	}
}

void IterativeMergeSort(vector<int> &items, int start_index, int final_index) {
	vector<int> temp(items.size());// creating a temp array of size items
	for (int i = 1; i <= final_index; i = 2*i) {
		for (int j = 0; j < final_index; j += 2 * i) {
			int mid_index = min(j + i-1, final_index);
			int right_position = min(j + 2 * i -1, final_index);
			iterative_merge(items, j, mid_index, right_position);
		}
	}
}
