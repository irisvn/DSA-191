﻿#include <iostream>

using namespace std;

int partition(int arr[], int left, int right)
{
	int pivot = left;
	int smallerIndex = left + 1;
	
	for (int i = left + 1; i <= right; i++)
	{
		if (arr[i] < arr[pivot])
		{
			swap(arr[i], arr[smallerIndex]);
			++smallerIndex;
		}
	}
	swap(arr[smallerIndex - 1], arr[pivot]);
	return (smallerIndex - 1);
}

void QuickSort(int arr[], int left, int right)
{
	if (left < right)
	{
		int pivot = partition(arr, left, right);
		
		QuickSort(arr, left, pivot - 1);
		QuickSort(arr, pivot + 1, right);
	}
}

int main()
{
	int arr[] = {19, 16, 15, 13, 6, 7, 21};
	
	QuickSort(arr, 0, sizeof(arr) / sizeof(arr[0]) - 1);
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << " ";
	}
	cin.get();
	return 0;
}