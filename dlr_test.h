#ifndef DLR_TEST
#define DLR_TEST
#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include "dlr.h"

using namespace std;


template <typename Key, typename Info>
void test_size(dlr<Key, Info> &ring, int expected_size) {
    int actual_size = ring.size();

    if (actual_size != expected_size) {
        cout << "Failed test_size: expected " << expected_size << ", got " << actual_size << endl;
    }

}

template <typename Key, typename Info>
void test_empty(dlr<Key, Info> &ring, bool expected_empty) {
    bool actual_empty = ring.empty();

    if (actual_empty != expected_empty) {
        cout << "Failed test_empty: expected " << expected_empty << ", got " << actual_empty << endl;
    }

}

template<typename Key, typename Info>
void test_value(dlr<Key, Info> &ring, typename dlr<Key,Info>::iterator position, Key expected_Key, Info expected_Info) {
    pair<Key, Info> actual_values = ring.value(position);

    if(actual_values.first != expected_Key || actual_values.second != expected_Info) {
        cout<< "Failed test_value: expected ("<<expected_Key<<", "<<expected_Info<<") got ("<<actual_values.first<<", "<<actual_values.second<<")"<<endl;
    }

}

template <typename Key, typename Info>
void test_push(dlr<Key, Info> &ring, Key key, Info info, int expected_size) {
    typename dlr<Key, Info>::iterator it = ring.push(key, info);
    int actual_size = ring.size();

    if (actual_size != expected_size) {
        cout << "Failed test_push: expected size " << expected_size << ", got " << actual_size << endl;
    }

    pair<Key, Info> actual_value = ring.value(it);
    
    if (actual_value.first != key || actual_value.second != info) {
        cout << "Failed test_push: expected value (" << key << ", " << info << "), got (" << actual_value.first << ", " << actual_value.second << ")" << endl;
    }

}

template <typename Key, typename Info>
void test_pop(dlr<Key, Info> &ring, Key expected_key, Info expected_info, int expected_size) {
    typename dlr<Key, Info>::iterator it = ring.pop();
    int actual_size = ring.size();

    if (actual_size != expected_size) {
        cout << "Failed test_pop: expected size " << expected_size << ", got " << actual_size << endl;
    }
    
    pair<Key, Info> actual_value = ring.value(it);
    
    if (actual_value.first != expected_key || actual_value.second != expected_info) {
        cout << "Failed test_pop: expected value (" << expected_key << ", " << expected_info << "), got (" << actual_value.first << ", " << actual_value.second << ")" << endl;
    }

}

template <typename Key, typename Info>
void test_find(dlr<Key, Info> &ring, Key key, Info expected_info, int occurence, bool expected_found) {
    typename dlr<Key, Info>::iterator it = ring.find(key, occurence);
    typename dlr<Key, Info>::iterator null(nullptr);
    bool found = true;

    if(it == null) found = false;
    
    if(found != expected_found) {
        cout << "Failed test_find: expected found " << expected_found << ", got " << found << endl;
    }

    if(found) {
        pair<Key, Info> actual_value = ring.value(it);
        
        if (actual_value.first != key || actual_value.second != expected_info) {
            cout << "Failed test_find: expected value (" << key << ", " << expected_info << "), got (" << actual_value.first << ", " << actual_value.second << ")" << endl;
        }

    }

}

template <typename Key, typename Info>
void testClearAll(dlr<Key, Info> &ring) {   
    ring.clearAll();

    if(ring.empty() == false) {
        cout << "Failed testClearAll: ring is not empty"<<endl;
    }
    
}

template <typename Key, typename Info>
void test_erase(dlr<Key, Info> &ring, Key key, Key expected_Key, Info expected_info, int occurence, int expected_size) {
    typename dlr<Key, Info>::iterator it = ring.find(key, occurence);
    typename dlr<Key, Info>::iterator result = ring.erase(it);
    int actual_size = ring.size();

    if (actual_size != expected_size) {
        cout << "Failed test_erase: expected size " << expected_size << ", got " << actual_size << endl;
    }

    pair<Key, Info> actual_value = ring.value(result);
    
    if (actual_value.first != expected_Key || actual_value.second != expected_info) {
        cout << "Failed test_erase: expected value (" << expected_Key << ", " << expected_info << "), got (" << actual_value.first << ", " << actual_value.second << ")" << endl;
    }

}

template <typename Key, typename Info>
void test_insert(dlr<Key, Info> &ring,typename dlr<Key, Info>::iterator position, Key key, Info info, int expected_size) {
    typename dlr<Key, Info>::iterator result = ring.insert(position, key, info);
    int actual_size = ring.size();
    
    if (actual_size != expected_size) {
        cout << "Failed test_insert: expected size " << expected_size << ", got " << actual_size << endl;
    }
    
    pair<Key, Info> actual_value = ring.value(result);
    
    if (actual_value.first != key || actual_value.second != info) {
        cout << "Failed test_insert: expected value (" << key << ", " << info << "), got (" << actual_value.first << ", " << actual_value.second << ")" << endl;
    }

}

template<typename Key, typename Info>
void test_begin(dlr<Key, Info> &ring, Key expected_Key, Info expected_Info) {
    typename dlr<Key, Info>::iterator it = ring.begin();
    pair<Key, Info> actual_value = ring.value(it);

    if (actual_value.first != expected_Key || actual_value.second != expected_Info) {
        cout << "Failed test_begin: expected value (" << expected_Key << ", " << expected_Info << "), got (" << actual_value.first << ", " << actual_value.second << ")" << endl;
    }

}

template<typename Key, typename Info>
void test_cbegin(dlr<Key, Info> &ring, Key expected_Key, Info expected_Info) {
    typename dlr<Key, Info>::const_iterator it = ring.cbegin();
    pair<Key, Info> actual_value = ring.value(it);

    if (actual_value.first != expected_Key || actual_value.second != expected_Info) {
        cout << "Failed test_cbegin: expected value (" << expected_Key << ", " << expected_Info << "), got (" << actual_value.first << ", " << actual_value.second << ")" << endl;
    }

}

template<typename Key, typename Info>
void test_operatorplus(dlr<Key, Info> &first, dlr<Key,Info> &second, dlr<Key, Info> &expected_result) {
    dlr<Key, Info> actual_result = first + second;
    int actual_size = actual_result.size();
    int expected_size = expected_result.size();

    if(actual_size != expected_size) {
        cout << "Failed test_operatorplus: expected size " << expected_size << ", got " << actual_size << endl; 
    }

    if(actual_result != expected_result) {
        cout<< "Failed test_operatorplus: expected result:"<<endl; expected_result.print();
        cout<< "Actual result:\t"<<endl; actual_result.print(); 
    }
    
}

#endif