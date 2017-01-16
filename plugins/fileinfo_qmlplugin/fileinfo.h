#ifndef FILEINFO_H
#define FILEINFO_H

#include <QObject>
#include <QUrl>
#include <QString>
#include <QSize>
#include <QQmlEngine>
#include <QJSEngine>
#include <QStandardPaths>
#include <QImage>

class FileInfo : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(FileInfo)

public:
    FileInfo(QObject *parent = 0);
    ~FileInfo();

    static QObject* qmlInstance(QQmlEngine* engine, QJSEngine* scriptEngine);

    enum StandardLocation {
        DesktopLocation,
        DocumentsLocation,
        FontsLocation,
        ApplicationsLocation,
        MusicLocation,
        MoviesLocation,
        PicturesLocation,
        TempLocation,
        HomeLocation,
        DataLocation,
        CacheLocation,
        GenericDataLocation,
        RuntimeLocation,
        ConfigLocation,
        DownloadLocation,
        GenericCacheLocation,
        GenericConfigLocation,
        AppDataLocation,
        AppConfigLocation,
        AppLocalDataLocation = DataLocation
    };
    Q_ENUM(StandardLocation)

public slots:
    QUrl fromLocalFile(const QString& localFile);
    QString toLocalFile(const QUrl& localFile);

    QUrl currentPath();
    QUrl homePath();
    QUrl rootPath();
    QUrl tempPath();

    QUrl filePath(const QUrl& file);
    QString fileName(const QUrl& file);
    QString completeBaseName(const QUrl& file);
    QString completeSuffix(const QUrl& file);
    QString baseName(const QUrl& file);
    QString suffix(const QUrl& file);

    bool exists(const QUrl& file);
    bool remove(const QUrl& file);
    bool copy(const QUrl& file, const QUrl& target);
    bool rename(const QUrl& file, const QUrl& target);

    bool mkdir(const QUrl& path);
    bool rmdir(const QUrl& path);

    QSize imageSize(const QUrl& imagePath);

    QString displayName(StandardLocation type);
    QStringList standardLocations(StandardLocation type);
    QString writableLocation(StandardLocation type);

    bool saveImageAs(const QUrl& source, const QUrl& target, int compression);
};

#endif // FILEINFO_H

