#ifndef DLR
#define DLR
#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>

using namespace std;

template <typename Key, typename Info>
class dlr {

    private:

        struct Node {
            Key key;
            Info info;
            Node *prev;
            Node *next;

            Node(Key k, Info val) : key(k), info(val), prev(NULL), next(NULL) {}
        };

    public:

        class iterator {

            private:

                Node *node;

            public:

                iterator(Node *n) : node(n){};

                Node &operator*() { 
                    return *node; 
                }

                Node *operator->() { 
                    return node; 
                }

                iterator &operator++() {
                    node = node->next;
                    return *this;
                }

                iterator &operator++(int) {
                    iterator &Old = *this;
                    ++(*this);
                    return Old;
                }

                iterator &operator--() {
                    node = node->prev;
                    return *this;
                }

                iterator &operator--(int) {
                    iterator &Old = *this;
                    --(*this);
                    return Old;
                }

                bool operator!=(const iterator &other) const { 
                    return node != other.node; 
                }

                bool operator==(const iterator &other) const { 
                    return node == other.node;
                }

        };

        class const_iterator {

            private:

                Node *node;

            public:

                const_iterator(Node *n) : node(n){};

                const Node &operator*() { 
                    return *node; 
                }

                const_iterator &operator++() {
                    node = node->next;
                    return *this;
                }

                const_iterator &operator++(int) {
                    const_iterator &Old = *this;
                    ++(*this);
                    return Old;
                }

                const_iterator &operator--() {
                    node = node->prev;
                    return *this;
                }

                const_iterator &operator--(int) {
                    const_iterator &Old = *this;
                    --(*this);
                    return Old;
                }

                bool operator!=(const const_iterator &other) const { 
                    return node != other.node; 
                }

                bool operator==(const const_iterator &other) const { 
                    return node == other.node; 
                }

        };

        dlr() : any(NULL) {}
        ~dlr();
        dlr(const dlr &other);
        dlr &operator=(const dlr &other);

        void clearAll();

        iterator push(const Key &, const Info &);
        iterator pop();
        iterator find(const Key &, int occurence = 1);

        iterator erase(iterator position);
        iterator insert(iterator position, const Key &, const Info &);

        int size() const;
        
        bool empty() const { 
            return any == NULL; 
        }

        iterator begin() { return iterator(any); }
        
        const_iterator cbegin() const { 
            return const_iterator(any); 
        }

        dlr<Key, Info> operator+(const dlr &them) const;

        bool operator==(const dlr &them) const;
        bool operator!=(const dlr &them) const;

         pair<Key, Info> value(const_iterator position) const {
            const Node &curr = *position;
            return  make_pair(curr.key, curr.info);
        }

         pair<Key, Info> value(iterator position) {
            Node &curr = *position;
            return  make_pair(curr.key, curr.info);
        }

        void const print();

    private:
        Node *any;
};

template <typename Key, typename Info>
void dlr<Key, Info> :: clearAll() {

    if (any == NULL) return;

    any->prev->next = NULL;

    while (any != NULL) {
        Node *ToDel = any;
        any = any->next;
        delete ToDel;
    }

    any = NULL;
}

template <typename Key, typename Info>
dlr<Key, Info>::~dlr() {
    clearAll();
}

template <typename Key, typename Info>
dlr<Key, Info> &dlr<Key, Info> :: operator=(const dlr<Key, Info> &other) {
    
    if (this != &other) {
        clearAll();
        // Traverse the doubly-linked ring of the other object
        // and push each node to the back of this object.
        dlr :: const_iterator it = other.cbegin();
        
        do {
            const Node &node = *it;
            push(node.key, node.info);
            ++it;
        } while (it != other.cbegin());
    
    }

    return *this;
}

template <typename Key, typename Info>
dlr<Key, Info> :: dlr(const dlr &other) {
    any = NULL;
    *this = other;
}

template <typename Key, typename Info>
int dlr<Key, Info> :: size() const {
    
    if (empty()) return 0;
    int count = 0;
    dlr :: const_iterator it = this->cbegin();
    
    do {
        count++;
        ++it;
    } while (it != this->cbegin());
    
    return count;
}

template <typename Key, typename Info>
typename dlr<Key, Info> :: iterator dlr<Key, Info> :: find(const Key &key, int occurence) {
    
    if (!empty() && occurence > 0) {
        int occ = 0;
        iterator it = this->begin();
        
        do {
            const Node &node = *it;
            
            if (node.key == key) occ++;
            
            if (occ == occurence) return it;
            
            it++;
        } while (it != this->begin());

    }
    return iterator(NULL);
}

template <typename Key, typename Info>
typename dlr<Key, Info> :: iterator dlr<Key, Info> :: erase(iterator position) {
    Node *toDel = &(*position);

    if (toDel == NULL) {
        return iterator(any->prev);
    }

    if (toDel == any) {
        Node *next = any->next;
        any->prev->next = any->next;
        any->next->prev = any->prev;
        delete any;
        any = next;
        return iterator(next);
    }

    Node *next = toDel->next;
    toDel->prev->next = toDel->next;
    toDel->next->prev = toDel->prev;
    delete toDel;
    return iterator(next);
}

