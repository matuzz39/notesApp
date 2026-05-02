# Менеджер заметок
Десктопное приложение для управления заметками.
## Стек
- C++ - язык разработки;
- Qt 6.11.0 - фреймворк для графического интерфейса;
- MS SQL Server - СУБД;
- Visual Studio 2022 - среда разработки.
## Функционал
- Создание, редактирование, удаление заметки;
- Просмотр списка заметок;
- Просмотр содержимого выбранной заметки.
## Настройка базы данных
Откройте SQL Server Management Studio и выполните следующий скрипт:
```
CREATE DATABASE NotesDB
GO

USE NotesDB
GO

CREATE TABLE notes (
	id INT IDENTITY(1,1) PRIMARY KEY,
	title NVARCHAR(255) NOT NULL,
	content NVARCHAR(MAX),
	created DATETIME DEFAULT GETDATE(),
	updated DATETIME DEFAULT GETDATE()
)
GO
```
Это создаст базу данных и таблицу в ней.
## Настройка подключения к базе данных
В файле `database.cpp` в функции `connect()` замените имя сервера на свое:
```
SERVER=ВАШ-СЕРВЕР;
```
Имя сервера можно найти в SQL Server Management Studio при подключении к серверу в поле "Server name".
## Запуск
1. Установить MS SQL Server и SQL Server Management Studio (SSMS);
2. Установить Visual Studio 2022;
3. Установить Qt 6.x, при установке выбрать компонент MSVC 2022 64-bit;
4. В Visual Studio 2022 установить плагин LEGACY Qt Visual Studio Tools;
5. Создайте БД и таблицу по скрипту выше;
6. Настройте строку подключения в `database.cpp`;
7. Откройте `notesApp.sln` в Visual Studio 2022 и запустите.
