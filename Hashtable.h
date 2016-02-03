#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "Student.h"

#define REMOVE_INDICATOR -100
#define EMPTY_INDICATOR -10
#define LOAD_FACTOR 0.7
#define INIT_TABLE_SIZE 5

class Hashtable {
private:
    struct Bucket {
        int key = EMPTY_INDICATOR;
        Student* s = NULL;
    };
    
    int table_size = INIT_TABLE_SIZE;
    Bucket* table;
    int num_entries = 0;
    bool doubleHash = false;
    bool lookupSuccess = true;

    int hash1(const int &key);
    int hash2(const int &key);
    
    int returnPrimeSize(const int &current_size);
    bool isPrime(const int &num);
    void rehashLinear(const int &old_table_size);
    void rehashDouble(const int &old_table_size);
public:
    Hashtable();
    ~Hashtable();
    
    void insert(const int &key, Student* s);
    bool lookup(const int &key);
    void remove(const int &key);
    void print() const;
    
    void setMode(const int &mode);
};

#endif
