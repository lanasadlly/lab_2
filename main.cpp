#include <iostream>
#include <ctime>
#include <chrono>
#include <conio.h>
#define N (1000)
using namespace std;
using namespace chrono;

void printMenu ()
{
    cout << "Choose an action" << endl;
    cout << "1 - Create an int array, containing 100 element, each from -99 to 99" << endl;
    cout << "2 - Sort the array. Count time elapsed" << endl;
    cout << "3 - Find maximum and minimum values in the sorted and the unsorted array." << endl;
    cout << "    Count time elapsed" << endl;
    cout << "4 - Print average of maximum and minimum values in the sorted and unsorted array." << endl;
    cout << "    Print indexes of all elements with the same value and the number of them." << endl;
    cout << "    Count time elapsed" << endl;
    cout << "5 - Print a number of elements that are smaller than the entered value in the sorted array" << endl;
    cout << "6 - Print a number of elements that are bigger than the entered value in the sorted array" << endl;
    cout << "7 - Print if the sorted array contains the entered value" << endl;
    cout << "    Release the binary search." << endl;
    cout << "    Compare time elapsed for the binary search and the iterational search" << endl;
    cout << "8 - Change the places of values with entered indexes" << endl;
    cout << "   Count time elapsed" << endl;
    cout << "9 - Finish" << endl << endl;
}

void doBubbleSort (int sortedArr [])
{
    int end = N - 1;
    bool swapped = 1;
    while (swapped)
    {
        swapped = 0;
        for (int i = 0; i < end; i ++)
        {
            if (sortedArr [i] > sortedArr [i + 1])
            {
                swap (sortedArr [i], sortedArr [i + 1]);
                swapped = 1;
            }
        }
        end--;
    }
}

void doShakerSort (int sortedArr [])
{
    bool swapped = 1;
    int end = N - 1;
    int start = 0;
    while (swapped)
    {
        swapped = 0;
        for (int i = start; i < end; i++)
        {
            if (sortedArr [i] > sortedArr [i + 1])
            {
                swap (sortedArr [i], sortedArr [i + 1]);
                swapped = 1;
            }
        }
        end--;
        for (int i = end - 1; i >= start; i--)
        {
            if (sortedArr [i] > sortedArr [i + 1])
            {
                swap (sortedArr [i], sortedArr [i + 1]);
                swapped = 1;
            }
        }
        start++;
    }
}

void doCombSort (int sortedArr [])
{
    int end = N - 1;
    bool swapped = 1;
    float k = 1.247, step = N - 1;
    while (step >= 1)
    {
        for (int i = 0; i + step < N; i++)
        {
            if (sortedArr [i] > sortedArr [int (i + step)])
                swap (sortedArr [i], sortedArr [int (i + step)]);
        }
        step /= k;
    }
    while (swapped)
    {
        swapped = 0;
        for (int i = 0; i < end; i ++)
        {
            if (sortedArr [i] > sortedArr [i + 1])
            {
                swap (sortedArr [i], sortedArr [i + 1]);
                swapped = 1;
            }
        }
        end--;
    }
}

void doInsertSort (int sortedArr [])
{
    int key, j;
    for(int i = 1; i < N ; i++)
    {
        j = i - 1;
        key = sortedArr [i];
        while (j >= 0 && sortedArr [j] > key)
        {
            sortedArr [j + 1] = sortedArr [j];
            j --;
        }
        sortedArr [j + 1] = key;
    }
}

void doQuickSort (int sortedArr [], int start, int end)
{
    int left = start;
    int right = end;
    int mid = (start + end) / 2;
    int key = sortedArr [mid];
    int countLess = 0;
    for (int i = start; i <= end; i++)
        if (sortedArr [i] < key)
            countLess += 1;
    swap (sortedArr [mid], sortedArr [start + countLess]);
    while (left <= right)
    {
        while (sortedArr [left] < key)
            left++;
        while (sortedArr [right] >= key)
            right--;
        if (left < right)
        {
            swap (sortedArr [left], sortedArr [right]);
            left++;
            right--;
        }
    }
    if (right > start)
        doQuickSort (sortedArr, start, right);
    if (left + 1 < end)
        doQuickSort (sortedArr, left + 1, end);
}

