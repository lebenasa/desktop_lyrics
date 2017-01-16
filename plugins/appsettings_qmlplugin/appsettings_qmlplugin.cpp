#include "appsettings_qmlplugin.h"
#include "appsettings.h"

#include <qqml.h>

void AppSettings_QmlPlugin::registerTypes(const char *uri)
{
    // @uri com.leben.appsettings
    qmlRegisterSingletonType<AppSettings>(uri, 1, 0, "AppSettings", &AppSettings::qmlInstance);
}
