#pragma once

#include <QAbstractListModel>
#include <QStringList>

class RoutesListModel : public QAbstractListModel {
    Q_OBJECT
   public:
    enum RouteRole { NameRole = Qt::DisplayRole};
    Q_ENUM(RouteRole)

    explicit RoutesListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex & = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;
    QStringList getRoutesList() const;
    void renameRoute(const QString &oldName, const QString &newName);

    Q_PROPERTY(bool isEmpty READ isEmpty NOTIFY isEmptyChanged)
    bool isEmpty() const;
    Q_SIGNAL void isEmptyChanged();

    Q_PROPERTY(int size READ getSize NOTIFY sizeChanged)
    int getSize() const;
    Q_SIGNAL void sizeChanged();

    Q_INVOKABLE void append(const QString &routeName);
    Q_INVOKABLE void remove(int index);
    Q_INVOKABLE bool contains(const QString &routeName);
    Q_INVOKABLE void clear();
    Q_INVOKABLE void resetList(const QStringList &mAllLocalitiesList);

    static void declareQML();

   private:
    QStringList mAllRoutes;
};
