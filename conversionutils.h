#ifndef NUMBERCONVERSIONUTILS_H
#define NUMBERCONVERSIONUTILS_H

#include <QObject>

class ConversionUtils : public QObject
{
    Q_OBJECT
public:
    //16进制字符串转10进制
    static int strHexToDecimal(const QString &strHex);

    //10进制字符串转10进制
    static int strDecimalToDecimal(const QString &strDecimal);

    //2进制字符串转10进制
    static int strBinToDecimal(const QString &strBin);

    //16进制字符串转2进制字符串
    static QString strHexToStrBin(const QString &strHex);

    //10进制转2进制字符串一个字节
    static QString decimalToStrBin8(int decimal);

    //10进制转2进制字符串两个字节
    static QString decimalToStrBin16(int decimal);

    //10进制转16进制字符串,补零.
    static QString decimalToStrHex(int decimal);


    //int转字节数组
    static QByteArray intToByte(int i);
    static QByteArray intToByteRec(int i);

    //字节数组转int
    static int byteToInt(const QByteArray &data);
    static int byteToIntRec(const QByteArray &data);
    static quint32 byteToUInt(const QByteArray &data);
    static quint32 byteToUIntRec(const QByteArray &data);

    //ushort转字节数组
    static QByteArray ushortToByte(ushort i);
    static QByteArray ushortToByteRec(ushort i);

    //字节数组转ushort
    static int byteToUShort(const QByteArray &data);
    static int byteToUShortRec(const QByteArray &data);

    //字节数组转Ascii字符串
    static QString byteArrayToAsciiStr(const QByteArray &data);

    //16进制字符串转字节数组
    static QByteArray hexStrToByteArray(const QString &str);
    static char convertHexChar(char ch);

    //Ascii字符串转字节数组
    static QByteArray asciiStrToByteArray(const QString &str);

    //字节数组转16进制字符串
    static QString byteArrayToHexStr(const QByteArray &data);
};

#endif // NUMBERCONVERSIONUTILS_H
