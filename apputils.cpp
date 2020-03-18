#include "apputils.h"
#include <QSettings>
#include <QFile>
#include <QApplication>
#include <QDesktopWidget>
#include <QTime>
#include <QTranslator>
#include <QTextCodec>
#include <QProcess>

//代码中所用到的字段尽量写成全局变量，放置后期更改
static const QString INI_SQL_CONFIG = "SqlConfig";
static const QString INI_SQL_CONFIG_USERNAME = "username";
static const QString INI_SQL_CONFIG_PASSWORD = "password";

QString AppUtils::configFile = "config.ini";
QString AppUtils::username = "administrator";
QString AppUtils::password = "123123";

#ifdef __arm__
#ifdef Q_OS_ANDROID
QString AppUtils::fontName = "Droid Sans Fallback";
int AppUtils::fontSize = 15;
#else
QString AppUtils::fontName = "WenQuanYi Micro Hei";
int AppUtils::fontSize = 18;
#endif
#else
QString AppUtils::fontName = "Microsoft Yahei";
int AppUtils::fontSize = 12;
#endif

void AppUtils::setConfigFile(const QString &value)
{
    configFile = value;
}

void AppUtils::readConfig()
{
    if (!checkConfig()) {
        return;
    }

    QSettings settings(AppUtils::configFile, QSettings::IniFormat);

    settings.beginGroup(INI_SQL_CONFIG);
    AppUtils::username = settings.value(INI_SQL_CONFIG_USERNAME).toString();
    AppUtils::password = settings.value(INI_SQL_CONFIG_PASSWORD).toString();
    settings.endGroup();
}

void AppUtils::writeConfig()
{
    //参数 QSettings::IniFormat：代表读取的是 ini 文件，默认是注册表
    QSettings settings(AppUtils::configFile, QSettings::IniFormat);
	
	//防止中文乱码
	settings.setIniCodec("utf-8");
	
    //按分组写入设置
    settings.beginGroup(INI_SQL_CONFIG);
    settings.setValue(INI_SQL_CONFIG_USERNAME, AppUtils::username);
    settings.setValue(INI_SQL_CONFIG_PASSWORD, AppUtils::password);
    settings.endGroup();
}

void AppUtils::newConfig()
{
    writeConfig();
}

bool AppUtils::checkConfig()
{
    //如果配置文件大小为0,则以初始值继续运行,并生成配置文件
    QFile file(AppUtils::configFile);
    if (file.size() == 0) {
        newConfig();
        return false;
    }

    if (file.open(QFile::ReadOnly)) {
        bool ok = true;
        while (!file.atEnd()) {
            QString line = file.readLine();
            line = line.replace("\r", "");
            line = line.replace("\n", "");
            QStringList list = line.split("=");
            if (list.isEmpty() || list.count() != 2 || list.at(1) == "") {
                ok = false;
                break;
            }
        }
        if (ok) {
            return true;
        }
    }
    //如果配置文件不完整,则以初始值继续运行,并生成配置文件
    newConfig();
    return false;
}

QString AppUtils::getFontName()
{
    return fontName;
}

int AppUtils::getFontSize()
{
    return fontSize;
}

int AppUtils::deskWidth()
{
    //没有必要每次都获取,只有当变量为空时才去获取一次
    static int width = 0;
    if (width == 0) {
        qApp->desktop()->availableGeometry().width();
    }
    return width;
}

int AppUtils::deskHeight()
{
    static int height = 0;
    if (height == 0) {
        qApp->desktop()->availableGeometry().height();
    }
    return height;
}

QString AppUtils::appName()
{
    static QString appName;
    if (appName.isEmpty()) {
        appName = qApp->applicationFilePath();
        QStringList list = appName.split("/");
        appName = list.at(list.count() - 1).split(".").at(0);;
    }
    return appName;
}

QString AppUtils::appPath()
{
    return qApp->applicationDirPath();
}

void AppUtils::initRand()
{
    //初始化随机数种子
    QTime t = QTime::currentTime();
    qsrand(t.msec() + t.second() * 1000);
}

void AppUtils::setStyle(const QString qssFilePath)
{
    QFile file(qssFilePath);
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        qApp->setStyleSheet(qss);
        file.close();
    }
}

void AppUtils::setWidgetInCenter(QWidget *widget)
{
    int widgetWidth = widget->width();
    int widgetHeight = widget->height();
    QDesktopWidget desktop;
    int deskWidth = desktop.availableGeometry().width();
    int deskHeight = desktop.availableGeometry().height();
    QPoint movePoint((deskWidth - widgetWidth) / 2, (deskHeight - widgetHeight) / 2);
    widget->move(movePoint);
}

void AppUtils::setTranslator(const QString &qmFile)
{
    QTranslator *translator = new QTranslator(qApp);
    translator->load(qmFile);
    qApp->installTranslator(translator);
}

void AppUtils::setCode()
{
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
#if _MSC_VER
    QTextCodec *codec = QTextCodec::codecForName("gbk");
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
#endif
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
#endif
}
/**
 * 延时：
 *     传入参数mSec，使程序延时mSec毫秒。这种方法不会阻塞当前线程，尤其适合Qt的单线程带UI程序，
 * 或者UI线程，因为线程阻塞时，很明显的现象就是UI卡死。当然，你也可以更改addMSecs为addSecs使
 * 程序延时msec秒。
 *     如果去掉QCoreApplication::processEvents(QEventLoop::AllEvents, 100); 可以延时，但
 * 也会阻塞线程.
 *     QCoreApplication::processEvents(QEventLoop::AllEvents, 100);使程序在while等待期间，
 * 去处理一下本线程的事件循环，处理事件循环最多100ms必须返回本语句，如果提前处理完毕，则立即返
 * 回这条语句。
 */
void AppUtils::sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while (QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void AppUtils::setSystemDateTime(const QString &year, const QString &month, const QString &day, const QString &hour, const QString &min, const QString &sec)
{
#ifdef Q_OS_WIN
    QProcess process(0);
    process.start("cmd");
    process.waitForStarted();
    //Latin1是ISO-8859-1的别名，有些环境下写作Latin-1。ISO-8859-1编码是单字节编码，向下兼容ASCII
    process.write(QString("date %1-%2-%3\n").arg(year).arg(month).arg(day).toLatin1());
    process.closeWriteChannel();
    process.waitForFinished(1000);
    process.close();
    process.start("cmd");
    process.write(QString("time %1:%2:%3.00\n").arg(hour).arg(min).arg(sec).toLatin1());
    process.waitForStarted();
    process.closeWriteChannel();
    process.waitForFinished(1000);
    process.close();
#else
    QString cmd = QString("date %1%2%3%4%5.%6").arg(month).arg(day).arg(hour).arg(min).arg(year).arg(sec);
    system(cmd.toLatin1());
    system("hwclock -w");
#endif
}

void AppUtils::runWithSystem(const QString &strName, const QString &strPath, bool autoRun)
{
#ifdef Q_OS_WIN
    QSettings reg("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    reg.setValue(strName, autoRun ? strPath : "");
#endif
}


