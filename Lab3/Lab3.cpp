

#include <iostream>
#include <fstream>
#include <random>
#include <cmath>
#include <windows.h>

using namespace std;

const double PI = 3.14;

// =====================================================================
// ЗАДАЧА 1.8: КЛАС КРУГ
// =====================================================================
class Circle {
    double r; // радіус круга
    unsigned int color; // колір у вигляді числа
public:
    // 1. Конструктор за замовчуванням
    Circle() : r(1.0), color(0) {}

    // 2. Конструктор лише з радіусом
    Circle(double ri) : r(ri), color(0) {}

    // 3. Конструктор лише з кольором
    Circle(int ic) : r(1.0) { if (ic >= 0) color = ic; else color = 0; }

    // 4. Конструктор з усіма параметрами
    Circle(double r, int c) {
        this->r = r;
        if (c >= 0) color = c; else color = 0;
    }

    // Гетери та Сетери
    double getR() const { return r; }

    void setR(double r) {
        if (r < 0 || r > 1.e+100) {
            cout << " Error set r \n";
            return;
        }
        this->r = r;
    }

    double getColor() const { return color; }

    void setColor(int c) {
        if (c < 0 || c > 10000) {
            cout << " Error set color \n";
            return;
        }
        this->color = c;
    }

    // Математичні функції
    double S() {
        return PI * r * r; // Площа
    }

    double L() {
        return 2 * PI * r; // Довжина кола
    }

    // Функція виведення
    void printInfo() {
        cout << "\n r= " << r << " color = " << color;
        cout << "  S= " << S() << " L = " << L() << endl;
    }
};

// =====================================================================
// ПІДМЕНЮ ВВОДУ ДАНИХ ДЛЯ 1.8
// =====================================================================
void Task_1_8_Menu() {
    int subChoice;
    double inputR;
    int inputColor;

    do {
        cout << "\n>>> ЗАДАЧА 1.8: КРУГ (МЕНЮ ВВОДУ) <<<\n";
        cout << "1. Ввести з клавіатури\n";
        cout << "2. Згенерувати випадкові числа\n";
        cout << "3. Зчитати з файлу\n";
        cout << "0. Повернутися до Головного меню\n";
        cout << "Ваш вибір: ";

        cin >> subChoice;

        if (cin.fail()) {
            cin.clear(); cin.ignore(32767, '\n');
            subChoice = -1;
        }

        switch (subChoice) {
        case 1: { // КЛАВІАТУРА
            cout << "Введіть радіус (дійсне число): ";
            cin >> inputR;
            cout << "Введіть код кольору (ціле число): ";
            cin >> inputColor;

            if (cin.fail()) {
                cin.clear(); cin.ignore(32767, '\n');
                cout << "Помилка вводу! Спробуйте ще раз.\n";
            }
            else {
                Circle c1(inputR, inputColor);
                c1.printInfo();
            }
            break;
        }
        case 2: { // ВИПАДКОВІ ЧИСЛА
            random_device rd;
            mt19937 gen(rd());
            uniform_real_distribution<double> radDist(0.1, 50.0);
            uniform_int_distribution<int> colorDist(0, 9999);

            inputR = radDist(gen);
            inputColor = colorDist(gen);

            cout << "Згенеровані дані: Радіус = " << inputR << ", Колір = " << inputColor << "\n";
            Circle c2(inputR, inputColor);
            c2.printInfo();
            break;
        }
        case 3: { // ФАЙЛ
            string filename = "circle_data.txt";

            ofstream outFile(filename, ios::app);
            if (outFile.is_open()) {
                if (outFile.tellp() == 0) {
                    outFile << "1 0\n";
                }
                outFile.close();
            }

            ifstream inFile(filename);
            if (inFile.is_open()) {
                inFile >> inputR >> inputColor;
                inFile.close();

                cout << "Дані зчитано з файлу '" << filename << "':\n";
                Circle c3(inputR, inputColor);
                c3.printInfo();
            }
            else {
                cout << "Помилка відкриття файлу!\n";
            }
            break;
        }
        case 0:
            cout << "Повернення...\n";
            break;
        default:
            cout << "Невірний вибір. Введіть цифру від 0 до 3.\n";
        }
    } while (subChoice != 0);
}

