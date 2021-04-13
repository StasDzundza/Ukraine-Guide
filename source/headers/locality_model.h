#pragma once

#include <QObject>
#include <QVector>
#include <QPair>

#include "locality_data_provider.h"
#include "locality_type.h"

class LocalityModel : public QObject {
    Q_OBJECT
    Q_ENUMS(LocalityType::Type)
public:
    explicit LocalityModel(QObject *parent = nullptr);

    friend class LocalityDataProvider;

    // properties
    Q_PROPERTY(QString keyName READ getKeyName NOTIFY keyNameChanged)
    QString getKeyName() const;
    Q_SIGNAL void keyNameChanged();

    Q_PROPERTY(QString ukrName READ getUkrName NOTIFY ukrNameChanged)
    QString getUkrName() const;
    Q_SIGNAL void ukrNameChanged();

    Q_PROPERTY(QString engName READ getEngName NOTIFY engNameChanged)
    QString getEngName() const;
    Q_SIGNAL void engNameChanged();

    Q_PROPERTY(QString oblast READ getOblast NOTIFY oblastChanged)
    QString getOblast() const;
    Q_SIGNAL void oblastChanged();

    Q_PROPERTY(QString region READ getRegion NOTIFY regionChanged)
    QString getRegion() const;
    Q_SIGNAL void regionChanged();

    Q_PROPERTY(int population READ getPopulation NOTIFY populationChanged)
    int getPopulation() const;
    Q_SIGNAL void populationChanged();

    Q_PROPERTY(float area READ getArea NOTIFY areaChanged)
    float getArea() const;
    Q_SIGNAL void areaChanged();

    Q_PROPERTY(LocalityType type READ getType NOTIFY typeChanged)
    LocalityType getType() const;
    Q_SIGNAL void typeChanged();

    Q_PROPERTY(bool isFavorite READ isFavorite NOTIFY isFavoriteChanged)
    bool isFavorite() const;
    Q_SIGNAL void isFavoriteChanged();

    // qml methods
    Q_INVOKABLE void changeFavoriteStatus();

    // other methods
    static void declareQML();

private:
    QString mKeyName{}, mUkrName{}, mEngName{};
    QString mOblast{}, mRegion{};
    unsigned int mPopulation{};
    float mArea{};
    QPair<QString, QString> mCoordinates{};
    QVector<QString> mNeighbours{};
    LocalityType mType = LocalityType::CITY;
    bool mIsFavorite{};
};
