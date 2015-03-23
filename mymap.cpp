//TODO в operator[] добавить, если нет ключа, то добавить (ключ,деф.значение) 
//DONE
//TODO в insert передавать (ключ,значение) по pair из <utility>
//DONE
#include <iostream>
#include <string>
#include <locale>
#include <algorithm>
#include <exception>
#include <utility>
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
    
    void insert(const pair<Tkey, Tval> q) {
        if (first_empty >= 0 && first_empty < size) {
            int res = this->find_ind(q.first);
            if (res == -1) {        // Если такой ключ k свободен
                key[first_empty] = q.first;
                val[first_empty] = q.second;
                ++first_empty;
                cout << "Entry [" << q.first << "; " << q.second << "] was inserted\n"; 
            }
            else cerr << "[!] Insertion failed. Entry with key " << q.first << \
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
                key[first_empty-1] = Tkey();
                val[first_empty-1] = Tval();
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
            cout << "Entry with key " << k << " doesn't exist! \n";
            
            pair<Tkey,Tval> p = make_pair(k, Tval());

            if (first_empty < size) insert(p);
            else {
                resize(size + 10);
                insert(p);
            }
            
            i = find_ind(k);
            return val[i];  // exception checkout is NOT needed ANYMORE
        }
        else return val[i];
    }
    
};

int main()
{
    try {
        MyMap<string, double> constants(3);
        pair<string, double> p("pi", 3.1415926);
        constants.insert(p);
        p = make_pair("e", 2.7818281828);
        constants.insert(p);
        constants.insert(p);
        p = make_pair("g", 9.81);
        constants.insert(p);
/*        constants.insert("pi", 3.1415926);
        constants.insert("e", 2.7818281828);
        constants.insert("e", 2.7818281828);    //explicit error generation
        constants.insert("g", 9.81);*/
        cout << constants["pi"] << endl;
        constants.print();
        constants.remove("pi");
        cout << constants["pi"] << endl;

        constants.resize(10);
        constants.print();
        
        MyMap<int, string> nums(3);
        pair<int, string> q(1, "one");
        nums.insert(q);
        nums.print();
        nums.remove(1);
        nums.print();
        nums[1];
        nums.print();
        
        MyMap<int, double> chart(1);
        pair<int, double> r(1, 2.34);
        chart.insert(r);
        chart[123];
        chart.print();
    }
    catch (exception& e) {
        cout << "Exception: " << e.what() << endl;
    }
    
}

