#ifndef QCALCULATOR_H
#define QCALCULATOR_H

#include <QWidget>

class QCalculator : public QWidget
{
    Q_OBJECT

public:
    QCalculator(QWidget *parent = 0);
    ~QCalculator();
};

#endif // QCALCULATOR_H
