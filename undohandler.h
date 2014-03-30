#ifndef UNDOHANDLER_H
#define UNDOHANDLER_H

#include <QStack>
#include <QByteArray>
#include <QDataStream>
#include "scene.h"

class MainWindow;

class UndoHandler : public QObject
{
    Q_OBJECT
public:
    UndoHandler(QObject* parent = 0);
    void setScene(Scene* scene);
    Scene* scene() const { return _currentScene; }
    void clearUndos();
    void clearRedos();


public slots:
    void undo();
    void redo();
    void takeSnapshot();

signals:
    void canUndo(bool);
    void canRedo(bool);
    void currentSceneChanged(Scene* scene);

private:
    QByteArray _undoBuffer;     // when undo, the last snapshot will be restored, not the current!
    QStack<QByteArray> _undoStack;
    QStack<QByteArray> _redoStack;
    Scene* _currentScene = 0;

};

#endif // UNDOHANDLER_H
