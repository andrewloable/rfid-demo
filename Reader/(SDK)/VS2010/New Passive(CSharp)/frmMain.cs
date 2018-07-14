using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Runtime.InteropServices;
using System.IO.Ports;

namespace NewPassive
{
    public partial class frmMain : Form
    {
        public const int RS232 = 0;
        public const int TCPIP = 1;
        public const int USB = 2;

        public int m_Handle = 0;
        public int m_SerialNum = 1;
        public int m_Version = 0;
        public int m_WorkMode = 0;

        public int FCount = 0;
        public byte[] bytRcvData = new byte[512];
        public byte bytRcvLen = 0;
        
        public frmMain()
        {
            InitializeComponent();
        }

        private void frmMain_Load(object sender, EventArgs e)
        {
            InitCommunicationParamater();
            InitBasicParamater();
            InitOtherParamater();
            InitEPCParamater();
            ChangeLanguage();
            InitAutoReadPtr();
        }

        private void frmMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            UnloadInitCommunicationParamater();
        }

        private void tabBody_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (tabBody.SelectedTab.Name == "tabAutoRead")
            {
                switch (m_WorkMode)
                {
                    case 2:
                        btnActive.Enabled = true;
                        btnPassive.Enabled = false;
                        break;
                    default:
                        btnActive.Enabled = false;
                        btnPassive.Enabled = true;
                        break;
                }
            }
            else if (tabBody.SelectedTab.Name == "tabWriteCard")
            {
                btnAutoCard.Text = blnReadFlag ? "Stop" : "Start";
                nudWriteLength_ValueChanged(sender,e);
            }
            else
            {
                blnActiveEnabled = blnPassiveEnabled = false;
                blnReadFlag = false;
                ChangeGetCardStatus();
            }
        }

        #region ---Status Show---
        private int intCount = 0;
        private void CheckMessage(int sec)
        {
            intCount++;
            if (intCount > sec)
            {
                intCount = 0;
                tsslMessage.Text = "";
            }
        }

        #region ---卡号获取超时变色显示---
        private int intActiveCount = 0;
        private const int ACTIVEMARK = 10;
        /// <summary>
        /// 卡号获取超时过程
        /// </summary>
        private void ActiveTime()
        {
            intActiveCount++;
            if (intActiveCount > ACTIVEMARK)
            {
                intActiveCount = 0;
                for (int i = 0; i < dgvShow.Rows.Count; i++)
                {
                    if (this.dgvShow.Rows[i].DefaultCellStyle.BackColor == Color.Gray)
                    {
                        this.dgvShow.Rows[i].DefaultCellStyle.BackColor = Color.LightGray;
                    }
                    else if (this.dgvShow.Rows[i].DefaultCellStyle.BackColor == Color.LightGray)
                    {
                        this.dgvShow.Rows[i].DefaultCellStyle.BackColor = Color.White;
                    }
                }
            }
        }
        #endregion

        private void tmrClock_Tick(object sender, EventArgs e)
        {
            ActiveTime();
            CheckMessage(4);
            if (blnPassiveEnabled)
            {
                GetPassiveTag();
            }
            else if (blnActiveEnabled)
            {
                GetActiveTag();
            }
        }

        public void OutPutMessage(string messageCH, string messageEN, int state)
        {
            intCount = 0;
            tsslMessage.Text = "";
            for (int i = 0; i < 10; i++)
            {
                Application.DoEvents();
                Thread.Sleep(10);
            }

            if (SSOption.Language == SSOption.CHN)
            {
                tsslMessage.Text = messageCH + state.ToString("[0]");
            }
            else
            {
                tsslMessage.Text = messageEN + state.ToString("[0]");
            }

            switch (state)
            {
                case 0:
                    tsslMessage.ForeColor = Color.Green;
                    break;
                case 1000:
                    tsslMessage.ForeColor = Color.Black;
                    break;
                default:
                    tsslMessage.ForeColor = Color.Red;
                    break;
            }
        }

        public void OutPutMessage(string messageCH, string messageEN, int state, Label lbl)
        {
            intCount = 0;
            lbl.Text = "";
            for (int i = 0; i < 10; i++)
            {
                Application.DoEvents();
                Thread.Sleep(10);
            }

            if (SSOption.Language == SSOption.CHN)
                lbl.Text = messageCH;
            else
                lbl.Text = messageEN;

            switch (state)
            {
                case 0:
                    lbl.ForeColor = Color.Green;
                    break;
                case 1000:
                    lbl.ForeColor = Color.Black;
                    break;
                default:
                    lbl.ForeColor = Color.Red;
                    break;
            }
        }
        #endregion

        #region ---Change Language---
        private void ChangeLanguage()
        {
            int intSelectItem = 0;
            switch (SSOption.Language)
            { 
                case SSOption.ENG:
                    toolTip.Active = false;
                    #region ---Communication---
                    grbCommType.Text = "Communication";
                    grbPortName.Text = "PortName";
                    grbBaudRate.Text = "BaudRate";

                    grbRemoteIP.Text = "Remote IP";
                    grbRemotePort.Text = "Remote Port";

                    grbVer.Text = "Version";
                    grbAddress.Text = "Address";

                    btnConnect.Text = "Connect(&C)";
                    btnDisConnect.Text = "DisConnect(&D)";
                    btnGetVer.Text = "Get Version(&V)";
                    #endregion
                    
                    #region ---Parameter config---
                    tabPara.Text = "Parameters Config";
                    
                    #region ---Wiegand---
                    grbWiegand.Text = "Wiegand Parameters Input Zone";
                    grbByteOffset.Text = "Byte Offset";
                    grbPulseWidth.Text = "Pulse Width";
                    grbOutInterval.Text = "Out Interval";
                    grbPulsePeriod.Text = "Pulse Period";
                    #endregion

                    #region ---Basic Para---
                    grbParaB.Text = "Basic Parameters Input Zone";
                    grbWorkMode.Text = "Work Mode:";
                    intSelectItem = cmbWorkMode.SelectedIndex;
                    cmbWorkMode.Items.Clear();
                    cmbWorkMode.Items.Add("Command");
                    cmbWorkMode.Items.Add("Active");
                    cmbWorkMode.Items.Add("Passive");
                    cmbWorkMode.SelectedIndex = intSelectItem;

                    grbOutputMode.Text = "Output Mode:";
                    grbReadInterval.Text = "Read Interval:";
                    grbPowerSize.Text = "Power Size:";
                    grbTrigger.Text = "Trigger:";
                    intSelectItem = cmbTrigger.SelectedIndex;
                    cmbTrigger.Items.Clear();
                    cmbTrigger.Items.Add("Close");
                    cmbTrigger.Items.Add("Low Trigger");
                    cmbTrigger.SelectedIndex = intSelectItem;

                    grbSameIDinterval.Text = "Same ID interval:";
                    grbBuzzer.Text = "Buzzer:";
                    intSelectItem = cmbBuzzer.SelectedIndex;
                    cmbBuzzer.Items.Clear();
                    cmbBuzzer.Items.Add("DisEnable");
                    cmbBuzzer.Items.Add("Enabled");
                    cmbBuzzer.SelectedIndex = intSelectItem;

                    grbCardType.Text = "Card Type:";
                    intSelectItem = cmbCardType.SelectedIndex;
                    cmbCardType.Items.Clear();
                    cmbCardType.Items.Add("ISO18000-6B");
                    cmbCardType.Items.Add("EPC(GEN 2)Single-Tag");
                    cmbCardType.Items.Add("EPC(GEN 2)Multi-Tag");
                    cmbCardType.Items.Add("EPC(GEN 2)Multi-Data");
                    cmbCardType.Items.Add("ISO18000-6B + EPC(GEN 2)");
                    cmbCardType.SelectedIndex = intSelectItem;
                    #endregion

                    #region ---Senior Para---
                    grbParaS.Text = "Senior Parameters Input Zone";
                    grbAntenna.Text = "Antenna:";

                    chkAntenna1.Text = "ANT 1";
                    chkAntenna2.Text = "ANT 2";
                    chkAntenna3.Text = "ANT 3";
                    chkAntenna4.Text = "ANT 4";

                    grbChangePwd.Text = "Encrypt authorized:";
                  
                    grbEncrypt.Text = "Encrypt";
                    intSelectItem = cmbEncrypt.SelectedIndex;
                    cmbEncrypt.Items.Clear();
                    cmbEncrypt.Items.Add("DisEnable");
                    cmbEncrypt.Items.Add("Enabled");
                    cmbEncrypt.SelectedIndex = intSelectItem;
                    
                    grbPassword.Text = "Password";
                    grbMemory.Text = "Other Memory";
                    grbStartAddress.Text = "Start Address";
                    grbLength.Text = "Length";
                    grbMaxTag.Text = "Max Tags";
                    #endregion
                    
                    #region ---Hopping---
                    grbHopping.Text = "Freq Parameters Input Zone";
                    grbFreqHopping.Text = "Hopping Enabled";
                    intSelectItem = cmbFreqHopping.SelectedIndex;
                    cmbFreqHopping.Items.Clear();
                    cmbFreqHopping.Items.Add("DisEnable");
                    cmbFreqHopping.Items.Add("Enabled");
                    cmbFreqHopping.SelectedIndex = intSelectItem;

                    grbHoppingO.Text = "International standard";
                    btnChina.Text = "China";
                    btnAmerica.Text = "America";
                    btnEurope.Text = "Europe";
                    grbFixedFreq.Text = "Fixed Freq";
                    grbHopping1.Text = "Hopping 1";
                    grbHopping2.Text = "Hopping 2";
                    grbHopping3.Text = "Hopping 3";
                    grbHopping4.Text = "Hopping 4";
                    grbHopping5.Text = "Hopping 5";
                    grbHopping6.Text = "Hopping 6";
                    #endregion
                    
                    #region ---Button---
                    btnGetConfig.Text = "Get Para(&G)";
                    btnSetConfig.Text = "Set Para(&S)";
                    btnDefaultConfig.Text = "Default All(&A)";
                    #endregion
                    #endregion
                    
                    #region ---Other Config---
                    tabOther.Text = "Other Config";
                    
                    #region ---Address Parameters---
                    grbAddressPara.Text = "Address Parameters";

                    grbAddressOld.Text = "Old Address";
                    grbAddressNew.Text = "New Address";

                    btnGetAddress.Text = "Get Address";
                    btnSetAddress.Text = "Set Address";
                    btnDefaultAddress.Text = "Default Address";
                    #endregion

                    #region ---TCPIP Parameters---
                    grbTcpip.Text = "TCPIP Parameters";

                    grbIPAddress.Text = "IP Address";
                    grbIPPort.Text = "IP Port";
                    grbSubnet.Text = "Subnet Mask";
                    grbGateway.Text = "GateWay";
                    grbMac.Text = "MAC Address";

                    btnGetTcpip.Text = "Get Tcpip";
                    btnSetTcpip.Text = "Set Tcpip";
                    btnDefaultTcpip.Text = "Default Tcpip";
                    #endregion

                    #region ---USB Output Type---
                    grbOutType.Text = "USB Output Type";

                    grbOutMode.Text = "Out Mode";
                    grbOutLen.Text = "Out Length";
                    grbOutEnter.Text = "Is Key Enter";

                    btnGetOutType.Text = "Get OutType";
                    btnSetOutType.Text = "Set OutType";
                    btnDefaultOutType.Text = "Default OutType";
                    #endregion
                    #endregion

                    #region ---ISO18000-6B---
                    tab6B.Text = "ISO18000-6B Demo";

                    grbIdentify6B.Text = "ISO18000-6B Identify";
                    grbCard6B.Text = "Tag No.";

                    grbRead6B.Text = "ISO18000-6B Read";
                    grbReadAddr6B.Text = "Address";
                    grbReadLen6B.Text = "Length";
                    grbReadData6B.Text = "Data";

                    grbWrite6B.Text = "ISO18000-6B Write";
                    grbWriteAddr6B.Text = "Address";
                    grbWriteLen6B.Text = "Length";
                    grbWriteData6B.Text = "Data";


                    btnIdentify6B.Text = "Identify(&E)";
                    btnRead6B.Text = "Read(&A)";
                    btnWrite6B.Text = "Write(&R)";
                    #endregion

                    #region ---ISO18000-6C---
                    tab6C.Text = "ISO18000-6C Demo";

                    grbIdentify6C.Text = "EPC(GEN 2) Identify";
                    grbCard6C.Text = "Tag No.";

                    grbRead6C.Text = "EPC(GEN 2) Read";
                    grbReadBlock6C.Text = "Block";
                    grbReadAddr6C.Text = "Address";
                    grbReadLen6C.Text = "Length";
                    grbReadData6C.Text = "Data";

                    grbWrite6C.Text = "EPC(GEN 2) Write";
                    grbWriteBlock6C.Text = "Block";
                    grbWriteAddr6C.Text = "Address";
                    grbWriteLen6C.Text = "Length";
                    grbWriteData6C.Text = "Data";


                    btnIdentify6C.Text = "Identify(&E)";
                    btnRead6C.Text = "Read(&A)";
                    btnWrite6C.Text = "Write(&R)";
                    #endregion

                    #region ---Auto Read Tag---
                    tabAutoRead.Text = "Auto Read Tag";

                    grbAutoReadTag.Text = "EPC(GEN 2) Auto Read Tag";
                    lblReadType.Text = "ReadType:";
                    rdbSingle.Text = "Single:";
                    rdbMult.Text = "Multiple:";
                    chkIsSpt.Text = "Distinguish antenna";
                    lblMaxCard.Text = "Single Sum:";
                    lblCount.Text = "Card Sum:";
                    btnClear.Text = "&Clear";
                    dgvShow.Columns["colID"].HeaderText = "No.";
                    dgvShow.Columns["colAddress"].HeaderText = "Ant";
                    dgvShow.Columns["colHexCard"].HeaderText = "Hex Card Number";
                    dgvShow.Columns["colTime"].HeaderText = "Time";
                    dgvShow.Columns["colCount"].HeaderText = "Count";

                    btnClear.Text = "Clear(&C)";
                    #endregion

                    break;
                case SSOption.CHN:
                    toolTip.Active = true;
                    #region ---Communication---
                    grbCommType.Text = "通讯方式选择";
                    grbPortName.Text = "串口选择";
                    grbBaudRate.Text = "波特率选择";

                    grbRemoteIP.Text = "远程IP地址";
                    grbRemotePort.Text = "远程端口";

                    grbVer.Text = "版本";
                    grbAddress.Text = "通讯地址";

                    btnConnect.Text = "联机(&C)";
                    btnDisConnect.Text = "断开(&D)";
                    btnGetVer.Text = "获取设备信息(&V)";
                    #endregion

                    #region ---Parameter config---
                    tabPara.Text = "基本参数设置";
                    
                    #region ---Wiegand---
                    grbWiegand.Text = "韦根参数输入区";
                    grbByteOffset.Text = "数据偏移";
                    grbPulseWidth.Text = "脉冲宽度";
                    grbOutInterval.Text = "输出周期";
                    grbPulsePeriod.Text = "脉冲周期";
                    #endregion

                    #region ---Basic Para---
                    grbParaB.Text = "基本参数输入区";
                    grbWorkMode.Text = "工作模式";

                    intSelectItem = cmbWorkMode.SelectedIndex;
                    cmbWorkMode.Items.Clear();
                    cmbWorkMode.Items.Add("应答方式");
                    cmbWorkMode.Items.Add("主动方式");
                    cmbWorkMode.Items.Add("被动方式");
                    cmbWorkMode.SelectedIndex = intSelectItem;

                    grbOutputMode.Text = "通讯模式";
                    grbReadInterval.Text = "读卡周期";
                    grbPowerSize.Text = "功率大小";
                    grbTrigger.Text = "外部触发方式";
                    intSelectItem = cmbTrigger.SelectedIndex;
                    cmbTrigger.Items.Clear();
                    cmbTrigger.Items.Add("关闭");
                    cmbTrigger.Items.Add("低电压触发");
                    cmbTrigger.SelectedIndex = intSelectItem;

                    grbSameIDinterval.Text = "相同ID输出间隔:";
                    grbBuzzer.Text = "嗡鸣器";
                    intSelectItem = cmbBuzzer.SelectedIndex;
                    cmbBuzzer.Items.Clear();
                    cmbBuzzer.Items.Add("禁止");
                    cmbBuzzer.Items.Add("使能");
                    cmbBuzzer.SelectedIndex = intSelectItem;

                    grbCardType.Text = "读卡类别";
                    intSelectItem = cmbCardType.SelectedIndex;
                    cmbCardType.Items.Clear();
                    cmbCardType.Items.Add("ISO18000-6B标签");
                    cmbCardType.Items.Add("EPC(GEN 2)单标签");
                    cmbCardType.Items.Add("EPC(GEN 2)多标签");
                    cmbCardType.Items.Add("EPC(GEN 2)单标签-多区域数据");
                    cmbCardType.Items.Add("ISO18000-6B标签 + EPC(GEN 2)标签");
                    cmbCardType.SelectedIndex = intSelectItem;
                    #endregion

                    #region ---Senior Para---
                    grbParaS.Text = "高级参数输入区";
                    grbAntenna.Text = "天线个数";

                    chkAntenna1.Text = "天线 1";
                    chkAntenna2.Text = "天线 2";
                    chkAntenna3.Text = "天线 3";
                    chkAntenna4.Text = "天线 4";

                    grbEncrypt.Text = "加密使能:";
                    intSelectItem = cmbEncrypt.SelectedIndex;
                    cmbEncrypt.Items.Clear();
                    cmbEncrypt.Items.Add("禁止");
                    cmbEncrypt.Items.Add("使能");
                    cmbEncrypt.SelectedIndex = intSelectItem;

                    grbChangePwd.Text = "加密授权";
                    grbPassword.Text = "密码";
                    grbMemory.Text = "其他区域卡号";
                    grbStartAddress.Text = "起始地址";
                    grbLength.Text = "长度";
                    grbMaxTag.Text = "最大读卡数量";
                    #endregion

                    #region ---Hopping---
                    grbHopping.Text = "跳频参数输入区";
                    grbFreqHopping.Text = "跳频使能";
                    intSelectItem = cmbFreqHopping.SelectedIndex;
                    cmbFreqHopping.Items.Clear();
                    cmbFreqHopping.Items.Add("禁止");
                    cmbFreqHopping.Items.Add("使能");
                    cmbFreqHopping.SelectedIndex = intSelectItem;

                    grbHoppingO.Text = "快捷设置国际标准";
                    btnChina.Text = "国标";
                    btnAmerica.Text = "美标";
                    btnEurope.Text = "欧标";
                    grbFixedFreq.Text = "定频值";
                    grbHopping1.Text = "跳频值1";
                    grbHopping2.Text = "跳频值2";
                    grbHopping3.Text = "跳频值3";
                    grbHopping4.Text = "跳频值4";
                    grbHopping5.Text = "跳频值5";
                    grbHopping6.Text = "跳频值6";
                    #endregion
                    
                    #region ---Button---
                    btnGetConfig.Text = "获取参数(&G)";
                    btnSetConfig.Text = "设置参数(&S)";
                    btnDefaultConfig.Text = "默认所有参数(&A)";
                    #endregion
                    #endregion

                    #region ---Other Config---
                    tabOther.Text = "其他参数设置";
                    
                    #region ---Address配置---
                    grbAddressPara.Text = "通讯地址配置";

                    grbAddressOld.Text = "原有通讯地址";
                    grbAddressNew.Text = "待设置通讯地址";

                    btnGetAddress.Text = "获取地址";
                    btnSetAddress.Text = "设置新地址";
                    btnDefaultAddress.Text = "恢复地址默认值";
                    #endregion

                    #region ---TCPIP配置---
                    grbTcpip.Text = "TCPIP参数设置";

                    grbIPAddress.Text = "IP地址";
                    grbIPPort.Text = "IP端口";
                    grbSubnet.Text = "子网掩码";
                    grbGateway.Text = "网关地址";
                    grbMac.Text = "MAC地址";

                    btnGetTcpip.Text = "获取TCPIP参数";
                    btnSetTcpip.Text = "设置TCPIP参数";
                    btnDefaultTcpip.Text = "恢复TCPIP默认值";
                    #endregion

                    #region ---USB Output Type---
                    grbOutType.Text = "USB输出模式设置";

                    grbOutMode.Text = "输出类型";
                    grbOutLen.Text = "输出长度";
                    grbOutEnter.Text = "是否带回车符";

                    btnGetOutType.Text = "获取输出模式参数";
                    btnSetOutType.Text = "设置输出模式参数";
                    btnDefaultOutType.Text = "恢复输出模式默认值";
                    #endregion
                    #endregion

                    #region ---ISO18000-6B---
                    tab6B.Text = "ISO18000-6B 读写区";

                    grbIdentify6B.Text = "卡号识别区";
                    grbCard6B.Text = "卡号";

                    grbRead6B.Text = "读数据区";
                    grbReadAddr6B.Text = "地址";
                    grbReadLen6B.Text = "读数据长度";
                    grbReadData6B.Text = "数据显示";
                    
                    grbWrite6B.Text = "读数据区";
                    grbWriteAddr6B.Text = "地址";
                    grbWriteLen6B.Text = "读数据长度";
                    grbWriteData6B.Text = "数据显示";


                    btnIdentify6B.Text = "识别(&E)";
                    btnRead6B.Text = "读卡(&A)";
                    btnWrite6B.Text = "写卡(&R)";
                    #endregion

                    #region ---ISO18000-6C---
                    tab6C.Text = "EPC(GEN 2) 读写区";

                    grbIdentify6C.Text = "卡号识别区";
                    grbCard6C.Text = "卡号";

                    grbRead6C.Text = "读数据区";
                    grbReadBlock6C.Text = "块选择";
                    grbReadAddr6C.Text = "地址";
                    grbReadLen6C.Text = "读数据长度";
                    grbReadData6C.Text = "数据显示";
                    
                    grbWrite6C.Text = "读数据区";
                    grbWriteBlock6C.Text = "块选择";
                    grbWriteAddr6C.Text = "地址";
                    grbWriteLen6C.Text = "读数据长度";
                    grbWriteData6C.Text = "数据显示";


                    btnIdentify6C.Text = "识别(&E)";
                    btnRead6C.Text = "读卡(&A)";
                    btnWrite6C.Text = "写卡(&R)";

                    #endregion

                    #region ---Auto Read Tag---
                    tabAutoRead.Text = "自动获取标签演示";

                    grbAutoReadTag.Text = "EPC(GEN 2) 自动获取标签";
                      lblReadType.Text = "读卡类别:";
                    rdbSingle.Text = "单卡";
                    rdbMult.Text = "多卡";
                    chkIsSpt.Text = "是否区分天线号";
                    lblMaxCard.Text = "单次读卡数:";
                    lblCount.Text = "读卡总数:";
                    btnClear.Text = "清除(&C)";
                    dgvShow.Columns["colID"].HeaderText = "序号";
                    dgvShow.Columns["colAddress"].HeaderText = "天线号";
                    dgvShow.Columns["colHexCard"].HeaderText = "十六进制卡号";
                    dgvShow.Columns["colTime"].HeaderText = "时间";
                    dgvShow.Columns["colCount"].HeaderText = "次数";

                    btnClear.Text = "清除(&C)";
                    #endregion
                    break;
            }
        }
        #endregion

        #region ---Communication---
        private void InitCommunicationParamater()
        {
            #region ---Language---
            cmbLanguage.SelectedIndex = SSOption.Language;
            #endregion

            #region ---Communication---
            cmbCommType.SelectedIndex = SSOption.Communication;
            #endregion

            #region ---RS232---
            //串口
            foreach (string st in SerialPort.GetPortNames())
            {
                cmbPortName.Items.Add(st);
            }
            if (cmbPortName.Items.Count > 0) cmbPortName.SelectedIndex = 0;
            #endregion

            cmbPortName.Text = "COM" + SSOption.PortName;
            cmbBaudRate.Text = SSOption.BaudRate.ToString();

            txtRemoteIP.Text = SSOption.IP;
            txtRemotePort.Text = SSOption.IPPort.ToString();
        }

        public void UnloadInitCommunicationParamater()
        {
            SSOption.Language = cmbLanguage.SelectedIndex;
            SSOption.Communication = cmbCommType.SelectedIndex;
            SSOption.PortName = Convert.ToInt32(cmbPortName.Text.Replace("COM", ""));
            SSOption.BaudRate = Convert.ToInt32(cmbBaudRate.Text);
            SSOption.IP = txtRemoteIP.Text;
            SSOption.IPPort = Convert.ToInt32(txtRemotePort.Text);
        }

        private void cmbCommType_SelectedIndexChanged(object sender, EventArgs e)
        {
            SSOption.Communication = ((ComboBox)sender).SelectedIndex;
            switch (SSOption.Communication)
            {
                case RS232:
                    pnlRS232.Visible = true;
                    pnlTCPIP.Visible = false;
                    grbTcpip.Visible = true;
                    grbOutType.Visible = false;
                    rdbMult.Enabled = true;
                    break;
                case TCPIP:
                    pnlRS232.Visible = false;
                    pnlTCPIP.Visible = true;
                    grbTcpip.Visible = true;
                    grbOutType.Visible = false;
                    rdbMult.Enabled = true;
                    break;
                case USB:
                    pnlRS232.Visible = false;
                    pnlTCPIP.Visible = false;
                    grbTcpip.Visible = false;
                    grbOutType.Visible = true;
                    rdbMult.Enabled = false;
                    break;
            }
        }

        private void cmbLanguage_SelectedIndexChanged(object sender, EventArgs e)
        {
            SSOption.Language = cmbLanguage.SelectedIndex;

            ChangeLanguage();
        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            btnConnect.Enabled = false;
            UnloadInitCommunicationParamater();
            int intHandle = 0;
            switch (SSOption.Communication)
            {
                case RS232:
                    intHandle = Adpdll.ap_open(SSOption.PortName, SSOption.BaudRate);
                    break;
                case TCPIP:
                    intHandle = Adpdll.an_open(SSOption.IP, SSOption.IPPort);
                    break;
                case USB:
                    while (intHandle == 0)
                    {
                        Application.DoEvents();
                        intHandle = Adpdll.ad_open();
                    }
                    break;
            }

            grbCommType.Enabled = pnlComm.Enabled = btnConnect.Enabled = !(intHandle > 0);
            btnDisConnect.Enabled = btnGetVer.Enabled = (intHandle > 0);

            OutPutMessage(string.Format("连接设备{0}!", intHandle > 0 ? "成功" : "失败"),
                            string.Format("Connect {0}!", intHandle > 0 ? "Succeed" : "failed"),
                            intHandle > 0 ? 0 : 1);
            if (intHandle > 0)
            {
                m_Handle = intHandle;
                tabBody.SelectedIndex = 0;
            }
        }

        private void btnDisConnect_Click(object sender, EventArgs e)
        {
            if (m_Handle <= 0) return;
            switch (SSOption.Communication)
            {
                case RS232:
                    Adpdll.ap_close(m_Handle);
                    break;
                case TCPIP:
                    Adpdll.an_close(m_Handle);
                    break;
                case USB:
                    Adpdll.ad_close(m_Handle);
                    break;
            }
            m_Handle = 0;
            grbCommType.Enabled = pnlComm.Enabled = btnConnect.Enabled = true;
            btnDisConnect.Enabled = btnGetVer.Enabled = false;
            tabBody.SelectedIndex = 0;
            tabBody.Enabled = false;
        }

        private int GetAddress()
        {
            switch (SSOption.Communication)
            {
                case RS232:
                    FCount = Adpdll.ap_getaddress(m_Handle, ref m_SerialNum, ref m_Version);
                    break;
                case TCPIP:
                    FCount = Adpdll.an_getaddress(m_Handle, ref m_SerialNum, ref m_Version);
                    break;
                case USB:
                    FCount = Adpdll.ad_getaddress(m_Handle, ref m_SerialNum, ref m_Version);
                    break;
            }

            if (FCount == 0)
            {
                txtAddressOld.Text = txtAddress.Text = m_SerialNum.ToString();
            }
            else
            {
                txtAddressOld.Text = txtAddress.Text = "- -";
            }
            return FCount;
        }

        private int SetAddress(int intAddress)
        {
            switch (SSOption.Communication)
            {
                case RS232:
                    FCount = Adpdll.ap_setaddress(m_Handle, m_SerialNum, intAddress);
                    break;
                case TCPIP:
                    FCount = Adpdll.an_setaddress(m_Handle, m_SerialNum, intAddress);
                    break;
                case USB:
                    FCount = Adpdll.ad_setaddress(m_Handle, m_SerialNum, intAddress);
                    break;
            }

            if (FCount == 0)
            {
                m_SerialNum = intAddress;
                txtAddressOld.Text = txtAddress.Text = m_SerialNum.ToString();
            }
            else
            {
                txtAddressOld.Text = txtAddress.Text = "- -";
            }
            return FCount;
        }

        private void btnGetVer_Click(object sender, EventArgs e)
        {
            GetAddress();
            OutPutMessage(string.Format("获取设备信息{0}!", FCount == 0 ? "成功" : "失败"),
                            string.Format("Get Version {0}!", FCount == 0 ? "Succeed" : "failed"),
                            FCount);

            if (FCount == 0)
            {
                txtVer.Text = m_Version.ToString().Insert(1, ".");
                tabBody.Enabled = true;
                Application.DoEvents();
                GetBasicConfig();
            }
            else
            {
                txtVer.Text = "- -";
                tabBody.Enabled = false;
            }
        }
        #endregion

        #region ---Parameter config---
        private void InitBasicParamater()
        {
            #region ---Hopping---
            cmbFixedFreq.Items.Clear();
            cmbHopping1.Items.Clear();
            cmbHopping2.Items.Clear();
            cmbHopping3.Items.Clear();
            cmbHopping4.Items.Clear();
            cmbHopping5.Items.Clear();
            cmbHopping6.Items.Clear();

            string[] strList;
            strList = new string[(int)((HOPPING_STOP - HOPPING_START) / HOPPING_STEP) + 1];
            for (int i = 0; i < strList.Length; i++)
            {
                strList[i] = (HOPPING_START + i * HOPPING_STEP).ToString("00.0");
            }

            cmbFixedFreq.Items.AddRange(strList);
            cmbHopping1.Items.AddRange(strList);
            cmbHopping2.Items.AddRange(strList);
            cmbHopping3.Items.AddRange(strList);
            cmbHopping4.Items.AddRange(strList);
            cmbHopping5.Items.AddRange(strList);
            cmbHopping6.Items.AddRange(strList);

            DefaultPara();
            #endregion
        }
        
        private void DefaultPara()
        {
            cmbPowerSize.SelectedIndex = 30;
            cmbWorkMode.SelectedIndex = 2 - 1;
            nudReadInterval.Value = 10;
            cmbTrigger.SelectedIndex = 0;
            cmbOutputMode.SelectedIndex = 6 - 1;
            nudByteOffset.Value = 0;
            nudOutInterval.Value = 30;
            nudPulseWidth.Value = 10;
            nudPulsePeriod.Value = 15;
            cmbCardType.SelectedIndex = 1;
            nudSameIDinterval.Value = 1;
            cmbBuzzer.SelectedIndex = 1;
            cmbMaxTag.SelectedIndex = 32 - 10;
            cmbEncrypt.SelectedIndex = 0;
            cmbFreqHopping.SelectedIndex = 1;
            LoadStandard(STANDARD.China);
            chkAntenna1.Checked = true;
            chkAntenna2.Checked = false;
            chkAntenna3.Checked = false;
            chkAntenna4.Checked = false;
            cmbMemory.SelectedIndex = 0;
            cmbStartAddress.SelectedIndex = 0;
            cmbLength.SelectedIndex = 1;
        }

        #region ---Hopping---
        const int HOPPING_START = 860;
        const int HOPPING_STOP = 960;
        const double HOPPING_STEP = 0.5;
        
        public enum STANDARD
        {
            China,
            America,
            Europe

        }

        private void LoadStandard(STANDARD stand)
        {
            switch (stand)
            {
                case STANDARD.Europe:
                    cmbFixedFreq.SelectedIndex = (int)((865 - HOPPING_START) / HOPPING_STEP);
                    cmbHopping1.SelectedIndex = (int)((860 - HOPPING_START) / HOPPING_STEP);
                    cmbHopping2.SelectedIndex = (int)((862 - HOPPING_START) / HOPPING_STEP);
                    cmbHopping3.SelectedIndex = (int)((864 - HOPPING_START) / HOPPING_STEP);
                    cmbHopping4.SelectedIndex = (int)((866 - HOPPING_START) / HOPPING_STEP);
                    cmbHopping5.SelectedIndex = (int)((868 - HOPPING_START) / HOPPING_STEP);
                    cmbHopping6.SelectedIndex = (int)((870 - HOPPING_START) / HOPPING_STEP);
                    break;
                case STANDARD.America:
                    cmbFixedFreq.SelectedIndex = (int)((915 - HOPPING_START) / HOPPING_STEP);
                    cmbHopping1.SelectedIndex = (int)((902 - HOPPING_START) / HOPPING_STEP);
                    cmbHopping2.SelectedIndex = (int)((907 - HOPPING_START) / HOPPING_STEP);
                    cmbHopping3.SelectedIndex = (int)((912 - HOPPING_START) / HOPPING_STEP);
                    cmbHopping4.SelectedIndex = (int)((917 - HOPPING_START) / HOPPING_STEP);
                    cmbHopping5.SelectedIndex = (int)((922 - HOPPING_START) / HOPPING_STEP);
                    cmbHopping6.SelectedIndex = (int)((928 - HOPPING_START) / HOPPING_STEP);
                    break;
                default:
                    cmbFixedFreq.SelectedIndex = (int)((915 - HOPPING_START) / HOPPING_STEP);
                    cmbHopping1.SelectedIndex = (int)((902 - HOPPING_START) / HOPPING_STEP);
                    cmbHopping2.SelectedIndex = (int)((906.5 - HOPPING_START) / HOPPING_STEP);
                    cmbHopping3.SelectedIndex = (int)((911 - HOPPING_START) / HOPPING_STEP);
                    cmbHopping4.SelectedIndex = (int)((915 - HOPPING_START) / HOPPING_STEP);
                    cmbHopping5.SelectedIndex = (int)((919.5 - HOPPING_START) / HOPPING_STEP);
                    cmbHopping6.SelectedIndex = (int)((925 - HOPPING_START) / HOPPING_STEP);
                    break;
            }
        }

        private void btnEurope_Click(object sender, EventArgs e)
        {
            LoadStandard(STANDARD.Europe);
            OutPutMessage("初始化欧标参数!", "Init Europe Standard!", 0);
        }

        private void btnAmerica_Click(object sender, EventArgs e)
        {
            LoadStandard(STANDARD.America);
            OutPutMessage("初始化美标参数!", "Init America Standard!",0);
        }

        private void btnChina_Click(object sender, EventArgs e)
        {
            LoadStandard(STANDARD.China);
            OutPutMessage("初始化国标参数!", "Init China Standard!", 0);
        }

        private void cmbFreqHopping_SelectedIndexChanged(object sender, EventArgs e)
        {
            grbHoppingO.Visible = ((ComboBox)sender).SelectedIndex > 0;
            pnlHopping2.Visible = grbHoppingO.Visible;
            grbFixedFreq.Visible = !grbHoppingO.Visible;
        }
        #endregion

        private void txtChangePwd_TextChanged(object sender, EventArgs e)
        {
            if (txtChangePwd.Text == "0987654321")
            {
                grbPassword.Visible = true;
                grbPassword.Enabled = false;
                grbEncrypt.Visible = true;
                grbChangePwd.Visible = false;
            }
        }

        private void cmbEncrypt_SelectedIndexChanged(object sender, EventArgs e)
        {
            grbPassword.Enabled = ((ComboBox)sender).SelectedIndex > 0;
        }

        private void cmbCardType_SelectedIndexChanged(object sender, EventArgs e)
        {
            pnlParaS2.Visible = (cmbCardType.SelectedIndex == 3 || cmbCardType.SelectedIndex == 2);
            grbLength.Visible = cmbCardType.SelectedIndex == 3;
            grbStartAddress.Visible = cmbCardType.SelectedIndex == 3;
            grbMemory.Visible = cmbCardType.SelectedIndex == 3;

            grbMaxTag.Visible = cmbCardType.SelectedIndex == 2;
        }

        private void btnDefaultConfig_Click(object sender, EventArgs e)
        {
            DefaultPara();
            OutPutMessage("初始化所有参数!", "Init all parameters!", 0);
        }

        private bool ShowBasicParaInfo(byte[] info)
        {
            try
            {
                int intStepCount = 0;
                cmbPowerSize.SelectedIndex = info[intStepCount++];

                cmbFreqHopping.SelectedIndex = info[intStepCount++];

                cmbFixedFreq.SelectedIndex = info[intStepCount++];

                cmbHopping1.SelectedIndex = info[intStepCount++];

                cmbHopping2.SelectedIndex = info[intStepCount++];

                cmbHopping3.SelectedIndex = info[intStepCount++];

                cmbHopping4.SelectedIndex = info[intStepCount++];

                cmbHopping5.SelectedIndex = info[intStepCount++];

                cmbHopping6.SelectedIndex = info[intStepCount++];

                m_WorkMode = info[intStepCount++];
                cmbWorkMode.SelectedIndex = m_WorkMode - 1;

                nudReadInterval.Value = info[intStepCount++];

                cmbTrigger.SelectedIndex = info[intStepCount++] > 0 ? 1 : 0;

                cmbOutputMode.SelectedIndex = info[intStepCount++] -1;

                nudByteOffset.Value = info[intStepCount++];

                nudOutInterval.Value = info[intStepCount++];

                nudPulseWidth.Value = info[intStepCount++];

                nudPulsePeriod.Value = info[intStepCount++];

                int intAntenna = info[intStepCount++];

                chkAntenna1.Checked = Convert.ToBoolean(intAntenna & 1);
                chkAntenna2.Checked = Convert.ToBoolean(intAntenna & 2);
                chkAntenna3.Checked = Convert.ToBoolean(intAntenna & 4);
                chkAntenna4.Checked = Convert.ToBoolean(intAntenna & 8);

                int intCardType = info[intStepCount++];
                switch (intCardType)
                {
                    case 1:
                        cmbCardType.SelectedIndex = 0;
                        break;
                    case 16:
                        cmbCardType.SelectedIndex = 1;
                        break;
                    case 32:
                        cmbCardType.SelectedIndex = 2;
                        break;
                    case 64:
                        cmbCardType.SelectedIndex = 3;
                        break;
                    case 17:
                        cmbCardType.SelectedIndex = 4;
                        break;
                    default:
                        MessageBox.Show("CardType Set Error!", this.Text, MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
                        break;
                }

                nudSameIDinterval.Value = info[intStepCount++];

                cmbBuzzer.SelectedIndex = info[intStepCount++];

                int intMemory = info[intStepCount++];
                cmbMemory.SelectedIndex = intMemory >= 2 ? (intMemory - 2) : 0;

                cmbStartAddress.SelectedIndex = info[intStepCount++];

                cmbLength.SelectedIndex = info[intStepCount++] -1;

                cmbEncrypt.SelectedIndex = info[intStepCount++];

                int intPassword = info[intStepCount++] * 256 + info[intStepCount++];
                txtPassword.Text = intPassword.ToString("0000");

                cmbMaxTag.SelectedIndex = info[intStepCount++] - 10;
                return true;

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString(), this.Text, MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            return false;
        }

        private byte[] GetBasicParaInfo()
        {
            List<byte> lstByte = new List<byte>();

            lstByte.Add((byte)cmbPowerSize.SelectedIndex);

            lstByte.Add((byte)cmbFreqHopping.SelectedIndex);
            lstByte.Add((byte)cmbFixedFreq.SelectedIndex);
            lstByte.Add((byte)cmbHopping1.SelectedIndex);
            lstByte.Add((byte)cmbHopping2.SelectedIndex);
            lstByte.Add((byte)cmbHopping3.SelectedIndex);
            lstByte.Add((byte)cmbHopping4.SelectedIndex);
            lstByte.Add((byte)cmbHopping5.SelectedIndex);
            lstByte.Add((byte)cmbHopping6.SelectedIndex);

            lstByte.Add((byte)(cmbWorkMode.SelectedIndex + 1));
            lstByte.Add((byte)nudReadInterval.Value);
            lstByte.Add((byte)(cmbTrigger.SelectedIndex > 0 ? 2 : 0));

            lstByte.Add((byte)(cmbOutputMode.SelectedIndex + 1));

            lstByte.Add((byte)nudByteOffset.Value);
            lstByte.Add((byte)nudOutInterval.Value);
            lstByte.Add((byte)nudPulseWidth.Value);
            lstByte.Add((byte)nudPulsePeriod.Value);

            int intAntenna = 0;
            if (chkAntenna1.Checked) intAntenna = intAntenna | 1;
            if (chkAntenna2.Checked) intAntenna = intAntenna | 2;
            if (chkAntenna3.Checked) intAntenna = intAntenna | 4;
            if (chkAntenna4.Checked) intAntenna = intAntenna | 8;

            lstByte.Add((byte)intAntenna);


            int intCardType = 0;
            switch (cmbCardType.SelectedIndex)
            {
                case 0:
                    intCardType = 1;
                    break;
                case 1:
                    intCardType = 16;
                    break;
                case 2:
                    intCardType = 32;
                    break;
                case 3:
                    intCardType = 64;
                    break;
                case 4:
                    intCardType = 17;
                    break;
                default:
                    intCardType = 16;
                    break;
            }

            lstByte.Add((byte)intCardType);

            lstByte.Add((byte)nudSameIDinterval.Value);

            lstByte.Add((byte)cmbBuzzer.SelectedIndex);

            lstByte.Add((byte)(cmbMemory.SelectedIndex + 2));

            lstByte.Add((byte)cmbStartAddress.SelectedIndex);

            lstByte.Add((byte)(cmbLength.SelectedIndex + 1));

            lstByte.Add((byte)cmbEncrypt.SelectedIndex);

            int intPassword = Convert.ToInt32(txtPassword.Text);
            lstByte.Add((byte)(intPassword / 256));
            lstByte.Add((byte)(intPassword % 256));

            lstByte.Add((byte)(cmbMaxTag.SelectedIndex + 10));

            return lstByte.ToArray();
        }

        private int GetBasicConfig()
        {
            IntPtr ptrRcvData = Marshal.UnsafeAddrOfPinnedArrayElement(bytRcvData, 0);

            switch (SSOption.Communication)
            {
                case RS232:
                    FCount = Adpdll.ap_getconfig(m_Handle, m_SerialNum, ptrRcvData, ref bytRcvLen);
                    break;
                case TCPIP:
                    FCount = Adpdll.an_getconfig(m_Handle, m_SerialNum, ptrRcvData, ref bytRcvLen);
                    break;
                case USB:
                    FCount = Adpdll.ad_getconfig(m_Handle, m_SerialNum, ptrRcvData, ref bytRcvLen);
                    break;
            }
            if (FCount == 0)
            {
                ShowBasicParaInfo(bytRcvData);
            }
            return FCount;
        }

        private int SetBasicConfig()
        {
            byte[] data = GetBasicParaInfo();
            Console.WriteLine( Adpdll.ByteArrayToHexString(data, 0, data.Length)+Environment.NewLine );
            switch (SSOption.Communication)
            {
                case RS232:
                    FCount = Adpdll.ap_setconfig(m_Handle, m_SerialNum, data, (byte)data.Length);
                    break;
                case TCPIP:
                    FCount = Adpdll.an_setconfig(m_Handle, m_SerialNum, data, (byte)data.Length);
                    break;
                case USB:
                    FCount = Adpdll.ad_setconfig(m_Handle, m_SerialNum, data, (byte)data.Length);
                    break;
            }
            if (FCount == 0) m_WorkMode = cmbWorkMode.SelectedIndex + 1;
            return FCount;
        }

        private void btnGetConfig_Click(object sender, EventArgs e)
        {
            GetBasicConfig();
            OutPutMessage(string.Format("获取基本参数{0}!", FCount == 0 ? "成功" : "失败"),
                            string.Format("Get Basic Parameters {0}!", FCount == 0 ? "Succeed" : "failed"),
                            FCount);
        }

        private void btnSetConfig_Click(object sender, EventArgs e)
        {
            SetBasicConfig();
            OutPutMessage(string.Format("设置基本参数{0}!", FCount == 0 ? "成功" : "失败"),
                            string.Format("Set Basic Parameters {0}!", FCount == 0 ? "Succeed" : "failed"),
                            FCount);
        }
        #endregion

        #region ---Other Config---
        private void InitOtherParamater()
        {
            txtAddressNew.Text = "65535";
            DefaultTcpipParaInfo();
            DefaultOutTypeParaInfo();
        }

        private void btnDefaultAddress_Click(object sender, EventArgs e)
        {
            txtAddressNew.Text = "65535";
            OutPutMessage("初始化通讯地址!", "Init Communication Address!", 0);
        }

        private void btnGetAddress_Click(object sender, EventArgs e)
        {
            GetAddress();
            OutPutMessage(string.Format("获取通讯地址{0}!", FCount == 0 ? "成功" : "失败"),
                            string.Format("Get Communication Address {0}!", FCount == 0 ? "Succeed" : "failed"),
                            FCount);
        }

        private void btnSetAddress_Click(object sender, EventArgs e)
        {
            SetAddress(Convert.ToInt32(txtAddressNew.Text.ToString().Trim()));
            OutPutMessage(string.Format("设置通讯地址{0}!", FCount == 0 ? "成功" : "失败"),
                            string.Format("Set Communication Address {0}!", FCount == 0 ? "Succeed" : "failed"),
                            FCount);
        }

        #region ---Tcpip---
        private void DefaultTcpipParaInfo()
        {
            txtIPAddress.Text = "192.168.1.115";

            txtSubnet.Text = "255.255.255.0";

            txtGateWay.Text = "192.168.1.1";

            txtIPPort.Text = "49152";

            txtMac.Text = "5E-45-A2-6C-30-1E";
        }

        private void ShowTcpipParaInfo(byte[] info)
        {
            try
            {
                int intStepCount = 0;
                txtIPAddress.Text = string.Format("{0}.{1}.{2}.{3}", info[intStepCount++], info[intStepCount++], info[intStepCount++], info[intStepCount++]);

                txtSubnet.Text = string.Format("{0}.{1}.{2}.{3}", info[intStepCount++], info[intStepCount++], info[intStepCount++], info[intStepCount++]);

                txtGateWay.Text = string.Format("{0}.{1}.{2}.{3}", info[intStepCount++], info[intStepCount++], info[intStepCount++], info[intStepCount++]);

                txtIPPort.Text = (info[intStepCount++] + info[intStepCount++]*256).ToString();

                byte[] bytMac = new byte[6];
                for (int i = 0; i < bytMac.Length; i++)
                {
                    bytMac[i] = info[intStepCount++];
                }
                txtMac.Text = Convert.ToString(bytMac[0], 16).PadLeft(2, '0').ToUpper() + "-" +
                   Convert.ToString(bytMac[1], 16).PadLeft(2, '0').ToUpper() + "-" +
                   Convert.ToString(bytMac[2], 16).PadLeft(2, '0').ToUpper() + "-" +
                   Convert.ToString(bytMac[3], 16).PadLeft(2, '0').ToUpper() + "-" +
                   Convert.ToString(bytMac[4], 16).PadLeft(2, '0').ToUpper() + "-" +
                   Convert.ToString(bytMac[5], 16).PadLeft(2, '0').ToUpper();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString(), this.Text, MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private byte[] GetTcpipParaInfo()
        {
            List<byte> lstByte = new List<byte>();
            string[] strTemp;

            strTemp = txtIPAddress.Text.ToString().Trim().Split('.');
            lstByte.Add(Convert.ToByte(Convert.ToInt32(strTemp[0])));
            lstByte.Add(Convert.ToByte(Convert.ToInt32(strTemp[1])));
            lstByte.Add(Convert.ToByte(Convert.ToInt32(strTemp[2])));
            lstByte.Add(Convert.ToByte(Convert.ToInt32(strTemp[3])));

            strTemp = txtSubnet.Text.ToString().Trim().Split('.');
            lstByte.Add(Convert.ToByte(Convert.ToInt32(strTemp[0])));
            lstByte.Add(Convert.ToByte(Convert.ToInt32(strTemp[1])));
            lstByte.Add(Convert.ToByte(Convert.ToInt32(strTemp[2])));
            lstByte.Add(Convert.ToByte(Convert.ToInt32(strTemp[3])));

            strTemp = txtGateWay.Text.ToString().Trim().Split('.');
            lstByte.Add(Convert.ToByte(Convert.ToInt32(strTemp[0])));
            lstByte.Add(Convert.ToByte(Convert.ToInt32(strTemp[1])));
            lstByte.Add(Convert.ToByte(Convert.ToInt32(strTemp[2])));
            lstByte.Add(Convert.ToByte(Convert.ToInt32(strTemp[3])));

            int intPort = Convert.ToInt32(txtIPPort.Text.ToString().Trim());
            lstByte.Add(Convert.ToByte(intPort % 256));
            lstByte.Add(Convert.ToByte(intPort / 256));

            string strMac = txtMac.Text.ToString().Trim().Replace("-", "");
            byte[] bytMac = Adpdll.HexStringToByteArray(strMac);
            if (bytMac.Length < 6)
            {
                bytMac = new byte[] { 0x5E, 0x45, 0xA2, 0x6C, 0x30, 0x1E };
            }
            lstByte.Add(bytMac[0]);
            lstByte.Add(bytMac[1]);
            lstByte.Add(bytMac[2]);
            lstByte.Add(bytMac[3]);
            lstByte.Add(bytMac[4]);
            lstByte.Add(bytMac[5]);
            return lstByte.ToArray();
        }

        private int GetTcpipConfig()
        {
            IntPtr ptrRcvData = Marshal.UnsafeAddrOfPinnedArrayElement(bytRcvData, 0);

            switch (SSOption.Communication)
            {
                case RS232:
                    FCount = Adpdll.ap_gettcpip(m_Handle, m_SerialNum, ptrRcvData, ref bytRcvLen);
                    break;
                case TCPIP:
                    FCount = Adpdll.an_gettcpip(m_Handle, m_SerialNum, ptrRcvData, ref bytRcvLen);
                    break;
            }
            if (FCount == 0)
            {
                ShowTcpipParaInfo(bytRcvData);
            }
            return FCount;
        }

        private int SetTcpipConfig()
        {
            byte[] data = GetTcpipParaInfo();
            switch (SSOption.Communication)
            {
                case RS232:
                    FCount = Adpdll.ap_settcpip(m_Handle, m_SerialNum, data, (byte)data.Length);
                    break;
                case TCPIP:
                    FCount = Adpdll.an_settcpip(m_Handle, m_SerialNum, data, (byte)data.Length);
                    break;
            }
            return FCount;
        }

        private void btnDefaultTcpip_Click(object sender, EventArgs e)
        {
            DefaultTcpipParaInfo();
            OutPutMessage("初始化网络参数!", "Init Network Parameters!", 0);
        }

        private void btnGetTcpip_Click(object sender, EventArgs e)
        {
            GetTcpipConfig();
            OutPutMessage(string.Format("获取网络参数{0}!", FCount == 0 ? "成功" : "失败"),
                            string.Format("Get Network Parameters {0}!", FCount == 0 ? "Succeed" : "failed"),
                            FCount);
        }

        private void btnSetTcpip_Click(object sender, EventArgs e)
        {
            SetTcpipConfig();
            OutPutMessage(string.Format("设置网络参数{0}!", FCount == 0 ? "成功" : "失败"),
                            string.Format("Set Network Parameters {0}!", FCount == 0 ? "Succeed" : "failed"),
                            FCount);
        }
        #endregion

        #region ---OutType---
        private void DefaultOutTypeParaInfo()
        {
            cmbOutMode.SelectedIndex = 0;
            cmbOutLen.SelectedIndex = 0;
            cmbOutEnter.SelectedIndex = 0;
        }

        private void ShowOutTypeParaInfo(byte[] info)
        {
            try
            {
                int intStepCount = 0;
                cmbOutMode.SelectedIndex = info[intStepCount++] - 1;
                cmbOutLen.SelectedIndex = info[intStepCount++] - 8;
                cmbOutEnter.SelectedIndex = info[intStepCount++];
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString(), this.Text, MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private byte[] GetOutTypeParaInfo()
        {
            List<byte> lstByte = new List<byte>();
            lstByte.Add(Convert.ToByte(cmbOutMode.SelectedIndex+1));
            lstByte.Add(Convert.ToByte(cmbOutLen.SelectedIndex+8));
            lstByte.Add(Convert.ToByte(cmbOutEnter.SelectedIndex));
            return lstByte.ToArray();
        }

        private int GetOutTypeConfig()
        {
            IntPtr ptrRcvData = Marshal.UnsafeAddrOfPinnedArrayElement(bytRcvData, 0);

            switch (SSOption.Communication)
            {
                case USB:
                    FCount = Adpdll.ad_getoutstatus(m_Handle, m_SerialNum, ptrRcvData, ref bytRcvLen);
                    break;
            }
            if (FCount == 0)
            {
                ShowOutTypeParaInfo(bytRcvData);
            }
            return FCount;
        }

        private int SetOutTypeConfig()
        {
            byte[] data = GetOutTypeParaInfo();
            switch (SSOption.Communication)
            {
                case USB:
                    FCount = Adpdll.ad_setoutstatus(m_Handle, m_SerialNum, data, (byte)data.Length);
                    break;
            }
            return FCount;
        }

        private void btnDefaultOutType_Click(object sender, EventArgs e)
        {
            DefaultOutTypeParaInfo();
        }

        private void btnGetOutType_Click(object sender, EventArgs e)
        {
            GetOutTypeConfig();
            OutPutMessage(string.Format("获取输出参数{0}!", FCount == 0 ? "成功" : "失败"),
                            string.Format("Get OutPut Parameters {0}!", FCount == 0 ? "Succeed" : "failed"),
                            FCount);
        }

        private void btnSetOutType_Click(object sender, EventArgs e)
        {
            SetOutTypeConfig();
            OutPutMessage(string.Format("设置输出参数{0}!", FCount == 0 ? "成功" : "失败"),
                            string.Format("Set OutPut Parameters {0}!", FCount == 0 ? "Succeed" : "failed"),
                            FCount);
        }
        #endregion
        #endregion

        #region ---ISO18000-6B---
        private void btnIdentify6B_Click(object sender, EventArgs e)
        {
            IntPtr ptrRcvData = Marshal.UnsafeAddrOfPinnedArrayElement(bytRcvData, 0);

            switch (SSOption.Communication)
            {
                case RS232:
                    FCount = Adpdll.ap_identify6b(m_Handle, m_SerialNum, ptrRcvData, ref bytRcvLen);
                    break;
                case TCPIP:
                    FCount = Adpdll.an_identify6b(m_Handle, m_SerialNum, ptrRcvData, ref bytRcvLen);
                    break;
                case USB:
                    FCount = Adpdll.ad_identify6b(m_Handle, m_SerialNum, ptrRcvData, ref bytRcvLen);
                    break;
            }

            OutPutMessage(string.Format("识别标签{0}!", FCount == 0 ? "成功" : "失败"),
                            string.Format("Identify Tag {0}!", FCount == 0 ? "Succeed" : "failed"),
                            FCount);

            txtCard6B.Text = (FCount == 0 ? Adpdll.ByteArrayToHexString(bytRcvData, 1, bytRcvLen) : "");
        }

        private void btnRead6B_Click(object sender, EventArgs e)
        {
            byte addr = Convert.ToByte(txtReadAddr6B.Text);
            byte len = Convert.ToByte(txtReadLen6B.Text);

            IntPtr ptrRcvData = Marshal.UnsafeAddrOfPinnedArrayElement(bytRcvData, 0);

            switch (SSOption.Communication)
            {
                case RS232:
                    FCount = Adpdll.ap_read6b(m_Handle, m_SerialNum, ptrRcvData, addr, len);
                    break;
                case TCPIP:
                    FCount = Adpdll.an_read6b(m_Handle, m_SerialNum, ptrRcvData, addr, len);
                    break;
                case USB:
                    FCount = Adpdll.ad_read6b(m_Handle, m_SerialNum, ptrRcvData, addr, len);
                    break;
            }

            OutPutMessage(string.Format("{0}!", FCount == 0 ? "成功" : "失败"),
                            string.Format("Read Tag Data {0}!", FCount == 0 ? "Succeed" : "failed"),
                            FCount);

            txtReadData6B.Text = (FCount == 0 ? Adpdll.ByteArrayToHexString(bytRcvData, 1, len) : "");
        }

        private void btnWrite6B_Click(object sender, EventArgs e)
        {
            byte addr = Convert.ToByte(txtWriteAddr6B.Text);
            byte len = Convert.ToByte(txtWriteLen6B.Text);
            byte[] data = Adpdll.HexStringToByteArray(txtWriteData6B.Text);

            IntPtr ptrRcvData = Marshal.UnsafeAddrOfPinnedArrayElement(bytRcvData, 0);

            switch (SSOption.Communication)
            {
                case RS232:
                    FCount = Adpdll.ap_write6b(m_Handle, m_SerialNum, data, addr, len);
                    break;
                case TCPIP:
                    FCount = Adpdll.an_write6b(m_Handle, m_SerialNum, data, addr, len);
                    break;
                case USB:
                    FCount = Adpdll.ad_write6b(m_Handle, m_SerialNum, data, addr, len);
                    break;
            }

            OutPutMessage(string.Format("写入标签数据{0}!", FCount == 0 ? "成功" : "失败"),
                            string.Format("Write Tag Data {0}!", FCount == 0 ? "Succeed" : "failed"),
                            FCount);
        }
        #endregion

        #region ---ISO18000-6C---
        private void InitEPCParamater()
        {
            cmbReadBlock6C.SelectedIndex = cmbWriteBlock6C.SelectedIndex = 0;
        }

        Adpdll.CardInfo idCardInfo = new Adpdll.CardInfo();
        private void btnIdentify6C_Click(object sender, EventArgs e)
        {
            IntPtr ptrRcvData = Marshal.UnsafeAddrOfPinnedArrayElement(bytRcvData, 0);
            idCardInfo.DataBytes = new byte[64];
            switch (SSOption.Communication)
            {
                case RS232:
                   // FCount = Adpdll.ap_identify6c_c(m_Handle, m_SerialNum, ref idCardInfo);
                    FCount = Adpdll.ap_identify6c(m_Handle, m_SerialNum, ptrRcvData, ref bytRcvLen);
                    break;
                case TCPIP:
                    FCount = Adpdll.an_identify6c(m_Handle, m_SerialNum, ptrRcvData, ref bytRcvLen);
                    break;
                case USB:
                    FCount = Adpdll.ad_identify6c(m_Handle, m_SerialNum, ptrRcvData, ref bytRcvLen);
                    break;
            }

            OutPutMessage(string.Format("识别标签{0}!", FCount == 0 ? "成功" : "失败"),
                            string.Format("Identify Tag {0}!", FCount == 0 ? "Succeed" : "failed"),
                            FCount);

            //txtCard6C.Text = (FCount == 0 ? Adpdll.ByteArrayToHexString(idCardInfo.DataBytes, 0, idCardInfo.DataLength) : "");
           txtCard6C.Text = (FCount == 0 ? Adpdll.ByteArrayToHexString(bytRcvData, 1, bytRcvLen) : "");
        }

        private void btnRead6C_Click(object sender, EventArgs e)
        {
            byte mem = Convert.ToByte(cmbReadBlock6C.SelectedIndex+1);
            byte addr = Convert.ToByte(txtReadAddr6C.Text);
            byte len = Convert.ToByte(txtReadLen6C.Text);

            IntPtr ptrRcvData = Marshal.UnsafeAddrOfPinnedArrayElement(bytRcvData, 0);

            switch (SSOption.Communication)
            {
                case RS232:
                    FCount = Adpdll.ap_read6c(m_Handle, m_SerialNum, ptrRcvData, mem,addr, len);
                    break;
                case TCPIP:
                    FCount = Adpdll.an_read6c(m_Handle, m_SerialNum, ptrRcvData, mem, addr, len);
                    break;
                case USB:
                    FCount = Adpdll.ad_read6c(m_Handle, m_SerialNum, ptrRcvData, mem, addr, len);
                    break;
            }

            OutPutMessage(string.Format("读取标签数据{0}!", FCount == 0 ? "成功" : "失败"),
                            string.Format("Read Tag Data {0}!", FCount == 0 ? "Succeed" : "failed"),
                            FCount);

            txtReadData6C.Text = (FCount == 0 ? Adpdll.ByteArrayToHexString(bytRcvData, 1, len) : "");
        }

        private void btnWrite6C_Click(object sender, EventArgs e)
        {
            byte mem = Convert.ToByte(cmbWriteBlock6C.SelectedIndex + 1);
            byte addr = Convert.ToByte(txtWriteAddr6C.Text);
            byte len = Convert.ToByte(txtWriteLen6C.Text);
            byte[] data = Adpdll.HexStringToByteArray(txtWriteData6C.Text);

            IntPtr ptrRcvData = Marshal.UnsafeAddrOfPinnedArrayElement(bytRcvData, 0);

            switch (SSOption.Communication)
            {
                case RS232:
                    FCount = Adpdll.ap_write6c(m_Handle, m_SerialNum, data, mem,addr, len);
                    break;
                case TCPIP:
                    FCount = Adpdll.an_write6c(m_Handle, m_SerialNum, data, mem, addr, len);
                    break;
                case USB:
                    FCount = Adpdll.ad_write6c(m_Handle, m_SerialNum, data, mem, addr, len);
                    break;
            }

            OutPutMessage(string.Format("写入标签数据{0}!", FCount == 0 ? "成功" : "失败"),
                            string.Format("Write Tag Data {0}!", FCount == 0 ? "Succeed" : "failed"),
                            FCount);
        }
        #endregion

        #region ---Auto Read Tag---
        bool blnActiveEnabled = false;
        bool blnPassiveEnabled = false;
        byte[] autoDelData = new byte[512];
        byte[] autoRcvData = new byte[256];
        int autoDelCount = 0;

        Adpdll.CommandInfo autoDelCommand = new Adpdll.CommandInfo();

        IntPtr[] ptArray = new IntPtr[25];
        IntPtr ptrDelCard = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(Adpdll.CardInfo)));

        private void InitAutoReadPtr()
        {
            ptArray[0] = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(Adpdll.CardInfo)) * 25);
            Marshal.Copy(ptArray, 0, ptrDelCard, 1);
        }
        private delegate void CardManageDelegate(Adpdll.CardInfo cardInfo);

        private void CardManage(Adpdll.CardInfo cardInfo)
        {
            string strCard = Adpdll.ByteArrayToHexString(cardInfo.DataBytes, 0, cardInfo.DataLength);
            SystemPub.OutputLog(DateTime.Now.ToLongTimeString() + "," + cardInfo.Antenna.ToString() + "," + strCard);
            if (dgvShow.Rows.Count == 0)
            {
                dgvShow.Rows.Add((dgvShow.Rows.Count + 1).ToString(), cardInfo.Antenna, strCard, DateTime.Now.ToLongTimeString(), "1");
            }
            else
            {
                bool blnSearchflag = false;
                for (int m = 0; m < dgvShow.Rows.Count; m++)
                {
                    if (strCard == dgvShow["colHexCard", m].Value.ToString() &&
                        (chkIsSpt.Checked ? cardInfo.Antenna == Convert.ToInt32(dgvShow["colAddress", m].Value) : true))
                    {
                        int intcount = Convert.ToInt32(dgvShow["colCount", m].Value);
                        dgvShow["colAddress", m].Value = cardInfo.Antenna;
                        dgvShow["colCount", m].Value = (intcount + 1).ToString();
                        dgvShow["colTime", m].Value = DateTime.Now.ToLongTimeString();
                        blnSearchflag = true;

                        if (this.dgvShow.Rows[m].DefaultCellStyle.BackColor != Color.Gray)
                        {
                            this.dgvShow.Rows[m].DefaultCellStyle.BackColor = Color.Gray;
                        }
                        break;
                    }
                }
                if (!blnSearchflag)
                {
                    dgvShow.Rows.Add((dgvShow.Rows.Count + 1).ToString(), cardInfo.Antenna, strCard, DateTime.Now.ToLongTimeString(), "1");
                    this.dgvShow.Rows[dgvShow.Rows.Count - 1].DefaultCellStyle.BackColor = Color.Gray;
                }
            }
            txtCount.Text = dgvShow.Rows.Count.ToString();
        }

        private void GetActiveTag()
        {
            byte autoRcvLen = 255;
            FCount = 11;
            try
            {
                IntPtr ptrRcvData = Marshal.UnsafeAddrOfPinnedArrayElement(autoRcvData, 0);

                switch (SSOption.Communication)
                {
                    case RS232:
                        FCount = Adpdll.ap_getautocard(m_Handle, ptrRcvData, ref autoRcvLen);
                        break;
                    case TCPIP:
                        FCount = Adpdll.an_getautocard(m_Handle, ptrRcvData, ref autoRcvLen);
                        break;
                    case USB:
                        FCount = Adpdll.ad_getautocard(m_Handle, ptrRcvData, ref autoRcvLen);
                        break;
                }

                Console.WriteLine(FCount.ToString("00--") + autoRcvLen.ToString("00--") + autoDelCount.ToString());
                if (FCount == 0)
                {
                    for (int i = 0; i < autoRcvLen; i++) autoDelData[autoDelCount + i] = autoRcvData[i];
                    autoDelCount += autoRcvLen;

                    //IntPtr ptrDelData = Marshal.UnsafeAddrOfPinnedArrayElement(autoDelData, 0);
                    //int osize = 0;
                    //while (Adpdll.at_datatocard(ptrDelData, ref autoDelCount, ptrDelCard, ref osize) == 0)
                    //{
                    //    Adpdll.CardInfo autoDelCard = new Adpdll.CardInfo();
                    //    txtMaxCard.Text = osize.ToString();
                    //    for (int j = 0; j < osize; j++)
                    //    {
                    //        autoDelCard =
                    //        (Adpdll.CardInfo)Marshal.PtrToStructure((IntPtr)((UInt32)ptrDelCard + j * Marshal.SizeOf(typeof(Adpdll.CardInfo)))
                    //        , typeof(Adpdll.CardInfo));
                    //        this.BeginInvoke(new CardManageDelegate(CardManage), autoDelCard);
                    //    }
                    //}

                    IntPtr ptrDelData = Marshal.UnsafeAddrOfPinnedArrayElement(autoDelData, 0);
                    while (Adpdll.at_datatocommand(ptrDelData, ref autoDelCount, ref autoDelCommand) == 0)
                    {
                        Adpdll.CardInfo autoDelCard = new Adpdll.CardInfo();

                        txtMaxCard.Text = autoDelCommand.Count.ToString();
                        while (Adpdll.at_commandtocard(ref autoDelCommand, ref autoDelCard) == 0)
                        {
                            //CardManage(autoDelCard);
                            this.BeginInvoke(new CardManageDelegate(CardManage), autoDelCard);
                        }
                    }
                }
            }
            catch { }
        }

        private void GetPassiveTag()
        {
            FCount = 11;
            try
            {
                IntPtr ptrRcvData = Marshal.UnsafeAddrOfPinnedArrayElement(bytRcvData, 0);

                if (rdbMult.Checked)
                {
                    switch (SSOption.Communication)
                    {
                        case RS232:
                            FCount = Adpdll.ap_identify6cmult(m_Handle, m_SerialNum, ptrRcvData, ref bytRcvLen);
                            break;
                        case TCPIP:
                            FCount = Adpdll.an_identify6cmult(m_Handle, m_SerialNum, ptrRcvData, ref bytRcvLen);
                            break;
                        case USB:
                            break;
                    }
                }
                else
                {
                    switch (SSOption.Communication)
                    {
                        case RS232:
                            FCount = Adpdll.ap_identify6c(m_Handle, m_SerialNum, ptrRcvData, ref bytRcvLen);
                            break;
                        case TCPIP:
                            FCount = Adpdll.an_identify6c(m_Handle, m_SerialNum, ptrRcvData, ref bytRcvLen);
                            break;
                        case USB:
                            FCount = Adpdll.ad_identify6c(m_Handle, m_SerialNum, ptrRcvData, ref bytRcvLen);
                            break;
                    }
                }

                Console.WriteLine(Adpdll.ByteArrayToHexString(bytRcvData, 1, bytRcvLen));
                if (FCount == 0)
                {
                    if (bytRcvLen > 13)
                    {
                        IntPtr ptrCheckData = Marshal.UnsafeAddrOfPinnedArrayElement(bytRcvData, 0);
                        for (int i = 0; i < bytRcvLen / 14; i++)
                        {

                            txtMaxCard.Text = (bytRcvLen / 14).ToString();
                            if (Adpdll.at_checksum(ptrCheckData, i * 14, 13) == bytRcvData[i * 14 + 13])
                            {
                                Adpdll.CardInfo card = new Adpdll.CardInfo() { Antenna = bytRcvData[i * 14], DataLength = 12 };
                                card.DataBytes = new byte[64];
                                for (int m = 0; m < card.DataLength; m++)
                                {
                                    card.DataBytes[m] = bytRcvData[i * 14 + m + 1];
                                }
                                this.BeginInvoke(new CardManageDelegate(CardManage), card);
                            }
                        }
                    }
                    else
                    {
                        Adpdll.CardInfo card = new Adpdll.CardInfo() { Antenna = bytRcvData[0], DataLength = 12 };
                        card.DataBytes = new byte[64];
                        for (int m = 0; m < card.DataLength; m++)
                        {
                            card.DataBytes[m] = bytRcvData[1 + m];
                        }
                        this.BeginInvoke(new CardManageDelegate(CardManage), card);
                    }
                }
            }
            catch { }
        }

        private void ChangeGetCardStatus()
        {
            if (blnActiveEnabled)
            {
                blnPassiveEnabled = false;
                btnPassive.Text = "Passive";
                pnlReadType.Enabled = false;

                btnActive.Text = "Stop";
            }
            else if (blnPassiveEnabled)
            {
                blnActiveEnabled = false;
                btnActive.Text = "Acitve";
                pnlReadType.Enabled = true;

                btnPassive.Text = "Stop";
            }
            else
            {
                btnActive.Text = "Acitve";
                btnPassive.Text = "Passive";
            }

        }

        private void btnActive_Click(object sender, EventArgs e)
        {
            blnActiveEnabled = !blnActiveEnabled;
            ChangeGetCardStatus();
        }

        private void btnPassive_Click(object sender, EventArgs e)
        {
            blnPassiveEnabled = !blnPassiveEnabled;
            ChangeGetCardStatus();
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            dgvShow.Rows.Clear();
        }
        #endregion


        private string GetUserTextBoxMask(int count)
        {
            string strMask = "";
            if (count > 0)
            {
                strMask = "HH";
                for (int i = 0; i < count - 1; i++)
                {
                    strMask += "-HH";
                }
            }
            return strMask;
        }
        
        private void btnWriteCard_Click(object sender, EventArgs e)
        {
            blnWriteFlag = true;
        }

        private void btnReadCard_Click(object sender, EventArgs e)
        {
            blnReadFlag = !blnReadFlag;
            btnAutoCard.Text = blnReadFlag ? "Stop" : "Start";
        }

        bool blnWriteFlag = false;
        bool blnWriteMark = false;
        bool blnReadFlag = false;
        private void tmrWrite_Tick(object sender, EventArgs e)
        {
            Application.DoEvents();
            if (blnReadFlag && !blnWriteMark)
            {
                bool blnReadTempFlag = ReadCard();

                if (!ReadCard())
                {
                    OutPutMessage("未检测到卡!", "Please put the card!", 1000);
                    return;
                }
                    lblReadCardResult.Text = "";
                    lblWriteCardResult.Text = "";
                    OutPutMessage("已经检测到卡!", "The card have been detected!", 0);

                    if (CheckIsAddNewCard())
                    {
                        OutPutMessage("该卡已写!", "The card is written!", 1000, lblReadCardResult);
                        return;
                    }

                    if (chkIsAutoWrite.Checked) blnWriteFlag = true;

                    if (blnWriteFlag)
                    {
                        blnWriteMark = true;
                        if (WriteCard())
                        {
                            txtAlreadyCard.Value = txtStandbyCard.Value;
                            ChangeCardColor(txtAlreadyCard);

                            bool blnConfirmflag = false;
                            do
                            {
                                blnConfirmflag = ReadCard();
                                Application.DoEvents();
                            }
                            while (!blnConfirmflag);

                            blnConfirmflag = CheckIsAddNewCard();

                            OutPutMessage(string.Format("比对数据{0}!", blnConfirmflag ? "成功" : "失败"),
                                string.Format("Confirm Data {0}!", blnConfirmflag ? "Succeed" : "failed"), blnConfirmflag ? 0 : 1, lblReadCardResult);
                            if (blnConfirmflag)
                            {
                                if (chkIsAutoAdd.Checked) AddCard();
                            }
                        }
                        blnWriteFlag = false;
                        blnWriteMark = false;
                    }


                Application.DoEvents();
            }
        }
        
        byte[] bytOldWriteCardArray = new byte[12];
        byte[] bytNewWriteCardArray = new byte[12];
        byte[] bytWriteCardArray = new byte[4];

        int intPosition = 0;
        int intLength = 3;

        private bool CheckIsAddNewCard()
        {
            string strC = txtConfirmCard.Value;
            string strA = txtAlreadyCard.Value;
            return strC.Equals(strA);
        }

        private bool ReadCard()
        {
            IntPtr ptrRcvData = Marshal.UnsafeAddrOfPinnedArrayElement(bytRcvData, 0);
            idCardInfo.DataBytes = new byte[64];
            switch (SSOption.Communication)
            {
                case RS232:
                    FCount = Adpdll.ap_identify6c(m_Handle, m_SerialNum, ptrRcvData, ref bytRcvLen);
                    break;
                case TCPIP:
                    FCount = Adpdll.an_identify6c(m_Handle, m_SerialNum, ptrRcvData, ref bytRcvLen);
                    break;
                case USB:
                    FCount = Adpdll.ad_identify6c(m_Handle, m_SerialNum, ptrRcvData, ref bytRcvLen);
                    break;
            }

            if (FCount == 0)
            {

                if (chkIsEdit.Checked)
                {
                    for (int i = 0; i < 12; i++)
                    {
                        bytOldWriteCardArray[i] = bytRcvData[i + 1];
                    }
                    ShowOfSetCard(txtStandbyCard);
                }
                string strCard = Adpdll.ByteArrayToHexString(bytRcvData, 1, bytRcvLen - 1);
                txtConfirmCard.InputMask = GetUserTextBoxMask(bytRcvLen - 1);
                txtConfirmCard.Value = strCard;
                ChangeCardColor(txtConfirmCard);
                return true;
            }
            return false;
        }

        private bool WriteCard()
        {
                byte mem = Convert.ToByte(1);
                byte addr = Convert.ToByte(2);
                byte len = Convert.ToByte(12);
                byte[] data = Adpdll.HexStringToByteArray(txtStandbyCard.Value);

                IntPtr ptrRcvData = Marshal.UnsafeAddrOfPinnedArrayElement(bytRcvData, 0);
                switch (SSOption.Communication)
                {
                    case RS232:
                        FCount = Adpdll.ap_write6c(m_Handle, m_SerialNum, data, mem, addr, len);
                        break;
                    case TCPIP:
                        FCount = Adpdll.an_write6c(m_Handle, m_SerialNum, data, mem, addr, len);
                        break;
                    case USB:
                        FCount = Adpdll.ad_write6c(m_Handle, m_SerialNum, data, mem, addr, len);
                        break;
                }

                OutPutMessage(string.Format("写入数据{0}!", FCount == 0 ? "成功" : "失败"),
                                string.Format("Write Data {0}!", FCount == 0 ? "Succeed" : "failed"), FCount, lblWriteCardResult);
                if (FCount == 0)
                {
                    return true;
                }
            return false;
        }

        private void ChangeCardData(string inputCard)
        {
            byte[] bytNewWriteCardArray = Adpdll.HexStringToByteArray(inputCard);
            for (int i = 0; i < intPosition; i++)
            {
                bytOldWriteCardArray[i] = bytNewWriteCardArray[i];
            }
            for (int i = 0; i < intLength; i++)
            {
                bytWriteCardArray[intLength > 3 ? i : i + 1] = bytNewWriteCardArray[intPosition + i];
            }
            for (int i = intPosition + intLength; i < 12; i++)
            {
                bytOldWriteCardArray[i] = bytNewWriteCardArray[i];
            }
        }

        private void ShowOfSetCard(ADSDK.Control.UserRichTextBox ObjectivesBox)
        {
            ChangeCard();
            ShowWriteCard();
            ObjectivesBox.Value = Adpdll.ByteArrayToHexString(bytNewWriteCardArray, 0, 12);
            ChangeCardColor(ObjectivesBox);
        }

        private void ChangeCardColor(ADSDK.Control.UserRichTextBox ObjectivesBox)
        {
            ObjectivesBox.SelectionStart = 0;
            ObjectivesBox.SelectionLength = ObjectivesBox.Text.Length;
            ObjectivesBox.SelectionColor = Color.Black;

            ObjectivesBox.SelectionStart = intPosition * 3;
            ObjectivesBox.SelectionLength = intLength * 3 - 1;
            ObjectivesBox.SelectionColor = Color.Red;
        }

        private void ChangeCard(int intPosition, int intLength)
        {
            if (intLength != 3 && intLength != 4) return;
            if (intPosition + intLength - 12 > 0) intPosition -= 1;

            for (int i = 0; i < 12; i++)
            {
                bytNewWriteCardArray[i] = bytOldWriteCardArray[i];
            }
            for (int i = 0; i < intLength; i++)
            {
                bytNewWriteCardArray[intPosition + i] = bytWriteCardArray[(intLength > 3 ? i : i + 1)];
            }
        }

        private void ChangeCard()
        {
            ChangeCard(intPosition, intLength);
        }

        private void AddCard()
        {
            if (bytWriteCardArray[3] == 255)
            {
                if (bytWriteCardArray[2] == 255)
                {
                    if (bytWriteCardArray[1] == 255)
                    {
                        if (bytWriteCardArray[0] == 255)
                        {
                            bytWriteCardArray[0] = 0;
                        }
                        else
                            bytWriteCardArray[0]++;
                        bytWriteCardArray[1] = 0;
                    }
                    else
                        bytWriteCardArray[1]++;
                    bytWriteCardArray[2] = 0;
                }
                else
                    bytWriteCardArray[2]++;
                bytWriteCardArray[3] = 0;
            }
            else
                bytWriteCardArray[3]++;
            ShowOfSetCard(txtStandbyCard);
        }

        private void SubtractCard()
        {
            if (bytWriteCardArray[3] == 0)
            {
                if (bytWriteCardArray[2] == 0)
                {
                    if (bytWriteCardArray[1] == 0)
                    {
                        if (bytWriteCardArray[0] == 0)
                        {
                            bytWriteCardArray[0] = 255;
                        }
                        else
                            bytWriteCardArray[0]--;
                        bytWriteCardArray[1] = 255;
                    }
                    else
                        bytWriteCardArray[1]--;
                    bytWriteCardArray[2] = 255;
                }
                else
                    bytWriteCardArray[2]--;

                bytWriteCardArray[3] = 255;
            }
            else
                bytWriteCardArray[3]--;
            ShowOfSetCard(txtStandbyCard);
        }

        private void nudWriteLength_ValueChanged(object sender, EventArgs e)
        {
            intLength = (int)nudWriteLength.Value;
            blnShowWriteCardFlag = true;
            txtHexCard.InputMask = GetUserTextBoxMask(intLength);
            blnShowWriteCardFlag = false;

            ShowOfSetCard(txtStandbyCard);
        }

        private void txtStandbyCard_TextChanged(object sender, EventArgs e)
        {
            ChangeCardData(txtStandbyCard.Value);
            ShowOfSetCard(txtStandbyCard);
        }

        bool blnShowWriteCardFlag = false;
        private void ShowWriteCard()
        {
            blnShowWriteCardFlag = true;
            txtDecCard.Text = (intLength > 3 ?
                           ((long)bytWriteCardArray[0]) * 65536 * 256 +
                           ((long)bytWriteCardArray[1]) * 65536 +
                           ((long)bytWriteCardArray[2]) * 256 +
                           ((long)bytWriteCardArray[3]) :
                           ((long)bytWriteCardArray[1]) * 65536 +
                           ((long)bytWriteCardArray[2]) * 256 +
                           ((long)bytWriteCardArray[3])).ToString();
            txtHexCard.Value = Adpdll.ByteArrayToHexString(bytWriteCardArray, intLength > 3 ? 0 : 1, intLength);
            txtWiegandCard.Value = bytWriteCardArray[1].ToString("000")+
                                (bytWriteCardArray[2] * 256 +
                           bytWriteCardArray[3]).ToString("00000");
            blnShowWriteCardFlag = false;
        }

        private void txtDecCard_TextChanged(object sender, EventArgs e)
        {
            if (blnShowWriteCardFlag) return;
            try
            {
                long lngTemp = Convert.ToInt64(txtDecCard.Text);
                bytWriteCardArray[0] = Convert.ToByte(lngTemp / 65536 / 256);
                bytWriteCardArray[1] = Convert.ToByte((lngTemp % (65536 * 256)) / 65536);
                bytWriteCardArray[2] = Convert.ToByte((lngTemp % 65536) / 256);
                bytWriteCardArray[3] = Convert.ToByte(lngTemp % 256);
            }
            catch { }
             ShowOfSetCard(txtStandbyCard);
        }

        private void txtHexCard_TextChanged(object sender, EventArgs e)
        {
            if (blnShowWriteCardFlag) return;
            byte[] bytTemp = Adpdll.HexStringToByteArray(txtHexCard.Value);
            for (int i = 0; i < intLength; i++)
            {
                bytWriteCardArray[3 - i] = bytTemp[bytTemp.Length - 1 - i];
            }
            ShowOfSetCard(txtStandbyCard);
        }

        private void txtWiegandCard_TextChanged(object sender, EventArgs e)
        {
            if (blnShowWriteCardFlag) return;
            int intArea = Convert.ToInt32(txtWiegandCard.Value.Substring(0, 3));
            int intNum = Convert.ToInt32(txtWiegandCard.Value.Substring(3, 5));
            bytWriteCardArray[1] = (byte)intArea;
            bytWriteCardArray[2] = (byte)(intNum / 256);
            bytWriteCardArray[3] = (byte)(intNum % 256);
            ShowOfSetCard(txtStandbyCard);
        }

        private void chkIsAutoWrite_CheckedChanged(object sender, EventArgs e)
        {
            btnWriteCard.Visible = !chkIsAutoWrite.Checked;
        }

        private void btnDec_Click(object sender, EventArgs e)
        {
            SubtractCard();
        }

        private void btnAdd_Click(object sender, EventArgs e)
        {
            AddCard();
        }

        private void btnLeft_Click(object sender, EventArgs e)
        {
            btnRight.Enabled = true;
            if (intPosition > 0)
                intPosition--;
            else
                btnLeft.Enabled = false;
            ShowOfSetCard(txtStandbyCard);
        }

        private void btnRight_Click(object sender, EventArgs e)
        {
            btnLeft.Enabled = true;
            if (intPosition < 12 - intLength)
                intPosition++;
            else
                btnRight.Enabled = false;
            ShowOfSetCard(txtStandbyCard);
        }
        
        private void frmMain_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Subtract)
            {
                SubtractCard();
            }
            else if (e.KeyCode == Keys.Add)
            {
                AddCard();
            }
            else if (e.KeyCode == Keys.Enter)
            {
                blnWriteFlag = true;
            }
        }

        private void btnRandomA_Click(object sender, EventArgs e)
        {
            txtAlreadyCard.Value = "FFFFFFFFFFFFFFFFFFFFFFFF";
        }

        private void btnRandomC_Click(object sender, EventArgs e)
        {
            txtConfirmCard.Value = "FFFFFFFFFFFFFFFFFFFFFFFF";
        }
    }
}
