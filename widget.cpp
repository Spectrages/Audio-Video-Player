#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QDir>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_playListModel = new QStandardItemModel(this);
    ui->playlistView->setModel(m_playListModel);
    m_playListModel->setHorizontalHeaderLabels(QStringList() << tr("Audio/Video Track") << tr("File Path"));
    ui->playlistView->hideColumn(1);
    ui->playlistView->verticalHeader()->setVisible(false);
    ui->playlistView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->playlistView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->playlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->playlistView->horizontalHeader()->setStretchLastSection(true);

    volumeSlider = new QSlider(Qt::Vertical);

    m_player = new QMediaPlayer(this);
    m_playlist = new QMediaPlaylist(m_player);
    m_player->setPlaylist(m_playlist);
    m_playlist->setPlaybackMode(QMediaPlaylist::Loop);
    videoWidget = new QVideoWidget;
    ui->volumeSlider->setValue(50);
    connect(ui->volumeSlider, SIGNAL(valueChanged(int)), m_player, SLOT(setVolume(int)));
    connect(ui->btn_previous, &QToolButton::clicked, m_playlist, &QMediaPlaylist::previous);
    connect(ui->btn_next, &QToolButton::clicked, m_playlist, &QMediaPlaylist::next);
    connect(ui->btn_play, &QToolButton::clicked, m_player, &QMediaPlayer::play);
    connect(ui->btn_pause, &QToolButton::clicked, m_player, &QMediaPlayer::pause);
    connect(ui->btn_stop, &QToolButton::clicked, m_player, &QMediaPlayer::stop);

    connect(ui->playlistView, &QTableView::doubleClicked, [this](const QModelIndex &index){
        m_playlist->setCurrentIndex(index.row());
    });

    connect(m_playlist, &QMediaPlaylist::currentIndexChanged, [this](int index) {
        ui->currentTrack->setText(m_playListModel->data(m_playListModel->index(index,0)).toString());
    });
}
Widget::~Widget()
{
    delete ui;
    delete m_playListModel;
    delete m_playlist;
    delete m_player;
    delete videoWidget;
}

int Widget::volume() const
{
    return volumeSlider->value();
}

void Widget::setVolume(int volume)
{
    return m_player->setVolume(volume);
}

void Widget::on_btn_add_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Open files"), QString(), tr("Audio/Video files (*.mp3 *.mp4 *.mid *.midi)"));
    foreach (QString filePath, files)
    {
        QList<QStandardItem*> items;
        items.append(new QStandardItem(QDir(filePath).dirName()));
        items.append(new QStandardItem(filePath));
        m_playListModel->appendRow(items);
        m_playlist->addMedia(QUrl("file://" + filePath));
        m_player->setVideoOutput(videoWidget);
        videoWidget->show();
        videoWidget->resize(700, 500);
        m_playlist->setCurrentIndex(1);
        m_player->play();
    }
}








