

#include "jlink.h"


/* 防止空指针 */
bool JlinkView::jlinkOpen(void)
{
    if (JlinkOpenFuncPtr){
        return JlinkOpenFuncPtr();
    }
    return false;
}
void JlinkView::jlinkClose(void)
{
    if (JlinkCloseFuncPtr){
        JlinkCloseFuncPtr();
    }
}
bool JlinkView::jlinkIsOpen(void)
{
    if (JlinkIsOpenFuncPtr){
        return JlinkIsOpenFuncPtr();
    }
    return false;
}
unsigned int JlinkView::jlinkTIFSelectFunc(int type)
{
    if (JlinkTIFSelectFuncPtr){
        return JlinkTIFSelectFuncPtr(type);
    }
    return false;
}
void JlinkView::jlinkSetSpeedFunc(unsigned int speed)
{
    if (JlinkSetSpeedFuncPtr){
        JlinkSetSpeedFuncPtr(speed);
    }
}
unsigned int JlinkView::jlinkGetSpeedFunc(void)
{
    if (JlinkGetSpeedFuncPtr){
        return JlinkGetSpeedFuncPtr();
    }
    return 0;
}
void JlinkView::jlinkSetResetTypeFunc(int type)
{
    if (JlinkSetResetTypeFuncPtr){
        JlinkSetResetTypeFuncPtr(type);
    }
}
void JlinkView::jlinkResetFunc(void)
{
    if (JlinkResetFuncPtr){
        JlinkResetFuncPtr();
    }
}
int JlinkView::jlinkHaltFunc(void)
{
    if (JlinkHaltFuncPtr){
        return JlinkHaltFuncPtr();
    }
    return 0;
}
int JlinkView::jlinkReadMemFunc(unsigned int addr, int len, void *buf)
{
    if (JlinkReadMemFuncPtr){
        return JlinkReadMemFuncPtr(addr, len, buf);
    }
    return 0;
}
int JlinkView::jlinkWriteMemFunc(unsigned int addr, int len, void *buf)
{
    if (JlinkWriteMemFuncPtr){
        return JlinkWriteMemFuncPtr(addr, len, buf);
    }
    return 0;
}
int JlinkView::jlinkEraseChipFunc(void)
{
    if (JlinkEraseChipFuncPtr){
        return JlinkEraseChipFuncPtr();
    }
    return 0;
}
bool JlinkView::jlinkExecCommandFunc(const char *cmd, int a, int b)
{
    if (JlinkExecCommandFuncPtr){
        return JlinkExecCommandFuncPtr(cmd, a, b);
    }
    return false;
}
unsigned int JlinkView::jlinkGetDLLVersionFunc(void)
{
    if (JlinkGetDLLVersionFuncPtr){
        return JlinkGetDLLVersionFuncPtr();
    }
    return 0;
}
unsigned int JlinkView::jlinkGetSNFunc(void)
{
    if (JlinkGetSNFuncPtr){
        return JlinkGetSNFuncPtr();
    }
    return 0;
}
unsigned int JlinkView::jlinkGetIdFunc(void)
{
    if (JlinkGetIdFuncPtr){
        return JlinkGetIdFuncPtr();
    }
    return 0;
}
bool JlinkView::jlinkConnectFunc(void)
{
    if (JlinkConnectFuncPtr){
        return JlinkConnectFuncPtr();
    }
    return false;
}
bool JlinkView::jlinkIsConnectedFunc(void)
{
    if (JlinkIsConnectedFuncPtr){
        return JlinkIsConnectedFuncPtr();
    }
    return false;
}

