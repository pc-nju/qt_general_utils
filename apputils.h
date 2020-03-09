#ifndef APPUTILS_H
#define APPUTILS_H

#include <QObject>

class AppUtils : public QObject
{
    Q_OBJECT

public:
    static void setConfigFile(const QString &value); //设置配置文件名
    static void readConfig();                        //读取配置参数
    static void writeConfig();                       //写入配置参数
    static void newConfig();                         //初始值新建配置文件
    static bool checkConfig();                       //校验配置文件

    static QString getFontName();                    //获取字体名
    static int getFontSize();                        //获取字体大小
    
    //桌面宽度高度
    static int deskWidth();
    static int deskHeight();
    
    //程序本身文件名称
    static QString appName();
    //程序当前所在路径
    static QString appPath();
    
    //初始化随机数种子
    static void initRand();
    
    //设置全局样式
    static void setStyle(const QString qssFilePath);
    
    //设置窗体居中显示
    static void setWidgetInCenter(QWidget *widget);
    //设置翻译文件
    static void setTranslator(const QString &qmFile);
    //设置编码
    static void setCode();
    //设置延时
    static void sleep(int msec);
    //设置系统时间
    static void setSystemDateTime(const QString &year, const QString &month, const QString &day,
                                  const QString &hour, const QString &min, const QString &sec);
    //设置开机自启动
    static void runWithSystem(const QString &strName, const QString &strPath, bool autoRun = true);


    
private:
    static QString configFile;                       //配置文件名
    static QString username;                         //测试用户名
    static QString password;                         //测试密码
    static QString fontName;                         //使用字体
    static int fontSize;                             //字体大小
    
};

#endif // APPUTILS_H
