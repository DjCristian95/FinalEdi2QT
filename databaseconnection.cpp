#include "databaseconnection.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QtSql/QSqlDatabase>

DataBaseConnection::DataBaseConnection(const QString &databaseName,
                                       const QString &port,
                                       const QString &user,
                                       const QString &password) {
    mDatabase = QSqlDatabase::addDatabase("QSQLITE");
    mDatabaseName = databaseName;
    mPort = port;
    mUser = user;
    mPassword = password;
}
