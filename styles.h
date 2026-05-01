#pragma once
#include <QString>

inline QString appStyleSheet() {
    return R"(
        QMainWindow, QWidget {
            background-color: #2C1F1F;
        }
        QListWidget {
            background-color: #3D2B2B;
            color: #F0E6D3;
            border-radius: 8px;
            padding: 4px;
            font-size: 14px;
        }
        QListWidget::item {
            padding: 10px;
            border-radius: 6px;
        }
        QListWidget::item:selected {
            background-color: #E07A8F;
            color: #2C1F1F;
            outline: none;
        }
        QListWidget:focus {
            outline: none;
        }
        QListWidget::item:hover {
            background-color: #4F3535;
        }
        QTextEdit, QLineEdit {
            background-color: #3D2B2B;
            color: #F0E6D3;
            border-radius: 8px;
            padding: 8px;
            font-size: 14px;
        }
        QPushButton {
            background-color: #8B4A55;
            color: #F0E6D3;
            border: none;
            border-radius: 8px;
            padding: 8px 16px;
            font-size: 13px;
        }
        QPushButton:hover {
            background-color: #E07A8F;
            color: #2C1F1F;
        }
        QPushButton:pressed {
            background-color: #C05A6F;
        }
    )";
}