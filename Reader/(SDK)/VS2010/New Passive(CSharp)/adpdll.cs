using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

public class Adpdll
{
    #region ---Public---
    [DllImport("adppub.dll")]
    public static extern int at_datatocommand(IntPtr iData, ref int iSize, ref CommandInfo oCommand);
    [DllImport("adppub.dll")]
    public static extern int at_commandtocard(ref CommandInfo oCommand, ref CardInfo oCard);
    [DllImport("adppub.dll")]
    public static extern int at_datatocard(IntPtr iData, ref int iSize, IntPtr oCard, ref int oSize);
    [DllImport("adppub.dll")]
    public static extern int at_checksum(IntPtr iData, int iStart, int iSize);
    #endregion

    #region ---RS232---
    [DllImport("adpcom.dll")]
    public static extern int ap_open(int iPort, int iBaudrate); // ap_open - 打开串口
    [DllImport("adpcom.dll")]
    public static extern void ap_close(int iHandle);   // ap_close - 关闭串口
    [DllImport("adpcom.dll")]
    public static extern int ap_getaddress(int iHandle, ref int oAddress, ref int oVer);// ap_getaddress - 获取地址
    [DllImport("adpcom.dll")]
    public static extern int ap_setaddress(int iHandle, int iAddress, int iData);// ap_setaddress - 设置地址
    [DllImport("adpcom.dll")]
    public static extern int ap_getconfig(int iHandle, int iAddress, IntPtr oData, ref byte oSize);// ap_getconfig - 获取参数
    [DllImport("adpcom.dll")]
    public static extern int ap_setconfig(int iHandle, int iAddress, byte[] iData, byte iSize);// ap_setconfig - 设置参数
    [DllImport("adpcom.dll")]
    public static extern int ap_gettcpip(int iHandle, int iAddress, IntPtr oData, ref byte oSize);// ap_gettcpip - 获取tcpip参数
    [DllImport("adpcom.dll")]
    public static extern int ap_settcpip(int iHandle, int iAddress, byte[] iData, byte iSize);// ap_settcpip - 设置tcpip参数
    [DllImport("adpcom.dll")]
    public static extern int ap_identify6b(int iHandle, int iAddress, IntPtr oData, ref byte oSize);// ap_identify6b - 识别6b卡号
    [DllImport("adpcom.dll")]
    public static extern int ap_read6b(int iHandle, int iAddress, IntPtr oData, byte iAddr, byte iSize);// ap_read6b - 读6b数据
    [DllImport("adpcom.dll")]
    public static extern int ap_write6b(int iHandle, int iAddress, byte[] iData, byte iAddr, byte iSize);// ap_write6b - 写6b数据
    [DllImport("adpcom.dll")]
    public static extern int ap_identify6c(int iHandle, int iAddress, IntPtr oData, ref byte oSize);// ap_identify6c - 识别6C卡号
    [DllImport("adpcom.dll")]
    public static extern int ap_identify6c_c(int iHandle, int iAddress, ref CardInfo oCard);// ap_identify6c - 识别6C卡号
    [DllImport("adpcom.dll")]
    public static extern int ap_identify6cmult(int iHandle, int iAddress, IntPtr oData, ref byte oSize);// ap_identify6cmult - 识别6C卡号-多卡
    [DllImport("adpcom.dll")]
    public static extern int ap_read6c(int iHandle, int iAddress, IntPtr oData, byte iMem, byte iAddr, byte iSize);// ap_read6c - 读6C数据
    [DllImport("adpcom.dll")]
    public static extern int ap_write6c(int iHandle, int iAddress, byte[] iData, byte iMem, byte iAddr, byte iSize);// ap_write6c - 写6C数据
    [DllImport("adpcom.dll")]
    public static extern int ap_encrypt(int iHandle, int iAddress);// ap_encrypt - 加密
    [DllImport("adpcom.dll")]
    public static extern int ap_softreset(int iHandle, int iAddress);// ap_softreset - 软重启设备
    [DllImport("adpcom.dll")]
    public static extern int ap_getautocard(int iHandle, IntPtr oData, ref byte oSize);//ap_getautocard - 获取自动上送卡号
    #endregion

