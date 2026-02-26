#pragma once

#include <QObject>
#include <QStringList>
#include <QTimer>

class Backend : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList lapList READ lapList NOTIFY lapListChanged)
    Q_PROPERTY(int counter READ counter WRITE setCounter NOTIFY counterChanged FINAL)
    Q_PROPERTY(float percent READ percent NOTIFY percentChanged FINAL)
public:
    explicit Backend(QObject *parent = nullptr);

    int counter();
    void setCounter(int);

    float percent();

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();
    Q_INVOKABLE bool reset();
    Q_INVOKABLE void addLap();

    Q_INVOKABLE bool setResetTimeSec(const QString &timeStr);

    QStringList lapList() const;

signals:
    void counterChanged();
    void lapListChanged();
    void percentChanged();

private slots:
    void onTimer();

private:
    void updatePercent();
    void setPercent(float);

private:
    QStringList m_lapList;
    int m_restartCounterValue = 30 * 60;
    int m_counter = m_restartCounterValue;
    float m_percent = 50.0f;
    QTimer *m_timer;
};
