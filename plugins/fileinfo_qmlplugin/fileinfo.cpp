#include "fileinfo.h"

#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QImage>

FileInfo::FileInfo(QObject *parent)
    : QObject{ parent }
{
}

FileInfo::~FileInfo()
{
}

QUrl FileInfo::fromLocalFile(const QString &localFile)
{
    return QUrl::fromLocalFile(localFile);
}

QString FileInfo::toLocalFile(const QUrl &localFile)
{
    return localFile.toLocalFile();
}

QUrl FileInfo::currentPath()
{
    return QUrl::fromLocalFile(QDir::currentPath());
}

QUrl FileInfo::homePath()
{
    return QUrl::fromLocalFile(QDir::homePath());
}

QUrl FileInfo::rootPath()
{
    return QUrl::fromLocalFile(QDir::rootPath());
}

QUrl FileInfo::tempPath()
{
    return QUrl::fromLocalFile(QDir::tempPath());
}

QUrl FileInfo::filePath(const QUrl &file)
{
    QFileInfo fi{ file.toLocalFile() };
    return QUrl::fromLocalFile(fi.absolutePath());
}

QString FileInfo::fileName(const QUrl &file)
{
    QFileInfo fi{ file.toLocalFile() };
    return fi.fileName();
}

QString FileInfo::completeBaseName(const QUrl &file)
{
    QFileInfo fi{ file.toLocalFile() };
    return fi.completeBaseName();
}

QString FileInfo::completeSuffix(const QUrl &file)
{
    QFileInfo fi{ file.toLocalFile() };
    return fi.completeSuffix();
}

QString FileInfo::baseName(const QUrl &file)
{
    QFileInfo fi{ file.toLocalFile() };
    return fi.baseName();
}

QString FileInfo::suffix(const QUrl &file)
{
    QFileInfo fi{ file.toLocalFile() };
    return fi.suffix();
}
bool FileInfo::exists(const QUrl &file)
{
    return QFileInfo::exists(file.toLocalFile());
}

bool FileInfo::remove(const QUrl &file)
{
    return QFile::remove(file.toLocalFile());
}

bool FileInfo::copy(const QUrl &file, const QUrl &target)
{
    return QFile::copy(file.toLocalFile(), target.toLocalFile());
}

bool FileInfo::rename(const QUrl &file, const QUrl &target)
{
    return QFile::rename(file.toLocalFile(), target.toLocalFile());
}

bool FileInfo::mkdir(const QUrl &path)
{
    return QDir{}.mkpath(path.toLocalFile());
}

bool FileInfo::rmdir(const QUrl &path) {
    return QDir{}.rmpath(path.toLocalFile());
}

QSize FileInfo::imageSize(const QUrl &imagePath)
{
    return QImage(imagePath.toLocalFile()).size();
}

QString FileInfo::displayName(StandardLocation type)
{
    return QStandardPaths::displayName(static_cast<QStandardPaths::StandardLocation>(type));
}

QStringList FileInfo::standardLocations(StandardLocation type)
{
    return QStandardPaths::standardLocations(static_cast<QStandardPaths::StandardLocation>(type));
}

QString FileInfo::writableLocation(StandardLocation type)
{
    return QStandardPaths::writableLocation(static_cast<QStandardPaths::StandardLocation>(type));
}

bool FileInfo::saveImageAs(const QUrl &source, const QUrl &target, int compression)
{
    QImage src( source.toLocalFile() );
    return src.save(target.toLocalFile(), 0, compression);
}

QObject* FileInfo::qmlInstance(QQmlEngine* engine, QJSEngine* scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new FileInfo;
}













