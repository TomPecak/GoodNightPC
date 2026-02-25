#pragma once

#include <QObject>
#include <QStringList>
#include <QTimer>

class Backend : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList lapList READ lapList NOTIFY lapListChanged)
    Q_PROPERTY(int counter READ counter WRITE setCounter NOTIFY counterChanged FINAL)
public:
    explicit Backend(QObject *parent = nullptr);

    int counter();
    void setCounter(int);

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();
    Q_INVOKABLE bool reset();
    Q_INVOKABLE void addLap();

    Q_INVOKABLE bool setResetTimeSec(const QString &timeStr);

    QStringList lapList() const;

signals:
    void counterChanged();
    void lapListChanged();

private slots:
    void onTimer();

private:
    QStringList m_lapList;
    int m_restartCounterValue = 30 * 60;
    int m_counter = m_restartCounterValue;
    QTimer *m_timer;
};
