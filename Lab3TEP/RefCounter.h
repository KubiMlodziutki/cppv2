#ifndef REFCOUNTER_H
#define REFCOUNTER_H

class RefCounter {
public:
    RefCounter() : count(0) {}
    int add() { return ++count; }
    int dec() { return --count; }
    int get() const { return count; }

private:
    int count;
};

#endif
