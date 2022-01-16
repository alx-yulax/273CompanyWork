#include <iostream>
#include <vector>

class Employee {
protected:
    int id;
};

enum class TaskTypes {
    A,
    B,
    C
};

class Task {
    TaskTypes type;
};

class Worker : public Employee {
    Task* task;

};

class Manager : public Employee {
    std::vector<Worker *> team;
};

int main() {

    return 0;
}
