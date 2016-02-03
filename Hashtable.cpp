#include <stdlib.h>
#include <iomanip>
#include <iostream>
#include "Hashtable.h"
#include "Student.h"
using namespace std;

Hashtable::Hashtable() {
    this->table = new Bucket[table_size];
}

Hashtable::~Hashtable() {
    for (int i=0; i < table_size; i++) {
        if(table[i].s != NULL)
            delete table[i].s;
    }
}

int Hashtable::hash1(const int &key) {
    if((key % 492113) % table_size == 0)
        return 1;
    return (key % 492113) % table_size;
}

int Hashtable::hash2(const int &key) {
    return (key % 392113) % table_size;
}

void Hashtable::insert(const int &key, Student* s) {

    if (this->doubleHash == false) { // linearprobing insert method
        lookupSuccess = false;
        if (lookup(key) == true) {
            cout << "item already present" << endl;
            lookupSuccess = true;
            return;
        } else {
            lookupSuccess = true;
        }
        if(( (double) (num_entries + 1)/table_size) >= LOAD_FACTOR) {
            int old_table_size = this->table_size;
            this->table_size = returnPrimeSize(old_table_size);
            rehashLinear(old_table_size);
            cout << "table doubled" << endl;
        }
        int it = 0;
        if (table[hash1(key)].s == NULL) {
            table[hash1(key)].s = s;
    	    table[hash1(key)].key = key;
    	    ++num_entries;
            cout << "item successfully inserted" << endl;
            return;
        }
        else {
            while(table[(hash1(key) + it)%table_size].s != NULL) {
                ++it;
            }
            table[(hash1(key) + it)%table_size].s = s;
    	    table[(hash1(key) + it)%table_size].key = key;
    	    ++num_entries;
            cout << "item successfully inserted" << endl;
            return;
        }
    }
    else if (this->doubleHash == true) { //
        lookupSuccess = false;
        if (lookup(key) == true) {
            cout << "item already present" << endl;
            lookupSuccess = true;
            return;
        } else {
            lookupSuccess = true;
        }
        if(( (double) (num_entries + 1)/table_size) >= LOAD_FACTOR) {
            int old_table_size = this->table_size;
            this->table_size = returnPrimeSize(old_table_size);
            rehashDouble(old_table_size);
            cout << "table doubled" << endl;
        }
        int it = 0;
        if (table[hash1(key)].s == NULL) {
            table[hash1(key)].s = s;
            table[hash1(key)].key = key;
            ++num_entries;
            cout << "item successfully inserted" << endl;
            return;
        }
        else {
            while(table[(hash1(key) + it*hash2(key))%table_size].s != NULL) {
                ++it;
            }
            table[(hash1(key) + it*hash2(key))%table_size].s = s;
            table[(hash1(key) + it*hash2(key))%table_size].key = key;
            ++num_entries;
            cout << "item successfully inserted" << endl;
            return;
        }
    }
}

bool Hashtable::lookup(const int &key) {

    if (this->doubleHash == false) {
        int it = 0;
        if(table[hash1(key)].s == NULL && table[hash1(key)].key != REMOVE_INDICATOR) {
            if(lookupSuccess == true)
                cout << "item not found" << endl;
            return false;
        }
        else {
            while(table[(hash1(key) + it)%table_size].s != NULL || table[(hash1(key) + it)%table_size].key == REMOVE_INDICATOR) {
                if (table[(hash1(key) + it)%table_size].key == REMOVE_INDICATOR) {
                    ++it;
                    continue;
                }
                if(table[(hash1(key) + it)%table_size].key == key) {
                    if(lookupSuccess == true) {
                        cout << "item found; ";
                        cout << table[(hash1(key) + it)%table_size].s->getName() << " ";
                        cout << (hash1(key) + it)%table_size << endl;
                    }
                    return true;
                }
                ++it;
            }
            if(lookupSuccess == true)
                cout << "item not found" << endl;
            return false;
        }
    }
    else if (this->doubleHash == true) {
        int it = 0;
        if(table[hash1(key)].s == NULL && table[hash1(key)].key != REMOVE_INDICATOR) {
            if(lookupSuccess == true)
                cout << "item not found" << endl;
            return false;
        }
        else {
            while(table[(hash1(key) + it*hash2(key))%table_size].s != NULL || table[(hash1(key) + it*hash2(key))%table_size].key == REMOVE_INDICATOR) {
                if (table[(hash1(key) + it*hash2(key))%table_size].key == REMOVE_INDICATOR) {
                    ++it;
                    continue;
                }
                if(table[(hash1(key) + it*hash2(key))%table_size].key == key) {
                    if (lookupSuccess == true) {
                        cout << "item found; ";
                        cout << table[(hash1(key) + it*hash2(key))%table_size].s->getName() << " ";
                        cout << (hash1(key) + it*hash2(key))%table_size << endl;
                    }
                    return true;
                }
                ++it;
            }
            if (lookupSuccess == true)
                cout << "item not found" << endl;
            return false;
        }
    }
    return false;
}

