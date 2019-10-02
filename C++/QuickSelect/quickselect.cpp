#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

// chooses the last element as the pivot
int partition (std::vector<int>& arr, int low, int high)
{
    // pivot (Element to be placed at right position)
    int pivot = arr[high];  
 
    int i = low - 1;  // Index of smaller element

    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++;    // increment index of smaller element

            // swap arr[i], arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

     // swap arr[i+1], arr[high] = pivot
    int temp = arr[i+1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    // the actual index of the pivot
    return i + 1;
}

int quickselect(int index_to_search, std::vector<int> vector, int left_limit, int right_limit) {
    if (left_limit < 0 || right_limit > (vector.size() - 1) ) {
        throw std::out_of_range("limits out of vector");
    }

    int partition_index = partition(vector,left_limit,right_limit);

    // found element at desired index
    if (index_to_search == partition_index) {
        return vector[partition_index];
    } else if (index_to_search < partition_index) { 
        // desired index is before current pivot's index
        return quickselect(index_to_search, vector, left_limit, partition_index - 1);
    } else {
        // desired index is after current pivot's index
        return quickselect(index_to_search, vector, partition_index + 1, right_limit);
    }
}

int main() {
    std::vector<int> vec{10,-2,13,54,175,1024,2028};

    std::cout << "Element at index 2 is " << quickselect(2,vec,0,vec.size() - 1) << std::endl;
    std::cout << "Element at index 5 is " << quickselect(5,vec,0,vec.size() - 1) << std::endl;
    std::cout << "Element at index 0 is " << quickselect(0,vec,0,vec.size() - 1) << std::endl;

    std::sort(vec.begin(),vec.end());

    std::cout << "Sorted elements" << std::endl;
    for (auto &&i : vec)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
}