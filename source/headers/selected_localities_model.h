#pragma once

#include <QObject>
#include <QStringList>

class SelectedLocalitiesModel : public QObject {
    Q_OBJECT
   public:
    explicit SelectedLocalitiesModel(QObject *parent = nullptr);

    Q_PROPERTY(QStringList selectedLocalities READ getSelectedLocalities NOTIFY selectedLocalitiesChanged)
    QStringList getSelectedLocalities() const;
    Q_SIGNAL void selectedLocalitiesChanged();

    Q_PROPERTY(bool isEmpty READ isEmpty NOTIFY isEmptyChanged)
    bool isEmpty() const;
    Q_SIGNAL void isEmptyChanged();

    Q_INVOKABLE void append(const QString &keyName);
    Q_INVOKABLE void remove(const QString &keyName);
    Q_INVOKABLE bool contains(const QString &keyName);
    Q_INVOKABLE void clear();

    static void declareQML();

private:
    QStringList mSelectedLocalities;
};
