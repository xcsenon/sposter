#include <iostream>
#include <vector>
#include <algorithm>

// Observer
class Observer {
public:
    virtual void update(const std::string& message) const = 0;
};

// ConcreteObserver
class ConcreteObserver : public Observer {
private:
    std::string name;

public:
    ConcreteObserver(const std::string& name) : name(name) {}

    void update(const std::string& message) const override {
        std::cout << name << " received message: " << message << std::endl;
    }
};

// Subject
class Subject {
private:
    std::vector<Observer*> observers;
    std::string state;

public:
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notifyObservers() const {
        for (const auto& observer : observers) {
            observer->update(state);
        }
    }

    void setState(const std::string& newState) {
        state = newState;
        notifyObservers();
    }
};

int main() {
    ConcreteObserver observerA("Observer A");
    ConcreteObserver observerB("Observer B");

    Subject subject;
    subject.addObserver(&observerA);
    subject.addObserver(&observerB);

    subject.setState("New State");

    subject.removeObserver(&observerA);

    subject.setState("Another State");

    return 0;
}
