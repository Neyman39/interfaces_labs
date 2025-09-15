// Pract_1_RI.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
    SetConsoleOutputCP(CP_UTF8); // Устанавливаем UTF-8 для вывода
    SetConsoleCP(CP_UTF8);
    //
    // system("chcp 65001 > nul");
    cout << "Что за бред то ==++==\n" << endl;
}

//#include <iostream>
//#include <string>
//#include <regex>
//#include <iomanip>
//#include <sstream>
//#include <limits>
//#include <windows.h>
//
//using namespace std;
//
//struct Date {
//    int dd;
//    int mm;
//    int yyyy;
//};
//
//struct Patient {
//    string passport; // ss ss-nnnnnn
//    string name; // any string
//    Date birth_date; // yyyy-mm-dd
//    string phone; // +X(XXX) XXX-XX-XX or X(XXX) XXX-XXXX
//    double temperature; // XX.XX
//};
//
//// Функция для проверки корректности паспорта
//bool isValidPassport(const string& passport) {
//    regex pattern(R"(^\d{2} \d{2}-\d{6}$)");
//    return regex_match(passport, pattern);
//}
//
//// Функция для проверки корректности даты
//bool isValidDate(int day, int month, int year) {
//    if (year < 1900 || year > 2100) return false;
//    if (month < 1 || month > 12) return false;
//
//    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
//
//    // Проверка на високосный год
//    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
//        daysInMonth[1] = 29;
//    }
//
//    return day >= 1 && day <= daysInMonth[month - 1];
//}
//
//// Функция для проверки корректности телефона
//bool isValidPhone(const string& phone) {
//    // Проверяем оба формата: +X(XXX)XXX-XX-XX и X(XXX)XXX-XXXX
//    regex pattern1(R"(^\+\d\(\d{3}\)\s\d{3}-\d{2}-\d{2}$)");
//    regex pattern2(R"(^\d\(\d{3}\)\s\d{3}-\d{4}$)");
//
//    return regex_match(phone, pattern1) || regex_match(phone, pattern2);
//}
//
//// Функция для проверки корректности температуры
//bool isValidTemperature(double temp) {
//    return temp >= 35.0 && temp <= 42.0;
//}
//
//// Функция для ввода паспорта
//string inputPassport() {
//    string passport;
//    while (true) {
//        cout << "Введите номер паспорта (формат: 12 34-567890): ";
//        getline(cin, passport);
//
//        if (isValidPassport(passport)) {
//            return passport;
//        }
//        else {
//            cout << "Ошибка! Неверный формат паспорта. Пример: 12 34-567890\n";
//        }
//    }
//}
//
//// Функция для ввода имени
//string inputName() {
//    string name;
//    while (true) {
//        cout << "Введите ФИО пациента: ";
//        getline(cin, name);
//
//        if (!name.empty()) {
//            return name;
//        }
//        else {
//            cout << "Ошибка! Имя не может быть пустым.\n";
//        }
//    }
//}
//
//// Функция для ввода даты рождения
//Date inputBirthDate() {
//    Date date;
//    string input;
//
//    while (true) {
//        cout << "Введите дату рождения (формат: yyyy-mm-dd): ";
//        getline(cin, input);
//
//        // Проверяем формат с помощью регулярного выражения
//        regex datePattern(R"(^(\d{4})-(\d{2})-(\d{2})$)");
//        smatch matches;
//
//        if (regex_match(input, matches, datePattern)) {
//            try {
//                date.yyyy = stoi(matches[1].str());
//                date.mm = stoi(matches[2].str());
//                date.dd = stoi(matches[3].str());
//
//                if (isValidDate(date.dd, date.mm, date.yyyy)) {
//                    return date;
//                }
//                else {
//                    cout << "Ошибка! Неверная дата.\n";
//                }
//            }
//            catch (...) {
//                cout << "Ошибка преобразования чисел!\n";
//            }
//        }
//        else {
//            cout << "Ошибка! Неверный формат даты. Пример: 1990-05-15\n";
//        }
//    }
//}
//
//// Функция для ввода телефона
//string inputPhone() {
//    string phone;
//    while (true) {
//        cout << "Введите телефон (формат: +7(123)456-78-90 или 7(123)456-7890): ";
//        getline(cin, phone);
//
//        if (isValidPhone(phone)) {
//            return phone;
//        }
//        else {
//            cout << "Ошибка! Неверный формат телефона.\n";
//            cout << "Примеры: +7(123)456-78-90 или 7(123)456-7890\n";
//        }
//    }
//}
//
//// Функция для ввода температуры
//double inputTemperature() {
//    double temp;
//    string input;
//
//    while (true) {
//        cout << "Введите температуру (формат: XX.XX, от 35.0 до 42.0): ";
//        getline(cin, input);
//
//        try {
//            temp = stod(input);
//            if (isValidTemperature(temp)) {
//                return temp;
//            }
//            else {
//                cout << "Ошибка! Температура должна быть от 35.0 до 42.0\n";
//            }
//        }
//        catch (...) {
//            cout << "Ошибка! Введите число в формате XX.XX\n";
//        }
//    }
//}
//
//// Функция для вывода информации о пациенте
//void printPatient(const Patient& patient) {
//    cout << "\n=== Информация о пациенте ===\n";
//    cout << "Паспорт: " << patient.passport << endl;
//    cout << "ФИО: " << patient.name << endl;
//    cout << "Дата рождения: " << setw(4) << setfill('0') << patient.birth_date.yyyy << "-"
//        << setw(2) << setfill('0') << patient.birth_date.mm << "-"
//        << setw(2) << setfill('0') << patient.birth_date.dd << endl;
//    cout << "Телефон: " << patient.phone << endl;
//    cout << "Температура: " << fixed << setprecision(2) << patient.temperature << "°C" << endl;
//    cout << "=============================\n";
//}
//
//int main() {
//    SetConsoleOutputCP(CP_UTF8); // Устанавливаем UTF-8 для вывода
//    SetConsoleCP(CP_UTF8);
//
//    system("chcp 65001 > nul");
//
//    cout << "=== Программа ввода данных о пациенте ===\n";
//    cout << "Пожалуйста, введите данные пациента:\n\n";
//
//    Patient patient;
//
//    // Ввод всех данных
//    patient.passport = inputPassport();
//    patient.name = inputName();
//    patient.birth_date = inputBirthDate();
//    patient.phone = inputPhone();
//    patient.temperature = inputTemperature();
//
//    // Вывод результатов
//    printPatient(patient);
//
//    cout << "Данные успешно сохранены!\n";
//
//    return 0;
//}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
