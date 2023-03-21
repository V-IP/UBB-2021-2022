#pragma once

#include <QAbstractTableModel>
#include <qfont.h>
#include <qbrush.h>
#include <vector>
#include "Obj.h"

class MyTableModel : public QAbstractTableModel {
private:
	std::vector<Obj> all;
	std::string tip;
public:
	MyTableModel(const std::vector<Obj>& all, const string tip) :all{ all }, tip{ tip }{};
	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return 100;
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 5;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (index.row() >= all.size())
			return QVariant{};
		if (role == Qt::DisplayRole) {
			int ct = 0;
			auto o = this->all[index.row()];
			for (const Obj& it : all) {
				if (o.getTip() == it.getTip())
					ct++;
			}
			if (index.column() == 0) {
				return QString::number(o.getId());
			}
			if (index.column() == 1) {
				return QString::fromStdString(o.getDenumire());
			}
			if (index.column() == 2) {
				return QString::fromStdString(o.getTip());
			}
			if (index.column() == 3) {
				return QString::number(o.getNrRoti());
			}
			if (index.column() == 4) {
				return ct;
			}
		}
		if (role == Qt::BackgroundRole) {
			auto o = this->all[index.row()];
			if (o.getTip() == tip) {
				return QBrush(Qt::red);
			}
		}
		return QVariant{};
	}
	void setObj(const vector<Obj>& all) {
		this->all = all;
		auto topIndex = createIndex(0, 0);
		auto bottomIndex = createIndex(all.size(), 5);
		emit dataChanged(topIndex, bottomIndex);
	}
};