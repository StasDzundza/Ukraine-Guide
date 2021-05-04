#include <QQmlEngine>
#include <algorithm>

#include "selected_localities_model.h"

SelectedLocalitiesModel::SelectedLocalitiesModel(QObject *parent): QObject(parent) {}

QStringList SelectedLocalitiesModel::getSelectedLocalities() const {
    return mSelectedLocalities;
}

bool SelectedLocalitiesModel::isEmpty() const { return mSelectedLocalities.isEmpty(); }

void SelectedLocalitiesModel::append(const QString &keyName) {
    mSelectedLocalities.append(keyName);
    selectedLocalitiesChanged();
    isEmptyChanged();
}

void SelectedLocalitiesModel::remove(const QString &keyName) {
    mSelectedLocalities.removeAll(keyName);
    selectedLocalitiesChanged();
    isEmptyChanged();
}

bool SelectedLocalitiesModel::contains(const QString &keyName) {
    if (mSelectedLocalities.isEmpty()) {
        return false;
    }
    return mSelectedLocalities.contains(keyName);
}

void SelectedLocalitiesModel::clear() {
    mSelectedLocalities.clear();
    selectedLocalitiesChanged();
    isEmptyChanged();
}

void SelectedLocalitiesModel::declareQML() {
    qmlRegisterType<SelectedLocalitiesModel>("com.UkraineGuide.SelectedLocalitiesModel", 1, 0, "SelectedLocalitiesModel");
}
