#pragma once
#include <qabstractitemmodel.h>
#include "Service.h"
class AstronomersTableModel :
    public QAbstractTableModel
{

public:
    explicit AstronomersTableModel(Service& s) : service (s) {};

    int rowCount(const QModelIndex& parent = QModelIndex()) const;

    int columnCount(const QModelIndex& parent = QModelIndex()) const { return 5; };

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);

    Qt::ItemFlags flags(const QModelIndex& index) const;
    void changed();
private:
    Service& service;

    

};

