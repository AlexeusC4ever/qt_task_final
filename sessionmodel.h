#ifndef SESSIONMODEL_H
#define SESSIONMODEL_H

#include "fieldmodel.h"
#include <QAbstractListModel>
#include <QColor>
#include <QTcpSocket>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlComponent>

class QLabel;
class QLineEdit;
class QDialog;
class QDialogButtonBox;

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
        NOTIFY modelChanged)

    Q_PROPERTY(
        int winner
        READ winner
        CONSTANT)

    Q_PROPERTY(
        int onlineMoveFlag
        READ abilityToMakeMoveInOnline
        CONSTANT)

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    FieldModel* pModel() const;
    int player();
    void setPModel(FieldModel *newPModel);
    int winner();
    Q_INVOKABLE void saveModel(QString &fileName);
    Q_INVOKABLE void loadModel(QString &fileName);
    Q_INVOKABLE QColor playerColor(int);
    Q_INVOKABLE QColor playerColorForArea(int);
    Q_INVOKABLE void connectRequest();
    Q_INVOKABLE void nextPlayer();
    Q_INVOKABLE void showSettingsDialog();

    bool abilityToMakeMoveInOnline() const;

signals:
    Q_INVOKABLE void addedPoints();
    Q_INVOKABLE void sendWinner(int, QString);
//    Q_INVOKABLE void saveGameRequest(QString &fileName);
//    Q_INVOKABLE void loadGameRequest(QString &fileName);
    void modelChanged(/*FieldModel *newModel*/);
    Q_INVOKABLE void readyToMove();

private slots:
    void addPoints(int player, int points);
    void endGame();
    void sendPointToServer(int index);
    void onReadyRead();
    void changeFieldModel();

private:
//    QQmlEngine m_engine;
//    QQmlContext *m_pContext;
//    QQmlComponent *m_pComponent;
    std::vector<Player> m_players;
    QLineEdit *m_pLineEditHeight;
    QLabel *m_pLabelHeight;
    QLineEdit *m_pLineEditWidth;
    QLabel *m_pLabelWidth;
    QDialogButtonBox *m_okButton;
    QDialog *m_settingsDialog;
    FieldModel *m_pModel;
    QTcpSocket *m_pSocket;
    QDataStream m_in;
    QDataStream m_out;
    int m_winner;
    int m_currentOnlinePlayer;
    bool m_onlineGame;
    bool m_abilityToMakeMoveInOnline;

};

#endif // SESSIONMODEL_H
