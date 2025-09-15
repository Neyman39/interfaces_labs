#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

// Базовый класс для геометрических фигур
class Shape {
public:
    virtual void print() const = 0;
    virtual string getType() const = 0;
    virtual ~Shape() {} // Простой виртуальный деструктор
};

// Класс для точки
class Point : public Shape {
public:
    double x, y;
    
    Point(double x, double y) {
        this->x = x;
        this->y = y;
    }
    
    void print() const override {
        cout << "Point(" << x << ", " << y << ")";
    }
    
    string getType() const override {
        return "Point";
    }
};

// Класс для линии
class Line : public Shape {
public:
    Point start;
    Point end;
    
    Line(Point start, Point end) : start(start), end(end) {}
    
    void print() const override {
        cout << "Line(";
        start.print();
        cout << ", ";
        end.print();
        cout << ")";
    }
    
    string getType() const override {
        return "Line";
    }
};

// Класс для окружности
class Circle : public Shape {
public:
    Point center;
    double radius;
    
    Circle(Point center, double radius) : center(center), radius(radius) {}
    
    void print() const override {
        cout << "Circle(";
        center.print();
        cout << ", " << radius << ")";
    }
    
    string getType() const override {
        return "Circle";
    }
};

// Функция для парсинга точки
Point* parsePoint(string str) {
    regex point_regex(R"(Point\(([-+]?[0-9]*\.?[0-9]+),\s*([-+]?[0-9]*\.?[0-9]+)\))");
    smatch match;
    
    if (regex_match(str, match, point_regex)) {
        try {
            double x = stod(match[1]);
            double y = stod(match[2]);
            return new Point(x, y);
        } catch (...) {
            return nullptr;
        }
    }
    return nullptr;
}

// Функция для парсинга линии
Line* parseLine(string str) {
    regex line_regex(R"(Line\(Point\(([^)]+)\),\s*Point\(([^)]+)\)\))");
    smatch match;
    
    if (regex_match(str, match, line_regex)) {
        try {
            string point1_str = "Point(" + string(match[1]) + ")";
            string point2_str = "Point(" + string(match[2]) + ")";
            
            Point* point1 = parsePoint(point1_str);
            Point* point2 = parsePoint(point2_str);
            
            if (point1 && point2) {
                return new Line(*point1, *point2);
            }
            delete point1;
            delete point2;
        } catch (...) {
            return nullptr;
        }
    }
    return nullptr;
}

// Функция для парсинга окружности
Circle* parseCircle(string str) {
    regex circle_regex(R"(Circle\(Point\(([^)]+)\),\s*([-+]?[0-9]*\.?[0-9]+)\))");
    smatch match;
    
    if (regex_match(str, match, circle_regex)) {
        try {
            string center_str = "Point(" + string(match[1]) + ")";
            double radius = stod(match[2]);
            
            Point* center = parsePoint(center_str);
            
            if (center && radius > 0) {
                return new Circle(*center, radius);
            }
            delete center;
        } catch (...) {
            return nullptr;
        }
    }
    return nullptr;
}

// Функция для парсинга строки с фигурой
Shape* parseShape(string line) {
    // Пробуем распарсить как точку
    if (Point* point = parsePoint(line)) {
        return point;
    }
    
    // Пробуем распарсить как линию
    if (Line* line_obj = parseLine(line)) {
        return line_obj;
    }
    
    // Пробуем распарсить как окружность
    if (Circle* circle = parseCircle(line)) {
        return circle;
    }
    
    return nullptr;
}

// Функция для чтения файла
vector<Shape*> readFile(string filename) {
    vector<Shape*> shapes;
    ifstream file(filename);
    
    if (!file.is_open()) {
        cout << "Error: Cannot open file: " << filename << endl;
        return shapes;
    }
    
    string line;
    int line_number = 0;
    
    while (getline(file, line)) {
        line_number++;
        
        // Убираем лишние пробелы
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);
        
        // Пропускаем пустые строки
        if (line.empty()) {
            continue;
        }
        
        Shape* shape = parseShape(line);
        if (shape) {
            shapes.push_back(shape);
        } else {
            cout << "Warning: Invalid shape at line " << line_number << ": " << line << endl;
        }
    }
    
    file.close();
    return shapes;
}

// Функция для печати всех фигур
void printShapes(vector<Shape*> shapes) {
    for (Shape* shape : shapes) {
        shape->print();
        cout << endl;
    }
}

// Функция для подсчета количества фигур
void countShapes(vector<Shape*> shapes) {
    int points = 0, lines = 0, circles = 0;
    
    for (Shape* shape : shapes) {
        if (shape->getType() == "Point") points++;
        else if (shape->getType() == "Line") lines++;
        else if (shape->getType() == "Circle") circles++;
    }
    
    cout << "Total shapes: " << shapes.size() << endl;
    cout << "Points: " << points << endl;
    cout << "Lines: " << lines << endl;
    cout << "Circles: " << circles << endl;
}

// Функция для очистки памяти
void cleanup(vector<Shape*>& shapes) {
    for (Shape* shape : shapes) {
        delete shape;
    }
    shapes.clear();
}

// Функция для вывода справки
void printHelp() {
    cout << "Usage: program -f <filename> -o <operation>" << endl;
    cout << "Options:" << endl;
    cout << "  -f, --file <filename>   Input file with shapes" << endl;
    cout << "  -o, --oper <operation>  Operation: print or count" << endl;
    cout << "  -h, --help              Show this help message" << endl;
}

int main(int argc, char* argv[]) {
    string filename;
    string operation;
    
    // Обработка аргументов командной строки
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        
        if (arg == "-f" || arg == "--file") {
            if (i + 1 < argc) {
                filename = argv[++i];
            } else {
                cout << "Error: Missing filename after " << arg << endl;
                return 1;
            }
        } else if (arg == "-o" || arg == "--oper") {
            if (i + 1 < argc) {
                operation = argv[++i];
            } else {
                cout << "Error: Missing operation after " << arg << endl;
                return 1;
            }
        } else if (arg == "-h" || arg == "--help") {
            printHelp();
            return 0;
        } else {
            cout << "Error: Unknown argument " << arg << endl;
            printHelp();
            return 1;
        }
    }
    
    // Проверка обязательных аргументов
    if (filename.empty() || operation.empty()) {
        cout << "Error: Missing required arguments" << endl;
        printHelp();
        return 1;
    }
    
    // Проверка допустимых операций
    if (operation != "print" && operation != "count") {
        cout << "Error: Unknown operation '" << operation << "'. Use 'print' or 'count'" << endl;
        return 1;
    }
    
    // Чтение и парсинг файла
    vector<Shape*> shapes = readFile(filename);
    
    if (shapes.empty()) {
        cout << "No valid shapes found or file is empty" << endl;
        return 1;
    }
    
    // Выполнение операции
    if (operation == "print") {
        printShapes(shapes);
    } else if (operation == "count") {
        countShapes(shapes);
    }
    
    // Очистка памяти
    cleanup(shapes);
    
    return 0;
}