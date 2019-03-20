#ifndef CONVERTTOOL_H
#define CONVERTTOOL_H
#include <QString>
#include <QMap>

class ConvertTool
{
public:
    ///
    /// \brief getInstance
    /// \return
    ///单例模式
    static ConvertTool& getInstance();

    ///
    /// \brief IPToCode
    /// \param ip
    /// \param port
    /// \param safetyCode
    /// \return
    ///根据输入 IP 端口号 安全码 返回一个六位数
    ///
    /// 如果返回“Invalid” 说明 输入的参数非法
    QString IPToCode(QString ip,int port,int safetyCode);

    ///
    /// \brief CodeToIP
    /// \param code
    /// \return
    ///QStringList 大小为4
    /// 0: 安全码  1: 端口号 2:IP地址高位  3:IP地址低位
    QStringList CodeToIP(QString code);

public:
    virtual ~ConvertTool();
private:
    ConvertTool();
    ConvertTool(const ConvertTool &) = delete;
    ConvertTool & operator = (const ConvertTool &) = delete;

    bool isValidIPAddress(const QString & ip);

private:
    QString m_ip;
    QString m_port;
    QString m_safetyCode;

    QMap<int,QString> m_portMap;
    QMap<QString,int> m_codeMap;
};

#endif // CONVERTTOOL_H
