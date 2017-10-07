#include "QCalculator.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QStackedLayout>
#include <QPalette>
#include <QPushButton>
#include <QFont>
#include <QDebug>

const char* QCalculator::buttonText[] = {"7","8","9","+","(",
                                           "4","5","6","-",")",
                                           "1","2","3","X","<-",
                                           "0",".","=","÷","C"};

QCalculator::QCalculator(QWidget *parent) : QWidget(parent,Qt::WindowCloseButtonHint)
{
    setWindowTitle(tr("calculator"));
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

    QVBoxLayout* mainColumn = new QVBoxLayout();
    if( mainColumn != NULL )
    {
        mainColumn->setSpacing(10);
        QGridLayout* buttonGrid = new QGridLayout();
        if( buttonGrid != NULL )
        {
            buttonGrid->setSpacing(5);
            for( int i=0;i<20;i++ )
            {
                QPushButton* button = new QPushButton();
                if( button!= NULL )
                {
                    button->setText(buttonText[i]);
                    button->setFixedSize(40,40);
                    connect(button,SIGNAL(clicked()),this,SLOT(onButtonClicked()));
                    buttonGrid->addWidget(button,i/5,i%5);
                }
                else
                {
                    ret = false;
                    break;
                }
            }
            if( ret )
            {
                textEdit.insert("0");
                textEdit.setFixedSize(20+40*5,40);
                QFont font = textEdit.font();
                font.setPixelSize(18);
                textEdit.setFont(font);
                textEdit.setReadOnly(true);
                textEdit.setAlignment(Qt::AlignRight);
                mainColumn->addWidget(&textEdit);
                mainColumn->addLayout(buttonGrid);

                setLayout(mainColumn);
                setFixedSize(sizeHint());
            }
        }

    }
    return ret;
}

void QCalculator::onButtonClicked()
{
    QPushButton* send = dynamic_cast<QPushButton*>(sender());
    qDebug()<< send->text();
}

