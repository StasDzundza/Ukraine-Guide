#pragma once

#include <QObject>
#include <QVector>
#include <QPointF>

#include "locality_data_provider.h"
#include "locality_type.h"
#include "list_entities.h"
#include "establishments_list_model.h"

class LocalityModel : public QObject {
    Q_OBJECT
    Q_ENUMS(LocalityType::Type)
public:
    explicit LocalityModel(QObject *parent = nullptr);

    friend class LocalityDataProvider;

    // properties
    Q_PROPERTY(QString shortInfo READ getShortInfo NOTIFY shortInfoChanged)
    QString getShortInfo() const;
    Q_SIGNAL void shortInfoChanged();

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

    Q_PROPERTY(QString foundationDate READ getFoundationDate NOTIFY foundationDateChanged)
    QString getFoundationDate() const;
    Q_SIGNAL void foundationDateChanged();

    Q_PROPERTY(unsigned int population READ getPopulation NOTIFY populationChanged)
    unsigned int getPopulation() const;
    Q_SIGNAL void populationChanged();

    Q_PROPERTY(float area READ getArea NOTIFY areaChanged)
    float getArea() const;
    Q_SIGNAL void areaChanged();

    Q_PROPERTY(LocalityType::Type type READ getType NOTIFY typeChanged)
    LocalityType::Type getType() const;
    Q_SIGNAL void typeChanged();

    Q_PROPERTY(QPointF coordinates READ getCoordinates NOTIFY coordinatesChanged)
    QPointF getCoordinates() const;
    Q_SIGNAL void coordinatesChanged();

    Q_PROPERTY(QVector<QString> previewImages READ getPreviewImages NOTIFY previewImagesChanged)
    QVector<QString> getPreviewImages() const;
    Q_SIGNAL void previewImagesChanged();

    Q_PROPERTY(int numOfPreviewImages READ getNumOfPreviewImages NOTIFY numOfPreviewImagesChanged)
    int getNumOfPreviewImages() const;
    Q_SIGNAL void numOfPreviewImagesChanged();

    Q_PROPERTY(bool isFavorite READ isFavorite WRITE setFavorite NOTIFY isFavoriteChanged)
    bool isFavorite() const;
    void setFavorite(const bool isFavorite);
    Q_SIGNAL void isFavoriteChanged();

    Q_PROPERTY(QString moreInfoUrl READ getMoreInfoUrl NOTIFY moreInfoUrlChanged)
    QString getMoreInfoUrl() const;
    Q_SIGNAL void moreInfoUrlChanged();

    Q_PROPERTY(EstablishmentsListModel* establishments READ getEstablishments NOTIFY establishmentsChanged)
    EstablishmentsListModel* getEstablishments();
    Q_SIGNAL void establishmentsChanged();

    // qml methods
    Q_INVOKABLE void changeFavoriteStatus();

    // other methods
    static void declareQML();
    void allPropertiesChanged();

    // signals
    Q_SIGNAL void favoriteLocalityAdded(const LocalityListEntity &locality);
    Q_SIGNAL void favoriteLocalityRemoved(const LocalityListEntity &locality);

private:
    QString mShortInfo{};
    QString mKeyName{}, mUkrName{}, mEngName{};
    QString mOblast{}, mRegion{};
    QString mFoundationDate{};
    unsigned int mPopulation{};
    float mArea{};
    QPointF mCoordinates{};
    QVector<QString> mNeighbours{};
    QVector<QString> mPreviewImages{};
    LocalityType mType = LocalityType::CITY;
    bool mIsFavorite{};
    QString mMoreInfoUrl{};
    EstablishmentsListModel mEstablishmentsListModel;
};
