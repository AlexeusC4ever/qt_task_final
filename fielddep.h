#ifndef FIELDMODEL_H
#define FIELDMODEL_H

#include <QAbstractItemModel>
#include <QVector>
#include "cell.h"

class FieldModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit FieldModel(QAbstractItemModel *parent = nullptr);

    Q_PROPERTY
    (int rows
     READ rows)
    Q_PROPERTY
    (int columns
     READ columns)

    int rows();
    int columns();
signals:


private:
    QVector<QVector<Cell*>> cells;
    int n_rows;
    int n_columns;

};

#endif // FIELDMODEL_H
