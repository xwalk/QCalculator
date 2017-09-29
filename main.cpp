#include "QCalculator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCalculator* calc = QCalculator::NewInstance();
    calc->show();

    return a.exec();
}
