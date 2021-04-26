#include <QQmlEngine>
#include <algorithm>

#include "routes_list_model.h"

QHash<int, QByteArray> RoutesListModel::roleNames() const {
    return {
        {NameRole, "routeName"},
    };
}

QStringList RoutesListModel::getRoutesList() const { return mAllRoutes; }

bool RoutesListModel::isEmpty() const { return mAllRoutes.isEmpty(); }

int RoutesListModel::getSize() const { return mAllRoutes.size(); }

RoutesListModel::RoutesListModel(QObject *parent) : QAbstractListModel(parent) {}

int RoutesListModel::rowCount(const QModelIndex &) const { return mAllRoutes.size(); }

QVariant RoutesListModel::data(const QModelIndex &index, int role) const {
    if (index.row() < rowCount()) {
        switch (role) {
            case NameRole:
                return mAllRoutes.at(index.row());
            default:
                return QVariant();
        }
    }
    return QVariant();
}

void RoutesListModel::append(const QString &entity) {
    int row = 0;
    row = mAllRoutes.count();
    beginInsertRows(QModelIndex(), row, row);
    mAllRoutes.insert(row, entity);
    endInsertRows();
    emit isEmptyChanged();
    emit sizeChanged();
}

void RoutesListModel::remove(int row) {
    beginRemoveRows(QModelIndex(), row, row);
    mAllRoutes.removeAt(row);
    endRemoveRows();
    emit isEmptyChanged();
    emit sizeChanged();
}

bool RoutesListModel::contains(const QString &routeName) {
    return mAllRoutes.contains(routeName, Qt::CaseInsensitive);
}

void RoutesListModel::clear() {
    beginResetModel();
    mAllRoutes.clear();
    endResetModel();
    emit isEmptyChanged();
    emit sizeChanged();
}

void RoutesListModel::resetList(const QStringList &routes) {
    mAllRoutes.clear();
    beginResetModel();
    mAllRoutes = routes;
    endResetModel();
    dataChanged(index(0, 0), index(mAllRoutes.count(), 0), {NameRole});
    emit isEmptyChanged();
    emit sizeChanged();
}

void RoutesListModel::declareQML() {
    qmlRegisterType<RoutesListModel>("com.UkraineGuide.RoutesListModel", 1, 0, "RoutesListModel");
}
