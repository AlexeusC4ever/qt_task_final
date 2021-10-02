#include "field.h"

FieldModel::FieldModel(QAbstractItemModel *parent) : QAbstractItemModel(parent)
{

}



int FieldModel::rows()
{
    return n_rows;
}

int FieldModel::columns()
{
    return n_columns;
}
