#include <QQmlEngine>

#include "locality_model.h"

LocalityModel::LocalityModel(QObject *parent) : QObject(parent){}

// properties
QString LocalityModel::getKeyName() const { return mKeyName; }

QString LocalityModel::getUkrName() const { return mUkrName; }

QString LocalityModel::getEngName() const { return mEngName; }

QString LocalityModel::getOblast() const { return mOblast; }

QString LocalityModel::getRegion() const { return mRegion; }

int LocalityModel::getPopulation() const { return mPopulation; }

float LocalityModel::getArea() const { return mArea; }

LocalityType LocalityModel::getType() const { return mType; }

bool LocalityModel::isFavorite() const { return mIsFavorite; }

//qml methods
void LocalityModel::changeFavoriteStatus() {
    mIsFavorite = !mIsFavorite;
    emit isFavoriteChanged();

    // send signal to application and remove or add locality to favorite list
}

void LocalityModel::declareQML() {
    qmlRegisterType<LocalityListModel>("com.UkraineGuide.LocalityModel", 1, 0, "LocalityModel");
}
