#include "fileutils.h"
#include <QFileDialog>

QString FileUtils::getSaveName(const QString &filter, QString defaultDir)
{
    return QFileDialog::getSaveFileName(0, "选择文件", defaultDir, filter);
}

QString FileUtils::getFileName(const QString &filter, QString defaultDir)
{
    return QFileDialog::getOpenFileName(0, "选择文件", defaultDir, filter);
}

QStringList FileUtils::getFileNames(const QString &filter, QString defaultDir)
{
    return QFileDialog::getOpenFileNames(0, "选择文件", defaultDir, filter);
}

QString FileUtils::getFolderName()
{
    return QFileDialog::getExistingDirectory();
}

QString FileUtils::getFileNameWithExtension(const QString &strFilePath)
{
    QFileInfo fileInfo(strFilePath);
    return fileInfo.fileName();
}

QStringList FileUtils::getFolderFileNames(const QStringList &filter)
{
    QString strFolder = QFileDialog::getExistingDirectory();
    QStringList fileList;
    
    if (!strFolder.length() == 0) {
        QDir myFolder(strFolder);
        if (myFolder.exists()) {
            fileList = myFolder.entryList(filter);
        }
    }
    return fileList;
}

bool FileUtils::folderIsExist(const QString &strFolder)
{
    QDir tempFolder(strFolder);
    return tempFolder.exists();
}

bool FileUtils::fileIsExist(const QString &strFile)
{
    QFile tempFile(strFile);
    return tempFile.exists();
}

bool FileUtils::copyFile(const QString &sourceFile, const QString &targetFile)
{
    bool ok;
    ok = QFile::copy(sourceFile, targetFile);
    if (ok) {
        //将复制过去的文件只读属性取消
        ok = QFile::setPermissions(targetFile, QFile::WriteOwner);
    }
    return ok;
}

void FileUtils::deleteDirectory(const QString &path)
{
    QDir dir(path);
    if (!dir.exists()) {
        return;
    }
    dir.removeRecursively();
}

void FileUtils::newDir(const QString &dirName)
{
    QString fileDir = dirName;
    //如果路径中包含斜杠字符则说明是绝对路径
    //linux系统路径字符带有 /  windows系统 路径字符带有 :/
    if (!fileDir.startsWith("/") && !fileDir.contains(":/")) {
        fileDir = QString("%1/%2").arg(qApp->applicationDirPath()).arg(fileDir);
    }
    QDir dir(fileDir);
    if (!dir.exists()) {
        dir.mkpath(fileDir);
    }
}
