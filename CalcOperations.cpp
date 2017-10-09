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
        QQueue<QString> postExp = toPostfix(exp);
        qDebug() << postExp;
        double r = calcPostfix(postExp,&errNum);
        if( errNum == ERR_NULL )
        {
            m_result = QString().setNum(r);
            return;
        }
    }
    m_result = "ERROR" + QString::number(errNum);
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

    QStack<QString> tmpStack;
    QString popStr;
    QString tmpStr;
    int len = str.length();
    for( int i=0; i<len; i++)
    {
        qDebug() << tmpStack;
        tmpStr = str[i];
        if( isOperand(tmpStr) )
        {
            ret.enqueue(tmpStr);
        }
        else
        {
            if( tmpStr == "(" )
            {
                tmpStack.push(tmpStr);
            }
            else if( tmpStr == ")" )
            {
                popStr = tmpStack.pop();
                while( popStr != "(" )
                {
                    ret.enqueue(popStr);
                    popStr = tmpStack.pop();
                }
            }
            else
            {
                while( !tmpStack.isEmpty() && (opPriority(tmpStr) <= opPriority(tmpStack.top())) )
                {
                    ret.enqueue(tmpStack.pop());
                }
                tmpStack.push(tmpStr);
            }
        }
    }
    while( !tmpStack.isEmpty() )
    {
        ret.enqueue(tmpStack.pop());
    }

    return ret;
}

double CalcOperations::calcPostfix(const QQueue<QString>& str,ErrEnum* num)
{
    *num = ERR_NULL;
    double ret = 0;
    const double zo = 0.00000001;

    QStack<QString> tmpStack;
    int len = str.length();
    QString tmpStr;
    for( int i=0; i<len; i++)
    {
        tmpStr = str[i];
        if( isOperand( tmpStr ))
        {
            tmpStack.push( tmpStr );
        }
        else
        {
            double leftOper = tmpStack.pop().toDouble();
            double rightOper = tmpStack.pop().toDouble();
            if( tmpStr == "+" )
            {
                tmpStack.push( QString().setNum(leftOper + rightOper) );
            }
            else if( tmpStr == "-" )
            {
                tmpStack.push( QString().setNum(leftOper - rightOper) );
            }
            else if( tmpStr == "*" )
            {
                tmpStack.push( QString().setNum(leftOper * rightOper) );
            }
            else if( tmpStr == "/" )
            {
                if( !(rightOper < zo && rightOper > -zo) )
                {
                    tmpStack.push( QString().setNum(leftOper / rightOper) );
                }
                else
                {
                    *num = ERR_DEV_ZERO;
                    break;
                }
            }
        }
    }
    ret = tmpStack.pop().toDouble();

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

int CalcOperations::opPriority(const QString& ch)
{
    int ret = 0;

    if( isOperation(ch) )
    {
        ret = 2;
        if( isSign(ch) )
        {
            ret = 1;
        }
    }
    else
    {
        ret = 0;
    }

    return ret;
}

bool CalcOperations::isOperand(const QString& ch)
{
    bool ret = true;

    ch.toDouble(&ret);

    return ret;
}
