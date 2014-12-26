#include "servicemonitorconfiguration.h"
#include "../../qtjsonsettings/qtjsonsettings.h"
#include "exception.h"
#include "logmanager.h"

#include <QFile>

using namespace rpi;


const QString ServiceMonitorConfiguration::ServiceConfigurationPath = "ServiceMonitor/Services";
const QString ServiceMonitorConfiguration::ServiceIdConfigurationPath = "Id";
const QString ServiceMonitorConfiguration::ServiceNameConfigurationPath = "Name";
const QString ServiceMonitorConfiguration::ServiceTimeoutConfigurationPath = "Timeout";


ServiceMonitorConfiguration::ServiceMonitorConfiguration(QString const & fileName, QObject * pParent /*= NULL*/) : Configuration(fileName, pParent)
{
    if (QFile::exists(fileName))
    {
        RPI_DEBUG("rpiConfigurator", "loading file: " + fileName);
        QSharedPointer<QtJsonSettings> settings(new QtJsonSettings(fileName));
        const int count = settings->beginReadArray(ServiceConfigurationPath);
        RPI_DEBUG("rpiConfigurator", "number of services: " + QString::number(count));
        for (int i = 0; i < count; ++i)
        {
            settings->setArrayIndex(i);
            const int id = settings->value(ServiceIdConfigurationPath).toInt();
            const QString name = settings->value(ServiceNameConfigurationPath).toString();
            const unsigned int timeout = settings->value(ServiceTimeoutConfigurationPath).toUInt();
            RPI_DEBUG("rpiConfigurator", QString("loading service (%1, %2, %3)").arg(QString::number(id), name, QString::number(timeout)));
            m_Services.push_back(ServiceConfiguration(id, name, timeout));
        }
    }
}

ServiceMonitorConfiguration::ServiceConfiguration::ServiceConfiguration(int id, QString const & name, unsigned int timeout) : Id(id), Name(name), Timeout(timeout) { }

ServiceMonitorConfiguration::~ServiceMonitorConfiguration() { }

void ServiceMonitorConfiguration::addService(int id, QString const & name, unsigned int timeout)
{
    m_Services.push_back(ServiceConfiguration(id, name, timeout));
}

void ServiceMonitorConfiguration::removeService(int index)
{
    m_Services.remove(index);
}

void ServiceMonitorConfiguration::setId(int index, int value)
{
    const int size = m_Services.size();
    Q_ASSERT_X(index >= 0 && index < size, Q_FUNC_INFO, "index out of range");
    if (index >= 0 && index < size)
    {
        m_Services[index].Id = value;
        return;
    }
    THROW_EXCEPTION_DETAILED("Index out of range");
}

void ServiceMonitorConfiguration::setName(int index, QString const & value)
{
    const int size = m_Services.size();
    Q_ASSERT_X(index >= 0 && index < size, Q_FUNC_INFO, "index out of range");
    if (index >= 0 && index < size)
    {
        m_Services[index].Name = value;
        return;
    }
    THROW_EXCEPTION_DETAILED("Index out of range");
}

void ServiceMonitorConfiguration::setTimeout(int index, unsigned int value)
{
    const int size = m_Services.size();
    Q_ASSERT_X(index >= 0 && index < size, Q_FUNC_INFO, "index out of range");
    if (index >= 0 && index < size)
    {
        m_Services[index].Timeout = value;
        return;
    }
    THROW_EXCEPTION_DETAILED("Index out of range");
}

int ServiceMonitorConfiguration::id(int index) const
{
    const int size = m_Services.size();
    Q_ASSERT_X(index >= 0 && index < size, Q_FUNC_INFO, "index out of range");
    if (index >= 0 && index < size)
    {
        return m_Services[index].Id;
    }
    THROW_EXCEPTION_DETAILED("Index out of range");
}

const QString & ServiceMonitorConfiguration::name(int index) const
{
    const int size = m_Services.size();
    Q_ASSERT_X(index >= 0 && index < size, Q_FUNC_INFO, "index out of range");
    if (index >= 0 && index < size)
    {
        return m_Services[index].Name;
    }
    THROW_EXCEPTION_DETAILED("Index out of range");
}

unsigned int ServiceMonitorConfiguration::timeout(int index) const
{
    const int size = m_Services.size();
    Q_ASSERT_X(index >= 0 && index < size, Q_FUNC_INFO, "index out of range");
    if (index >= 0 && index < size)
    {
        return m_Services[index].Timeout;
    }
    THROW_EXCEPTION_DETAILED("Index out of range");
}

int ServiceMonitorConfiguration::count() const
{
    return m_Services.size();
}

const ServiceMonitorConfiguration::Services & ServiceMonitorConfiguration::serviceConfigurations() const
{
    return m_Services;
}

void ServiceMonitorConfiguration::save()
{
    QSharedPointer<QtJsonSettings> settings(new QtJsonSettings(m_ConfigurationFile));
    settings->beginWriteArray(ServiceConfigurationPath);

    int i = 0;
    for (Services::const_iterator iter = m_Services.begin(); iter != m_Services.end(); ++iter, ++i)
    {
        settings->setArrayIndex(i);
        settings->setValue(ServiceIdConfigurationPath, iter->Id);
        settings->setValue(ServiceNameConfigurationPath, iter->Name);
        settings->setValue(ServiceTimeoutConfigurationPath, iter->Timeout);
    }
}

ServiceMonitorConfiguration::ConfigurationType ServiceMonitorConfiguration::configurationType()
{
    return Configuration::ServiceMonitor;
}

