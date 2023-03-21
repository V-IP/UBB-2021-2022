#pragma once

#include <QAbstractTableModel>
#include <qfont.h>
#include <qbrush.h>
#include <vector>
#include "Obj.h"

class MyTableModel : public QAbstractTableModel {
private:
	std::vector<Tenant> all;
public:
	MyTableModel(const std::vector<Tenant>& all) :all{ all } {};
	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return 100;
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (index.row() >= all.size())
			return QVariant{};
		if (role == Qt::DisplayRole) {
			auto t = this->all[index.row()];
			if (index.column() == 0) {
				return QString::number(t.getNrAp());
			}
			if (index.column() == 1) {
				return QString::fromStdString(t.getOwner());
			}
			if (index.column() == 2) {
				return QString::fromStdString(t.getType());
			}
			if (index.column() == 3) {
				return QString::number(t.getSurface());
			}
		}
		if (role == Qt::BackgroundRole) {
			auto t = this->all[index.row()];
			if (t.getNrAp() > 10) {
				return QBrush(Qt::yellow);
			}
		}
		if (role == Qt::FontRole) {
			auto t = this->all[index.row()];
			if (t.getType() == "Garsoniera") {
				auto font = QFont();
				font.setBold(true);
				return font;
			}
		}
		if (role == Qt::ForegroundRole) {
			auto t = this->all[index.row()];
			if (t.getSurface() < 10) {
				return QBrush(Qt::blue);
			}
		}
		return QVariant{};
	}
	void setTenant(vector<Tenant>& all) {
		this->all = all; 
		auto topIndex = createIndex(0,0);
		auto bottomIndex = createIndex(all.size(),4); 
		emit dataChanged(topIndex, bottomIndex);
	}
};