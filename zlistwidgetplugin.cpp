#include "zlistwidget.h"
#include "zlistwidgetplugin.h"

#include <QtPlugin>

ZListWidgetPlugin::ZListWidgetPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void ZListWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ZListWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ZListWidgetPlugin::createWidget(QWidget *parent)
{
    return new ZListWidget(parent);
}

QString ZListWidgetPlugin::name() const
{
    return QLatin1String("ZListWidget");
}

QString ZListWidgetPlugin::group() const
{
    return QLatin1String("");
}

QIcon ZListWidgetPlugin::icon() const
{
    return QIcon();
}

QString ZListWidgetPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ZListWidgetPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ZListWidgetPlugin::isContainer() const
{
    return false;
}

QString ZListWidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ZListWidget\" name=\"zListWidget\">\n</widget>\n");
}

QString ZListWidgetPlugin::includeFile() const
{
    return QLatin1String("zlistwidget.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(zlistwidgetplugin, ZListWidgetPlugin)
#endif // QT_VERSION < 0x050000
