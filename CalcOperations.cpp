#include "CalcOperations.h"
#include <QStack>
#include <QDebug>

CalcOperations::CalcOperations()
{
    m_origin = "0";
    m_result = "0";
}

void CalcOperations::setOrigin(const QString& origin)
{
    m_origin = origin;
    QQueue<QString> exp = separateStr(m_origin);
    qDebug() << exp;
    ErrEnum errNum = isValidOperation(exp);
    if( errNum == ERR_NULL )
    {
        m_result = "0";
    }
    else
    {
        m_result = "ERROR" + QString::number(errNum);
    }
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
            if( numString != "")
            {
                ret.enqueue(numString);
                numString.clear();
            }
            if(isSign(ch) && (ret.isEmpty() || ret.last() == "(" || isOperation(ret.last())))
            {
                numString += ch;
            }
            else
            {
                ret.enqueue(ch);
            }
        }
    }
    if(numString != "")
    {
        ret.enqueue(numString);
    }
    return ret;
}


CalcOperations::ErrEnum CalcOperations::isValidOperation(const QQueue<QString>& str)
{
    ErrEnum ret = ERR_NULL;

    int leftBracket = 0;
    int len = str.length();
    for( int i=0; i<len; i++ )
    {
        if( isOperation(str[i]) )
        {
            if( i==0 || str[i-1] == "(" || isOperation(str[i-1]) )
            {
                ret = ERR_MOREOP;
                break;
            }
        }
        else
        {
            if( str[i] == "(" )
            {
                leftBracket++;
            }
            else if( str[i] == ")" )
            {
                leftBracket--;
                if( leftBracket < 0 )
                {
                    ret = ERR_LESS_LEFTBRACKET;
                    break;
                }
            }
        }
    }
    if( ret == ERR_NULL && leftBracket > 0 )
    {
        ret = ERR_LESS_RIGHTBRACKET;
    }
    return ret;
}

QQueue<QString> CalcOperations::toPostfix(const QQueue<QString>& str)
{
    QQueue<QString> ret;



    return ret;
}

bool CalcOperations::isNumber(const QString& ch)
{
    bool ret = false;

    if( ch == "0" || ch == "1" || ch == "2" || ch == "3" || ch == "4" ||
            ch == "5" || ch == "6" || ch == "7" || ch == "8" || ch == "9" || ch == ".")
    {
        ret = true;
    }

    return ret;
}

bool CalcOperations::isOperation(const QString& ch)
{
    bool ret = false;

    if( ch == "+" || ch == "-" || ch == "*" || ch == "/" )
    {
        ret  = true;
    }

    return ret;
}

bool CalcOperations::isSign(const QString& ch)
{
    bool ret = false;

    if( ch == "+" || ch == "-" )
    {
        ret = true;
    }

    return ret;
}

bool CalcOperations::isBracket(const QString& ch)
{
    bool ret = false;

    if( ch == "(" || ch == ")" )
    {
        ret = true;
    }

    return ret;
}
