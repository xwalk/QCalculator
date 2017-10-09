#ifndef CALCOPERATIONS_H
#define CALCOPERATIONS_H

#include <QString>
#include <QQueue>
#include <QChar>

class CalcOperations
{
    typedef enum{
        ERR_NULL = 0,
        ERR_MOREOP,
        ERR_LESS_LEFTBRACKET,
        ERR_LESS_RIGHTBRACKET,
        ERR_DEV_ZERO
    }ErrEnum;
public:
    CalcOperations();
    void setOrigin(const QString& origin);
    QString result();
private:
    QQueue<QString> separateStr(const QString& origin);
    ErrEnum isValidOperation(const QQueue<QString>& str);
    QQueue<QString> toPostfix(const QQueue<QString>& str);
    double calcPostfix(const QQueue<QString>& str,ErrEnum* num);

    bool isNumber(const QString& ch);
    bool isOperation(const QString& ch);
    bool isSign(const QString& ch);
    bool isBracket(const QString& ch);
    int  opPriority(const QString& ch);
    bool isOperand(const QString& ch);
private:
    QString m_origin;
    QString m_result;

};

#endif // CALCOPERATIONS_H
