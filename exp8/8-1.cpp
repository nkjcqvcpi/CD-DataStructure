//
//  main.cpp
//  8-1
//
//  Created by Houtong Lei on 2021/6/16.
//

#include <iostream>


int binary_search(const int arr[], int start, int end, int khey) {
    if (start > end)
        return -1;
    int mid = start + (end - start) / 2;
    if (arr[mid] > khey)
        return binary_search(arr, start, mid - 1, khey);
    else if (arr[mid] < khey)
        return binary_search(arr, mid + 1, end, khey);
    else
        return mid;
}

int main(int argc, const char * argv[]) {
    int data[] = {33, 88, 22, 55, 90, 11, 66, 99};
    int len = sizeof(data)/sizeof(int);
    int result1 = binary_search(data, 0, len, 77);
    std::cout << result1 << '\n';
    int result2 = binary_search(data, 0, len, 99);
    std::cout << result2 << '\n';
}