    #region ---TCPIP---
    [DllImport("adpnet.dll")]
    public static extern int an_open(string ip, int port);
    [DllImport("adpnet.dll")]
    public static extern int an_close(int iHandle);
    [DllImport("adpnet.dll")]
    public static extern int an_getaddress(int iHandle, ref int oAddress, ref int oVer);
    [DllImport("adpnet.dll")]
    public static extern int an_setaddress(int iHandle, int iAddress, int iData);
    [DllImport("adpnet.dll")]
    public static extern int an_getconfig(int iHandle, int iAddress, IntPtr oData, ref byte oSize);
    [DllImport("adpnet.dll")]
    public static extern int an_setconfig(int iHandle, int iAddress, byte[] iData, byte iSize);
    [DllImport("adpnet.dll")]
    public static extern int an_gettcpip(int iHandle, int iAddress, IntPtr oData, ref byte oSize);
    [DllImport("adpnet.dll")]
    public static extern int an_settcpip(int iHandle, int iAddress, byte[] iData, byte iSize);
    [DllImport("adpnet.dll")]
    public static extern int an_identify6b(int iHandle, int iAddress, IntPtr oData, ref byte oSize);
    [DllImport("adpnet.dll")]
    public static extern int an_read6b(int iHandle, int iAddress, IntPtr oData, byte iAddr, byte iSize);
    [DllImport("adpnet.dll")]
    public static extern int an_write6b(int iHandle, int iAddress, byte[] iData, byte iAddr, byte iSize);
    [DllImport("adpnet.dll")]
    public static extern int an_identify6c(int iHandle, int iAddress, IntPtr oData, ref byte oSize);
    [DllImport("adpnet.dll")]
    public static extern int an_identify6cmult(int iHandle, int iAddress, IntPtr oData, ref byte oSize);
    [DllImport("adpnet.dll")]
    public static extern int an_read6c(int iHandle, int iAddress, IntPtr oData, byte iMem, byte iAddr, byte iSize);
    [DllImport("adpnet.dll")]
    public static extern int an_write6c(int iHandle, int iAddress, byte[] iData, byte iMem, byte iAddr, byte iSize);
    [DllImport("adpnet.dll")]
    public static extern int an_encrypt(int iHandle, int iAddress);
    [DllImport("adpnet.dll")]
    public static extern int an_getautocard(int iHandle, IntPtr oData, ref byte oSize);
    #endregion

    #region ---USB---
    [DllImport("adpusb.dll")]
    public static extern int ad_open();
    [DllImport("adpusb.dll")]
    public static extern int ad_close(int iHandle);
    [DllImport("adpusb.dll")]
    public static extern int ad_exitprogram(int iHandle);
    [DllImport("adpusb.dll")]
    public static extern int ad_getaddress(int iHandle, ref int oAddress, ref int oVer);
    [DllImport("adpusb.dll")]
    public static extern int ad_setaddress(int iHandle, int iAddress, int iData);
    [DllImport("adpusb.dll")]
    public static extern int ad_getconfig(int iHandle, int iAddress, IntPtr oData, ref byte oSize);
    [DllImport("adpusb.dll")]
    public static extern int ad_setconfig(int iHandle, int iAddress, byte[] iData, byte iSize);
    [DllImport("adpusb.dll")]
    public static extern int ad_getoutstatus(int iHandle, int iAddress, IntPtr oData, ref byte oSize);
    [DllImport("adpusb.dll")]
    public static extern int ad_setoutstatus(int iHandle, int iAddress, byte[] iData, byte iSize);
    [DllImport("adpusb.dll")]
    public static extern int ad_identify6b(int iHandle, int iAddress, IntPtr oData, ref byte oSize);
    [DllImport("adpusb.dll")]
    public static extern int ad_read6b(int iHandle, int iAddress, IntPtr oData, byte iAddr, byte iSize);
    [DllImport("adpusb.dll")]
    public static extern int ad_write6b(int iHandle, int iAddress, byte[] iData, byte iAddr, byte iSize);
    [DllImport("adpusb.dll")]
    public static extern int ad_identify6c(int iHandle, int iAddress, IntPtr oData, ref byte oSize);
    [DllImport("adpusb.dll")]
    public static extern int ad_read6c(int iHandle, int iAddress, IntPtr oData, byte iMem, byte iAddr, byte iSize);
    [DllImport("adpusb.dll")]
    public static extern int ad_write6c(int iHandle, int iAddress, byte[] iData, byte iMem, byte iAddr, byte iSize);
    [DllImport("adpusb.dll")]
    public static extern int ad_encrypt(int iHandle, int iAddress);
    [DllImport("adpusb.dll")]
    public static extern int ad_getautocard(int iHandle, IntPtr oData, ref byte oSize);
    #endregion

