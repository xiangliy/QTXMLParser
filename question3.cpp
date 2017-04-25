#include "question3.h"
#include "qdebug.h"

Question3::Question3()
{

}

std::string Question3::getAllFibo(const int iUpperLimit)
{
    std::string strTotal;
    try
    {
        if(iUpperLimit < 0)
        {
            throw;
        }

        int iIndex = 0;

        while (true)
        {
            iIndex ++;
            int iFibo = calFibo(iIndex);

            if (iFibo < iUpperLimit)
            {
                 strTotal += std::to_string(iFibo);
                 strTotal += " ";
            }
            else
            {
                break;
            }
        }
    }
    catch (...)
    {
        qInfo() << "Exception in Third Question";
    }
    return strTotal;
}

/*
 * * Recursive calculate Fibonacci
 *
 *
 */
int Question3::calFibo(const int i)
{
    if (i == 1 || i == 2)
    {
        return 1;
    }
    else
    {
        return calFibo(i - 1) + calFibo(i - 2);
    }
}
