#ifndef QCALCULATOR_H
#define QCALCULATOR_H

#include <QWidget>
#include <QLineEdit>


class QCalculator : public QWidget
{
    Q_OBJECT

public:
    static QCalculator* NewInstance(QWidget *parent = 0);
    ~QCalculator();
private:
    bool construct();
    QCalculator(QWidget *parent = 0);
protected slots:
    void onButtonClicked();
private:
    QLineEdit textEdit;
    static const char* buttonText[20];
};

#endif // QCALCULATOR_H
