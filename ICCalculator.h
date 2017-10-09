#ifndef ICCALCULATOR_H
#define ICCALCULATOR_H

#include <QWidget>
#include <CalcOperations.h>
#include <CalculatorUI.h>

class ICCalculator : public QWidget
{
    Q_OBJECT
public:
    static ICCalculator* NewInstance(QWidget *parent = NULL);
private:
    bool construct();
    explicit ICCalculator(QWidget *parent = NULL);
private:
    CalculatorUI* calcUI;
    CalcOperations calcOp;
};

#endif // ICCALCULATOR_H
