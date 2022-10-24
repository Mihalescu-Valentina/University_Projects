#include "AstronomersTableModel.h"
#include <windows.h>

int AstronomersTableModel::rowCount(const QModelIndex& parent) const
{
	return this->service.getSize();
}

QVariant AstronomersTableModel::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		int row = index.row();
		int column = index.column();
		Star star = this->service.getsortedStars()[row];
		if (column == 0)
		{
			return QString::fromStdString(star.getName());
		}
		if (column == 1)
		{
			return QString::fromStdString(star.getConstellation());
		}
		if (column == 2)
		{
			return QString::number(star.getRa());
		}
		if (column == 3)
		{
			return QString::number(star.getDec());
		}

		if (column == 4)
			return QString::number(star.getDiameter());

	}
	return QVariant();
}

QVariant AstronomersTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
	{
		if (section == 0)
		{
			return "Name";
		}
		if (section == 1)
		{
			return "Constellation";
		}
		if (section == 2)
		{
			return "RA";
		}
		if (section == 3)
		{
			return "Declination";
		}

		if (section == 4)
			return "Diameter";
	}

	return QVariant();
}

bool AstronomersTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (role == Qt::EditRole)
	{
		int row = index.row();
		int column = index.column();
		Star star= this->service.getStars()[row];
		if (column == 0)
		{
			star.setName(value.value<std::string>());
		}
		if (column == 2)
		{
			star.setRa(value.value<int>());
		}

		if (column == 3)
		{
			star.setDec(value.value<int>());
		}

		if (column == 4)
		{
			star.setDiameter(value.value<int>());
		}

		emit dataChanged(index,index);
		return true;
	}
	return false;
}

Qt::ItemFlags AstronomersTableModel::flags(const QModelIndex& index) const
{
	int col = index.column();
	if (col == 0 or col==2 or col==4 or col == 3)
	{
		return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	}
	return Qt::ItemFlags();
}




void AstronomersTableModel::changed() 
{	
	emit layoutChanged();
	
}