void JlinkView::jlinkLibLoadHandle(void)
{
    jlinkLib = new QLibrary("JLinkARM.dll");
    if (jlinkLib->load())
    {
        JlinkOpenFuncPtr = (JlinkOpenFunc)jlinkLib->resolve("JLINKARM_Open");                             // 打开设备
        JlinkCloseFuncPtr = (JlinkCloseFunc)jlinkLib->resolve("JLINKARM_Close");                          // 关闭设备
        JlinkIsOpenFuncPtr = (JlinkIsOpenFunc)jlinkLib->resolve("JLINKARM_IsOpen");                       // 判断设备是否打开
        JlinkTIFSelectFuncPtr = (JlinkTIFSelectFunc)jlinkLib->resolve("JLINKARM_TIF_Select");             // 选择设备
        JlinkSetSpeedFuncPtr = (JlinkSetSpeedFunc)jlinkLib->resolve("JLINKARM_SetSpeed");                 // 设置烧录速度
        JlinkGetSpeedFuncPtr = (JlinkGetSpeedFunc)jlinkLib->resolve("JLINKARM_GetSpeed");                 // 获取烧录速度
        JlinkSetResetTypeFuncPtr = (JlinkSetResetTypeFunc)jlinkLib->resolve("JLINK");
        JlinkResetFuncPtr = (JlinkResetFunc)jlinkLib->resolve("JLINKARM_Reset");                          // 复位设备
        JlinkHaltFuncPtr = (JlinkHaltFunc)jlinkLib->resolve("JLINKARM_Halt");                             // 中断程序执行
        JlinkReadMemFuncPtr = (JlinkReadMemFunc)jlinkLib->resolve("JLINKARM_ReadMem");                    // 读取内存
        JlinkWriteMemFuncPtr = (JlinkWriteMemFunc)jlinkLib->resolve("JLINKARM_WriteMem");                 // 写入内存
        JlinkEraseChipFuncPtr = (JlinkEraseChipFunc)jlinkLib->resolve("JLINK_EraseChip");                 // 擦除芯片
        JlinkExecCommandFuncPtr = (JlinkExecCommandFunc)jlinkLib->resolve("JLINKARM_ExecCommand");        // 执行命令
        JlinkGetDLLVersionFuncPtr = (JlinkGetDLLVersionFunc)jlinkLib->resolve("JLINKARM_GetDLLVersion");  // 获取DLL版本号
        JlinkGetSNFuncPtr = (JlinkGetSNFunc)jlinkLib->resolve("JLINKARM_GetSN");                          // 获取sn号
        JlinkGetIdFuncPtr = (JlinkGetIdFunc)jlinkLib->resolve("JLINKARM_GetId");                          // 获取ID
        JlinkConnectFuncPtr = (JlinkConnectFunc)jlinkLib->resolve("JLINKARM_Connect");                    // 连接设备
        JlinkIsConnectedFuncPtr = (JlinkIsConnectedFunc)jlinkLib->resolve("JLINKARM_IsConnected");        // 判断是否连接设备
        qDebug() << "解析函数完成";
    }
    else
    {
        qDebug() << "加载JlinkARM.dll失败!";
    }
}

void JlinkView::infoShowHandle(QString info)
{
    qDebug() << info;
    emit sig_infoShowHandle(info);
}

void showRmCode(void *packet, int size)
{
    QByteArray data((const char*)packet, size);
    QString hexString;
    for (int i = 0; i < data.size(); i++)
    {
        hexString += QString("%1 ").arg((quint8)data.at(i), 2, 16, QChar('0'));
    }
    qDebug() << hexString;
}

bool JlinkView::jlinkConnectHandle(void)
{
    unsigned char read_arry[1024];
    if (jlinkIsOpen())
    {
        infoShowHandle(tr("设备连接成功"));
        return true;
    }
    jlinkOpen();
    if (jlinkIsOpen())
    {
        jlinkExecCommandFunc("device = NRF52810_XXAA", 0, 0);
        jlinkTIFSelectFunc(JLINKARM_TIF_SWD);
        jlinkSetSpeedFunc(4000);
        jlinkConnectFunc();
        if (jlinkIsConnectedFunc()){
            infoShowHandle(tr("设备连接成功"));
            qDebug("cpuid: 0x%08x", jlinkGetIdFunc());

//            jlinkReadMemFunc(0x10000100, 1024, read_arry);
//            showRmCode(read_arry, 1024);

            return true;
        }else
        {
            infoShowHandle(tr("连接设备失败! 请检查设备连接..."));
        }
    }
    else
    {
        infoShowHandle(tr("连接设备失败! 请检查烧录器连接..."));
    }
    return false;
}

void JlinkView::jlinkdisconnectHandle(void)
{
    jlinkClose();
    if (!jlinkIsOpen())
    {
        infoShowHandle(tr("断开设备成功!"));
    }
    else {
        infoShowHandle(tr("断开设备失败..."));
    }
}

QString JlinkView::jlinkGetCpuIdHandle(void)
{
    unsigned char cpuId[12]={0};
    char cpuIdTemp[128]={0};
    jlinkReadMemFunc(0x1FFF7A10, 12, cpuId);
    sprintf(cpuIdTemp, "%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X",
            cpuId[3], cpuId[2], cpuId[1], cpuId[0],
            cpuId[7], cpuId[6], cpuId[5], cpuId[4],
            cpuId[11], cpuId[10], cpuId[9], cpuId[8]);
    return QString(cpuIdTemp);
}

JlinkView &JlinkView::getInstance()
{
    static JlinkView s_obj;    // 创建1个实例，并以引用的形式返回
    return s_obj;
}

JlinkView::JlinkView(QObject *parent) : QObject(parent)
{
    jlinkLibLoadHandle();
}

JlinkView::~JlinkView()
{
}
