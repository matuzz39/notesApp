#include "notesApp.h"
#include "database.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMessageBox>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    if (!Database::connect()) {
        QMessageBox::critical(nullptr, "ошибка", "не удалось подключиться к БД");
        return 1;
    }

    notesApp w;
    w.show();
    return a.exec();
}
