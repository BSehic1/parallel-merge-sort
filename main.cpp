#include <iostream>
#include <vector>
#include <list>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;

bool is_in_order(const vector<int> &v)
{
    if (v.size() < 2)
    {
        return true;
    }
    for (int i = 1; i < v.size(); i++)
    {
        if (v[i - 1] > v[i])
        {
            return false;
        }
    }
    return true;
}


void insertion_sort(vector<int>::iterator &first, const unsigned int &size, vector<int> &v)
{
    if (size < 2)
    {
        return;
    }
    if (size == 2)
    {
        if (*first > *next(first))
        {
            iter_swap(first, next(first));
        }
        return;
    }
    //because iterators passed as arguments are const_iterators
    auto first_element = first;
    auto element_to_be_sorted(next(first_element));

    for (int i = 1; i < size; i++)
    {
        auto seeker = prev(element_to_be_sorted);
        bool swap_first(false);
        if (*element_to_be_sorted > *seeker)
        {
            element_to_be_sorted = next(first_element, i + 1);
            continue;
        }
        while (*element_to_be_sorted < *seeker)
        {
            if (seeker == first_element)
            {
                swap_first = true;
                break;
            }
            seeker--;
        }
        if (swap_first)
        {
            v.insert(seeker, *element_to_be_sorted);
            v.erase(element_to_be_sorted + 1);
            first_element = seeker;
        }
        else
        {
            v.insert(next(seeker), *element_to_be_sorted);
            v.erase(element_to_be_sorted + 1);
        }
        element_to_be_sorted = next(first_element, i + 1);
    }
    first = first_element;
}

void merge(vector<int>::iterator &start_first, const unsigned int &first_size, vector<int>::iterator &start_second, const unsigned int &second_size, vector<int> &v)
{
    vector<int> container;
    int i(0), j(0);
    auto begining = start_first;
    while (i < first_size || j < second_size)
    {
        if (i == first_size)
        {
            container.push_back(*start_second);
            start_second++;
            j++;
        }
        else if (j == second_size)
        {
            container.push_back(*start_first);
            start_first++;
            i++;
        }
        else
        {
            if (*start_first <= *start_second)
            {
                container.push_back(*start_first);
                start_first++;
                i++;
            } else
            //if (*start_first > *start_second)
            {
                container.push_back(*start_second);
                start_second++;
                j++;
            }
        }
    }
    move(container.begin(), container.end(), begining);
}

void merge(const unsigned int& start_first_index, const unsigned int& first_size, const unsigned int& start_second_index, const unsigned int& second_size, vector<int> &v)
{
    vector<int> container;
    int i(0), j(0);

    auto start_first = v.begin()+start_first_index;
    auto start_second = v.begin()+start_second_index;

    while (i < first_size || j < second_size)
    {
        if (i == first_size)
        {
            container.push_back(*start_second);
            start_second++;
            j++;
        }
        else if (j == second_size)
        {
            container.push_back(*start_first);
            start_first++;
            i++;
        }
        else
        {
            if (*start_first <= *start_second)
            {
                container.push_back(*start_first);
                start_first++;
                i++;
            } else
                //if (*start_first > *start_second)
            {
                container.push_back(*start_second);
                start_second++;
                j++;
            }
        }
    }
    move(container.begin(), container.end(), v.begin()+start_first_index);
}

void serial_merge(const unsigned int start_index, const unsigned int& size, vector<int>& v){
    auto start = v.begin()+start_index;

    if(size <= 43){
        insertion_sort(start,size,v);
        return;
    }
    unsigned int partition_size = size / 2;

    serial_merge(start_index, partition_size, v);
    serial_merge(start_index+partition_size, size - partition_size, v);
    merge(start_index, partition_size, start_index+partition_size, size - partition_size, v);
}

void serial_merge_sort(vector<int> &v)
{
    serial_merge(0, v.size(), v);
}




void binary_search_and_insert(list<int>::iterator& element_to_sort,list<int>::iterator& first_element, const unsigned int& sorted_size, list<int>& l){
    auto element_to_erase = element_to_sort;
    if(sorted_size == 1){
        if(*element_to_sort < *first_element){
            first_element = l.insert(first_element,*element_to_sort);
            advance(element_to_sort,1);
            l.erase(element_to_erase);
        } else {
            advance(element_to_sort,1);
        }
        return;
    }
    if(sorted_size == 2){
        auto second_element = next(first_element);
        if(*element_to_sort < *first_element){
            first_element = l.insert(first_element,*element_to_sort);
            advance(element_to_sort,1);
            l.erase(element_to_erase);
        } else if(*first_element < *element_to_sort && *element_to_sort < *second_element){
            l.insert(next(first_element),*element_to_sort);
            advance(element_to_sort,1);
            l.erase(element_to_erase);
        } else {
            advance(element_to_sort,1);
        }
        return;
    }
    auto middle_element = next(first_element,sorted_size/2);
    if(*middle_element == *element_to_sort){
        l.insert(middle_element,*element_to_sort);
        advance(element_to_sort,1);
        l.erase(element_to_erase);
        return;
    } else if(*element_to_sort < *middle_element){
        binary_search_and_insert(element_to_sort,first_element,sorted_size/2,l);
    } else {
        auto first_element_in_second_array = first_element;
        advance(first_element_in_second_array,sorted_size/2);
        binary_search_and_insert(element_to_sort,first_element_in_second_array,sorted_size-sorted_size/2,l);
    }
}

list<int>::iterator insertion_sort(const list<int>::iterator& first, const unsigned int& size, list<int>& l){
    if (size < 2)
    {
        return first;
    }
    if (size == 2)
    {
        auto second = next(first);
        if (*first > *second)
        {
            iter_swap(first, second);
            return second;
        }
        return first;
    }
    auto first_element = first;
    auto i = next(first);
    int sorted_size = 1;
    while (sorted_size < size){
        binary_search_and_insert(i,first_element,sorted_size,l);
        sorted_size++;
    }
    return first_element;
}


int main()
{
    int vector_length = 13;
    list<int> numbers;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, vector_length);

    for (int k = 0; k < vector_length; k++)
    {
        numbers.push_back(dist(mt));
    }

    auto first = numbers.begin();
    insertion_sort(first,numbers.size(),numbers);

    for(auto x : numbers)
        cout << x << " ";

//    int vector_length = 100000;
//    vector<int> numbers;
//
//    std::random_device rd;
//    std::mt19937 mt(rd());
//    std::uniform_int_distribution<int> dist(1, vector_length);
//
//    for (int k = 0; k < vector_length; k++)
//    {
//        numbers.push_back(dist(mt));
//    }
//
//    vector<int> numbers2(numbers);
//    vector<int> numbers3(numbers);
//
//    auto start = std::chrono::high_resolution_clock::now();
//    sort(numbers2.begin(), numbers2.end());
//    auto stop = std::chrono::high_resolution_clock::now();
//    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
//    cout << "Default sort duration in microseconds: " << duration.count() << endl;
//
//    start = std::chrono::high_resolution_clock::now();
//    stable_sort(numbers3.begin(), numbers3.end());
//    stop = std::chrono::high_resolution_clock::now();
//    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
//    cout << "Stable sort duration in microseconds: " << duration.count() << endl;
//
//    start = std::chrono::high_resolution_clock::now();
//    serial_merge_sort(numbers);
//    stop = std::chrono::high_resolution_clock::now();
//    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
//    cout << "My sort duration in microseconds: " << duration.count() << endl;
//
//
//    bool is_sorted_well = is_in_order(numbers);
//    cout << "Is sorted well: " << is_sorted_well << endl;

    return 0;
}