template <typename Key, typename Info>
typename dlr<Key, Info> :: iterator dlr<Key, Info> :: insert(iterator position, const Key &key, const Info &info) {
    Node *newNode = new Node(key, info);

    if (any == NULL) {
        any = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    }

    else {
        Node *pos = &(*position);
        newNode->prev = pos->prev;
        newNode->next = pos;
        pos->prev->next = newNode;
        pos->prev = newNode;
    }

    // Return an iterator pointing to the newly inserted node
    return iterator(newNode);
}

template <typename Key, typename Info>
typename dlr<Key, Info> :: iterator dlr<Key, Info> :: push(const Key &key, const Info &info) {
    Node *node = new Node(key, info);

    if (any == NULL) {
        any = node;
        any->prev = any;
        any->next = any;
    }

    else {
        any->prev->next = node;
        node->prev = any->prev;
        any->prev = node;
        node->next = any;
    }

    iterator it(node);
    return it;
}

template <typename Key, typename Info>
typename dlr<Key, Info> :: iterator dlr<Key, Info> :: pop() {

    if (empty()) {
        iterator it(any);
        return it;
    }

    if (any->prev == any) {
        delete any;
        any = NULL;
        iterator it(any);
        return it;
    }

    Node *toDel = any->prev;
    toDel->prev->next = any;
    any->prev = toDel->prev;
    delete toDel;
    iterator it(any);
    return it;
}

template <typename Key, typename Info>
void const dlr<Key, Info> :: print() {
    
    // Traverse the doubly-linked ring and print the value of each node.
    if (any == NULL) {
         cout << "Empty" <<  endl;
    }

    else {
         cout << "[";
        dlr :: const_iterator it = this->cbegin();
        
        do {
            const Node &node = *it;
             cout << node.key << ":" << node.info;
            
            if (node.next != any)
                cout << ", ";
            ++it;
        } while (it != this->cbegin());

         cout << "]" <<  endl;
    }
}

// ADDITIONAL FUNCTIONS
template <typename Key, typename Info>
dlr<Key, Info> filter(const dlr<Key, Info> &source, bool(pred)(const Key &)) {
    dlr<Key, Info> result;
    
    if (source.empty()) return result;

    typename dlr<Key, Info> :: const_iterator it = source.cbegin();
    
    do {
         pair<Key, Info> values = source.value(it);
        
        if (pred(values.first)) result.push(values.first, values.second);

        it++;
    } while (it != source.cbegin());
    
    return result;
}

template <typename Key, typename Info>
dlr<Key, Info> dlr<Key, Info> :: operator+(const dlr &them) const {
    dlr<Key, Info> result(*this);
    
    if (them.empty()) return result;

    dlr<Key, Info>::const_iterator it = them.cbegin();
    
    do {
        const Node &curr = *it;
        dlr<Key, Info> :: iterator me = result.find(curr.key);
        Node *node = &(*me);
        
        //it has not been found
        if (node == NULL) {
            result.push(curr.key, curr.info);
        }
        
        else { // There's atleast one
            int occurence = 1;
            
            while (node != NULL) {
                node->info += curr.info;
                me = result.find(curr.key, ++occurence);
                node = &(*me);
            }

        }

        it++;
    } while (it != them.cbegin());

    return result;
}

template<typename Key, typename Info>
bool dlr<Key, Info> :: operator==(const dlr<Key, Info> &them) const {
    
    if(this == &them) return true;
    
    if(this->size() != them.size(0)) return false;
    
    if(this->empty()) return true;
    
    typename dlr<Key, Info> :: const_iterator us = this->cbegin();
    typename dlr<Key, Info> :: const_iterator other = them.cbegin();
    
    do {
        pair<Key, Info> my_val = this->value(us);
        pair<Key, Info> his_val = them.value(other);
        
        if(my_val.first != his_val.first || my_val.second != his_val.second) {
            return false;
        }
        
        us++;
        other++;
    } while (us != this->cbegin() || other != them.cbegin());
    
    return true;
}

template<typename Key, typename Info>
bool dlr<Key, Info> :: operator!=(const dlr<Key, Info> &them) const {
    return !(*this == them);
}

template <typename Key, typename Info>
dlr<Key, Info> join(const dlr<Key, Info> &first, const dlr<Key, Info> &second) {
    dlr<Key, Info> result = first + second;
    return result;
}

template <typename Key, typename Info>
dlr<Key, Info> unique(const dlr<Key, Info> source, Info(aggregate)(const Key &, const Info &, const Info &)) {
    
    if (source.empty()) {
        return source;
    }
    
     map<Key, Info> unique_keys;
    typename dlr<Key, Info> :: const_iterator it = source.cbegin();
    
    do {
         pair<Key, Info> val = source.value(it);
        Key k = val.first;
        Info i = val.second;
        
        if (unique_keys.count(k) > 0) {
            unique_keys[k] = aggregate(k, unique_keys[k], i);
        }
        
        else
            unique_keys[k] = i;
        it++;
    } while (it != source.cbegin());

    dlr<Key, Info> result;
    
    for (const auto &[key, info] : unique_keys) {
        result.push(key, info);
    }
    
    return result;
}

#endif