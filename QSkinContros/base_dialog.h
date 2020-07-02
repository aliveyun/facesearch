#pragma once
#include <QtWidgets/QDialog>

class base_dialog : public QDialog
{
public:
    base_dialog(QWidget *parent);
    ~base_dialog();
    void set_enable_dialog_move_with_mouse();
    void set_hide_title();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    bool m_enable_dialog_move_with_mouse;
    QPoint m_mouse_move_point;
    bool m_mouse_press;
};

