#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <memory>

#include <QtCore>
#include <QtGui>
#include <QtQml>

class AppSettings : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AppSettings)

public:
    AppSettings(QObject* parent = nullptr);

    static QObject* qmlInstance(QQmlEngine* engine, QJSEngine* scriptEngine);

public slots:
    QVariant read(const QString& name, const QVariant& defval);
    int readInt(const QString& name, int defval);
    double readDouble(const QString& name, double defval);
    QString readString(const QString& name, const QString& defval);
    QSizeF readSize(const QString& name, const QSizeF& defval);
    QPointF readPoint(const QString& name, const QPointF& defval);
    QRectF readRect(const QString& name, const QRectF& defval);
    bool readBool(const QString& name, bool defval);

    void saveSettings(const QString& name, const QVariant& val);
    void eraseSettings(const QString& name);

    QString readShortcut(const QString& command, const QString& defkey);
    void saveShortcut(const QString& command, const QString& key);
    QString keyCodeToString(int key);

    void resetShortcut(const QString& command);
    void resetAllShortcut();

signals:
    void settingsChanged();
    void shortcutUpdated();

private:
    std::unique_ptr<QSettings> setting;

private slots:
    void initSettings();
};

#endif // APPSETTINGS_H
