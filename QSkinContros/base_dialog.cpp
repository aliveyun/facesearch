#include "base_dialog.h"
#include <QtGui>

base_dialog::base_dialog(QWidget *parent)
    : QDialog(parent)
    , m_enable_dialog_move_with_mouse(false)
    , m_mouse_press(false)
{
}

base_dialog::~base_dialog()
{
}

void base_dialog::set_enable_dialog_move_with_mouse()
{
    m_enable_dialog_move_with_mouse = true;
}

void base_dialog::set_hide_title()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
}

void base_dialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_mouse_press = true;
    }
    m_mouse_move_point = event->globalPos() - this->pos();
    QDialog::mousePressEvent(event);
}

void base_dialog::mouseReleaseEvent(QMouseEvent *event)
{
    m_mouse_press = false;
    QDialog::mouseReleaseEvent(event);
}

void base_dialog::mouseMoveEvent(QMouseEvent *event)
{
    if (m_mouse_press && m_enable_dialog_move_with_mouse)
    {
        QPoint move_pos = event->globalPos();
        move(move_pos - m_mouse_move_point);
    }
    QDialog::mouseMoveEvent(event);
}
