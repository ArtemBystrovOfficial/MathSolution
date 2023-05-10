#pragma once

#include <QAbstractListModel>

#include "mainlogic.h"

namespace kp = knapsack;

class MainModel1_0_1 : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(int bgWeight READ bgWeight WRITE setBgWeight NOTIFY bgWeightChanged)
public:
    enum class role_t {
        arg1,
        arg2
    };

    MainModel1_0_1(QObject *parent=nullptr) :  QAbstractListModel(parent),m_bgWeight(0){}
    virtual int rowCount(const QModelIndex &parent) const {
        return m_items.size();
    }
    Q_INVOKABLE int columnCount() {
        return 2;
    }
    virtual QVariant data(const QModelIndex &index, int role) const {
        if(!index.isValid())
           return QVariant();
        auto obj = m_items[index.row()];
        if(-1 < index.row() && index.row() < m_items.size()) {
            switch (static_cast<role_t>(role)) {
                case role_t::arg1: return obj.price;
                case role_t::arg2: return obj.bug.weight;
            }
        }
        return {};
    }
    virtual QHash<int, QByteArray> roleNames() const {
        static QHash<int,QByteArray> roles = {
            {static_cast<int> (role_t::arg1), "arg1" },
            {static_cast<int> (role_t::arg2), "arg2" }
        };
        return roles;
    }

    Q_INVOKABLE void push() {
        emit this->beginInsertRows(QModelIndex(),m_items.size(),m_items.size());
        m_items.push_back(kp::Object1_0 <kp::Bug1>{0,0});
        emit this->endInsertRows();
    }

    Q_INVOKABLE void update(int index, int arg1, int arg2) {
        m_items[index].price = arg1;
        m_items[index].bug.weight = arg2;
    }

    Q_INVOKABLE int getResult() {
        return kp::makeTask(m_items,kp::Bug1{m_bgWeight});
    }

    Q_INVOKABLE void remove(int index) {
        if(index>=m_items.size())
            return;
        emit this->beginRemoveRows(QModelIndex(), index, index);
        m_items.erase(m_items.begin()+index);
        emit this->endRemoveRows();
    }

    int bgWeight() const {
        return m_bgWeight;
    }
    void setBgWeight(int newBgWeight) {
        m_bgWeight = newBgWeight;
        emit bgWeightChanged();
    }

    Q_INVOKABLE void reset() {
        m_items.clear();
    }

signals:
    void bgWeightChanged();

private:
    std::deque< kp::Object1_0 <kp::Bug1> > m_items;
    int m_bgWeight;
};

class MainModelUnlimited_1 : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(int bgWeight READ bgWeight WRITE setBgWeight NOTIFY bgWeightChanged)
public:
    enum class role_t {
        arg1,
        arg2
    };

    MainModelUnlimited_1(QObject *parent=nullptr) :  QAbstractListModel(parent),m_bgWeight(0){}
    virtual int rowCount(const QModelIndex &parent) const {
        return m_items.size();
    }
    Q_INVOKABLE int columnCount() {
        return 2;
    }
    virtual QVariant data(const QModelIndex &index, int role) const {
        if(!index.isValid())
           return QVariant();
        auto obj = m_items[index.row()];
        if(-1 < index.row() && index.row() < m_items.size()) {
            switch (static_cast<role_t>(role)) {
                case role_t::arg1: return obj.price;
                case role_t::arg2: return obj.bug.weight;
            }
        }
        return {};
    }
    virtual QHash<int, QByteArray> roleNames() const {
        static QHash<int,QByteArray> roles = {
            {static_cast<int> (role_t::arg1), "arg1" },
            {static_cast<int> (role_t::arg2), "arg2" }
        };
        return roles;
    }

    Q_INVOKABLE void push() {
        emit this->beginInsertRows(QModelIndex(),m_items.size(),m_items.size());
        m_items.push_back(kp::ObjectUnlimited<kp::Bug1>{0,0});
        emit this->endInsertRows();
    }

    Q_INVOKABLE void update(int index, int arg1, int arg2) {
        m_items[index].price = arg1;
        m_items[index].bug.weight = arg2;
    }

    Q_INVOKABLE int getResult() {
        return kp::makeTask(m_items,kp::Bug1{m_bgWeight});
    }

    Q_INVOKABLE void remove(int index) {
        if(index>=m_items.size())
            return;
        emit this->beginRemoveRows(QModelIndex(), index, index);
        m_items.erase(m_items.begin()+index);
        emit this->endRemoveRows();
    }

    int bgWeight() const {
        return m_bgWeight;
    }
    void setBgWeight(int newBgWeight) {
        m_bgWeight = newBgWeight;
        emit bgWeightChanged();
    }

    Q_INVOKABLE void reset() {
        m_items.clear();
    }

signals:
    void bgWeightChanged();


private:
    std::deque< kp::ObjectUnlimited <kp::Bug1> > m_items;
    int m_bgWeight;
};

