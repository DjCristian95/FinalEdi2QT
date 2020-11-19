#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "databaseconnection.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QSqlQueryModel;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void buildComboBoxPaises();
    QTime actualizaHora();
    void crearTablaPaises();
    void insertarPaises();
    void borrarPaises();

private slots:
    void showTime();

    void on_cmbPaises_currentTextChanged();

private:
    Ui::MainWindow *ui;
    DataBaseConnection mDbConnection;
    QSqlQueryModel *mModel;
    QSqlDatabase db;
};
#endif // MAINWINDOW_H
