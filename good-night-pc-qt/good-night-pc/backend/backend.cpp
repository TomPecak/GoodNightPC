#include "backend.h"

#include <QDebug>

Backend::Backend(QObject *parent)
    : QObject(parent)
{
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &Backend::onTimer);
}

void Backend::onTimer()
{
    setCounter(counter() - 1);
}

int Backend::counter()
{
    return m_counter;
}

void Backend::setCounter(int counter)
{
    if (m_counter == counter)
        return;

    m_counter = counter;
    emit counterChanged();
}

void Backend::start()
{
    if (m_timer) {
        m_timer->start(1000);
    }
}

void Backend::stop()
{
    if (m_timer) {
        m_timer->stop();
    }
}

void Backend::reset()
{
    setCounter(m_restartCounterValue);
    m_lapList.clear();
    emit lapListChanged();
}

void Backend::addLap()
{
    m_lapList << QString::number(m_counter);
    emit lapListChanged();
}

bool Backend::setResetTimeSec(const QString &timeStr)
{
    qDebug() << __PRETTY_FUNCTION__;
    bool ok;
    int parsedValue = timeStr.toInt(&ok);

    if (ok) {
        m_restartCounterValue = parsedValue;
        return true;
    }

    // Jeśli tekst nie był poprawną liczbą (ok == false), zwracamy błąd
    return false;
}

QStringList Backend::lapList() const
{
    return m_lapList;
}
