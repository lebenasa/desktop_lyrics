#include "appsettings.h"
using namespace std;

AppSettings::AppSettings(QObject *parent)
    : QObject{ parent }
{
    connect(qApp, &QCoreApplication::applicationNameChanged, this, &AppSettings::initSettings);
    connect(qApp, &QCoreApplication::organizationNameChanged, this, &AppSettings::initSettings);
    initSettings();
}

void AppSettings::initSettings()
{
    setting.reset(new QSettings{ QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), qApp->organizationName(), this });
}

QObject* AppSettings::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    return new AppSettings;
}

QVariant AppSettings::read(const QString &name, const QVariant &defval)
{
    auto val = setting->value(name, defval);
    return val;
}

int AppSettings::readInt(const QString &name, int defval) {
    int val = setting->value(name, defval).toInt();
    return val;
}

double AppSettings::readDouble(const QString &name, double defval) {
    double val = setting->value(name, defval).toDouble();
    return val;
}

QString AppSettings::readString(const QString &name, const QString &defval) {
    QString val = setting->value(name, defval).toString();
    return val;
}

QSizeF AppSettings::readSize(const QString &name, const QSizeF &defval) {
    QSizeF val = setting->value(name, defval).toSizeF();
    return val;
}

QPointF AppSettings::readPoint(const QString &name, const QPointF &defval) {
    QPointF val = setting->value(name, defval).toPointF();
    return val;
}

QRectF AppSettings::readRect(const QString& name, const QRectF& defval)
{
    auto val = setting->value(name, defval).toRectF();
    return val;
}

bool AppSettings::readBool(const QString &name, bool defval) {
    bool val = setting->value(name, defval).toBool();
    return val;
}

void AppSettings::saveSettings(const QString &name, const QVariant &val) {
    setting->setValue(name, val);
    emit settingsChanged();
}

void AppSettings::eraseSettings(const QString &name) {
    setting->remove(name);
    emit settingsChanged();
}

QString AppSettings::readShortcut(const QString &command, const QString& defkey) {
    setting->beginGroup("Shortcuts");
    auto key = readString(command, defkey);
    setting->endGroup();
    return key;
}

void AppSettings::saveShortcut(const QString &command, const QString &key) {
    setting->beginGroup("Shortcuts");
    saveSettings(command, key);
    setting->endGroup();
    emit shortcutUpdated();
}

QString AppSettings::keyCodeToString(int key) {
    QKeySequence seq(key);
//    qDebug() << seq.toString();
    return seq.toString();
}

void AppSettings::resetShortcut(const QString &command) {
    setting->beginGroup("Shortcuts");
    setting->remove(command);
    setting->endGroup();
    emit shortcutUpdated();
}

void AppSettings::resetAllShortcut() {
    setting->beginGroup("Shortcuts");
    setting->remove("");
    setting->endGroup();
    emit shortcutUpdated();
}