class MainModelLimited_1 : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(int bgWeight READ bgWeight WRITE setBgWeight NOTIFY bgWeightChanged)
public:
    enum class role_t {
        arg1,
        arg2,
        arg3
    };

   MainModelLimited_1(QObject *parent=nullptr) :  QAbstractListModel(parent),m_bgWeight(0){}
    virtual int rowCount(const QModelIndex &parent) const {
        return m_items.size();
    }
    Q_INVOKABLE int columnCount() {
        return 3;
    }
    virtual QVariant data(const QModelIndex &index, int role) const {
        if(!index.isValid())
           return QVariant();
        auto obj = m_items[index.row()];
        if(-1 < index.row() && index.row() < m_items.size()) {
            switch (static_cast<role_t>(role)) {
                case role_t::arg1: return obj.price;
                case role_t::arg2: return obj.count;
                case role_t::arg3: return obj.bug.weight;
            }
        }
        return {};
    }
    virtual QHash<int, QByteArray> roleNames() const {
        static QHash<int,QByteArray> roles = {
            {static_cast<int> (role_t::arg1), "arg1" },
            {static_cast<int> (role_t::arg2), "arg2" },
            {static_cast<int> (role_t::arg3), "arg3" }
        };
        return roles;
    }

    Q_INVOKABLE void push() {
        emit this->beginInsertRows(QModelIndex(),m_items.size(),m_items.size());
        m_items.push_back(kp::ObjectLimited<kp::Bug1>{0,0,0});
        emit this->endInsertRows();
    }

    Q_INVOKABLE void update(int index, int arg1, int arg2, int arg3) {
        m_items[index].price = arg1;
        m_items[index].count = arg2;
        m_items[index].bug.weight = arg3;
    }

    Q_INVOKABLE int getResult() {
        return kp::makeTask(m_items,kp::Bug1{m_bgWeight});
    }

    Q_INVOKABLE void remove(int index) {
        if(index>=m_items.size())
            return;
        emit this->beginRemoveRows(QModelIndex(), index, index);
        m_items.erase(m_items.begin()+index);
        emit this->endRemoveRows();
    }

    int bgWeight() const {
        return m_bgWeight;
    }
    void setBgWeight(int newBgWeight) {
        m_bgWeight = newBgWeight;
        emit bgWeightChanged();
    }

    Q_INVOKABLE void reset() {
        m_items.clear();
    }

signals:
    void bgWeightChanged();

private:
    std::deque< kp::ObjectLimited <kp::Bug1> > m_items;
    int m_bgWeight;
};

class MainModel1_0_2 : public QAbstractListModel {
    Q_OBJECT

public:
    enum class role_t {
        arg1,
        arg2,
        arg3
    };

    MainModel1_0_2(QObject *parent=nullptr) :  QAbstractListModel(parent) {}
    virtual int rowCount(const QModelIndex &parent) const {
        return m_items.size();
    }
    Q_INVOKABLE int columnCount() {
        return 3;
    }
    virtual QVariant data(const QModelIndex &index, int role) const {
        if(!index.isValid())
           return QVariant();
        auto obj = m_items[index.row()];
        if(-1 < index.row() && index.row() < m_items.size()) {
            switch (static_cast<role_t>(role)) {
                case role_t::arg1: return obj.price;
                case role_t::arg2: return obj.bug.weight;
                case role_t::arg3: return obj.bug.size;
            }
        }
        return {};
    }
    virtual QHash<int, QByteArray> roleNames() const {
        static QHash<int,QByteArray> roles = {
            {static_cast<int> (role_t::arg1), "arg1" },
            {static_cast<int> (role_t::arg2), "arg2" },
            {static_cast<int> (role_t::arg3), "arg3" }
        };
        return roles;
    }

    Q_INVOKABLE void push() {
        emit this->beginInsertRows(QModelIndex(),m_items.size(),m_items.size());
        m_items.push_back(kp::Object1_0 <kp::Bug2>{0,0,0});
        emit this->endInsertRows();
    }

    Q_INVOKABLE void update(int index, int arg1, int arg2, int arg3) {
        m_items[index].price = arg1;
        m_items[index].bug.weight = arg2;
        m_items[index].bug.size = arg3;
    }

    Q_INVOKABLE int getResult() {
        return kp::makeTask(m_items,bg);
    }

    Q_INVOKABLE void remove(int index) {
        if(index>=m_items.size())
            return;
        emit this->beginRemoveRows(QModelIndex(), index, index);
        m_items.erase(m_items.begin()+index);
        emit this->endRemoveRows();
    }

    Q_INVOKABLE void setBg(int w, int s) {
        bg = {w,s};
    }

    Q_INVOKABLE void reset() {
        m_items.clear();
    }

signals:
    void bgWeightChanged();

private:
    std::deque< kp::Object1_0 <kp::Bug2> > m_items;
    kp::Bug2 bg;
};

