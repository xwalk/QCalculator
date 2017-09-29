#include "QCalculator.h"

QCalculator::QCalculator(QWidget *parent) : QWidget(parent)
{

}

QCalculator::~QCalculator()
{

}

QCalculator* QCalculator::NewInstance(QWidget *parent)
{
    QCalculator* ret = new QCalculator(parent);

    if( ret == NULL || !ret->construct() )
    {
        delete ret;
        ret = NULL;
    }
    return ret;
}

bool QCalculator::construct()
{
    bool ret = true;

    return ret;
}
