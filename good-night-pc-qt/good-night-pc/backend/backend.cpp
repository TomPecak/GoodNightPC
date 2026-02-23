#include "backend.h"

Backend::Backend(QObject *parent)
    : QObject(parent)
{
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &Backend::onTimer);
    m_timer->start(16);
}

void Backend::onTimer()
{
    setCounter(counter() + 1);
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
