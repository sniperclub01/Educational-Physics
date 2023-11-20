#include "educationalapp.h"
#include "levelselector.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //EducationalApp w;
    LevelSelector w;
    w.show();
    return a.exec();
}
