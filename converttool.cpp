#include "converttool.h"
#include <QStringList>
#include <QDebug>

ConvertTool& ConvertTool::getInstance()
{
    static ConvertTool instance;
    return instance;
}

QString ConvertTool::IPToCode(QString ip, int port, int safetyCode)
{
    QString ret = "Invalid";
    bool is  = isValidIPAddress(ip);
    bool  isValid = m_portMap.contains(port);
    bool isSafe = (safetyCode<3 && safetyCode > -1);
    if(is && isValid && isSafe)
    {
        QString code;
        QStringList lsP = ip.split(".");
        QString low = lsP.at(3);
        QString height = lsP.at(2);
        QString str1 = QString("%1").arg(height.toInt(),8,2,QLatin1Char( '0' ));
        QString str2 = QString("%1").arg(low.toInt(),8,2,QLatin1Char( '0' ));
        QString binaryPort = m_portMap.value(port);
        QString binarySafeCode= QString("%1").arg(safetyCode,2,2,QLatin1Char( '0' ));
        code = binarySafeCode + binaryPort + str1 + str2;
        bool ok;
        uint num = code.toUInt(&ok,2);
        ret = QString("%1").arg(num,6,10,QLatin1Char('0'));
    }
    return ret;
}

QStringList ConvertTool::CodeToIP(QString code)
{
    QStringList lst;
    bool ok = false;
    int codeValue = code.toInt(&ok);
    if(ok)
    {
        QString binaryInfo = QString("%1").arg(code.toInt(),20,2,QLatin1Char( '0' ));
    //    qDebug()<<binaryInfo;
    //    qDebug()<<binaryInfo.mid(0,2);
    //    qDebug()<<binaryInfo.mid(2,2);
    //    qDebug()<<binaryInfo.mid(4,8);
    //    qDebug()<<binaryInfo.mid(12,8);

        int safeNum = binaryInfo.mid(0,2).toInt(&ok,2);
        int port = m_codeMap.value( binaryInfo.mid(2,2));
        int height = binaryInfo.mid(4,8).toInt(&ok,2);
        int low = binaryInfo.mid(12,8).toInt(&ok,2);

    //    qDebug()<<safeNum;
    //    qDebug()<<port;
    //    qDebug()<<height;
    //    qDebug()<<low;

        lst.append(QString::number(safeNum));
        lst.append(QString::number(port));
        lst.append(QString::number(height));
        lst.append(QString::number(low));
    }
    return lst;
}

bool ConvertTool::isValidIPAddress(const QString &ip)
{
    bool ret = true;
    QRegExp regExp("\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b");
    ret = regExp.exactMatch(ip);
    return ret;
}

ConvertTool::ConvertTool()
{
    m_portMap.insert(11010,"00");
    m_portMap.insert(11013,"01");
    m_portMap.insert(11015,"10");
    m_portMap.insert(11017,"11");

    m_codeMap.insert("00",11010);
    m_codeMap.insert("01",11013);
    m_codeMap.insert("10",11015);
    m_codeMap.insert("11",11017);
}

ConvertTool::~ConvertTool()
{

}
