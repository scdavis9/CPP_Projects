#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
uint64_t djb2(string);

class Person {
    public:
    string Id;
    string firstName;
    string lastName;
    string email;
    string phone;
    string city;
    string state;
    string postalCode;
    Person() {

    }
    string get(string key) {
        if(key == "Id") {
            return Id;
        }
        else if(key == "FirstName") {
            return firstName;
        }
        else if(key == "LastName") {
            return lastName;
        }
        else if(key == "Email") {
            return email;
        }
        else if(key == "Phone") {
            return phone;
        }
        else if(key == "City") {
            return city;
        }
        else if(key == "State") {
            return state;
        }
        else {
            return postalCode;
        }
    }
};
class Slot {
    public:
        bool occupied;
        vector<Person> People;
        string key;

        Slot() {
            occupied = false;
            key = "\0";
        }
};
class HashTable {
   public: 
    Slot **table;
    int capacity;
    string key;
    HashTable(int capacity, string key);

    void insert(Person person);
    std::vector<Person> search(string key);
    void print();
};

HashTable::HashTable(int capacity, string key) {
    this->capacity = capacity; // refers to class capacity
    this->key = key;
    table = new Slot*[capacity];
    for(int i = 0; i < capacity; i++) {
        table[i] = new Slot;
    }
}

void HashTable::insert(Person person) {
    int base = djb2(person.get(key)) % capacity;
    int i = 0;
    
    while(table[(base + i * i) % capacity]->occupied == true && table[(base + i * i) % capacity]->key != person.get(key)) {
            i++;
    }

    Slot* slot = table[(base + i * i) % capacity];
    slot->occupied = true;
    slot->People.push_back(person);
    slot->key = person.get(key);
}

std::vector<Person> HashTable::search(string key) {
    std::vector<Person> results;

    int base = djb2(key) % capacity;
    int i = 0;
    while(table[(base + i * i) % capacity]->occupied == true && table[(base + i * i) % capacity]->key != key) {
            i++;
    }
    return table[(base + i * i) % capacity]->People;
          //  for(int j = 0; j < addPeople.size(); j++) {
            //    results.push_back(addPeople[j]);
          //  }
   // return results;
}

void HashTable::print() {
    for(int i = 0; i < capacity; i++) {
        if(table[i]->occupied) {
            cout << i << ": " << table[i]->key << " " << "(" << table[i]->People.size() << ")," << endl;
        }
    }
}

uint64_t djb2(string str) {
    const char *ptr = str.c_str();
    uint64_t hash = 5381;
    int c;
    while ((c = *ptr++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

void getVal(istream &is, string &str) {
    char ch;
    string line;

    is >> ch;
    getline(is, line);

    str = ch + line;
}

bool isValidKey(const string &key) {
    string validKeys[8] = { "Id", "FirstName", "LastName", "Email", "Phone", "City", "State", "PostalCode" };
    for (int i = 0; i < 8; i++) {
        if (key == validKeys[i]) {
            return true;
        }
    }
    return false;
}

int main(int argc, char **argv) {
    if (argc != 4) {
        cout << "Usage: ./a.out filename.txt table_size key" << endl;
        return 1;
    }

    string filename = argv[1];
    int tableSize = stoi(argv[2]);
    string key = argv[3];

    ifstream file(filename);
    if (!file) {
        cout << "Unable to open " << filename << endl;
        return 2;
    }

    if (!isValidKey(key)) {
        cout << "Invalid key: " << key << endl;
        return 3;
    }
    HashTable hash(tableSize, key);
   
    // This is an example of how to retreive the tokens from the input file
    // You will need to modify this to fit your needs to build the hash table
    int row = 0;
    int colId;
    int colFN;
    int colLN;
    int colEmail;
    int colPhone;
    int colCity;
    int colState;
    int colpostCode;
    
    string line, token;
    while (getline(file, line)) {
        istringstream iss(line);
        int col = 0;
        if(row == 0) {
            while (getline(iss, token, '\t')) {
                if(token == "Id") {
                    colId = col;
                }
                if(token == "FirstName") {
                    colFN = col;
                }
                if(token == "LastName") {
                    colLN= col;
                }
                if(token == "Email") {
                    colEmail = col;
                }
                if(token == "Phone") {
                    colPhone = col;
                }
                if(token == "City") {
                    colCity = col;
                }
                if(token == "State") {
                    colState = col;
                }
                if(token == "PostalCode") {
                    colpostCode = col;
                }
                col++;
            }
            
            
        }
        else {
            Person p;
            while (getline(iss, token, '\t')) {
                if(col == colId) {
                    p.Id = token;  //saves that data into our class
                }
                if(col == colFN) {
                    p.firstName = token;  //saves that data into our class
                }
                if(col == colLN) {
                    p.lastName = token;  //saves that data into our class
                }
                if(col == colEmail) {
                    p.email = token;  //saves that data into our class
                }
                if(col == colPhone) {
                    p.phone = token;  //saves that data into our class
                }
                if(col == colCity) {
                    p.city = token;  //saves that data into our class
                }
                if(col == colState) {
                    p.state = token;  //saves that data into our class
                }
                if(col == colpostCode) {
                    p.postalCode = token;  //saves that data into our class
                }
                col++;
            }
            hash.insert(p);
        }
        row++;
        
    }

    cout << "Commands:" << endl << "\tprint" << endl << "\tlookup <key>" << endl << "\tquit" << endl;
    string cmd, val;
    while (1) {
        cout << endl << "Enter a command:" << endl;
        cin >> cmd;
        if (cmd == "quit") {
            break;
        }
        else if (cmd == "print") {
            hash.print();
        }
        else if (cmd == "lookup") {
            getVal(cin, val);
            vector<Person> searchResults = hash.search(val);
            if(searchResults.size() == 0) {
                cout << "No results" << endl;
            }
            else {
                cout << "Id,FirstName,LastName,Email,Phone,City,State,PostalCode" << endl;
                for (int i = 0; i < searchResults.size(); i++) {
                    cout << searchResults[i].Id << "," << searchResults[i].firstName << "," << searchResults[i].lastName << "," << searchResults[i].email << "," << searchResults[i].phone << "," << searchResults[i].city << "," << searchResults[i].state << "," << searchResults[i].postalCode << endl;
                }
            }
    
        }
        else {
            getline(cin, val);
            cout << "Invalid command" << endl;
        }
    }

    return 0;
}
