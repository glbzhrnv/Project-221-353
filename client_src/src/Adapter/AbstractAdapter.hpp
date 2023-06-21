#ifndef ABSTRACTADAPTER_HPP
#define ABSTRACTADAPTER_HPP

#include <QObject>

class AbstractAdapter: public QObject
{
    Q_OBJECT
public:
    AbstractAdapter(QWidget *parent = nullptr);

    ~AbstractAdapter();
};

#endif // ABSTRACTADAPTER_HPP
