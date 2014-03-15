#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "scene.h"
#include <QWidget>

class Viewport : public QWidget
{
public:
    Viewport(QWidget* parent = 0);
    void setScene(Scene* scene);
    Scene* scene() const { return _scene; }

protected:
    void paintEvent(QPaintEvent *);

private:
    Scene* _scene = 0;
};

#endif // VIEWPORT_H
