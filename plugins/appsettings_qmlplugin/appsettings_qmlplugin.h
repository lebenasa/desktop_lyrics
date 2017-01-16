#ifndef APPSETTINGS_QMLPLUGIN_H
#define APPSETTINGS_QMLPLUGIN_H

#include <QQmlExtensionPlugin>

class AppSettings_QmlPlugin: public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);
};

#endif // APPSETTINGS_QMLPLUGIN_H
