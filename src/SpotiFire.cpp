#include "SpotiFire.hpp"
#include <QDBusArgument>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QTimer>
#include <QThread>

SpotiFire::SpotiFire(QObject* parent) :
	QObject(parent)
{
	QDBusConnection dbus = QDBusConnection::sessionBus();

	updateSongDuration();

	dbus.connect(SPOTIFY_SERVICE, MPRIS_PATH, DBUS_INTERFACE, "PropertiesChanged", this, SLOT(songChanged(QDBusMessage)));
	dbus.connect(SPOTIFY_SERVICE, MPRIS_PATH, MPRIS_PLAYER, "Seeked", this, SLOT(positionChanged(QDBusMessage)));

    progressTimer = new QTimer(this);
    progressTimer->setInterval(1000);
    connect(progressTimer, &QTimer::timeout, this, [this] {
		updateSpotifyProgress(getSpotifyProgress());
	});
    progressTimer->start();
}

SpotiFire::~SpotiFire()
{
	progressTimer->stop();
}

uint64_t SpotiFire::getSpotifyProgress()
{
	QDBusInterface iface(SPOTIFY_SERVICE, MPRIS_PATH, DBUS_INTERFACE);
	QDBusMessage result = iface.call("Get", MPRIS_PLAYER, "Position");
	return result.arguments().at(0).value<QDBusVariant>().variant().toULongLong();
}

void SpotiFire::updateSpotifyProgress(uint64_t progress)
{
	QDBusMessage signal = QDBusMessage::createSignal(MPRIS_PATH, "com.canonical.Unity.LauncherEntry", "Update");

	signal << "application://spotify.desktop";

	QVariantMap setProperty;

	double progressBar = (double) progress / songDuration;
	setProperty.insert("progress", progressBar);
	setProperty.insert("progress-visible", true);

	signal << setProperty;

	QDBusConnection::sessionBus().send(signal);
}

void SpotiFire::songChanged(QDBusMessage msg)
{
	const QDBusArgument& arg = msg.arguments().at(1).value<QDBusArgument>();
	arg.beginMap();

	QString key;

	while (!arg.atEnd())
	{
		arg.beginMapEntry();
		arg >> key;

		if (key == "Metadata")
		{
			updateSongDuration();
			arg.endMapEntry();
			break;
		}
		arg.endMapEntry();
	}
	arg.endMap();
}

void SpotiFire::positionChanged(QDBusMessage msg)
{
    uint64_t newPosition = msg.arguments().at(0).value<qint64>();
    updateSpotifyProgress(newPosition);
}

void SpotiFire::updateSongDuration()
{
	QDBusInterface iface(SPOTIFY_SERVICE, MPRIS_PATH, DBUS_INTERFACE);
	QDBusMessage result = iface.call("Get", MPRIS_PLAYER, "Metadata");
	const QDBusArgument& arg = result.arguments().at(0).value<QDBusVariant>().variant().value<QDBusArgument>();

	arg.beginMap();
	while (!arg.atEnd())
	{
		QVariant var;
		QString str;
		arg.beginMapEntry();
		arg >> str >> var;
		if (str == "mpris:length")
		{
			songDuration = var.toULongLong();
			arg.endMapEntry();
			break;
		}
		arg.endMapEntry();
	}
	arg.endMap();
}
