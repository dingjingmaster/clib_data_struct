#ifndef STYLEWINDOW_H
#define STYLEWINDOW_H

#include <QWidget>

class StyleWindow : public QWidget
{
    Q_OBJECT

public:
    StyleWindow(QWidget *parent = nullptr);
    ~StyleWindow();
};
#endif // STYLEWINDOW_H
