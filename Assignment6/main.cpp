// A Program that generates all (n-take-r) combinations of objects stored in
// an array.  
// Written by Prof. Sreenivas for IE523: Financial Computing 
// The implementation is inspired by the material at the following URL:
// http://stackoverflow.com/questions/9430568/generating-combinations-in-c

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() 
{
	int size_of_array, number_of_objects_to_be_picked;
	int *array;
	
	cout << "Array Size? ";
	cin >> size_of_array;
	cout << "#Objects to be picked from array? ";
	cin >> number_of_objects_to_be_picked;
	
	// I am just filling the array with integers... it could be a list of
	// other objects, for example.
	array = new int[size_of_array];
	for (int i = 0; i < size_of_array; i++)
		array[i] = i+1;
	
	// Create a boolean array where the first r items are "false" (i.e. 0)
	// the remaining n-r items are "true" (i.e. 1)
	vector <bool> did_i_pick_this(size_of_array);
	fill(did_i_pick_this.begin() + number_of_objects_to_be_picked, 
		 did_i_pick_this.end(), true);

	// I am going to use the next_permutation STL in C++ (see 
	// http://www.cplusplus.com/reference/algorithm/next_permutation/ )
	// to generate the required combinatorial outputs 
	do 
	{
		cout << "{ ";
		for (int i = 0; i < size_of_array; ++i) 
		{
			if (!did_i_pick_this[i]) 
				cout << array[i] << " ";
		}
		cout << "}" << endl;
	} while (next_permutation(did_i_pick_this.begin(), did_i_pick_this.end())); 
		
	return 0;
}
