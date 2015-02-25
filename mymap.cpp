#include <iostream>
#include <string>
#include <locale>
#include <algorithm>
using namespace std;

class MyMap {
private:
    string *key; // начало массива ключей
    string *val; // начало массива значений
    int size; // размер словаря
    int first_empty; // индекс ближайшей неинициализированной пары
public:
    MyMap(int sz = 32) {
        size = sz; 
        key = new string [size];
        val = new string [size];
        first_empty = 0;
        cout << "Constructor\n";
    }
    MyMap(const MyMap &m) { 
        size = m.size;
        key = new string [size];
        val = new string [size];
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
    string find(const string k) {
        for(int i=0; i<first_empty; ++i)
            if (key[i] == k) return val[i];
        return "";
    }
    int find_ind(const string k) {
        for(int i=0; i<first_empty; ++i)
            if (key[i] == k) return i;
        return -1;
    }
    void insert(const string k, const string v) {
        if (first_empty >= 0 && first_empty < size) {
            string res = this->find(k);
            if (res.empty()) {
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

    void remove(const string k) {
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
        string *old_key = key;
        string *old_val = val;

        key = new string [new_sz];
        val = new string [new_sz];
        first_empty = min(new_sz, first_empty);

        size = new_sz;

        for (int i=0;i<first_empty;i++) {
            key[i] = old_key[i];
            val[i] = old_val[i];
        }
        
        delete [] old_key; delete [] old_val;
        cout << "Map was resized to " << new_sz << " entries \n";
    }
    
};

int main()
{
    char ans;
    string in_key = "", in_val = "", res = "", input = "";
    int sz;
    
    cout << "Enter size of map: ";
    cin >> sz;
    MyMap a(sz), b(a);
    do {
            cout << "x - E(x)it\n";
            cout << "i - (I)nsert mode\n";
            cout << "r - (R)emove mode\n";
            cout << "s - (S)earch mode\n";
            cout << "p - (P)rint map\n";
            cout << "z - Resi(z)e map\n";
            cin >> ans;
            ans = tolower(ans);
            
            switch (ans) {
                case 'x':
                    
                    break;
                case 'i':
                    cout << "Enter new KEY and VALUE to INSERT \
                    in map or \"exit\" : \n";
                    in_key = "", in_val = "", res = "";
                
                    do {
                        cin >> in_key;
                        if (in_key == "exit") break;
                         cin >> in_val;
                        a.insert(in_key, in_val);
                    } while (in_key != "exit");
                
                    break;
                case 'r':
                    cout << "Enter the KEY to REMOVE in map or \"exit\" : \n";
                    input = ""; res = "";
        
                    do {
                        cin >> input;
                        if (input == "exit") break;
                        a.remove(input);
                    } while (input != "exit");
        
                    break;
                case 's':
                    cout << "Enter the KEY to SEARCH in map or \"exit\" : \n";
                    input = ""; res = "";
                    
                    do {
                        cin >> input;
                        if (input == "exit") break;
                        res = a.find(input);
                        if (res.empty()) cout << "\"" << input \
                        << "\" key wasn't found\n";
                        else cout << input << "; " << res << endl;
                    } while (input != "exit");
                    
                    break;
                case 'p':
                    a.print();
                    break;
                case 'z':
                    cout << "Current size: " << a.get_size() << " ";
                    cout << "Entries inserted: " << a.get_first_empty() \
                    << endl;
                    
                    int new_sz = a.get_size();
                    cout << "Enter NEW size: ";
                    cin >> new_sz;
                    
                    a.resize(new_sz);
                    break;
            }
                    
    } while(ans != 'x');
    
    
}

