#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <memory>
#include <algorithm>

using namespace std;

// Базовый класс для геометрических фигур
class Shape {
public:
    virtual ~Shape() = default;
    virtual void print() const = 0;
    virtual string type() const = 0;
};

// Класс для точки
class Point : public Shape {
private:
    double x, y;
public:
    Point(double x, double y) : x(x), y(y) {}
    
    void print() const override {
        cout << "Point(" << x << ", " << y << ")";
    }
    
    string type() const override {
        return "Point";
    }
    
    double getX() const { return x; }
    double getY() const { return y; }
};

// Класс для линии
class Line : public Shape {
private:
    shared_ptr<Point> start, end;
public:
    Line(shared_ptr<Point> start, shared_ptr<Point> end) 
        : start(start), end(end) {}
    
    void print() const override {
        cout << "Line(";
        start->print();
        cout << ", ";
        end->print();
        cout << ")";
    }
    
    string type() const override {
        return "Line";
    }
};

// Класс для окружности
class Circle : public Shape {
private:
    shared_ptr<Point> center;
    double radius;
public:
    Circle(shared_ptr<Point> center, double radius) 
        : center(center), radius(radius) {}
    
    void print() const override {
        cout << "Circle(";
        center->print();
        cout << ", " << radius << ")";
    }
    
    string type() const override {
        return "Circle";
    }
};

// Функция для парсинга точки
shared_ptr<Point> parsePoint(const string& str) {
    regex point_regex(R"(Point\(([-+]?[0-9]*\.?[0-9]+),\s*([-+]?[0-9]*\.?[0-9]+)\))");
    smatch match;
    
    if (regex_match(str, match, point_regex)) {
        try {
            double x = stod(match[1]);
            double y = stod(match[2]);
            return make_shared<Point>(x, y);
        } catch (...) {
            return nullptr;
        }
    }
    return nullptr;
}

// Функция для парсинга линии
shared_ptr<Line> parseLine(const string& str) {
    regex line_regex(R"(Line\(Point\(([^)]+)\),\s*Point\(([^)]+)\)\))");
    smatch match;
    
    if (regex_match(str, match, line_regex)) {
        try {
            string point1_str = "Point(" + string(match[1]) + ")";
            string point2_str = "Point(" + string(match[2]) + ")";
            
            auto point1 = parsePoint(point1_str);
            auto point2 = parsePoint(point2_str);
            
            if (point1 && point2) {
                return make_shared<Line>(point1, point2);
            }
        } catch (...) {
            return nullptr;
        }
    }
    return nullptr;
}

// Функция для парсинга окружности
shared_ptr<Circle> parseCircle(const string& str) {
    regex circle_regex(R"(Circle\(Point\(([^)]+)\),\s*([-+]?[0-9]*\.?[0-9]+)\))");
    smatch match;
    
    if (regex_match(str, match, circle_regex)) {
        try {
            string center_str = "Point(" + string(match[1]) + ")";
            double radius = stod(match[2]);
            
            auto center = parsePoint(center_str);
            
            if (center && radius > 0) {
                return make_shared<Circle>(center, radius);
            }
        } catch (...) {
            return nullptr;
        }
    }
    return nullptr;
}

// Функция для парсинга строки с фигурой
shared_ptr<Shape> parseShape(const string& line) {
    // Пробуем распарсить как точку
    if (auto point = parsePoint(line)) {
        return point;
    }
    
    // Пробуем распарсить как линию
    if (auto line_obj = parseLine(line)) {
        return line_obj;
    }
    
    // Пробуем распарсить как окружность
    if (auto circle = parseCircle(line)) {
        return circle;
    }
    
    return nullptr;
}

// Функция для чтения файла
vector<shared_ptr<Shape>> readFile(const string& filename) {
    vector<shared_ptr<Shape>> shapes;
    ifstream file(filename);
    
    if (!file.is_open()) {
        throw runtime_error("Cannot open file: " + filename);
    }
    
    string line;
    int line_number = 0;
    
    while (getline(file, line)) {
        line_number++;
        
        // Убираем лишние пробелы в начале и конце
        line = regex_replace(line, regex("^\\s+|\\s+$"), "");
        
        // Пропускаем пустые строки
        if (line.empty()) {
            continue;
        }
        
        if (auto shape = parseShape(line)) {
            shapes.push_back(shape);
        } else {
            cerr << "Warning: Invalid shape format at line " << line_number 
                 << ": " << line << endl;
        }
    }
    
    file.close();
    return shapes;
}

// Функция для печати всех фигур
void printShapes(const vector<shared_ptr<Shape>>& shapes) {
    for (const auto& shape : shapes) {
        shape->print();
        cout << endl;
    }
}

// Функция для подсчета количества фигур
void countShapes(const vector<shared_ptr<Shape>>& shapes) {
    int points = 0, lines = 0, circles = 0;
    
    for (const auto& shape : shapes) {
        if (shape->type() == "Point") points++;
        else if (shape->type() == "Line") lines++;
        else if (shape->type() == "Circle") circles++;
    }
    
    cout << "Total shapes: " << shapes.size() << endl;
    cout << "Points: " << points << endl;
    cout << "Lines: " << lines << endl;
    cout << "Circles: " << circles << endl;
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
                cerr << "Error: Missing filename after " << arg << endl;
                return 1;
            }
        } else if (arg == "-o" || arg == "--oper") {
            if (i + 1 < argc) {
                operation = argv[++i];
            } else {
                cerr << "Error: Missing operation after " << arg << endl;
                return 1;
            }
        } else if (arg == "-h" || arg == "--help") {
            printHelp();
            return 0;
        } else {
            cerr << "Error: Unknown argument " << arg << endl;
            printHelp();
            return 1;
        }
    }
    
    // Проверка обязательных аргументов
    if (filename.empty() || operation.empty()) {
        cerr << "Error: Missing required arguments" << endl;
        printHelp();
        return 1;
    }
    
    // Проверка допустимых операций
    if (operation != "print" && operation != "count") {
        cerr << "Error: Unknown operation '" << operation 
             << "'. Use 'print' or 'count'" << endl;
        return 1;
    }
    
    try {
        // Чтение и парсинг файла
        auto shapes = readFile(filename);
        
        // Выполнение операции
        if (operation == "print") {
            printShapes(shapes);
        } else if (operation == "count") {
            countShapes(shapes);
        }
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}