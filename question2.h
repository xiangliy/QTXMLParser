#ifndef QUESTION2_H
#define QUESTION2_H
#include <QtMath>

class Question2
{
public:
    Question2();

    const static inline double getArea(const double dInputR)
    {
        if (dInputR < 0)
        {
            return -1;
        }

        return M_PI * dInputR * dInputR;
    }
};

#endif // QUESTION2_H
