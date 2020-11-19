#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QSqlDatabase>

class DataBaseConnection
{
public:
    DataBaseConnection(const QString &databaseName,
                       const QString &port,
                       const QString &user,
                       const QString &password);

private:
    QSqlDatabase mDatabase;
    QString mDatabaseName;
    QString mPort;
    QString mUser;
    QString mPassword;

};

#endif // DATABASECONNECTION_H
