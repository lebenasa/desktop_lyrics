#ifndef FILEINFO_QMLPLUGIN_PLUGIN_H
#define FILEINFO_QMLPLUGIN_PLUGIN_H

#include <QQmlExtensionPlugin>

class Fileinfo_QmlpluginPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);
};

#endif // FILEINFO_QMLPLUGIN_PLUGIN_H

