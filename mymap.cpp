#include <iostream>
#include <string>
#include <locale>
#include <algorithm>
#include <exception>
using namespace std;

template<class Tkey, class Tval> class MyMap {
private:
    Tkey *key; // начало массива ключей
    Tval *val; // начало массива значений
    int size; // размер словаря
    int first_empty; // индекс ближайшей неинициализированной пары
public:
    MyMap(int sz = 32) {
        size = sz; 
        key = new Tkey [size];
        val = new Tval [size];
        first_empty = 0;
        cout << "Constructor\n";
    }
    MyMap(const MyMap &m) { 
        size = m.size;
        key = new Tkey [size];
        val = new Tval [size];
        first_empty = m.first_empty;
        
        int i = 0;
        for (i=0;i<size;i++) {
            key[i] = m.key[i];
            val[i] = m.val[i];
        }
        cout << "Copy constructor\n";
    } 
    ~MyMap(){ delete [] key; delete [] val; cout << "Destructor\n";}
    int get_size() { return size;}
    int get_first_empty() { return first_empty;}    

    int find_ind(const Tkey k) {
        for(int i=0; i<first_empty; ++i)
            if (key[i] == k) return i;
        return -1;
    }
    void insert(const Tkey k, const Tval v) {
        if (first_empty >= 0 && first_empty < size) {
            int res = this->find_ind(k);
            if (res == -1) {        // Если такой ключ k свободен
                key[first_empty] = k;
                val[first_empty] = v;
                ++first_empty;
                cout << "Entry [" << k << "; " << v << "] was inserted\n"; 
            }
            else cerr << "[!] Insertion failed. Entry with key " << k << \
            " already exists \n";
        }
        else cerr << "[!] Insertion failed. Map is full \n";
    }

    void remove(const Tkey k) {
            int ind = this->find_ind(k);
            if (ind >= 0 && ind < first_empty) {
                
                for (int i=ind+1;i<first_empty;++i) {
                    key[i-1] = key[i];
                    val[i-1] = val[i];
                }
                key[first_empty-1] = "";
                val[first_empty-1] = "";
                first_empty--;

                cout << "\"" << k << "\"" << " entry was REMOVED \n";
            }
            else cout << "[!] Removing failed. \"" << k << \
            "\" key wasn't found\n"; 
    }
    
    void print() {
        cout << "Map: \n";
        cout << "----------------------------------\n";
        
        for(int i=0; i<first_empty; ++i)
            cout << key[i] << "\t\t" << val[i] << endl;

        cout << "----------------------------------\n";
    }
    
    void resize(int new_sz) 
    {
        Tkey *old_key = key;
        Tval *old_val = val;

        key = new Tkey [new_sz];
        val = new Tval [new_sz];
        first_empty = min(new_sz, first_empty);

        size = new_sz;

        for (int i=0;i<first_empty;i++) {
            key[i] = old_key[i];
            val[i] = old_val[i];
        }
        
        delete [] old_key; delete [] old_val;
        cout << "Map was resized to " << new_sz << " entries \n";
    }
    
    Tval& operator[] (const Tkey& k) {
        int i = find_ind(k);
        if (i == -1) {
            cout << "Entry with key " << k << "doesn't exist! \n";
            return val[i];  // exception checkout is needed
        }
        else return val[i];
    }
    
};

int main()
{
    try {
        MyMap<char*, double> constants;
        constants.insert("pi", 3.1415926);
        constants.insert("e", 2.7818281828);
    }
    catch (exception& e) {
        cout << "Exception: " << e.what() << endl;
    }
    
}

