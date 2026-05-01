#include "database.h"

bool Database::connect() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={SQL Server}; SERVER=DESKTOP-A8IERN8; DATABASE=notesDB; Trusted_Connection=yes;");
    return db.open();
}

QList<Note> Database::getAllNotes() {
    QList<Note> notes;
    QSqlQuery query("SELECT id, title, content, created, updated FROM notes ORDER BY updated DESC");
    while (query.next()) {
        Note n;
        n.id = query.value(0).toInt();
        n.title = query.value(1).toString();
        n.content = query.value(2).toString();
        n.created = query.value(3).toString();
        n.updated = query.value(4).toString();
        notes.append(n);
    }
    return notes;
}

bool Database::addNote(const QString& title, const QString& content) {
    QSqlQuery query;
    query.prepare("INSERT INTO notes (title, content) VALUES (?, ?)");
    query.addBindValue(title);
    query.addBindValue(content);
    return query.exec();
}

bool Database::updateNote(int id, const QString& title, const QString& content) {
    QSqlQuery query;
    query.prepare("UPDATE notes SET title = ?, content = ?, updated = GETDATE() WHERE id = ?");
    query.addBindValue(title);
    query.addBindValue(content);
    query.addBindValue(id);
    return query.exec();
}

bool Database::deleteNote(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM notes WHERE id = ?");
    query.addBindValue(id);
    return query.exec();
}