// =====================================================================
// ЗАДАЧА 2.8: КЛАС КОМПЛЕКСНЕ ЧИСЛО
// =====================================================================
class MyComplex {
private:
    float re;
    float im;
    int state; // 0 - ОК, 1 - помилка вказівника (NULL), 2 - ділення на 0

public:
    static int objectCount;

    // Конструктор без параметрів
    MyComplex() : re(0.0f), im(0.0f), state(0) { objectCount++; }

    // Конструктор з одним параметром
    MyComplex(float val) : re(val), im(val), state(0) { objectCount++; }

    // Конструктор з параметром вказівником
    MyComplex(float* arr) {
        objectCount++;
        if (arr == nullptr) {
            state = 1;
            re = 0.0f;
            im = 0.0f;
        }
        else {
            state = 0;
            re = arr[0];
            im = arr[1];
        }
    }


    // Деструктор
    ~MyComplex() {
        objectCount--;
        cout << " [~] Деструктор викликано. Стан об'єкта: " << state << " (Залишилось: " << objectCount << ")\n";
    }

    // Сетери
    void setValues(float r = 0.0f, float i = 0.0f) {
        re = r;
        im = i;
    }

    // Гетери
    float getRe() const { return re; }
    float getIm() const { return im; }
    int getState() const { return state; }

    // Конструктор копій
    MyComplex(const MyComplex& other) {
        re = other.re;
        im = other.im;
        state = other.state;
        objectCount++;
    }

    // Операція присвоєння
    MyComplex& operator=(const MyComplex& other) {
        if (this != &other) {
            re = other.re;
            im = other.im;
            state = other.state;
        }
        return *this;
    }

    MyComplex Add(const MyComplex& b) const {
        MyComplex res;
        res.setValues(re + b.re, im + b.im);
        return res;
    }

    MyComplex Sub(const MyComplex& b) const {
        MyComplex res;
        res.setValues(re - b.re, im - b.im);
        return res;
    }

    MyComplex Mul(const MyComplex& b) const {
        MyComplex res;
        res.setValues(re * b.re - im * b.im, re * b.im + im * b.re);
        return res;
    }

    MyComplex Div(const MyComplex& b) const {
        MyComplex res;
        float denominator = b.re * b.re + b.im * b.im;
        if (denominator == 0.0f) {
            res.state = 2;
            res.setValues(0.0f, 0.0f);
        }
        else {
            res.setValues((re * b.re + im * b.im) / denominator, (im * b.re - re * b.im) / denominator);
        }
        return res;
    }

    MyComplex DivShort(short val) {
        MyComplex res;
        if (val == 0) {
            this->state = 2;
            res.state = 2;
            res.setValues(re, im);
        }
        else {
            res.setValues(re / val, im / val);
        }
        return res;
    }

    float Norm() const {
        return std::sqrt(re * re + im * im);
    }

    bool isEqual(const MyComplex& b) const {
        return (re == b.re && im == b.im);
    }

    bool isGreater(const MyComplex& b) const {
        return this->Norm() > b.Norm();
    }

    bool isLess(const MyComplex& b) const {
        return this->Norm() < b.Norm();
    }

    void Print() const {
        cout << re << (im >= 0 ? " + " : " - ") << std::abs(im) << "i [Стан: " << state << "]\n";
    }
};

int MyComplex::objectCount = 0;

