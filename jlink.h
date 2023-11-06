
#ifndef _JLINK_H_
#define _JLINK_H_

#include <QObject>
#include <QLibrary>
#include <QString>
#include <QDebug>

//REGISTER INDEX
/*
  0 - 15     R0 - R15(SP=R13, PC=R15)
 16          XPSR
 17          MSP
 18          PSP
 19          RAZ
 20          CFBP
 21          APSR
 22          EPSR
 23          IPSR
 24          PRIMASK
 25          BASEPRI
 26          FAULTMASK
 27          CONTROL
 28          BASEPRI_MAX
 29          IAPSR
 30          EAPSR
 31          IEPSR
 */

//JLINK TIF
#define JLINKARM_TIF_JTAG                0
#define JLINKARM_TIF_SWD                 1
#define JLINKARM_TIF_DBM3                2
#define JLINKARM_TIF_FINE                3
#define JLINKARM_TIF_2wire_JTAG_PIC32    4

//RESET TYPE
#define JLINKARM_RESET_TYPE_NORMAL       0
#define JLINKARM_RESET_TYPE_CORE         1
#define JLINKARM_RESET_TYPE_PIN          2

typedef bool  (*JlinkOpenFunc)(void);
typedef void  (*JlinkCloseFunc)(void);
typedef bool  (*JlinkIsOpenFunc)(void);
typedef unsigned int (*JlinkTIFSelectFunc)(int);
typedef void  (*JlinkSetSpeedFunc)(int);
typedef unsigned int (*JlinkGetSpeedFunc)(void);
typedef void  (*JlinkSetResetTypeFunc)(int type);
typedef void  (*JlinkResetFunc)(void);
typedef int   (*JlinkHaltFunc)(void);
typedef void  (*JlinkGoFunc)(void);

typedef int   (*JlinkReadMemFunc)(unsigned int addr, int len, void *buf);
typedef int   (*JlinkWriteMemFunc)(unsigned int addr, int len, void *buf);
typedef int   (*JlinkWriteU8Func)(unsigned int addr, unsigned char data);
typedef int   (*JlinkWriteU16Func)(unsigned int addr, unsigned short data);
typedef int   (*JlinkWriteU32Func)(unsigned int addr, unsigned int data);

typedef int   (*JlinkEraseChipFunc)(void);
typedef int   (*JlinkDownloadFileFunc)(const char *file, unsigned int addr);
typedef void  (*JlinkBeginDownloadFunc)(int index);
typedef void  (*JlinkEndDownloadFunc)(void);
typedef bool  (*JlinkExecCommandFunc)(const char* cmd, int a, int b);

typedef unsigned int (*JlinkReadRegFunc)(int index);
typedef int   (*JlinkWriteRegFunc)(int index, unsigned int data);

typedef void  (*JlinkSetLogFileFunc)(char *file);
typedef unsigned int (*JlinkGetDLLVersionFunc)(void);
typedef unsigned int (*JlinkGetHardwareVersionFunc)(void);
typedef unsigned int (*JlinkGetFirmwareStringFunc)(char *buff, int count);
typedef unsigned int (*JlinkGetSNFunc)(void);
typedef unsigned int (*JlinkGetIdFunc)(void);
typedef bool  (*JlinkConnectFunc)(void);
typedef bool  (*JlinkIsConnectedFunc)(void);


class JlinkView : public QObject
{
    Q_OBJECT
public:
    explicit JlinkView(QObject *parent = 0);
    ~JlinkView();

    static JlinkView & getInstance();   // 以引用方式返回函数值，类似于C语言里的指针*

signals:
    void sig_infoShowHandle(QString info);

public slots:

public:
    QLibrary *jlinkLib;

    JlinkOpenFunc JlinkOpenFuncPtr = NULL;
    JlinkCloseFunc JlinkCloseFuncPtr = NULL;
    JlinkIsOpenFunc JlinkIsOpenFuncPtr = NULL;
    JlinkTIFSelectFunc JlinkTIFSelectFuncPtr = NULL;
    JlinkSetSpeedFunc JlinkSetSpeedFuncPtr = NULL;
    JlinkGetSpeedFunc JlinkGetSpeedFuncPtr = NULL;
    JlinkSetResetTypeFunc JlinkSetResetTypeFuncPtr = NULL;
    JlinkResetFunc JlinkResetFuncPtr = NULL;
    JlinkHaltFunc JlinkHaltFuncPtr = NULL;
    JlinkGoFunc JlinkGoFuncPtr = NULL;
    JlinkReadMemFunc JlinkReadMemFuncPtr = NULL;
    JlinkWriteMemFunc JlinkWriteMemFuncPtr = NULL;
    JlinkWriteU8Func JlinkWriteU8FuncPtr = NULL;
    JlinkWriteU16Func JlinkWriteU16FuncPtr = NULL;
    JlinkWriteU32Func JlinkWriteU32FuncPtr = NULL;
    JlinkEraseChipFunc JlinkEraseChipFuncPtr = NULL;
    JlinkDownloadFileFunc JlinkDownloadFileFuncPtr = NULL;
    JlinkBeginDownloadFunc JlinkBeginDownloadFuncPtr = NULL;
    JlinkEndDownloadFunc JlinkEndDownloadFuncPtr = NULL;
    JlinkExecCommandFunc JlinkExecCommandFuncPtr = NULL;
    JlinkReadRegFunc JlinkReadRegFuncPtr = NULL;
    JlinkWriteRegFunc JlinkWriteRegFuncPtr = NULL;
    JlinkSetLogFileFunc JlinkSetLogFileFuncPtr = NULL;
    JlinkGetDLLVersionFunc JlinkGetDLLVersionFuncPtr = NULL;
    JlinkGetHardwareVersionFunc JlinkGetHardwareVersionFuncPtr = NULL;
    JlinkGetFirmwareStringFunc JlinkGetFirmwareStringFuncPtr = NULL;
    JlinkGetSNFunc JlinkGetSNFuncPtr = NULL;
    JlinkGetIdFunc JlinkGetIdFuncPtr = NULL;
    JlinkConnectFunc JlinkConnectFuncPtr = NULL;
    JlinkIsConnectedFunc JlinkIsConnectedFuncPtr = NULL;

    void jlinkLibLoadHandle(void);
    bool jlinkOpen(void);
    void jlinkClose(void);
    bool jlinkIsOpen(void);
    unsigned int jlinkTIFSelectFunc(int type);
    void jlinkSetSpeedFunc(unsigned int speed);
    unsigned int jlinkGetSpeedFunc(void);
    void jlinkSetResetTypeFunc(int type);
    void jlinkResetFunc(void);
    int jlinkHaltFunc(void);
    int jlinkReadMemFunc(unsigned int addr, int len, void *buf);
    int jlinkWriteMemFunc(unsigned int addr, int len, void *buf);
    int jlinkEraseChipFunc(void);
    bool jlinkExecCommandFunc(const char *cmd, int a, int b);
    unsigned int jlinkGetDLLVersionFunc(void);
    unsigned int jlinkGetSNFunc(void);
    unsigned int jlinkGetIdFunc(void);
    bool jlinkConnectFunc(void);
    bool jlinkIsConnectedFunc(void);

    bool jlinkConnectHandle(void);
    void jlinkdisconnectHandle(void);
    QString jlinkGetCpuIdHandle(void);

    void infoShowHandle(QString info);
};

#endif
