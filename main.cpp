#include "QCalculator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    int ret = -1;
    QApplication a(argc, argv);

    QCalculator* calc = QCalculator::NewInstance();
    if( calc != NULL )
    {
        calc->show();
        ret = a.exec();
    }

    return ret;
}
