#ifndef SESSIONMODEL_H
#define SESSIONMODEL_H

#include "fieldmodel.h"
#include <QAbstractListModel>
#include <QColor>

struct Player{
    QString name;
    QColor color;
    int points;
};

class SessionModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit SessionModel(QObject *parent = nullptr);
    ~SessionModel();

    Q_PROPERTY(
        int player
        READ player
        CONSTANT)

    Q_PROPERTY(
        QColor playerColor
        READ playerColor
        CONSTANT)

    Q_PROPERTY(
        QColor playerColorForArea
        READ playerColorForArea
        CONSTANT)

    Q_PROPERTY(
        FieldModel* model
        READ pModel
        WRITE setPModel
        /*NOTIFY modelChanged*/)

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    FieldModel* pModel() const;
    int player();
    QColor playerColor();
    QColor playerColorForArea();
    Q_INVOKABLE void nextPlayer();
    void setPModel(FieldModel *newPModel);

signals:
    Q_INVOKABLE void addedPoints();

private slots:
    void addPoints(int player, int points);

private:
    std::vector<Player> m_players;
    FieldModel *m_pModel;

};

#endif // SESSIONMODEL_H
