#ifndef QUESTION3_H
#define QUESTION3_H
#include <iostream>

class Question3
{
public:

    static Question3& getInstance()
    {
        static Question3 question3;
        return question3;
    }


    std::string getAllFibo(const int iUpperLimit);
private:
    Question3();
    int calFibo(const int i);
};

#endif // QUESTION3_H
