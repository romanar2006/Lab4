#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <iostream>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create actions and set shortcuts
    loadAction = new QAction("Выняць з", this);
    loadAction->setShortcut(QKeySequence("Ctrl+T"));
    connect(loadAction, &QAction::triggered, this, &MainWindow::on_loadButton_clicked);

    saveAction = new QAction("Захаваць як", this);
    saveAction->setShortcut(QKeySequence("Ctrl+S"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::on_saveButton_clicked);

    addAction = new QAction("Дадаць", this);
    addAction->setShortcut(QKeySequence("Ctrl+Q"));
    connect(addAction, &QAction::triggered, this, &MainWindow::on_addButton_clicked);

    replaceAction = new QAction("Замяніць", this);
    replaceAction->setShortcut(QKeySequence("Ctrl+R"));
    connect(replaceAction, &QAction::triggered, this, &MainWindow::on_replaceButton_clicked);

    findAction = new QAction("Знайсці", this);
    findAction->setShortcut(QKeySequence("Ctrl+F"));
    connect(findAction, &QAction::triggered, this, &MainWindow::on_findButton_clicked);

    removeAction = new QAction("Выдаліць", this);
    removeAction->setShortcut(QKeySequence("Ctrl+H"));
    connect(removeAction, &QAction::triggered, this, &MainWindow::on_removeButton_clicked);

    showAllAction = new QAction("Адлюстраваць", this);
    showAllAction->setShortcut(QKeySequence("Ctrl+W"));
    connect(showAllAction, &QAction::triggered, this, &MainWindow::on_showAllButton_clicked);

    // Create menu and add actions
    QMenu *menu = menuBar()->addMenu("Menu");
    menu->addAction(loadAction);
    menu->addAction(saveAction);
    menu->addAction(addAction);
    menu->addAction(replaceAction);
    menu->addAction(findAction);
    menu->addAction(removeAction);
    menu->addAction(showAllAction);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_loadButton_clicked() {
    QString filename = QFileDialog::getOpenFileName(this, "Выняць", "", "Text Files (*.txt)");
    if (!filename.isEmpty()) {
        dictionary.loadFromFile(filename.toStdString());
        QMessageBox::information(this, "Перамога", "Паспяхова вынята");
    }
    on_showAllButton_clicked();
}

void MainWindow::on_saveButton_clicked() {
    QString filename = QFileDialog::getSaveFileName(this, "Захаваць", "", "Text Files (*.txt)");
    if (!filename.isEmpty()) {
        dictionary.saveToFile(filename.toStdString());
        QMessageBox::information(this, "Перамога", "Паспяхова захавана");
    }
    on_showAllButton_clicked();
}

void MainWindow::on_addButton_clicked() {
    std::string englishWord = ui->englishWordLineEdit->text().toStdString();
    std::string russianTranslation = ui->russianWordLineEdit->text().toStdString();
    std::string belarusianTranslation = ui->belarusianWordLineEdit->text().toStdString();
    dictionary.addWord(englishWord, russianTranslation, belarusianTranslation);
    QMessageBox::information(this, "Перамога", "Паспяхова дададзена");
    on_showAllButton_clicked();
}

void MainWindow::on_replaceButton_clicked() {
    std::string englishWord = ui->englishWordLineEdit->text().toStdString();
    std::string russianTranslation = ui->russianWordLineEdit->text().toStdString();
    std::string belarusianTranslation = ui->belarusianWordLineEdit->text().toStdString();
    dictionary.replaceTranslation(englishWord, russianTranslation, belarusianTranslation);
    QMessageBox::information(this, "Перамога", "Паспяхова зменена");
    on_showAllButton_clicked();
}

void MainWindow::on_findButton_clicked() {
    std::string word = ui->searchWordLineEdit->text().toStdString();
    auto translation = dictionary.findTranslation(word);
    ui->resultLabel->setText(QString::fromStdString("English: " + std::get<0>(translation) + ", Русский: " + std::get<1>(translation) + ", Беларуская: " + std::get<2>(translation)));
    on_showAllButton_clicked();
}

void MainWindow::on_removeButton_clicked() {
    std::string englishWord = ui->englishWordLineEdit->text().toStdString();
    dictionary.removeWord(englishWord);
    QMessageBox::information(this, "Перамога", "Паспяхова выдалена");
    on_showAllButton_clicked();
}

void MainWindow::on_showAllButton_clicked() {
    std::cout << "Show All button clicked or Ctrl+W pressed" << std::endl;
    auto allWords = dictionary.getAllWords();
    int rowCount = allWords.size();

    ui->dictionaryTableWidget->setRowCount(rowCount);
    ui->dictionaryTableWidget->setColumnCount(3);
    ui->dictionaryTableWidget->setHorizontalHeaderLabels(QStringList() << "English" << "Russian" << "Belarusian");

    // Установить ширину столбцов равной ширине таблицы, деленной на 3
    int tableWidth = ui->dictionaryTableWidget->width();
    for (int col = 0; col < 3; ++col) {
        ui->dictionaryTableWidget->setColumnWidth(col, tableWidth / 3);
    }

    // Установить высоту строк
    int tableHeight = ui->dictionaryTableWidget->height();
    int rowHeight = tableHeight / (rowCount + 1);
    for (int row = 0; row < rowCount; ++row) {
        ui->dictionaryTableWidget->setRowHeight(row, rowHeight);
    }

    for (int row = 0; row < rowCount; ++row) {
        const auto& word = allWords[row];
        ui->dictionaryTableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(std::get<0>(word))));
        ui->dictionaryTableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(std::get<1>(word))));
        ui->dictionaryTableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(std::get<2>(word))));
    }
}
