#include <iostream>
using namespace std;

int binarySearch(int arr[], int l, int r, int x)
{
	if (r >= l) {
		int mid = l + (r - l) / 2;

		if (arr[mid] == x)
			return mid;


		if (arr[mid] > x)
			return binarySearch(arr, l, mid - 1, x);

		return binarySearch(arr, mid + 1, r, x);
	}
	return -1;
}

void insertionSort(int arr[], int n)
{
	int i, key, j;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		
		j = i - 1;

		while (j >= 0 && arr[j] > key)
		{
			cout << arr[i] << endl;
			arr[j + 1] = arr[j];
			j = j - 1;
			cout << arr[i] << endl;
			
		}
		
		arr[j + 1] = key;
	}
	
}

void printArray(int arr[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;
}

int main()
{
	bool repeat = true;
	int v;
	size_t size;

	cout<< "Please, enter a size of the array: ";
	cin>> size;

	int* array = new int[size];

	cout<< "Please, enter "<< size<< " values: ";

	for (size_t i = 0; i < size; i++) {

		cin>> array[i];

	}
	cout <<"The process:" << endl;
insertionSort(array, size);
cout << "The result:" << endl;
	printArray(array, size);
	
	do {

		cout << "Which element do you want to find:" << endl;
		cin >> v;
		int result = binarySearch(array, 0, size - 1, v);
		(result == -1) ? cout << "Element is not present in array!"<<""
			: cout << "Element is present at index: " << result<<""<<endl;
		cout << "Use the progrem one more time? \n 0.NO \n 1.YES \n";
		cin >> repeat;
	} while (repeat);
	return 0;
}
