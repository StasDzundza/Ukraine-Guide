#include <QQmlEngine>
#include <algorithm>

#include "selected_localities_model.h"

QStringList SelectedLocalitiesModel::getSelectedLocalities() const {
    return mSelectedLocalities;
}

void SelectedLocalitiesModel::append(const QString &keyName) {
    mSelectedLocalities.append(keyName);
    selectedLocalitiesChanged();
}

void SelectedLocalitiesModel::remove(const QString &keyName) {
    mSelectedLocalities.removeAll(keyName);
    selectedLocalitiesChanged();
}

bool SelectedLocalitiesModel::contains(const QString &keyName) {
    return mSelectedLocalities.contains(keyName);
}

void SelectedLocalitiesModel::clear() {
    mSelectedLocalities.clear();
    selectedLocalitiesChanged();
}

void SelectedLocalitiesModel::declareQML() {
    qmlRegisterType<SelectedLocalitiesModel>("com.UkraineGuide.SelectedLocalitiesModel", 1, 0, "SelectedLocalitiesModel");
}