int doBinarySearch (int arr [], int value, int start, int end)
{
    if (end >= start)
    {
        int mid = (start + end) / 2;
        if (arr [mid] == value)
            return mid;
        if (arr [mid] > value)
            return doBinarySearch (arr, value, start, mid - 1);
        return doBinarySearch (arr, value, mid + 1, end);
    }
    return -1;
}

int searchValue (int arr [], int value)
{
    for (int i = 0; i < N; i ++)
    {
        if (arr [i] == value)
            return i;
    }
    return -1;
}

int getMaxi (int arr [])
{
    int maxi = -99;
    for (int i = 0; i < N; i++)
    {
        if (arr [i] > maxi)
            maxi = arr [i];
    }
    return maxi;
}

int getMini (int arr [])
{
    int mini = 99;
    for (int i = 0; i < N; i++)
    {
        if (arr [i] < mini)
            mini = arr [i];
    }
    return mini;
}

void doPoint1 (int arr [], int sortedArr [])
{
    cout << "Original array:" << endl;
    for (int i = 0; i < N; i++)
    {
        arr [i] = rand () % 199 - 99;
        sortedArr [i] = arr [i];
        cout << arr [i] << " ";
    }
    cout << endl;
    cout << "Press any button to go to menu..." << endl << endl;
    getch ();
}

void doPoint2 (int arr [], int sortedArr [])
{
    int choose;
    cout << "Choose a sorting method:" << endl;
    cout << "1 - bubble sort" << endl;
    cout << "2 - shaker sort" << endl;
    cout << "3 - comb sort" << endl;
    cout << "4 - insert sort" << endl;
    cout << "5 - quick sort" << endl << endl;
    cin >> choose;
    cout << endl;
    switch (choose)
    {
    case 1:
        {
        for (int i = 0; i < N; i++)
            sortedArr [i] = arr [i];
        auto start = steady_clock :: now ();
        doBubbleSort (sortedArr);
        auto end = steady_clock :: now ();
        auto elapsed = duration_cast <milliseconds> (end - start). count ();
        cout << "Bubble sorting time: " << elapsed << " milliseconds" << endl;
        break;
        }
    case 2:
        {
        for (int i = 0; i < N; i++)
            sortedArr [i] = arr [i];
        auto start = steady_clock :: now ();
        doShakerSort (sortedArr);
        auto end = steady_clock :: now ();
        auto elapsed = duration_cast <milliseconds> (end - start). count ();
        cout << "Shaker sorting time: " << elapsed << " milliseconds" << endl;
        break;
        }
    case 3:
        {
        for (int i = 0; i < N; i++)
            sortedArr [i] = arr [i];
        auto start = steady_clock :: now ();
        doCombSort (sortedArr);
        auto end = steady_clock :: now ();
        auto elapsed = duration_cast <milliseconds> (end - start). count ();
        cout << "Comb sorting time: " << elapsed << " milliseconds" << endl;
        break;
        }
    case 4:
        {
        for (int i = 0; i < N; i++)
            sortedArr [i] = arr [i];
        auto start = steady_clock :: now ();
        doInsertSort (sortedArr);
        auto end = steady_clock :: now ();
        auto elapsed = duration_cast <milliseconds> (end - start). count ();
        cout << "Insert sorting time: " << elapsed << " milliseconds" << endl;
        break;
        }
    case 5:
        {
        for (int i = 0; i < N; i++)
            sortedArr [i] = arr [i];
        auto start = steady_clock :: now ();
        doQuickSort (sortedArr, 0, N - 1);
        auto end = steady_clock :: now ();
        auto elapsed = duration_cast <milliseconds> (end - start). count ();
        cout << "Quick sorting time: " << elapsed << " milliseconds" << endl;
        break;
        }
    default:
        {
        for (int i = 0; i < N; i++)
            sortedArr [i] = arr [i];
        cout << "Bubble sort picked...";
        auto start = steady_clock :: now ();
        doBubbleSort (sortedArr);
        auto end = steady_clock :: now ();
        auto elapsed = duration_cast <milliseconds> (end - start). count ();
        cout << "Sorting time: " << elapsed << " milliseconds" << endl;
        }
    }
    cout << "Sorted array:" << endl;
    for (int i = 0; i< N; i++)
        cout << sortedArr [i] << " ";
    cout << endl;
    cout << "Press any button to go to menu..." << endl << endl;
    getch ();
}

