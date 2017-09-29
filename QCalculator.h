#ifndef QCALCULATOR_H
#define QCALCULATOR_H

#include <QWidget>
#include <QGridLayout>

class QCalculator : public QWidget
{
    Q_OBJECT

public:
    static QCalculator* NewInstance(QWidget *parent = 0);
    ~QCalculator();
private:
    bool construct();
    QCalculator(QWidget *parent = 0);

private:
    QGridLayout mainGrid;
};

#endif // QCALCULATOR_H
