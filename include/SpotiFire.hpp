#pragma once

#include <QObject>
#include <QDBusMessage>

class SpotiFire : public QObject
{
    Q_OBJECT

public:
    uint64_t songDuration;

    SpotiFire(QObject *parent);
    virtual ~SpotiFire();

public Q_SLOTS:
    void songChanged(QDBusMessage msg);

private:
    uint64_t getSpotifyProgress();
    void updateSpotifyProgress(uint64_t position);
    void updateSongDuration();

    const QString &SPOTIFY_SERVICE = "org.mpris.MediaPlayer2.spotify";
    const QString &MPRIS_PATH = "/org/mpris/MediaPlayer2";
    const QString &DBUS_INTERFACE = "org.freedesktop.DBus.Properties";
    const QString &MPRIS_PLAYER = "org.mpris.MediaPlayer2.Player";
};
