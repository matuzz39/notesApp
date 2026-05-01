#pragma once
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QList>

struct Note {
    int id;
    QString title;
    QString content;
    QString created;
    QString updated;
};

class Database {
public:
    static bool connect();
    static QList<Note> getAllNotes();
    static bool addNote(const QString& title, const QString& content);
    static bool updateNote(int id, const QString& title, const QString& content);
    static bool deleteNote(int id);
};
