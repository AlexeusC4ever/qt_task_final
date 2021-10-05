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

//    Q_PROPERTY(
//        QColor playerColor
//        READ playerColor
//        CONSTANT)

//    Q_PROPERTY(
//        QColor playerColorForArea
//        READ playerColorForArea
//        CONSTANT)

    Q_PROPERTY(
        FieldModel* model
        READ pModel
        WRITE setPModel
        /*NOTIFY modelChanged*/)

    Q_PROPERTY(
        int winner
        READ winner
        CONSTANT)

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    FieldModel* pModel() const;
    int player();
    Q_INVOKABLE QColor playerColor(int);
    Q_INVOKABLE QColor playerColorForArea(int);
    Q_INVOKABLE void nextPlayer();
    void setPModel(FieldModel *newPModel);
    int winner();

signals:
    Q_INVOKABLE void addedPoints();
    Q_INVOKABLE void sendWinner();

private slots:
    void addPoints(int player, int points);
    void endGame();

private:
    std::vector<Player> m_players;
    FieldModel *m_pModel;
    int m_winner;

};

#endif // SESSIONMODEL_H
