#pragma once

#include <QObject>
#include <QTimer>

class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int counter READ counter WRITE setCounter NOTIFY counterChanged FINAL)
public:
    explicit Backend(QObject *parent = nullptr);

    int counter();
    void setCounter(int);

signals:
    void counterChanged();

private slots:
    void onTimer();

private:
    int m_counter = 0;
    QTimer *m_timer;
};
