#ifndef NETWORKUTILS_H
#define NETWORKUTILS_H

#include <QObject>

class NetWorkUtils : public QObject
{
    Q_OBJECT
public:
    //判断是否是IP地址
    static bool isIP(const QString &ip);

    //判断IP地址及端口是否在线
    static bool ipLive(const QString &ip, int port, int timeout = 1000);

    //获取本机公网IP地址
    static QString getNetIP(const QString &webCode);

    //获取本机IP
    static QString getLocalIP();

    //Url地址转为IP地址
    static QString urlToIP(const QString &url);

    //判断是否通外网
    static bool isWebOk();
};

#endif // NETWORKUTILS_H
