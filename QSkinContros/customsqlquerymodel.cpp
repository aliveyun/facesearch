#include "customsqlquerymodel.h"

CustomSqlQueryModel::CustomSqlQueryModel(QObject* parent) : QSqlQueryModel(parent)
{

}
/**
 * @brief 实现单元格内文字居中
 */
QVariant CustomSqlQueryModel::data(const QModelIndex& index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);
    /**
      * 单元格内容居中
      */
    if (Qt::TextAlignmentRole == role) {
        value = Qt::AlignCenter;
    }
    return value;
}


