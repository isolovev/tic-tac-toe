#ifndef MODEL_H
#define MODEL_H

#include <QAbstractListModel>
#include <QProperty>
#include <QQmlEngine>

class Model : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int gridSize READ gridSize WRITE setGridSize NOTIFY gridSizeChanged
               BINDABLE bindableGridSize)
    Q_PROPERTY(Players player READ player NOTIFY playerChanged BINDABLE bindablePlayer)
    Q_PROPERTY(bool gameInProgress READ gameInProgress BINDABLE bindableGameInProgress)
    Q_PROPERTY(GameStatus gameStatus READ gameStatus BINDABLE bindableGameStatus)
    QML_NAMED_ELEMENT(TicTacToeModel)
public:
    enum States {
        Unknown = 0,
        Cross,
        Circle
    };
    Q_ENUMS(States)

    enum Players {
        Player1 = 0,
        Player2
    };
    Q_ENUMS(Players)

    enum GameStatus {
        GameReset = 0,
        GameInProgress,
        GameOverWin,
        GameOverDraw
    };
    Q_ENUMS(GameStatus)

    enum Roles {
        StateRole = Qt::UserRole + 1
    };

    explicit Model(QObject *parent = nullptr);

    int gridSize() const;
    void setGridSize(int size);
    QBindable<int> bindableGridSize();

    Players player() const;
    QBindable<Players> bindablePlayer() const;

    bool gameInProgress() const;
    QBindable<bool> bindableGameInProgress() const;

    GameStatus gameStatus() const;
    QBindable<GameStatus> bindableGameStatus() const;

    bool gameFinished() const;

    int rowCount(const QModelIndex &parent) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

signals:
    void gridSizeChanged();
    void playerChanged();

public slots:
    Q_INVOKABLE void resetModel();
    Q_INVOKABLE void click(int ind);

private:
    GameStatus checkWin(int ind, States state);

    Q_OBJECT_BINDABLE_PROPERTY_WITH_ARGS(Model, int, m_gridSize, 3, &Model::gridSizeChanged)
    Q_OBJECT_BINDABLE_PROPERTY_WITH_ARGS(Model, Players, m_currentPlayer, Player1,
                                         &Model::playerChanged)
    Q_OBJECT_COMPUTED_PROPERTY(Model, bool, m_gameInProgress, &Model::gameInProgress)
    Q_OBJECT_BINDABLE_PROPERTY_WITH_ARGS(Model, GameStatus, m_gameStatus, GameReset)
    QList<States> m_elements;
    int m_numMoves = 0;
};

QML_DECLARE_TYPE(Model)

#endif // MODEL_H