void doPoint3 (int arr [], int sortedArr [])
{
    int mini, maxi;
    auto start = steady_clock :: now ();
    maxi = getMaxi (arr);
    mini = getMini (arr);
    auto end = steady_clock :: now ();
    auto elapsed = duration_cast <milliseconds> (end - start). count ();
    cout << "Maximum array value is " << maxi << endl;
    cout << "Minimum array value is " << mini << endl;
    cout << "Time getting minimum and maximum values in an unsorted array:" << endl;
    cout << elapsed << " milliseconds" << endl;
    start = steady_clock :: now ();
    maxi = getMaxi (sortedArr);
    mini = getMini (sortedArr);
    end = steady_clock :: now ();
    elapsed = duration_cast <milliseconds> (end - start). count ();
    cout << "Time getting minimum and maximum values in a sorted array:" << endl;
    cout << elapsed << " milliseconds" << endl;
    cout << "Press any button to go to menu..." << endl << endl;
    getch ();
}

void doPoint4 (int arr [], int sortedArr [])
{
    int maxi, mini, average;
    int number = 0;
    auto start = steady_clock :: now ();
    maxi = getMaxi (arr);
    mini = getMini (arr);
    average = (maxi + mini) / 2;
    cout << "Average of minimum and maximum values in an unsorted array: " << average << endl;
    cout << "Indexes of elements equal to the average: ";
    for (int i = 0; i < N; i++)
    {
        if (arr [i] == average)
        {
            cout << i << " ";
            number ++;
        }
    }
    auto end = steady_clock :: now ();
    auto elapsed = duration_cast <milliseconds> (end - start). count ();
    cout << endl;
    cout << "Number of elements equal to average: " << number << endl;
    cout << "Time of searching in an unsorted array: ";
    cout << elapsed << " milliseconds" << endl;
    number = 0;
    start = steady_clock :: now ();
    maxi = getMaxi (sortedArr);
    mini = getMini (sortedArr);
    average = (maxi + mini) / 2;
    cout << "Average of minimum and maximum values in a sorted array: " << average << endl;
    cout << "Indexes of elements equal to the average: ";
    for (int i = 0; i < N; i++)
    {
        if (sortedArr [i] == average)
        {
            cout << i << " ";
            number ++;
        }
    }
    end = steady_clock :: now ();
    elapsed = duration_cast <milliseconds> (end - start). count ();
    cout << endl;
    cout << "Number of elements equal to average: " << number << endl;
    cout << "Time of searching in a sorted array: ";
    cout << elapsed << " milliseconds" << endl;
    cout << "Press any button to go to menu..." << endl << endl;
    getch ();
}

void doPoint5 (int sortedArr [])
{
    int border, number = 0;
    cout << "Enter a value: ";
    cin >> border;
    for (int i = 0; i < N; i++)
    {
        if (sortedArr [i] < border)
            number ++;
    }
    cout << "Number of smaller array values: " << number << endl;
    cout << "Press any button to go to menu..." << endl << endl;
    getch ();
}

