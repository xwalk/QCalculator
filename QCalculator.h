#ifndef QCALCULATOR_H
#define QCALCULATOR_H

#include <QWidget>

class QCalculator : public QWidget
{
    Q_OBJECT

public:
    static QCalculator* NewInstance(QWidget *parent = 0);
    ~QCalculator();
private:
    bool construct();
    QCalculator(QWidget *parent = 0);
};

#endif // QCALCULATOR_H
