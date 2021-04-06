#include "locality_list_model.h"

#include <QQmlEngine>

QHash<int, QByteArray> LocalityListModel::roleNames() const {
    return {
        {KeyNameRole, "keyName"},
        {UkrNameRole, "ukrName"},
        {EngNameRole, "engName"},
    };
}

LocalityListModel::LocalityListModel(QObject *parent) : QAbstractListModel(parent) {}

int LocalityListModel::rowCount(const QModelIndex &) const { return mAllLocalitiesList.size(); }

QVariant LocalityListModel::data(const QModelIndex &index, int role) const {
    if (index.row() < rowCount())
        switch (role) {
            case KeyNameRole:
                return mAllLocalitiesList.at(index.row()).mKeyName;
            case UkrNameRole:
                return mAllLocalitiesList.at(index.row()).mUkrName;
            case EngNameRole:
                return mAllLocalitiesList.at(index.row()).mEngName;
            default:
                return QVariant();
        }
    return QVariant();
}

void LocalityListModel::append(const LocalityListEntity &entity) {
    int row = 0;
    row = mAllLocalitiesList.count();
    beginInsertRows(QModelIndex(), row, row);
    mAllLocalitiesList.insert(row, entity);
    endInsertRows();
}

void LocalityListModel::clear() {
    beginResetModel();
    mAllLocalitiesList.clear();
    endResetModel();
}

void LocalityListModel::resetList(const QVector<LocalityListEntity> &localities) {
    mAllLocalitiesList.clear();
    beginResetModel();
    mAllLocalitiesList = localities;
    endResetModel();
    dataChanged(index(0, 0), index(mAllLocalitiesList.count(), 0), {KeyNameRole, UkrNameRole, EngNameRole});
}

void LocalityListModel::declareQML() {
    qmlRegisterType<LocalityListModel>("com.UkraineGuide.LocalityList", 1, 0, "LocalityList");
}

