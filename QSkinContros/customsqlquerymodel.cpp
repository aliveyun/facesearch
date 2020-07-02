#include "customsqlquerymodel.h"

CustomSqlQueryModel::CustomSqlQueryModel(QObject* parent) : QSqlQueryModel(parent)
{

}
/**
 * @brief ʵ�ֵ�Ԫ�������־���
 */
QVariant CustomSqlQueryModel::data(const QModelIndex& index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);
    /**
      * ��Ԫ�����ݾ���
      */
    if (Qt::TextAlignmentRole == role) {
        value = Qt::AlignCenter;
    }
    return value;
}