    [StructLayout(LayoutKind.Sequential, Pack = 1, Size = 256)]
    public struct CommandInfo
    {
        /// <summary>
        /// 命令码
        /// </summary>
        [MarshalAs(UnmanagedType.U1)]
        public byte CID1;
        /// <summary>
        /// 操作码
        /// </summary>
        [MarshalAs(UnmanagedType.U1)]
        public byte CID2;
        /// <summary>
        /// 返回码
        /// </summary>
        [MarshalAs(UnmanagedType.U1)]
        public byte RTN;
        /// <summary>
        /// 信息数量
        /// </summary>
        [MarshalAs(UnmanagedType.U1)]
        public byte Count;
        /// <summary>
        /// 单个信息长度
        /// </summary>
        [MarshalAs(UnmanagedType.U1)]
        public byte Length;
        /// <summary>
        /// 总信息长度
        /// </summary>
        [MarshalAs(UnmanagedType.U1)]
        public byte DataLength;
        /// <summary>
        /// 信息
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 250)]
        public byte[] DataBytes;
    }

    [StructLayout(LayoutKind.Sequential, Pack = 1, Size = 66)]
    public struct CardInfo
    {
        /// <summary>
        /// 天线号
        /// </summary>
        [MarshalAs(UnmanagedType.U1, SizeConst = 1)]
        public byte Antenna;
        /// <summary>
        /// 单个卡数据长度
        /// </summary>
        [MarshalAs(UnmanagedType.U1, SizeConst = 1)]
        public byte DataLength;
        /// <summary>
        /// 卡号
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
        public byte[] DataBytes;
    }

    /// <summary>
    /// 十六进制转换字节数组
    /// </summary>
    /// <param name="hexStr">十六进制字符串</param>
    /// <returns></returns>
    public static byte[] HexStringToByteArray(string hexStr)
    {
        hexStr = hexStr.Replace(" ", "");
        byte[] bytResult = new byte[hexStr.Length / 2];
        for (int i = 0; i < hexStr.Length; i += 2)
        {
            try
            {
                bytResult[i / 2] = (byte)Convert.ToByte(hexStr.Substring(i, 2), 16);
            }
            catch { }
        }
        return bytResult;
    }
    /// <summary>
    /// 字节数组转换十六进制
    /// </summary>
    /// <param name="bytArray">字节数组</param>
    /// <returns></returns>
    public static string ByteArrayToHexString(byte[] bytArray)
    {
        StringBuilder sbResult = new StringBuilder(bytArray.Length * 2);
        foreach (byte b in bytArray)
        {
            try
            {
                sbResult.Append(Convert.ToString(b, 16).PadLeft(2, '0'));
            }
            catch { }
        }
        return sbResult.ToString().ToUpperInvariant();
    }
    /// <summary>
    /// 字节数组转换十六进制
    /// </summary>
    /// <param name="bytArray">字节数组</param>
    /// <param name="start"></param>
    /// <param name="length"></param>
    /// <returns></returns>
    public static string ByteArrayToHexString(byte[] bytArray, int start, int length)
    {
        StringBuilder sbResult = new StringBuilder(length * 2);
        for (int i = start; i < length + start; i++)
        {
            try
            {
                sbResult.Append(Convert.ToString(bytArray[i], 16).PadLeft(2, '0'));
            }
            catch {
                return "";
            }
        }
        string rtn = sbResult.ToString().ToUpperInvariant();
        return rtn;
    }
}