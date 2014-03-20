#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QHash>
#include "Objects/object.h"
#include "Objects/root.h"
#include <QQueue>
#include <QAbstractItemModel>
#include <QDataStream>
#include <QItemSelectionModel>
#include "interaction.h"
#include "Tools/tool.h"

class Scene : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit Scene(Root* root = new Root());
public:
    ~Scene();

    //------------
    // Add or remove Objects
    //------------
public:
    void addObject(Object* o);
    void removeObject(QModelIndex index);
    Object* root() const { return _root; }
private:
    Root* _root;
    quint64 _objectCounter = 0;
    QQueue<quint64> _freeIds;
    quint64 requestId();
    QHash<quint64, Object*> _objects;

    //------------
    // drawing
    //------------
public:
    void draw(QPainter &painter);
signals:
    void changed();

    //------------
    // Tree Model
    //------------
protected:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole);
    bool removeRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex());
    void insertRow(int position, const QModelIndex &parent, Object* object);
    void insertRows(int position, const QModelIndex &parent, QList<Object*> objects);
public:
    Object *getObject(const QModelIndex &index) const;

    //-----------
    // Drag & Drop
    //-----------
public:
    Qt::DropActions supportedDropActions() const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QStringList mimeTypes() const;
    QMimeData* mimeData(const QModelIndexList &indexes) const;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
private:
    static QList<QModelIndex> _draggedObjects;

    //-------------
    // interaction
    //-------------
public:
    void processInteraction(const Interaction &interaction);
    void setTool(Tool* tool = 0);
private:
    Tool* _tool = 0;


    //--------------
    // selection model
    //--------------
public:
    QItemSelectionModel* selectionModel() const { return _selectionModel; }
    QList<Object*> selectedObjects() const;
private:
    QItemSelectionModel* _selectionModel = 0;


private:
    static void serializeHeader(QDataStream &out);
    static bool deserializeHeader(QDataStream &in);
    friend QDataStream& operator<<(QDataStream& out, const Scene* s);
    friend QDataStream& operator>>(QDataStream& in, Scene* &s);




};

QDataStream& operator<<(QDataStream& out, const Scene* s);
QDataStream& operator>>(QDataStream& in, Scene* &s);

#endif // SCENE_H
