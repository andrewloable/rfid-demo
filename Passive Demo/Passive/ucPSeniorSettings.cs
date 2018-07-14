using ADSDK.Bases;
using ADSDK.Bases.Controls;
using ADSDK.Device;
using ADSDK.Device.Reader.Passive;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Aosid
{
    public partial class ucPSeniorSettings : BaseControl
    {
        public ucPSeniorSettings()
        {
            InitializeComponent();

            cmbSyrisID.SelectedIndex = 0;
            ChangeLanguage();
            DefaultTcpip();
        }

        public override void ControlLoad(object sender, EventArgs e)
        {
            base.ControlLoad(sender, e);
        }
        public override void ChangeLanguage()
        {
            try
            {

                string[] m_def_en = new string[] {  
                    "Get Para","Set Para","Default",
                    "TCPIP Config",
                    "IP Address","IP Port:","Subnet Mask:","GateWay:","Mac Address:",
                    "Network Mode:","Server IP:","Server Port:",
                    "SYRIS Config", "Set Syris",
                    "Address Config","Old Address:","New Address:","Set Address",
                    "Soft Config","Time Config","Now Time:","Reader Time:","Get Time","Set Time",
                    "IO1 Open","IO2 Open","IO1 Close","IO2 Close",
                    "SoftReset"};

                string[] m_def_cn = new string[] { "获取参数", "设置参数", "默认参数", "TCPIP参数设置", "IP地址:", "IP端口:", "子网掩码:", "网关地址:", "Mac地址:", "网络模式:", "服务器IP:", "服务器端口:", "SYRIS参数配置", "设置序列号", "通讯地址配置", "原有通讯地址:", "待设置通讯地址:", "设置地址", "软件设置", "时间设置", "当前时间:", "设备时间:", "获取时间", "同步时间", "IO1 开", "IO2 开", "IO1 关", "IO2 关", "软重启" };

                string[] m_def_tw = new string[] { "獲取參數", "設置參數", "默認參數", "TCPIP參數設置", "IP地址:", "IP端口:", "子網掩碼:", "網關地址:", "Mac地址:", "網路模式:", "服務器IP:", "服務器端口:", "SYRIS參數配置", "設置序列號", "通訊地址配置", "原有通訊地址:", "待設置通訊地址:", "設置地址", "軟體設置", "時間設置", "當前時間:", "設備時間:", "獲取時間", "同步時間", "IO1 開", "IO2 開", "IO1 關", "IO2 關", "軟體重啟" };

                string[] MainValue = BaseSettings.LoadLanguage(@"passive/senior", m_def_en, m_def_cn, m_def_tw);

                int index = 0;

                #region ---PUB---

                btnGetPara.Text = MainValue[index++] + "(&G)";
                btnSetPara.Text = MainValue[index++] + "(&S)";
                btnDefault.Text = MainValue[index++] + "(&D)";
                #endregion

                #region ---TCPIP Config---
                grbTCPIP.Text = MainValue[index++];

                lblTCPIP.Text = MainValue[index++];
                lblTCPPort.Text = MainValue[index++];
                lblTCPMask.Text = MainValue[index++];
                lblTCPGateway.Text = MainValue[index++];
                lblTCPMac.Text = MainValue[index++];
                lblIsServer.Text = MainValue[index++];
                lblRemoteIP.Text = MainValue[index++];
                lblRemotePort.Text = MainValue[index++];
                #endregion

                #region ---SYRIS Config---
                grbSYRIS.Text = MainValue[index++];
                btnInitSyris.Text = MainValue[index++];
                #endregion

                #region ---Address Config---
                grbAddress.Text = MainValue[index++];
                lblOldAddr.Text = MainValue[index++];
                lblNewAddr.Text = MainValue[index++];

                btnAddress.Text = MainValue[index++];
                #endregion

                #region ---Senior Config---
                grbSoft.Text = MainValue[index++];
                grbTime.Text = MainValue[index++];
                lblNowTime.Text = MainValue[index++];
                lblReaderTime.Text = MainValue[index++];
                btnGetTime.Text = MainValue[index++];
                btnSetTime.Text = MainValue[index++];

                btnIO1Open.Text = MainValue[index++];
                btnIO2Open.Text = MainValue[index++];
                btnIO1Close.Text = MainValue[index++];
                btnIO2Close.Text = MainValue[index++];

                btnReset.Text = MainValue[index++];
                #endregion
            }
            catch { }

            txtNowTime.Font = new Font(BaseSettings.AppsFont.FontFamily, 9F);
            txtReaderTime.Font = new Font(BaseSettings.AppsFont.FontFamily, 9F);
        }

        public override void PassOnKeys(object sender, KeyEventArgs e)
        {

        }
        private void btnDefaultTcpip_Click(object sender, EventArgs e)
        {
            DefaultTcpip();
        }

        private void btnSetTcpip_Click(object sender, EventArgs e)
        {
            btnSetPara.Enabled = false;
            SetTcpip();
            btnSetPara.Enabled = true;
        }

        private void btnGetTcpip_Click(object sender, EventArgs e)
        {
            btnGetPara.Enabled = false;
            GetTcpip();
            btnGetPara.Enabled = true;
        }

        private void btnAddress_Click(object sender, EventArgs e)
        {
            ((Button)sender).Enabled = false;
            Application.DoEvents();
            if (!SystemPub.ADRcp.SendBytePkt(PassiveRcp.SetAddress(SystemPub.ADRcp.Address, Convert.ToInt32(utxtNewAddr.Text)))) { }
            ((Button)sender).Enabled = true;
        }

        private void btnReset_Click(object sender, EventArgs e)
        {
            ((Button)sender).Enabled = false;
            Application.DoEvents();
            if (!SystemPub.ADRcp.SendBytePkt(PassiveRcp.SetReset(SystemPub.ADRcp.Address))) { }
            ((Button)sender).Enabled = true;
        }

        private void btnIO1Open_Click(object sender, EventArgs e)
        {
            ((Button)sender).Enabled = false;
            Application.DoEvents();
            if (!SystemPub.ADRcp.SendBytePkt(PassiveRcp.SetRemote(SystemPub.ADRcp.Address,1,1))) { }
            ((Button)sender).Enabled = true;
        }

        private void btnIO1Close_Click(object sender, EventArgs e)
        {
            ((Button)sender).Enabled = false;
            Application.DoEvents();
            if (!SystemPub.ADRcp.SendBytePkt(PassiveRcp.SetRemote(SystemPub.ADRcp.Address, 1, 0))) { }
            ((Button)sender).Enabled = true;
        }

        private void btnIO2Open_Click(object sender, EventArgs e)
        {
            ((Button)sender).Enabled = false;
            Application.DoEvents();
            if (!SystemPub.ADRcp.SendBytePkt(PassiveRcp.SetRemote(SystemPub.ADRcp.Address, 2, 1))) { }
            ((Button)sender).Enabled = true;
        }

        private void btnIO2Close_Click(object sender, EventArgs e)
        {
            ((Button)sender).Enabled = false;
            Application.DoEvents();
            if (!SystemPub.ADRcp.SendBytePkt(PassiveRcp.SetRemote(SystemPub.ADRcp.Address, 2,0))) { }
            ((Button)sender).Enabled = true;
        }

        private void btnInitSyris_Click(object sender, EventArgs e)
        {
            List<byte> lstByte = new List<byte>();

            byte[] bytSN = Encoding.ASCII.GetBytes(txtSyrisSN.Text);
            lstByte.AddRange(bytSN);

            bytSN = Encoding.ASCII.GetBytes((cmbSyrisID.SelectedIndex + 1).ToString());
            lstByte.AddRange(bytSN);

            byte[] bytOther = new byte[10];
            lstByte.AddRange(bytOther);

            byte[] bytResult = lstByte.ToArray();

            ((Button)sender).Enabled = false;
            Application.DoEvents();
            if (!SystemPub.ADRcp.SendBytePkt(PassiveRcp.InitSyris(SystemPub.ADRcp.Address, lstByte.ToArray()))) { }
            ((Button)sender).Enabled = true;
        }

        private void btnGetTime_Click(object sender, EventArgs e)
        {
            txtNowTime.Text = txtReaderTime.Text = "";

            ((Button)sender).Enabled = false;
            Application.DoEvents();
            if (!SystemPub.ADRcp.SendBytePkt(PassiveRcp.GetTime(SystemPub.ADRcp.Address))) { }
            ((Button)sender).Enabled = true;
        }

        private void btnSetTime_Click(object sender, EventArgs e)
        {
            txtNowTime.Text = txtReaderTime.Text = "";
            DateTime dtNow = DateTime.Now;
            
            byte[] dtTemp = new byte[7];
            dtTemp[0] = (byte)(dtNow.Year % 200);
            dtTemp[1] = (byte)dtNow.Month;
            dtTemp[2] = (byte)dtNow.Day;
            dtTemp[3] = (byte)dtNow.DayOfWeek;
            dtTemp[4] = (byte)dtNow.Hour;
            dtTemp[5] = (byte)dtNow.Minute;
            dtTemp[6] = (byte)dtNow.Second;

            ((Button)sender).Enabled = false;
            Application.DoEvents();
            if (!SystemPub.ADRcp.SendBytePkt(PassiveRcp.SetTime(SystemPub.ADRcp.Address, dtTemp))) { }
            ((Button)sender).Enabled = true;
        }

        private void cmbIsServer_SelectedIndexChanged(object sender, EventArgs e)
        {
            pnlRemote.Enabled = (cmbIsServer.SelectedIndex > 0);
        }

        #region ---Tcpip参数---
        private void SetTcpip()
        {

            if (!RegexBase.IsIPv4(txtTCPIP.Text.ToString().Trim()))
            {
                MessageStatus.Show("IP地址错误!", "IP Address Error!", (int)CommRtn.FAIL);
                return;
            }

            if (!RegexBase.IsIPv4(txtTCPMask.Text.ToString().Trim()))
            {
                MessageStatus.Show("子网掩码错误!", "Subnet Mask Error!", (int)CommRtn.FAIL);
                return;
            }

            if (!RegexBase.IsIPv4(txtTCPGateway.Text.ToString().Trim()))
            {
                MessageStatus.Show("网关地址错误!", "GateWay Error!", (int)CommRtn.FAIL);
                return;
            }
            if (!RegexBase.IsMac(txtTCPMac.Text.ToString().Trim()))
            {
                MessageStatus.Show("Mac地址错误!", "Mac Address Error!", (int)CommRtn.FAIL);
                return;
            }

            if (!RegexBase.IsIPv4(txtRemoteIP.Text.ToString().Trim()))
            {
                MessageStatus.Show("RemoteIP地址错误!", "RemoteIP Address Error!", (int)CommRtn.FAIL);
                return;
            }

            TcpipParameters newTemp = GetTcpipParaInfo();

            if (!SystemPub.ADRcp.SendBytePkt(PassiveRcp.SetTcpip(SystemPub.ADRcp.Address, newTemp.ToArray()))) { }
        }

        public void GetTcpip()
        {
            if (!SystemPub.ADRcp.SendBytePkt(PassiveRcp.GetTcpip(SystemPub.ADRcp.Address))) { }
        }

        private void ShowTcpipParaInfo(TcpipParameters info)
        {
            try
            {
                txtTCPIP.Text = info.IPToString();

                txtTCPMask.Text = info.MaskToString();

                txtTCPGateway.Text = info.GateWayToString();

                txtTCPPort.Text = info.Port.ToString();

                txtTCPMac.Text = info.MacToString();

                txtRemoteIP.Text = info.RemoteIPToString();

                txtRemotePort.Text = info.RemotePort.ToString();

                cmbIsServer.SelectedIndex = info.Server;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString(), this.Text, MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private TcpipParameters GetTcpipParaInfo()
        {
            TcpipParameters bpiTemp = new TcpipParameters();

            bpiTemp.SetIP(txtTCPIP.Text);

            bpiTemp.SetMask(txtTCPMask.Text);

            bpiTemp.SetGateWay(txtTCPGateway.Text);

            bpiTemp.Port = Convert.ToInt32(txtTCPPort.Text);

            bpiTemp.SetMac(txtTCPMac.Text);

            bpiTemp.SetRemoteIP(txtRemoteIP.Text);

            bpiTemp.RemotePort = Convert.ToInt32(txtRemotePort.Text);

            bpiTemp.Server = cmbIsServer.SelectedIndex;
            return bpiTemp;
        }

        private void DefaultTcpip()
        {
            TcpipParameters bpiTemp = new TcpipParameters();
            ShowTcpipParaInfo(bpiTemp);
        }
        #endregion
        
        public void ParseRsp(ProtocolStruct Data)
        {
            switch (Data.Code)
            {
                case PassiveRcp.RCP_CMD_TCPIP:
                    if (Data.Length > 0 && Data.Type == 0)
                    {
                        TcpipParameters bpiTemp = new TcpipParameters();
                        bpiTemp.AddRange(Data.Payload);
                        ShowTcpipParaInfo(bpiTemp);
                    }
                    else if (Data.Type == 0)
                    {

                        string stren = "Set the IP parameters under the network connection need restart the equipment!";
                        string strcn = "设置IP参数需要重启设备!";
                        string aMsg = BaseSettings.GetLanguageString(stren, strcn);
                        MessageBox.Show(aMsg, this.Text, MessageBoxButtons.OK,MessageBoxIcon.Information);
                    }
                    break;
                case PassiveRcp.RCP_CMD_INFO:
                    if (Data.Length > 0 && Data.Type == 0)
                    {
                        string strInfo = Encoding.ASCII.GetString(Data.Payload, 0, Data.Length);

                        SystemPub.ADRcp.Mode = strInfo.Substring(18, 1);
                        SystemPub.ADRcp.Version = strInfo.Substring(19, 5);
                        SystemPub.ADRcp.Address = Convert.ToInt32(strInfo.Substring(29, 5));

                        txtOldAddr.Text = SystemPub.ADRcp.Address.ToString();
                    }
                    else if (Data.Type == 0)
                    {
                        if (!SystemPub.ADRcp.SendBytePkt(PassiveRcp.GetInformation())) { }
                    }
                    break;
                case PassiveRcp.RCP_CMD_SECRET:
                    break;
                case PassiveRcp.RCP_CMD_SOFTRESET:
                    break;
                case PassiveRcp.RCP_CMD_INITSYRIS:
                    break;
                case PassiveRcp.RCP_CMD_REMOTE:
                    break;
                case PassiveRcp.RCP_CMD_TIME:
                    if (Data.Length > 0 && Data.Type == 0)
                    {
                        string y = Data.Payload[0].ToString("00");
                        string m = Data.Payload[1].ToString("00");
                        string d = Data.Payload[2].ToString("00");
                        string w = Data.Payload[3].ToString("00");
                        string h = Data.Payload[4].ToString("00");
                        string mi = Data.Payload[5].ToString("00");
                        string se = Data.Payload[6].ToString("00");
                        string D = string.Format("20{0}-{1}-{2} {3}:{4}:{5}", y, m, d, h, mi, se);      //2010-02-28 14:48:03
                        txtReaderTime.Text = DateTime.Parse(D).ToString();
                    }
                    break;
            }
        }

        private void tmrClock_Tick(object sender, EventArgs e)
        {
            txtNowTime.Text = DateTime.Now.ToString();
        }
    }
}
