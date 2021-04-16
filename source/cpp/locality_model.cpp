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

QPointF LocalityModel::getCoordinates() const { return mCoordinates; }

bool LocalityModel::isFavorite() const { return mIsFavorite; }

void LocalityModel::setFavorite(const bool isFavorite) { mIsFavorite = isFavorite; }

//qml methods
void LocalityModel::changeFavoriteStatus() {
    mIsFavorite = !mIsFavorite;
    emit isFavoriteChanged();

    if (mIsFavorite) {
        emit favoriteLocalityAdded({mKeyName, mUkrName, mEngName, LocalityType::toString(mType)});
    } else {
        emit favoriteLocalityRemoved({mKeyName, mUkrName, mEngName, LocalityType::toString(mType)});
    }
}

void LocalityModel::declareQML() {
    qmlRegisterType<LocalityListModel>("com.UkraineGuide.LocalityModel", 1, 0, "LocalityModel");
}

void LocalityModel::allPropertiesChanged() {
    keyNameChanged();
    ukrNameChanged();
    engNameChanged();
    oblastChanged();
    regionChanged();
    populationChanged();
    areaChanged();
    typeChanged();
    isFavoriteChanged();
}