void Hashtable::remove(const int &key) {

    if (this->doubleHash == false) {
        int it = 0;
        if(table[hash1(key)].s == NULL && table[hash1(key)].key != REMOVE_INDICATOR) {
            cout << "item not present in the table" << endl;
            return;
        }
        else {
            while(table[(hash1(key) + it)%table_size].s != NULL || table[(hash1(key) + it)%table_size].key == REMOVE_INDICATOR) {
                if (table[(hash1(key) + it)%table_size].key == REMOVE_INDICATOR) {
                    ++it;
                    continue;
                }
                if (table[(hash1(key) + it)%table_size].key == key) {
                    delete table[(hash1(key) + it)%table_size].s;
                    table[(hash1(key) + it)%table_size].s = NULL;
                    table[(hash1(key) + it)%table_size].key = REMOVE_INDICATOR;
                    --num_entries;
                    cout << "item successfully deleted" << endl;
                    return;
                }
                ++it;
            }
            cout << "item not present in the table" << endl;
            return;
        }
    }
    else if (this->doubleHash == true) {
        int it = 0;
        if(table[hash1(key)].s == NULL && table[hash1(key)].key != REMOVE_INDICATOR) {
            cout << "item not present in the table" << endl;
            return;
        }
        else {
            while(table[(hash1(key) + it*hash2(key))%table_size].s != NULL || table[(hash1(key) + it*hash2(key))%table_size].key == REMOVE_INDICATOR) {
                if (table[(hash1(key) + it*hash2(key))%table_size].key == REMOVE_INDICATOR) {
                    ++it;
                    continue;
                }
                if (table[(hash1(key) + it*hash2(key))%table_size].key == key) {
                    delete table[(hash1(key) + it*hash2(key))%table_size].s;
                    table[(hash1(key) + it*hash2(key))%table_size].s = NULL;
                    table[(hash1(key) + it*hash2(key))%table_size].key = REMOVE_INDICATOR;
                    --num_entries;
                    cout << "item successfully deleted" << endl;
                    return;
                }
                ++it;
            }
            cout << "item not present in the table" << endl;
            return;
        }
    }
}

void Hashtable::print() const {

    for (int i=0; i < table_size; i++) {
        if(table[i].s != NULL) {
            cout << "(" << table[i].key;
            cout << "," << table[i].s->getName();
            cout << "," << std::fixed << std::setprecision(1) << table[i].s->getGpa() << ")";
        }
    }
    cout << endl;

    return;

}

void Hashtable::rehashLinear(const int &old_table_size) {

    Bucket* old_table = new Bucket[old_table_size];
    for (int i=0; i < old_table_size; i++) {
        if(this->table[i].s != NULL) {
            old_table[i].key = this->table[i].key;
            old_table[i].s = new Student(this->table[i].s->getName(),this->table[i].s->getGpa());
        }
        this->table[i].key = EMPTY_INDICATOR;
    }
    this->table = new Bucket[this->table_size];
    for (int i=0; i < old_table_size; i++) {
        if(old_table[i].s != NULL) {
            int it = 0;
            if (this->table[hash1(old_table[i].key)].s == NULL) {
                this->table[hash1(old_table[i].key)].s = new Student(old_table[i].s-> getName(), old_table[i].s->getGpa());
        	    this->table[hash1(old_table[i].key)].key = old_table[i].key;
            }
            else {
                while(this->table[(hash1(old_table[i].key) + it)%this->table_size].s != NULL) {
                    ++it;
                }
                this->table[(hash1(old_table[i].key) + it)%this->table_size].s = new Student(old_table[i].s->getName(), old_table[i].s->getGpa());
        	    this->table[(hash1(old_table[i].key) + it)%this->table_size].key = old_table[i].key;
            }
            delete old_table[i].s;
        }
    }
    return;
}

void Hashtable::rehashDouble(const int &old_table_size) {

    Bucket* old_table = new Bucket[old_table_size];
    for (int i=0; i < old_table_size; i++) {
        if(this->table[i].s != NULL) {
            old_table[i].key = this->table[i].key;
            old_table[i].s = new Student(this->table[i].s->getName(),this->table[i].s->getGpa());
        }
        this->table[i].key = EMPTY_INDICATOR;
    }
    this->table = new Bucket[this->table_size];
    for (int i=0; i < old_table_size; i++) {
        if(old_table[i].s != NULL) {
            int it = 0;
            if (this->table[hash1(old_table[i].key)].s == NULL) {
                this->table[hash1(old_table[i].key)].s = new Student(old_table[i].s-> getName(), old_table[i].s->getGpa());
        	    this->table[hash1(old_table[i].key)].key = old_table[i].key;
            }
            else {
                while(this->table[(hash1(old_table[i].key) + it*hash2(old_table[i].key))%table_size].s != NULL) {
                    ++it;
                }
                this->table[(hash1(old_table[i].key) + it*hash2(old_table[i].key))%table_size].s = new Student(old_table[i].s->getName(), old_table[i].s->getGpa());
        	    this->table[(hash1(old_table[i].key) + it*hash2(old_table[i].key))%table_size].key = old_table[i].key;
            }
            delete old_table[i].s;
        }
    }
    return;
}

bool Hashtable::isPrime(const int &num)
{	// Given:   num an integer > 1
	// Returns: true if num is prime
	// 			false otherwise.
	int i;
	for (i=2; i<num; i++)
	{
		if (num % i == 0)
		{
			return false;
		}
	}
	return true;
}

int Hashtable::returnPrimeSize(const int &current_size) {
    int new_size = current_size*2 + 1;
    while (isPrime(new_size) == false) {
        new_size += 2;
    }
    return new_size;
}

void Hashtable::setMode(const int &mode) {
    if(mode == 1) {
        if (this->doubleHash == false)
            return;
        this->doubleHash = false;
        rehashLinear(this->table_size);
    }
    else if (mode == 2) {
        if (this->doubleHash == true)
            return;
        this->doubleHash = true;
        rehashDouble(this->table_size);
    }
    return;
}

