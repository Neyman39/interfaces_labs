#include <iostream>
#include <limits>
#include <iomanip>

using namespace std;

void clearKeyboardBuffer() {
    cin.clear(); 
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    
    double dollars;
    cout << "\n \n";

    while (true)
    {
        cout << "Введите сумму в долларах: ";
        cin >> dollars;

        if (cin.fail()) {
            cout << "Неверный формат! \n";
            clearKeyboardBuffer();
        } else if (dollars <= 0) {
            cout << "Сумма не может быть отрицательной или равна нулю! \n";
        } else {
            clearKeyboardBuffer();
            break;
        }
    }

    const double exchange_rate = 83.5;
    double rubles = dollars * exchange_rate;

    cout << "Курс конвертации: 1usd = 83.5rub" <<endl;
    cout << dollars << " долларов = " << rubles << " рублей" << endl;
    
    return 0;

}