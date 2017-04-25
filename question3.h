#ifndef QUESTION3_H
#define QUESTION3_H
#include <iostream>

class Question3
{
public:
    Question3();

    std::string getAllFibo(const int iUpperLimit);
private:
    int calFibo(const int i);
};

#endif // QUESTION3_H
