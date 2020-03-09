#ifndef CHECKUTILS_H
#define CHECKUTILS_H

#include <QObject>

class CheckUtils : public QObject
{
    Q_OBJECT
public:
    //判断是否是IP地址
    static bool isIP(const QString &ip);

    //判断是否是MAC地址
    static bool isMac(const QString &mac);

    //判断是否是合法的电话号码
    static bool isTel(const QString &tel);

    //判断是否是合法的邮箱地址
    static bool isEmail(const QString &email);

    //异或加密算法
    static QString getXorEncryptDecrypt(const QString &str, char key);

    //异或校验
    static uchar getOrCode(const QByteArray &data);

    //计算校验码
    static uchar getCheckCode(const QByteArray &data);

    //CRC校验
    static quint16 getRevCrc_16(quint8 *data, int len, quint16 init, const quint16 *table);
    static quint16 getCrc_16(quint8 *data, int len, quint16 init, const quint16 *table);
    //Modbus CRC16校验：
    static quint16 getModbus16(quint8 *data, int len);
    static QByteArray getCRCCode(const QByteArray &data);
};

#endif // CHECKUTILS_H
