#include <QtGui/QApplication>
#include "dialog.h"
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);
    Dialog w;
    w.show();

    return a.exec();
}
