#pragma once
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
#include <QDebug>

#include "model.h"

class DBManager {

private:
	const QString dbms = "QSQLITE";
	const QString dbName = "explorer";
	const QString hostName = "localhost";
	QSqlDatabase db;
	bool connected = false;
public:
	DBManager() {
		
		db = QSqlDatabase::addDatabase(dbms);
		db.setDatabaseName(dbName + ".db");
		QString qs; 
		if (db.open()) {
			qDebug() << "DB Setting succeed!";
			if (db.isValid()) {
				qs = "CREATE TABLE IF NOT EXISTS EXPLORER("
					   "ID INTEGER PRIMARY KEY AUTOINCREMENT, "						 
					     "NAME VARCHAR(50),"
					    "PATH VARCHAR(100),"
							"EXTENDED INTEGER DEFAULT 0,"
							"DATE DATETIME)";
				QSqlQuery query;
				query.prepare(qs);
				query.exec();

				connected = true;
			}
		}
		else {
			qDebug() << "DB Setting failed...";
			QSqlDatabase::removeDatabase(dbName);
		}
	}

	bool insertDB(QString name, QString path) {
		QSqlQuery query; 
		query.prepare("INSERT INTO EXPLORER (NAME, PATH, DATE) "
			"VALUES (:name, :path, :date)");
		query.bindValue(":name", name);
		query.bindValue(":path", path);
		query.bindValue(":date", "DATETIME('NOW')");

		/* Refresh model. */
		if (query.exec()) {
			selectDB();
			return true;
		}
		return false;
	}
	
	void selectDB() {
		QSqlQuery query;
		query.prepare("SELECT * FROM EXPLORER ORDER BY DATE ASC");
		query.exec();
		QList<Explorer*> dummy;
		while (query.next()) {
			dummy.append(new Explorer(query.value(0).toInt(),
																query.value(1).toString(),
																query.value(2).toString(),
																query.value(3).toInt()));
		}
		ViewModel::instance()->setProjects(dummy);		
	}

	bool modifyExtended(int id, bool extended) {
		QSqlQuery query;
		query.prepare("UPDATE EXPLORER SET EXTENDED = :extended WHERE id = :id");
		query.bindValue(":extended", extended ? 1 : 0);
		query.bindValue(":id", id);

		/* Refresh model. */
		if (query.exec()) {
			//selectDB();
			return true;
		}
		return false;
	}

	bool removeDB(int id) {
		QSqlQuery query;
		query.prepare("DELETE FROM EXPLORER WHERE id = :id");
		query.bindValue(":id", id);

		/* Refresh model. */
		if (query.exec()) {
			selectDB(); 
			return true;
		}
		return false;
		
	}


};