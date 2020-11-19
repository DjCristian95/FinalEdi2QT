#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QDateTime>
#include <QStringList>
#include <iostream>
using namespace std;
#include <QSqlQuery>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
    , mDbConnection("horamundial.sqlite", "3307",
                    "root", ""){

    ui->setupUi(this);
    mModel = nullptr;

   db = QSqlDatabase::addDatabase("QSQLITE");//le otorga a db los drives
   db.setDatabaseName("horamundial.sqlite");
   db.setPort(3307);
   db.setUserName("root");
   db.setPassword("");

    //crea o abre base dato ( retorna bool)
    if(db.open()){
        qDebug()<<"Base de datos conectada..";
    }else{
        qDebug()<<" ERROR Base de datos NO conectada..";
    }
    crearTablaPaises();
    QTimer *timer = new QTimer(this);
    buildComboBoxPaises();
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start();
 }

void MainWindow::showTime() {
    QString timeText = actualizaHora().toString("hh : mm : ss");
    ui->DigitalClock->setText(timeText);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::buildComboBoxPaises() {
    QSqlQuery query;
    query.prepare("SELECT * FROM paises");
    query.exec();
    qDebug()<<"ERROR "<<query.result();
    while(query.next()) {
        ui->cmbPaises->addItem(query.value(1).toString());
    }
 }

void MainWindow::on_cmbPaises_currentTextChanged() {
    showTime();
}

QTime MainWindow::actualizaHora() {
    QString valuePais = ui->cmbPaises->currentText();
    QTime time;
    if (valuePais == "Argentina"){
        time = QTime::currentTime().addSecs(-10800);
   } else if (valuePais == "España"){
        time = QTime::currentTime().addSecs(3580);
    } else if (valuePais == "Estados Unidos"){
         time = QTime::currentTime().addSecs(-18000);
    }
   return time;
}

void MainWindow::crearTablaPaises() {
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS paises("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "nombre VARCHAR(100),"
                    "utc  VARCHAR(100) "
                     ");");
    QSqlQuery crear;
    crear.prepare(consulta);
   if (!db.tables().contains(QLatin1String("paises"))) {
        if (crear.exec()){
            insertarPaises();
            qDebug()<<"La tabla paises existe o se creo correctamente";
        }else{
            qDebug()<<"ERROR "<<crear.lastError();
        }
    }
}

void MainWindow::borrarPaises() {
    QString consultaEliminar;
    consultaEliminar.append("DELETE FROM paises");
    QSqlQuery eliminar;
    eliminar.prepare(consultaEliminar);
    if (eliminar.exec()){
        qDebug()<<"Pais se ELIMNINOOOOO en tabla";
    }else{
        qDebug()<<"ERROR  en carga entregas"<<eliminar.lastError();
    }
}

void MainWindow::insertarPaises() {
    QString consulta;
    consulta.append("INSERT INTO paises (nombre, utc) VALUES ('Argentina', '1000'), ('Estados Unidos', '2000'), ('España', '6000');");
    QSqlQuery insertar;
    insertar.prepare(consulta);
    if (insertar.exec()){
        qDebug()<<"Pais se inserto en tabla";
    }else{
        qDebug()<<"ERROR  en carga entregas"<<insertar.lastError();
    }
}