void doPoint6 (int sortedArr [])
{
    int border, number = 0;
    cout << "Enter a value: ";
    cin >> border;
    for (int i = 0; i < N; i++)
    {
        if (sortedArr [i] > border)
            number ++;
    }
    cout << "Number of bigger array values: " << number << endl;
    cout << "Press any button to go to menu..." << endl << endl;
    getch ();
}

void doPoint7 (int sortedArr [])
{
    int value;
    cout << "Enter a value: ";
    cin >> value;
    if (doBinarySearch (sortedArr, value, 0, N - 1) > -1)
    {
        cout << value << " is in array with index ";
        cout << doBinarySearch (sortedArr, value, 0, N - 1) << endl;
    }
    else
        cout << value << " is not in array" << endl;
    auto startBinary = steady_clock :: now ();
    doBinarySearch (sortedArr, value, 0, N - 1);
    auto endBinary = steady_clock :: now ();
    auto elapsedBinary = duration_cast <milliseconds> (startBinary - endBinary). count ();
    auto start = steady_clock :: now ();
    searchValue (sortedArr, value);
    auto end = steady_clock :: now ();
    auto elapsed = duration_cast <milliseconds> (start - end). count ();
    cout << "Time of binary search: " << elapsedBinary << " milliseconds" << endl;
    cout << "Time of iterational search: " << elapsed << " milliseconds" << endl;
    cout << "Binary search is " << elapsed - elapsedBinary << " milliseconds faster" << endl;
    cout << "Press any button to go to menu..." << endl << endl;
    getch ();
}

void doPoint8 (int arr [])
{
    int first, second;
    bool choose;
    cout << "Enter indexes of 2 elements that you want to change places" << endl;
    cout << "(from 0 to " << N - 1 << "):" << endl;
    cin >> first >> second;
    auto start = steady_clock :: now ();
    swap (arr [first], arr[second]);
    auto end = steady_clock :: now ();
    auto elapsed = duration_cast <milliseconds> (end - start). count ();
    cout << "Time of changing places: ";
    cout << elapsed << " milliseconds" << endl;
    cout << "Do you want to see the Changed array?" << endl;
    cout << "Enter '1' for yes and '0' for no" << endl;
    cin >> choose;
    if (choose == 1)
    {
        cout << "Changed array:" << endl;
        for (int i = 0; i < N; i++)
            cout << arr [i] << " ";
        cout << endl;
    }
    cout << "Press any button to go to menu..." << endl << endl;
    getch ();
}

int main()
{
    setlocale (0, "");
    srand (time(NULL));
    int arr [N];
    int sortedArr [N];
    for (int i = 0; i < N; i++)
    {
        arr[i] = rand () % 199 - 99;
        sortedArr [i] = arr [i];
    }
    bool sorted = 0;
    int pick;
    while (true)
    {
        printMenu ();
        cin >> pick;
        cout << endl;
        switch (pick)
        {
        case 1:
            doPoint1 (arr, sortedArr);
            sorted = 0;
            break;
        case 2:
            doPoint2 (arr, sortedArr);
            sorted = 1;
            break;
        case 3:
            if (sorted)
                doPoint3 (arr, sortedArr);
            else
                cout << "You need to sort the array first! (point 2)" << endl << endl;
            break;
        case 4:
            if (sorted)
                doPoint4 (arr, sortedArr);
            else
                cout << "You need to sort the array first! (point 2)" << endl << endl;
            break;
        case 5:
            if (sorted)
                doPoint5 (sortedArr);
            else
                cout << "You need to sort the array first! (point 2)" << endl << endl;
            break;
        case 6:
            if (sorted)
                doPoint6 (sortedArr);
            else
                cout << "You need to sort the array first! (point 2)" << endl << endl;
            break;
        case 7:
            if (sorted)
                doPoint7 (sortedArr);
            else
                cout << "You need to sort the array first! (point 2)" << endl << endl;
            break;
        case 8:
            doPoint8 (arr);
            break;
        case 9:
            exit (0);
        default:
            exit (0);
        }
    }
    return 0;
}
