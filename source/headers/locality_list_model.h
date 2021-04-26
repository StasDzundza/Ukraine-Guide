#pragma once

#include <QAbstractListModel>
#include <QVector>
#include <functional>

#include "list_entities.h"

class LocalityListModel : public QAbstractListModel {
    Q_OBJECT
   public:
    enum LocalityRole { KeyNameRole = Qt::DisplayRole, UkrNameRole, EngNameRole, LocalityTypeRole };
    Q_ENUM(LocalityRole)

    explicit LocalityListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex & = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;
    QStringList getKeyNames() const;

    Q_PROPERTY(bool isEmpty READ isEmpty NOTIFY isEmptyChanged)
    bool isEmpty() const;
    Q_SIGNAL void isEmptyChanged();

    Q_PROPERTY(int size READ getSize NOTIFY sizeChanged)
    int getSize() const;
    Q_SIGNAL void sizeChanged();

    Q_INVOKABLE void append(const LocalityListEntity &entity);
    Q_INVOKABLE void remove(const LocalityListEntity &entity);
    Q_INVOKABLE bool contains(const QString &keyName);
    Q_INVOKABLE void clear();
    Q_INVOKABLE void resetList(const QVector<LocalityListEntity> &mAllLocalitiesList);
    Q_INVOKABLE void fillSearchModel(const QString &prefix, LocalityListModel* other);
    Q_INVOKABLE void sortByName();
    Q_INVOKABLE void sortByArea();
    Q_INVOKABLE void sortByPopulation();
    Q_INVOKABLE void moveUp(const int index);
    Q_INVOKABLE void moveDown(const int index);

    static void declareQML();

   private:
    void sort(std::function<bool(const LocalityListEntity&, const LocalityListEntity&)> comparator);

    QVector<LocalityListEntity> mAllLocalitiesList;
};
