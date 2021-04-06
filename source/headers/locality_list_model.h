#pragma once

#include <QAbstractListModel>
#include <QVector>

struct LocalityListEntity {
    QString mKeyName, mUkrName, mEngName;
};

class LocalityListModel : public QAbstractListModel {
    Q_OBJECT
   public:
    enum LocalityRole { KeyNameRole = Qt::DisplayRole, UkrNameRole, EngNameRole };
    Q_ENUM(LocalityRole)

    explicit LocalityListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex & = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;
    void append(const LocalityListEntity &entity);
    void clear();
    void resetList(const QVector<LocalityListEntity> &mAllLocalitiesList);

    static void declareQML();

   private:
    QVector<LocalityListEntity> mAllLocalitiesList;
};
