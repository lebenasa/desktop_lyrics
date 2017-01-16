#include "fileinfo_qmlplugin_plugin.h"
#include "fileinfo.h"

#include <qqml.h>

void Fileinfo_QmlpluginPlugin::registerTypes(const char *uri)
{
    // @uri com.leben.fileinfo
    qmlRegisterSingletonType<FileInfo>(uri, 1, 0, "FileInfo", &FileInfo::qmlInstance);
}


