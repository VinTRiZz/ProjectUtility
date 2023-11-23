#ifndef EXTENDEDTYPES_H
#define EXTENDEDTYPES_H

#include <atomic>
#include <mutex>
#include <map>

#include <QString>
#include <QStringList>

namespace Configuration
{

class IntSetting
{
public:
    IntSetting()        { data.store(0); }
    IntSetting(int val) { data.store(val); }

    IntSetting(const IntSetting & s) { data.store(s.data.load()); }
    IntSetting(IntSetting && s) { data.store(s.data.load()); }

    IntSetting & operator =(int newValue)
    {
        data.store(newValue);
        return *this;
    }

    IntSetting & operator =(const IntSetting newValue)
    {
        data.store(newValue.data.load());
        return *this;
    }

    operator int() const { return data.load(); }

protected:
    std::atomic<int> data;
};

class StringSetting
{
public:
    StringSetting()
    {
        this->data = QString();
    }

    StringSetting(const char * data)
    {
        mx.lock();
        this->data = data;
        mx.unlock();
    }

    StringSetting(const StringSetting & data)
    {
        mx.lock();
        this->data = data.getData();
        mx.unlock();
    }

    StringSetting(StringSetting && s)
    {
        mx.lock();
        data = s;
        mx.unlock();
    }

    StringSetting & operator =(const QString & data)
    {
        mx.lock();
        this->data = data;
        mx.unlock();
        return *this;
    }

    StringSetting & operator =(StringSetting & data)
    {
        mx.lock();
        this->data = data;
        mx.unlock();
        return *this;
    }

    StringSetting & operator =(const StringSetting & data)
    {
        mx.lock();
        this->data = data.data;
        mx.unlock();
        return *this;
    }

    StringSetting & operator =(const char * data)
    {
        mx.lock();
        this->data = data;
        mx.unlock();
        return *this;
    }

    StringSetting & operator +=(const QString data)
    {
        mx.lock();
        this->data = data;
        mx.unlock();
        return *this;
    }

    StringSetting & operator +=(const char * data)
    {
        mx.lock();
        this->data = data;
        mx.unlock();
        return *this;
    }

    bool operator ==(const QString & other)
    {
        mx.lock();
        bool result = data == other;
        mx.unlock();
        return result;
    }

    operator QString()
    {
        QString result;
        mx.lock();
        result = data;
        mx.unlock();
        return data;
    }

    bool isEmpty()
    {
        bool result;
        mx.lock();
        result = data.isEmpty();
        mx.unlock();
        return result;
    }

    QByteArray toUtf8() const
    {
        QByteArray result;
        mx.lock();
        result = data.toUtf8();
        mx.unlock();
        return result;
    }

    QStringList toList() const
    {
        std::string buffer = getData().toUtf8().data();
        QStringList result;

        std::string::iterator spacePosBegin = buffer.begin(), spacePosEnd = buffer.end();

        while (spacePosBegin != buffer.end())
        {
            spacePosEnd = std::find(spacePosBegin, buffer.end(), ' ');

            result << QString::fromStdString(std::string(spacePosBegin, spacePosEnd));

            if (spacePosEnd == buffer.end()) // Not found spaces
                break;
            spacePosBegin = spacePosEnd + 1;
        }
        return result;
    }

private:
    QString data;
    mutable std::mutex mx;

    QString getData() const
    {
        QString result;
        mx.lock();
        result = data;
        mx.unlock();
        return data;
    }
};

}

#endif // EXTENDEDTYPES_H
