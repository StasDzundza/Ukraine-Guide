#include <QQmlEngine>
#include <algorithm>

#include "establishments_list_model.h"

QHash<int, QByteArray> EstablishmentsListModel::roleNames() const {
    return {
        {UkrNameRole, "ukrName"},
        {EngNameRole, "engName"},
        {TypeRole, "type"},
        {MoreInfoUrlRole, "moreInfoUrl"}
    };
}

bool EstablishmentsListModel::isEmpty() const { return mEstablishmentsList.isEmpty(); }

EstablishmentsListModel::EstablishmentsListModel(QObject *parent) : QAbstractListModel(parent) {}

int EstablishmentsListModel::rowCount(const QModelIndex &) const { return mEstablishmentsList.size(); }

QVariant EstablishmentsListModel::data(const QModelIndex &index, int role) const {
    if (index.row() < rowCount())
        switch (role) {
            case UkrNameRole:
                return mEstablishmentsList.at(index.row()).mUkrName;
            case EngNameRole:
                return mEstablishmentsList.at(index.row()).mEngName;
            case TypeRole:
                return mEstablishmentsList.at(index.row()).mType;
            case MoreInfoUrlRole:
                return mEstablishmentsList.at(index.row()).mMoreInfoUrl;
            default:
                return QVariant();
        }
    return QVariant();
}

void EstablishmentsListModel::resetList(const QVector<EstablishmentsListEntity> &establishments) {
    mEstablishmentsList.clear();
    beginResetModel();
    mEstablishmentsList = establishments;
    endResetModel();
    dataChanged(index(0, 0), index(mEstablishmentsList.count(), 0), {UkrNameRole, EngNameRole, MoreInfoUrlRole});
    emit isEmptyChanged();
}

void EstablishmentsListModel::declareQML() {
    qmlRegisterType<EstablishmentsListModel>("com.UkraineGuide.EstablishmentsListModel", 1, 0, "EstablishmentsListModel");
}

