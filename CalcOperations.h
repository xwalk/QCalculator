#ifndef CALCOPERATIONS_H
#define CALCOPERATIONS_H

#include <QString>
#include <QQueue>
#include <QChar>

class CalcOperations
{
    typedef enum{
        ERR_NULL,
        ERR_NUMBER,
    }ErrEnum;
public:
    CalcOperations();
    void setOrigin(const QString& origin);
    QString result();
private:
    QQueue<QString> separateStr(const QString& origin);
    ErrEnum isValidOperation(const QQueue<QString>& str);

    bool isNumber(QChar ch);
    bool isOperation(QChar ch);
    bool isSign(QChar ch);
    bool iaBracket(QChar ch);
private:
    QString m_origin;
    QString m_result;

};

#endif // CALCOPERATIONS_H
