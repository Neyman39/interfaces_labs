#include <iostream>
#include <string>
#include <regex>
#include <iomanip>
#include <sstream>
#include <limits>
#include <windows.h>

using namespace std;

void clearKeyboardBuffer() {
    cin.clear(); 
    cin.ignore(10000, '\n'); 
};

struct Date {
    int dd;
    int mm;
    int yyyy;
};

struct Patient {
    string passport; // ss ss-nnnnnn
    string name; // any string
    Date birth_date; // yyyy-mm-dd
    string phone; // +X(XXX) XXX-XX-XX or X(XXX) XXX-XXXX
    double temperature; // XX.XX
};

bool isValidPassport(const string& passport) {
    regex pattern(R"(^\d{2} \d{2}-\d{6}$)");
    return regex_match(passport, pattern);
}

bool isValidDate(int day, int month, int year) {
    if (year < 1910 || year > 2025) return false;
    if (month < 1 || month > 12) return false;
    
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
        daysInMonth[1] = 29;
    }
    
    return day >= 1 && day <= daysInMonth[month - 1];
}

bool isValidPhone(const string& phone) {
    regex pattern1(R"(^\+7\(\d{3}\)\s\d{3}-\d{2}-\d{2}$)");
    regex pattern2(R"(^8\(\d{3}\)\s\d{3}-\d{4}$)");
    
    return regex_match(phone, pattern1) || regex_match(phone, pattern2);
}

string inputPassport() {
    string passport;
    while (true) {
        cout << "Введите номер паспорта (формат: 12 34-567890): ";
        getline(cin, passport);
        
        if (isValidPassport(passport)) {
            return passport;
        } else {
            cout << "Ошибка! Неверный формат паспорта. Пример: 12 34-567890\n";
        }
    }
}

string inputName() {
    string name;
    while (true) {
        cout << "Введите ФИО пациента: ";
        getline(cin, name);
        
        bool has_numbers = false;

        for (char n : name) {
            if (isdigit(n))
                has_numbers = true;
        }
            
        if (!name.empty() & !has_numbers) {
            return name;    
        } else if (has_numbers)
        {
            cout << "Ошибка! Имя не может содержать цифры.\n";
        } else {
            cout << "Ошибка! Имя не может быть пустым.\n";
        }
    }
}

Date inputBirthDate() {
    Date date;
    string input;
    
    while (true) {
        cout << "Введите дату рождения (формат: yyyy-mm-dd): ";
        getline(cin, input);
        
        regex datePattern(R"(^(\d{4})-(\d{2})-(\d{2})$)");
        smatch matches;
        
        if (regex_match(input, matches, datePattern)) {
            try {
                date.yyyy = stoi(matches[1].str());
                date.mm = stoi(matches[2].str());
                date.dd = stoi(matches[3].str());
                
                if (isValidDate(date.dd, date.mm, date.yyyy)) {
                    return date;
                } else {
                    cout << "Ошибка! Неверная дата.\n";
                }
            } catch (...) {
                cout << "Ошибка преобразования чисел!\n";
            }
        } else {
            cout << "Ошибка! Неверный формат даты. Пример: 1990-05-15\n";
        }
    }
}

string inputPhone() {
    string phone;
    while (true) {
        cout << "Введите телефон (формат: +7(123) 456-78-90 или 8(123) 456-7890): ";
        getline(cin, phone);
        
        if (isValidPhone(phone)) {
            return phone;
        } else {
            cout << "Ошибка! Неверный формат телефона.\n";
            cout << "Примеры: +7(123) 456-78-90 или 8(123) 456-7890\n";
        }
    }
}

double inputTemperature() {
    double temp;
    string input;
    
    while (true) {
        cout << "Введите температуру (формат: XX.XX, от 35.0 до 42.0): ";
        //getline(cin, input);
        cin >> temp;
        
        if (cin.fail()) {
            cout << "Неверный формат! \n";
            clearKeyboardBuffer();
        } else if (cin.peek() != '\n' && cin.peek() != EOF) {
            cout << "Неверный формат! Уберите лишние символы после числа. \n";
            clearKeyboardBuffer();
        } else if (temp >= 35.0 && temp <= 42.0) {
            return temp;
            clearKeyboardBuffer();
        } else {
            cout << "Ошибка! Температура должна быть от 35.0 до 42.0\n";
            clearKeyboardBuffer();
        }
        // bool hasLetters = false;
        // for (char c : input) {
        //     if (isalpha(c)) {
        //         hasLetters = true;
        //         break;
        //     }
        // }

        // if (hasLetters) {
        //     cout << "Неверный формат! Нельзя вводить буквы. \n";
        //     continue;
        // }

        // try {
        //     temp = stod(input);
        //     if (temp >= 35.0 && temp <= 42.0) {
        //         return temp;
        //     } else {
        //         cout << "Ошибка! Температура должна быть от 35.0 до 42.0\n";
        //     }
        // } catch (...) {
        //     cout << "Ошибка! Введите число в формате XX.XX\n";
        // }
    }
}

void printPatient(const Patient& patient) {
    // cout << "\n=== Информация о пациенте ===\n";
    // cout << "Паспорт: " << patient.passport << endl;
    // cout << "ФИО: " << patient.name << endl;
    // cout << "Дата рождения: " << setw(4) << setfill('0') << patient.birth_date.yyyy << "-"
    //      << setw(2) << setfill('0') << patient.birth_date.mm << "-"
    //      << setw(2) << setfill('0') << patient.birth_date.dd << endl;
    // cout << "Телефон: " << patient.phone << endl;
    cout << "Температура: " << fixed << setprecision(2) << patient.temperature << "°C" << endl;
    cout << "=============================\n";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    cout << "=== Программа ввода данных о пациенте ===\n";
    cout << "Пожалуйста, введите данные пациента:\n\n";
    
    Patient patient;
    
    // patient.passport = inputPassport();
    // patient.name = inputName();
    // patient.birth_date = inputBirthDate();
    // patient.phone = inputPhone();
    patient.temperature = inputTemperature();

    printPatient(patient);
    
    cout << "Данные успешно сохранены!\n";
    
    cout << "Нажмите Enter для выхода...";
    cin.clear();
    cin.sync(); 
    cin.get(); 

    return 0;
}