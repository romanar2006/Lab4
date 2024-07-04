#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QTableWidget>
#include "dictionary.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loadButton_clicked();
    void on_saveButton_clicked();
    void on_addButton_clicked();
    void on_replaceButton_clicked();
    void on_findButton_clicked();
    void on_removeButton_clicked();
    void on_showAllButton_clicked();

private:
    Ui::MainWindow *ui;
    Dictionary dictionary;

    // Actions for shortcuts
    QAction *loadAction;
    QAction *saveAction;
    QAction *addAction;
    QAction *replaceAction;
    QAction *findAction;
    QAction *removeAction;
    QAction *showAllAction;
};

#endif // MAINWINDOW_H
