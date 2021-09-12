#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QtMultimedia>
#include <QVideoWidget>
#include <QSlider>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_btn_add_clicked();

private:
    Ui::Widget *ui;
    QStandardItemModel  *m_playListModel;
    QMediaPlayer        *m_player;
    QMediaPlaylist      *m_playlist;
    QVideoWidget        *videoWidget;
    QSlider             *volumeSlider;
public:
    int volume() const;
    void setVolume(int volume);
};


#endif // WIDGET_H
