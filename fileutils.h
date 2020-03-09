#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QObject>
#include <QCoreApplication>


class FileUtils : public QObject
{
    Q_OBJECT
public:
    //获取保存的文件
    static QString getSaveName(const QString &filter, QString defaultDir = QCoreApplication::applicationDirPath());

    //获取选择的文件
    static QString getFileName(const QString &filter, QString defaultDir = QCoreApplication::applicationDirPath());

    //获取选择的文件集合
    static QStringList getFileNames(const QString &filter, QString defaultDir = QCoreApplication::applicationDirPath());

    //获取选择的目录
    static QString getFolderName();

    //获取文件名,含拓展名
    static QString getFileNameWithExtension(const QString &strFilePath);

    //获取选择文件夹中的文件
    static QStringList getFolderFileNames(const QStringList &filter);

    //文件夹是否存在
    static bool folderIsExist(const QString &strFolder);

    //文件是否存在
    static bool fileIsExist(const QString &strFile);

    //复制文件
    static bool copyFile(const QString &sourceFile, const QString &targetFile);

    //删除文件夹下所有文件
    static void deleteDirectory(const QString &path);

    //新建目录
    static void newDir(const QString &dirName);
};

#endif // FILEUTILS_H
