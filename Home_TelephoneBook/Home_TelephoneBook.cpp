#include <iostream>
#include <string>
#include<Windows.h>
using namespace std;

class Contact {
private:
    char* fullname = nullptr;
    string homePhone;
    string workPhone;
    string mobilePhone;
    string information;

public:
    
    Contact(const char* fullname = "", const string& homePhone = "", const string& workPhone = "", const string& mobilePhone = "", const string& information = "")
        : homePhone(homePhone), workPhone(workPhone), mobilePhone(mobilePhone), information(information)
    {
        copyStr(this->fullname, fullname);
    }

    Contact(const Contact& other)
        : homePhone(other.homePhone), workPhone(other.workPhone), mobilePhone(other.mobilePhone), information(other.information)
    {
        copyStr(this->fullname, other.fullname);
    }

    Contact& operator=(const Contact& other) {
        if (this == &other) {
            return *this; 
        }

        copyStr(this->fullname, other.fullname);  
        this->homePhone = other.homePhone;        
        this->workPhone = other.workPhone;
        this->mobilePhone = other.mobilePhone;
        this->information = other.information;

        return *this;
    }


    ~Contact() {
        
        delete[] fullname;
    }

    inline const char* getFullname() const { return fullname; }
    inline const string& getHomePhone() const { return homePhone; }
    inline const string& getWorkPhone() const { return workPhone; }
    inline const string& getMobilePhone() const { return mobilePhone; }
    inline const string& getInformation() const { return information; }

    
    void setFullname(const char* fullname) {
        if (isValid(fullname))
            copyStr(this->fullname, fullname);
        else
            copyStr(this->fullname, "None Name");
    }

    inline void setHomePhone(const string& homePhone) { this->homePhone = homePhone; }
    inline void setWorkPhone(const string& workPhone) { this->workPhone = workPhone; }
    inline void setMobilePhone(const string& mobilePhone) { this->mobilePhone = mobilePhone; }
    inline void setInformation(const string& information) { this->information = information; }

    
    inline bool searchByName(const char* name) const {
        return strcmp(fullname, name) == 0;
    }

    inline void print() const {
        cout << "\t Fullname       :: " << this->fullname << endl;
        cout << "\t Home Phone     :: " << this->homePhone << endl;
        cout << "\t Work Phone     :: " << this->workPhone << endl;
        cout << "\t Mobile Phone   :: " << this->mobilePhone << endl;
        cout << "\t Additional Info:: " << this->information << endl;
        cout << endl;
    }
private:
    inline bool isValid(const char* source) {
        return source != nullptr && source[0] != '\0';
    }
    void copyStr(char*& dest, const char* source) {
        if (dest != nullptr) {
            delete[] dest;
        }
        if (source != nullptr) {
            size_t size = strlen(source) + 1;
            dest = new char[size];
            strcpy_s(dest, size, source);
        }
        else {
            dest = nullptr;
        }
    }

    
};

class PhoneBook {
private:
    Contact* contacts = nullptr;
    size_t size = 0;
    size_t capacity = 10;

public:
    
    PhoneBook() {
        contacts = new Contact[capacity];
    }

    ~PhoneBook() {
        delete[] contacts;
    }

    void addContact(const char* fullname, const string& homePhone, const string& workPhone, const string& mobilePhone, const string& information) {
        if (size >= capacity) {
            capacity *= 2;
            Contact* tmp = new Contact[capacity];

            for (size_t i = 0; i < size; i++) {
                tmp[i] = contacts[i];  
            }

            delete[] contacts;  
            contacts = tmp;     
        }

        contacts[size++] = Contact(fullname, homePhone, workPhone, mobilePhone, information);  
    }


    
    void deleteContact(const char* fullname) {
        for (size_t i = 0; i < size; ++i) {
            if (contacts[i].searchByName(fullname)) {
                for (size_t j = i; j < size - 1; ++j) {
                    contacts[j] = contacts[j + 1];
                }
                --size;
                cout << "Абонент видалений." << endl;
                return;
            }
        }
        cout << "Абонент не знайдений." << endl;
    }

    
    void searchContact(const char* fullname) const {
        for (size_t i = 0; i < size; ++i) {
            if (contacts[i].searchByName(fullname)) {
                contacts[i].print(); 
                return;
            }
        }
        cout << "Абонент не знайдений." << endl;
    }

   
    void showAllContacts() const {
        if (size == 0) {
            cout << "Телефонна книга порожня." << endl;
        }
        else {
            for (size_t i = 0; i < size; ++i) {
                contacts[i].print(); 
                cout << "---------------------------" << endl;
            }
        }
    }
};


void createNewContact(PhoneBook& phoneBook) {
    string fullname, homePhone, workPhone, mobilePhone, information;
    cout << "Введіть ПІБ: ";
    getline(cin, fullname);
    cout << "Введіть домашній телефон: ";
    getline(cin, homePhone);
    cout << "Введіть робочий телефон: ";
    getline(cin, workPhone);
    cout << "Введіть мобільний телефон: ";
    getline(cin, mobilePhone);
    cout << "Введіть додаткову інформацію: ";
    getline(cin, information);

    phoneBook.addContact(fullname.c_str(), homePhone, workPhone, mobilePhone, information);
    cout << "Контакт додано!" << endl;
}


void menu(PhoneBook& phoneBook) {
    int choice;
    do {
        cout << "\nТелефонна книга - меню:\n";
        cout << "1. Додати новий контакт\n";
        cout << "2. Показати всі контакти\n";
        cout << "3. Пошук контакту за ПІБ\n";
        cout << "4. Видалити контакт\n";
        cout << "5. Вийти\n";
        cout << "Ваш вибір: ";
        cin >> choice;
        cin.ignore();  

        switch (choice) {
        case 1:
            createNewContact(phoneBook);
            break;
        case 2:
            phoneBook.showAllContacts();
            break;
        case 3: {
            string searchName;
            cout << "Введіть ПІБ для пошуку: ";
            getline(cin, searchName);
            phoneBook.searchContact(searchName.c_str());
            break;
        }
        case 4: {
            string delName;
            cout << "Введіть ПІБ для видалення: ";
            getline(cin, delName);
            phoneBook.deleteContact(delName.c_str());
            break;
        }
        case 5:
            cout << "Вихід з програми." << endl;
            break;
        default:
            cout << "Невірний вибір, спробуйте ще раз." << endl;
        }
    } while (choice != 5);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    PhoneBook phoneBook;
    menu(phoneBook);

    return 0;
}
