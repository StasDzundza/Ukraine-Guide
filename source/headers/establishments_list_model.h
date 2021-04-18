#pragma once

#include <QAbstractListModel>
#include <QVector>

#include "list_entities.h"

class EstablishmentsListModel : public QAbstractListModel {
    Q_OBJECT
   public:
    enum EstablishmentRole { UkrNameRole = Qt::DisplayRole, EngNameRole, TypeRole, MoreInfoUrlRole };
    Q_ENUM(EstablishmentRole)

    explicit EstablishmentsListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex & = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;

    Q_PROPERTY(bool isEmpty READ isEmpty NOTIFY isEmptyChanged)
    bool isEmpty() const;
    Q_SIGNAL void isEmptyChanged();

    Q_INVOKABLE void resetList(const QVector<EstablishmentsListEntity> &establishmentsList);

    static void declareQML();

   private:
    QVector<EstablishmentsListEntity> mEstablishmentsList;
};
