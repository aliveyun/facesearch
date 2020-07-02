#ifndef CUSTOMSQLQUERYMODEL_H
#define CUSTOMSQLQUERYMODEL_H

#include <QObject>
#include <QtSql/QSqlQueryModel>

class CustomSqlQueryModel : public QSqlQueryModel
{
public:
	CustomSqlQueryModel(QObject* parent = 0);

	// QAbstractItemModel interface
public:
	QVariant data(const QModelIndex& index, int role) const override;
};

#endif // CUSTOMSQLQUERYMODEL_H

