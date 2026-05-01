#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_notesApp.h"
#include "database.h"

class notesApp : public QMainWindow
{
    Q_OBJECT

public:
    notesApp(QWidget *parent = nullptr);
    ~notesApp();

private slots:
    void onAddButton();
    void onDeleteButton();
    void onNoteClicked(QListWidgetItem *item);
    void onBackButton();
    void onSaveButton();

private:
    Ui::notesAppClass *ui;
    QList<Note> m_notes;
    int m_currentNoteIndex;
    void loadNotes();
};
