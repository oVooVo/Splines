#include "undohandler.h"
#include <QDebug>
#include "Managers/manager.h"
#include "mainwindow.h"

UndoHandler::UndoHandler(QObject *parent) : QObject(parent)
{
}

QByteArray saveScene(const Scene* scene)
{
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly);
    stream << scene;
    return array;
}

Scene* readScene(QByteArray array)
{
    Scene* s;
    QDataStream stream(&array, QIODevice::ReadOnly);
    stream >> s;
    return s;
}

void UndoHandler::takeSnapshot()
{
    if (!_currentScene) return;

    clearRedos();
    _undoStack.push(saveScene(_currentScene));
    emit canUndo(true);
}

void UndoHandler::setScene(Scene* scene)
{
    if (_currentScene == scene) return;

    _currentScene = scene;
    _currentScene->setUndoHandler(this);
    clearRedos();
    clearUndos();

    if (_currentScene) {
        takeSnapshot();
    }
}

void UndoHandler::undo()
{
    if (_undoStack.isEmpty()) return;

    _redoStack.push(saveScene(_currentScene));
    emit canRedo(true);

    _currentScene = readScene(_undoStack.pop());
    _currentScene->setUndoHandler(this);

    emit currentSceneChanged(_currentScene);

    if (_undoStack.isEmpty())
        emit canUndo(false);
}

void UndoHandler::redo()
{
    if (_redoStack.isEmpty()) return;

    _undoStack.push(saveScene(_currentScene));
    emit canUndo(true);

    //QString tool = _currentScene->tool()->metaObject()->className();
    _currentScene = readScene(_redoStack.pop());
    _currentScene->setUndoHandler(this);
    //_currentScene->setTool(Tool::createInstance(tool));

    emit currentSceneChanged(_currentScene);

    if (_redoStack.isEmpty())
        emit canRedo(false);
}

void UndoHandler::clearRedos()
{
    if (_redoStack.isEmpty()) return;

    _redoStack.clear();
    emit canRedo(false);
}

void UndoHandler::clearUndos()
{
    if (_undoStack.isEmpty()) return;

    _undoStack.clear();
    emit canUndo(false);
}

void UndoHandler::discardLastSnapshot()
{
    if (_undoStack.isEmpty()) return;

    _undoStack.pop();
    emit canUndo(_undoStack.isEmpty());
}
