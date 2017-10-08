#include "CalcOperations.h"

CalcOperations::CalcOperations()
{
    m_origin = "0";
    m_result = "0";
}

void CalcOperations::setOrigin(const QString& origin)
{
    m_origin = origin;
}

QString CalcOperations::result()
{
    return m_result;
}

QQueue<QString> CalcOperations::separateStr(const QString& origin)
{
    QQueue<QString> ret;
    QString numString = "";
    int len = origin.count();
    for( int i=0;i<len;i++)
    {
        QChar ch = origin.at(i);
        if(isNumber(ch))
        {
            numString += ch;
        }
        else
        {

        }
    }


    return ret;
}


CalcOperations::ErrEnum CalcOperations::isValidOperation(const QQueue<QString>& str)
{
    ErrEnum ret = ERR_NULL;

    return ret;
}

bool CalcOperations::isNumber(QChar ch)
{
    bool ret = false;

    if( ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' ||
            ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9' || ch == '.')
    {
        ret = true;
    }

    return ret;
}

bool CalcOperations::isOperation(QChar ch)
{
    bool ret = false;

    if( ch == '+' || ch == '-' || ch == '*' || ch == '/')
    {
        ret  = true;
    }

    return ret;
}

bool isSign(QChar ch)
{
    bool ret = false;

    if( ch == '+' || ch == '-' )
    {
        ret = true;
    }

    return ret;
}

bool CalcOperations::iaBracket(QChar ch)
{
    bool ret = false;

    if( ch == '(' || ch == ')' )
    {
        ret = true;
    }

    return ret;
}
