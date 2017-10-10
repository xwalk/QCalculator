#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_

#include <QWidget>
#include <QLineEdit>
#include "CalcOperations.h"


class CalculatorUI : public QWidget
{
    Q_OBJECT

public:
    static CalculatorUI* NewInstance(QWidget *parent = 0);
    ~CalculatorUI();
    void setCalaDelegate(CalcOperations* calc);
private:
    bool construct();
    CalculatorUI(QWidget *parent = 0);
    void handleText(QString text);
protected slots:
    void onButtonClicked();
protected:
    bool eventFilter(QObject *ob, QEvent *e);
private:
    QLineEdit textEdit;
    CalcOperations* m_calc;
    bool nextCalc;
    static const char* buttonText[20];

};

#endif // CalculatorUI_H
