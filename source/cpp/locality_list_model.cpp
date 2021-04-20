#include <QQmlEngine>
#include <algorithm>

#include "locality_list_model.h"

QHash<int, QByteArray> LocalityListModel::roleNames() const {
    return {
        {KeyNameRole, "keyName"},
        {UkrNameRole, "ukrName"},
        {EngNameRole, "engName"},
        {LocalityTypeRole, "localityType"}
    };
}

bool LocalityListModel::isEmpty() const { return mAllLocalitiesList.isEmpty(); }

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
            case LocalityTypeRole:
                return mAllLocalitiesList.at(index.row()).mType;
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
    emit isEmptyChanged();
}

void LocalityListModel::remove(const LocalityListEntity &entity) {
    auto it = std::find_if(mAllLocalitiesList.cbegin(), mAllLocalitiesList.cend(), [&entity](const LocalityListEntity &curEntity){
        return curEntity.mKeyName == entity.mKeyName;
    });
    int row = std::distance(mAllLocalitiesList.cbegin(), it);
    beginRemoveRows(QModelIndex(), row, row);
    mAllLocalitiesList.removeAt(row);
    endRemoveRows();
    emit isEmptyChanged();
}

bool LocalityListModel::contains(const QString &keyName) {
    if (mAllLocalitiesList.isEmpty()) {
        return false;
    }
    auto it = std::find_if(mAllLocalitiesList.cbegin(), mAllLocalitiesList.cend(), [&keyName](const LocalityListEntity &entity){
        return keyName == entity.mKeyName;
    });
    return it != mAllLocalitiesList.end();
}

void LocalityListModel::clear() {
    beginResetModel();
    mAllLocalitiesList.clear();
    endResetModel();
    emit isEmptyChanged();
}

void LocalityListModel::resetList(const QVector<LocalityListEntity> &localities) {
    mAllLocalitiesList.clear();
    beginResetModel();
    mAllLocalitiesList = localities;
    endResetModel();
    dataChanged(index(0, 0), index(mAllLocalitiesList.count(), 0), {KeyNameRole, UkrNameRole, EngNameRole});
    emit isEmptyChanged();
}

void LocalityListModel::fillSearchModel(const QString &prefix, LocalityListModel *other) {
    QVector<LocalityListEntity> result;
    if (!prefix.isEmpty()) {
        std::copy_if(mAllLocalitiesList.cbegin(), mAllLocalitiesList.cend(), std::back_inserter(result),
            [prefix](const LocalityListEntity &locality) {
                return locality.mUkrName.startsWith(prefix, Qt::CaseInsensitive) || locality.mEngName.startsWith(prefix, Qt::CaseInsensitive);
            });
    }
    other->resetList(result);
}

void LocalityListModel::sortByName() {
    sort([](const LocalityListEntity &first, const LocalityListEntity &second) {
        return first.mEngName < second.mEngName;
    });
}

void LocalityListModel::sortByArea() {
    sort([](const LocalityListEntity &first, const LocalityListEntity &second) {
        return first.mArea > second.mArea;
    });
}

void LocalityListModel::sortByPopulation() {
    sort([](const LocalityListEntity &first, const LocalityListEntity &second) {
        return first.mPopulation > second.mPopulation;
    });
}

void LocalityListModel::declareQML() {
    qmlRegisterType<LocalityListModel>("com.UkraineGuide.LocalityListModel", 1, 0, "LocalityListModel");
}

void LocalityListModel::sort(std::function<bool(const LocalityListEntity&, const LocalityListEntity&)> comparator) {
    beginResetModel();
    std::sort(mAllLocalitiesList.begin(), mAllLocalitiesList.end(), comparator);
    endResetModel();
    dataChanged(index(0, 0), index(mAllLocalitiesList.count(), 0), {KeyNameRole, UkrNameRole, EngNameRole});
}

