#include "notesApp.h"
#include "styles.h"
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QInputDialog>

notesApp::notesApp(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::notesAppClass)
{
    ui->setupUi(this);
    setStyleSheet(appStyleSheet());
    setWindowTitle("Заметки");
    m_currentNoteIndex = -1;
    connect(ui->addButton, &QPushButton::clicked, this, &notesApp::onAddButton);
    connect(ui->deleteButton, &QPushButton::clicked, this, &notesApp::onDeleteButton);
    connect(ui->notesList, &QListWidget::itemDoubleClicked, this, &notesApp::onNoteClicked);
    connect(ui->backButton, &QPushButton::clicked, this, &notesApp::onBackButton);
    connect(ui->saveButton, &QPushButton::clicked, this, &notesApp::onSaveButton);
    connect(ui->noteTitle, &QLineEdit::textChanged, this, [this]() {ui->noteTitle->setStyleSheet(""); });
    ui->stackedWidget->setCurrentIndex(0);
    loadNotes();
}

notesApp::~notesApp()
{
    delete ui;
}

void notesApp::loadNotes()
{
    ui->notesList->blockSignals(true);
    ui->notesList->clear();
    m_notes = Database::getAllNotes();
    for (const Note& note : m_notes) {
        ui->notesList->addItem(note.title);
    }
    ui->notesList->setCurrentRow(-1);
    ui->notesList->blockSignals(false);
}

void notesApp::onAddButton()
{
    bool ok;
    QString title = QInputDialog::getText(this, "Новая заметка", "Заголовок:", QLineEdit::Normal, "", &ok);
    if (!ok || title.trimmed().isEmpty()) return;

    QString content = QInputDialog::getMultiLineText(this, "Новая заметка", "Текст заметки:", "", &ok);
    if (!ok) return;

    if (Database::addNote(title.trimmed(), content)) {
        loadNotes();
    } else {
        QMessageBox::warning(this, "ошибка", "не удалось добавить заметку");
    }
}

void notesApp::onDeleteButton()
{
    int row = ui->notesList->currentRow();
    if (row < 0) {
        QMessageBox::information(this, "Внимание", "Выберите заметку для удаления");
        return;
    }

    Note note = m_notes[row];
    auto reply = QMessageBox::question(this, "Удаление", "Удалить заметку \"" + note.title + "\"?", QMessageBox::Yes | QMessageBox::No);
    if (reply != QMessageBox::Yes) return;

    if (Database::deleteNote(note.id)) {
        loadNotes();
    } else {
        QMessageBox::warning(this, "ошибка", "не удалось удалить заметку");
    }
}

void notesApp::onNoteClicked(QListWidgetItem* item)
{
    int row = ui->notesList->row(item);
    if (row < 0) return;
    m_currentNoteIndex = row;
    Note note = m_notes[row];
    ui->noteTitle->setStyleSheet("");
    ui->noteTitle->setText(note.title);
    ui->noteContent->setText(note.content);
    ui->stackedWidget->setCurrentIndex(1);
}

void notesApp::onBackButton()
{
    ui->stackedWidget->setCurrentIndex(0);
    loadNotes();
}

void notesApp::onSaveButton()
{
    if (m_currentNoteIndex < 0) return;

    QString title = ui->noteTitle->text().trimmed();
    QString content = ui->noteContent->toPlainText();

    if (title.isEmpty()) {
        ui->noteTitle->setStyleSheet("border: 1px solid red; border-radius: 5px;");
        return;
    }

    ui->noteTitle->setStyleSheet("");

    Note note = m_notes[m_currentNoteIndex];
    if (Database::updateNote(note.id, title, content)) {
        loadNotes();
        ui->stackedWidget->setCurrentIndex(0);
    } else {
        QMessageBox::warning(this, "ошибка", "не удалось сохранить заметку");
    }
}
