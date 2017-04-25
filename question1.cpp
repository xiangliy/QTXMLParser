#include "question1.h"
#include "qdebug.h"

Question1::Question1()
{

}

int Question1::getSum(const int iUpperLimit)
{
    int iTotal = 0;
    try{
        if (iUpperLimit < 0)
        {
            throw;
        }

        int iPrev = 1;
        int iCur = 1;
        int iTempPrev = 0;

        while (true)
        {
            // save previous number
            iTempPrev = iPrev;
            iPrev = iCur;
            iCur = iTempPrev + iCur;

            if (iCur >= iUpperLimit)
            {
                break;
            }

            // if the number is even. add.
            if (iCur % 2 == 0)
            {
                iTotal += iCur;
            }
        }
    }
    catch (...)
    {
        qInfo() << "Exception in First Question";
    }

    return iTotal;
}
