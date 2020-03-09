#include "networkutils.h"

#include <QTcpSocket>
#include <QNetworkInterface>
#include <QHostInfo>

bool NetWorkUtils::isIP(const QString &ip)
{
    QRegExp regExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
    return regExp.exactMatch(ip);
}

bool NetWorkUtils::ipLive(const QString &ip, int port, int timeout)
{
    QTcpSocket tcpClient;
    tcpClient.abort();
    tcpClient.connectToHost(ip, port);
    //超时没有连接上则判断不在线
    return tcpClient.waitForConnected(timeout);
}

QString NetWorkUtils::getNetIP(const QString &webCode)
{
    QString web = webCode;
    web = web.replace(' ', "");
    web = web.replace("\r", "");
    web = web.replace("\n", "");
    QStringList list = web.split("<br/>");
    QString tar = list.at(3);
    QStringList ip = tar.split("=");
    return ip.at(1);
}

QString NetWorkUtils::getLocalIP()
{
    QStringList ips;
    QList<QHostAddress> addrs = QNetworkInterface::allAddresses();
    foreach (QHostAddress addr, addrs) {
        QString ip = addr.toString();
        if (isIP(ip)) {
            ips << ip;
        }
    }
    //优先取192开头的IP,如果获取不到IP则取127.0.0.1
    QString ip = "127.0.0.1";
    foreach (QString str , ips) {
        if (str.startsWith("192.168.1") || str.startsWith("192")) {
            ip = str;
            break;
        }
    }
    return ip;
}

QString NetWorkUtils::urlToIP(const QString &url)
{
    QHostInfo host = QHostInfo::fromName(url);
    return host.addresses().at(0).toString();
}

bool NetWorkUtils::isWebOk()
{
    return ipLive("140.205.94.189", 80);
}
