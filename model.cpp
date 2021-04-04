#include "model.h"

Model::Model(QObject *parent) : QAbstractListModel(parent)
{
    // We can't have complex setter for m_gridSize property, because
    // Q_OBJECT_BINDABLE_PROPERTY accepts only trivial getters and setters.
    // So we will have to connect to a signal to handle grid size change.
    connect(this, &Model::gridSizeChanged, this, &Model::resetModel);
    resetModel();
}

int Model::gridSize() const
{
    return m_gridSize;
}

void Model::setGridSize(int size)
{
    // The signal will be automatically emitted because of the bindable property
    m_gridSize = size;
}

QBindable<int> Model::bindableGridSize()
{
    return QBindable<int>(&m_gridSize);
}

Model::Players Model::player() const
{
    return m_currentPlayer;
}

QBindable<Model::Players> Model::bindablePlayer() const
{
    return QBindable<Players>(&m_currentPlayer);
}

bool Model::gameInProgress() const
{
    return m_gameStatus == GameInProgress;
}

QBindable<bool> Model::bindableGameInProgress() const
{
    return QBindable<bool>(&m_gameInProgress);
}

Model::GameStatus Model::gameStatus() const
{
    return m_gameStatus.value();
}

QBindable<Model::GameStatus> Model::bindableGameStatus() const
{
    return QBindable<GameStatus>(&m_gameStatus);
}

bool Model::gameFinished() const
{
    return (m_gameStatus == GameOverWin) || (m_gameStatus == GameOverDraw);
}


int Model::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_elements.size();
}

QHash<int, QByteArray> Model::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[StateRole] = "state";
    return roles;
}

QVariant Model::data(const QModelIndex &ind, int role) const
{
    if (!ind.isValid())
        return QVariant();

    if (role == StateRole)
        return m_elements[ind.row()];

    return QVariant();
}

void Model::resetModel()
{
    const auto newSize = m_gridSize * m_gridSize;
    if (newSize != m_elements.size()) {
        beginResetModel();
        m_elements.resize(m_gridSize * m_gridSize);
        std::fill(m_elements.begin(), m_elements.end(), Unknown);
        endResetModel();
    } else {
        // To get smooth animation
        for (auto i = 0; i < m_elements.size(); ++i) {
            if (m_elements[i] != Unknown) {
                m_elements[i] = Unknown;
                emit dataChanged(index(i), index(i), { StateRole });
            }
        }
    }
    m_gameStatus = GameReset;
    m_currentPlayer = Player1;
    m_numMoves = 0;
    m_gameInProgress.markDirty();
}

void Model::click(int ind)
{
    if (ind >= 0 && ind < m_elements.size()) {
        if (m_elements[ind] == Unknown && !gameFinished()) {
            m_numMoves++;
            m_elements[ind] = (m_currentPlayer == Player1) ? Cross : Circle;
            emit dataChanged(index(ind), index(ind), { StateRole });
            m_gameStatus = checkWin(ind, m_elements[ind]);
            if (!gameFinished())
                m_currentPlayer = (m_currentPlayer == Player1) ? Player2 : Player1;
            m_gameInProgress.markDirty();
        }
    }
}

Model::GameStatus Model::checkWin(int ind, Model::States state)
{
    // Check row/column/diag that contains currently changed element.

    const auto gs = m_gridSize.value();

    const int row = ind / gs;
    const int column = ind % gs;

    // check rows
    bool hasWin = true;
    for (int i = 0; i < gs; ++i) {
        if (m_elements[i + row * gs] != state) {
            hasWin = false;
            break;
        }
    }
    if (hasWin)
        return GameOverWin;

    // check columns
    hasWin = true;
    for (int i = 0; i < gs; ++i) {
        if (m_elements[i * gs + column] != state) {
            hasWin = false;
            break;
        }
    }
    if (hasWin)
        return GameOverWin;

    // check main diag
    if (row == column) {
        hasWin = true;
        for (int i = 0; i < gs; ++i) {
            if (m_elements[i * (gs + 1)] != state) {
                hasWin = false;
                break;
            }
        }
        if (hasWin)
            return GameOverWin;
    }

    // check anti-diag
    if (row + column == gs - 1) {
        hasWin = true;
        for (int i = 0; i < gs; ++i) {
            if (m_elements[(gs - 1) * (i + 1)] != state) {
                hasWin = false;
                break;
            }
        }
        if (hasWin)
            return GameOverWin;
    }

    if (m_numMoves == gs * gs)
        return GameOverDraw;

    return GameInProgress;
}
