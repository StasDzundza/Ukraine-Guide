#pragma once

#include <QAbstractListModel>
#include <QVector>

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

    Q_PROPERTY(bool isEmpty READ isEmpty NOTIFY isEmptyChanged)
    bool isEmpty() const;
    Q_SIGNAL void isEmptyChanged();

    Q_INVOKABLE void append(const LocalityListEntity &entity);
    Q_INVOKABLE void remove(const LocalityListEntity &entity);
    Q_INVOKABLE bool contains(const QString &keyName);
    Q_INVOKABLE void clear();
    Q_INVOKABLE void resetList(const QVector<LocalityListEntity> &mAllLocalitiesList);
    Q_INVOKABLE void fillSearchModel(const QString &prefix, LocalityListModel* other);

    static void declareQML();

   private:
    QVector<LocalityListEntity> mAllLocalitiesList;
};
