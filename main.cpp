#include <iostream>
#include <vector>
#include <assert.h>

enum class TaskTypes {
    A,
    B,
    C
};

class Employee {
    int id;
public:
    Employee(int inId) : id(inId) {
        assert(inId > 0);
    }

    int getId() {
        return id;
    }
};

class Task {
    TaskTypes type;
public:
    Task() {
        switch (std::rand() % 3) {
            case 0:
                type = TaskTypes::A;
                break;
            case 1:
                type = TaskTypes::B;
                break;
            case 2:
                type = TaskTypes::C;
                break;
        }
    }
};

class Worker : public Employee {
    Task *task;
public:
    Worker(int inId) : Employee(inId), task(nullptr) {

    }

    ~Worker() {
        if (task != nullptr) {
            delete task;
            task = nullptr;
        }
    }

    bool setTask(Task *inTask) {
        if (task == nullptr) {
            task = inTask;
            return true;
        } else {
            return false;
        }
    }
};

class Manager : public Employee {
    int workerHasTask;
    std::vector<Worker *> team;
public:
    Manager(int inId, int inWorkers) : Employee(inId), workerHasTask(0) {
        assert(inWorkers > 0);
        for (int i = 0; i < inWorkers; ++i) {
            team.push_back(new Worker(i + 1));
        }
    }

    ~Manager() {
        for (int i = 0; i < team.size(); ++i) {
            delete team[i];
            team[i] = nullptr;
        }
        team.clear();
    }

    int getNoBusy() {
        return team.size() - workerHasTask;
    }

    void setTasks(int inTasksCount) {
        for (int i = 0; i < inTasksCount; ++i) {
            Task *task = new Task();
            team[workerHasTask]->setTask(task);
            workerHasTask++;
        }

    }

};

int main() {
    std::vector<Manager *> managers;
    std::cout << "Input the number of managers in the company: ";
    int managersCount;
    std::cin >> managersCount;
    assert(managersCount > 0);
    for (int i = 0; i < managersCount; ++i) {
        std::cout << "Manager # " << i + 1 << ". Input the number of workers in his team: ";
        int workers;
        std::cin >> workers;
        assert(workers > 0);
        managers.push_back(new Manager(i + 1, workers));
    }

    while (true) {
        std::cout << "Input lead task: ";
        int leadTask;
        std::cin >> leadTask;
        int noBusy = 0;
        for (int i = 0; i < managersCount; ++i) {
            std::srand(leadTask + managers[i]->getId());
            if (managers[i]->getNoBusy() > 0) {
                int tasksCount = std::rand() % managers[i]->getNoBusy() + 1;
                std::cout << tasksCount << std::endl;
                managers[i]->setTasks(tasksCount);
            }

            std::cout << "Manager # " << managers[i]->getId() << " Workers are not busy: " << managers[i]->getNoBusy()
                      << std::endl;

            noBusy += managers[i]->getNoBusy();
        }
        if (noBusy == 0) break;
    }

    for (int i = 0; i < managers.size(); ++i) {
        delete managers[i];
        managers[i] = nullptr;
    }
    managers.clear();
    return 0;
}