// =====================================================================
// ТЕСТУВАННЯ ДЛЯ 2.8
// =====================================================================
void Task_2_8_Interactive() {
    int subChoice;

    // Створюємо два "порожніх" об'єкти (вони поки що 0 + 0i)
    MyComplex num1;
    MyComplex num2;

    float r, i;

    do {
        cout << "\n>>> РОБОТА З КОМПЛЕКСНИМИ ЧИСЛАМИ <<<\n";
        cout << "Поточна кількість об'єктів у пам'яті: " << MyComplex::objectCount << "\n";
        cout << " [1] Перше число:  "; num1.Print();
        cout << " [2] Друге число:  "; num2.Print();
        cout << "--------------------------------------\n";
        cout << "1. Ввести ПЕРШЕ число з клавіатури\n";
        cout << "2. Ввести ДРУГЕ число з клавіатури\n";
        cout << "3. Додавання (+)\n";
        cout << "4. Віднімання (-)\n";
        cout << "5. Множення (*)\n";
        cout << "6. Ділення (/)\n";
        cout << "7. Порівняння та Норма (модуль)\n";
        cout << "8. Ділення першого числа на ціле (short)\n";
        cout << "0. Вийти\n";
        cout << "Ваш вибір: ";

        cin >> subChoice;
        if (cin.fail()) { cin.clear(); cin.ignore(32767, '\n'); subChoice = -1; }

        switch (subChoice) {
        case 1: {
            cout << "\n--- Введення першого числа ---\n";
            cout << "Введіть дійсну частину (re): "; cin >> r;
            cout << "Введіть уявну частину (im): "; cin >> i;
            num1.setValues(r, i);
            break;
        }
        case 2: {
            cout << "\n--- Введення другого числа ---\n";
            cout << "Введіть дійсну частину (re): "; cin >> r;
            cout << "Введіть уявну частину (im): "; cin >> i;
            num2.setValues(r, i);
            break;
        }
        case 3: {
            cout << "\n--- Результат додавання ---\n";
            MyComplex result = num1.Add(num2);
            cout << "Сума: "; result.Print();
            break;
        }
        case 4: {
            cout << "\n--- Результат віднімання ---\n";
            MyComplex result = num1.Sub(num2);
            cout << "Різниця: "; result.Print();
            break;
        }
        case 5: {
            cout << "\n--- Результат множення ---\n";
            MyComplex result = num1.Mul(num2);
            cout << "Добуток: "; result.Print();
            break;
        }
        case 6: {
            cout << "\n--- Результат ділення ---\n";
            MyComplex result = num1.Div(num2);
            cout << "Частка: "; result.Print();
            if (result.getState() == 2) cout << "[Увага] Відбулося ділення на нуль!\n";
            break;
        }
        case 7: {
            cout << "\n--- Порівняння та Норма ---\n";
            cout << "Норма 1-го числа: " << num1.Norm() << "\n";
            cout << "Норма 2-го числа: " << num2.Norm() << "\n";

            if (num1.isEqual(num2)) cout << "Числа рівні (за координатами).\n";
            else if (num1.isGreater(num2)) cout << "Перше число БІЛЬШЕ за друге (за нормою).\n";
            else if (num1.isLess(num2)) cout << "Перше число МЕНШЕ за друге (за нормою).\n";
            break;
        }
        case 8: {
            cout << "\n--- Ділення на short ---\n";
            short divVal;
            cout << "Введіть ціле число (short) для ділення ПЕРШОГО числа: ";
            cin >> divVal;

            MyComplex result = num1.DivShort(divVal);
            cout << "Результат: "; result.Print();
            if (result.getState() == 2) cout << "[Увага] Відбулося ділення на нуль! Стан змінено.\n";
            break;
        }
        case 0:
            cout << "Повернення до головного меню...\n";
            break;
        default:
            cout << "Невірний вибір!\n";
        }
    } while (subChoice != 0);
}

// =====================================================================
// ГОЛОВНЕ МЕНЮ
// =====================================================================
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int mainChoice;

    do {
        cout << "\n================ ГОЛОВНЕ МЕНЮ =================\n";
        cout << "1. Задача 1.8 (Клас 'Круг')\n";
        cout << "2. Задача 2.8 (Клас 'Комплексне число')\n"; 
        cout << "0. Вихід з програми\n";
        cout << "===============================================\n";
        cout << "Ваш вибір: ";

        cin >> mainChoice;

        if (cin.fail()) {
            cin.clear(); cin.ignore(32767, '\n');
            mainChoice = -1;
        }

        switch (mainChoice) {
        case 1:
            Task_1_8_Menu(); 
            break;
        case 2:
            Task_2_8_Interactive(); 
            break;
        case 0:
            cout << "Роботу завершено. До побачення!\n";
            break;
        default:
            cout << "Невірний вибір. Спробуйте ще раз.\n";
        }
    } while (mainChoice != 0);

    return 0;
}