class MainModelUnlimited_2 : public QAbstractListModel {
    Q_OBJECT

public:
    enum class role_t {
        arg1,
        arg2,
        arg3
    };

    MainModelUnlimited_2(QObject *parent=nullptr) :  QAbstractListModel(parent) {}
    virtual int rowCount(const QModelIndex &parent) const {
        return m_items.size();
    }
    Q_INVOKABLE int columnCount() {
        return 3;
    }
    virtual QVariant data(const QModelIndex &index, int role) const {
        if(!index.isValid())
           return QVariant();
        auto obj = m_items[index.row()];
        if(-1 < index.row() && index.row() < m_items.size()) {
            switch (static_cast<role_t>(role)) {
                case role_t::arg1: return obj.price;
                case role_t::arg2: return obj.bug.weight;
                case role_t::arg3: return obj.bug.size;
            }
        }
        return {};
    }
    virtual QHash<int, QByteArray> roleNames() const {
        static QHash<int,QByteArray> roles = {
            {static_cast<int> (role_t::arg1), "arg1" },
            {static_cast<int> (role_t::arg2), "arg2" },
            {static_cast<int> (role_t::arg3), "arg3" }
        };
        return roles;
    }

    Q_INVOKABLE void push() {
        emit this->beginInsertRows(QModelIndex(),m_items.size(),m_items.size());
        m_items.push_back(kp::ObjectUnlimited <kp::Bug2>{0,0,0});
        emit this->endInsertRows();
    }

    Q_INVOKABLE void update(int index, int arg1, int arg2, int arg3) {
        m_items[index].price = arg1;
        m_items[index].bug.weight = arg2;
        m_items[index].bug.size = arg3;
    }

    Q_INVOKABLE int getResult() {
        return kp::makeTask(m_items,bg);
    }

    Q_INVOKABLE void remove(int index) {
        if(index>=m_items.size())
            return;
        emit this->beginRemoveRows(QModelIndex(), index, index);
        m_items.erase(m_items.begin()+index);
        emit this->endRemoveRows();
    }

    Q_INVOKABLE void reset() {
        m_items.clear();
    }

    Q_INVOKABLE void setBg(int w, int s) {
        bg = {w,s};
    }

signals:
    void bgWeightChanged();

private:
    std::deque< kp::ObjectUnlimited <kp::Bug2> > m_items;
    kp::Bug2 bg;
};

class MainModelLimited_2 : public QAbstractListModel {
    Q_OBJECT

public:
    enum class role_t {
        arg1,
        arg2,
        arg3,
        arg4
    };

    MainModelLimited_2(QObject *parent=nullptr) :  QAbstractListModel(parent) {}
    virtual int rowCount(const QModelIndex &parent) const {
        return m_items.size();
    }
    Q_INVOKABLE int columnCount() {
        return 4;
    }
    virtual QVariant data(const QModelIndex &index, int role) const {
        if(!index.isValid())
           return QVariant();
        auto obj = m_items[index.row()];
        if(-1 < index.row() && index.row() < m_items.size()) {
            switch (static_cast<role_t>(role)) {
                case role_t::arg1: return obj.price;
                case role_t::arg2: return obj.count;
                case role_t::arg3: return obj.bug.weight;
                case role_t::arg4: return obj.bug.size;
            }
        }
        return {};
    }
    virtual QHash<int, QByteArray> roleNames() const {
        static QHash<int,QByteArray> roles = {
            {static_cast<int> (role_t::arg1), "arg1" },
            {static_cast<int> (role_t::arg2), "arg2" },
            {static_cast<int> (role_t::arg3), "arg3" },
            {static_cast<int> (role_t::arg4), "arg4" }
        };
        return roles;
    }

    Q_INVOKABLE void push() {
        emit this->beginInsertRows(QModelIndex(),m_items.size(),m_items.size());
        m_items.push_back(kp::ObjectLimited <kp::Bug2>{0,0,0,0});
        emit this->endInsertRows();
    }

    Q_INVOKABLE void update(int index, int arg1, int arg2, int arg3, int arg4) {
        m_items[index].price = arg1;
        m_items[index].count = arg2;
        m_items[index].bug.weight = arg3;
        m_items[index].bug.size = arg4;
    }

    Q_INVOKABLE int getResult() {
        return kp::makeTask(m_items,bg);
    }

    Q_INVOKABLE void remove(int index) {
        if(index>=m_items.size())
            return;
        emit this->beginRemoveRows(QModelIndex(), index, index);
        m_items.erase(m_items.begin()+index);
        emit this->endRemoveRows();
    }

    Q_INVOKABLE void setBg(int w, int s) {
        bg = {w,s};
    }

    Q_INVOKABLE void reset() {
        m_items.clear();
    }
signals:
    void bgWeightChanged();

private:
    std::deque< kp::ObjectLimited <kp::Bug2> > m_items;
    kp::Bug2 bg;
};
