using ADSDK.Bases;
using ADSDK.Bases.Controls;
using ADSDK.Device;
using ADSDK.Device.Reader.Passive;
using System;
using System.Text;
using System.Windows.Forms;

namespace Aosid
{
    public partial class ucPWifiSettings : BaseControl
    {
        public ucPWifiSettings()
        {
            InitializeComponent();
        }

        public override void ChangeLanguage()
        {
            base.ChangeLanguage();

            ChangeFont(this);
            switch (BaseSettings.AppsLanguage)
            {
                case BaseSettings.LngType.CHN:
                    grbWifiPub.Text = "WIFI 公共参数输入区";
                    grbPSta.Text = "WIFI STA参数输入区";
                    grbPAP.Text = "WIFI AP参数输入区";
                    grbDefine.Text = "WIFI 自定义输入区";

                    #region ---Wifi Pub Parameters Input Zone---
                    lblPType.Text = "类型";
                    lblPMode.Text = "模式";
                    lblPHidessid.Text = "隐藏SSID";
                    lblPServer.Text = "网络模式";
                    lblPProtocol.Text = "网络协议";
                    lblPRemotePort.Text = "协议端口";
                    lblPRemoteIP.Text = "服务器地址";
                    lblPMaxsk.Text = "TCP连接数";
                    lblPTcpto.Text = "TCP延时";
                    lblPMac.Text = "MAC地址";
                    #endregion
                    #region ---Wifi STA Parameters Input Zone---
                    lblSMode.Text = "模式选择";
                    lblSChannel.Text = "信道选择";
                    lblSSSID.Text = "SSID号";
                    lblSAuth.Text = "加密方式";
                    lblSEncry.Text = "加密算法";
                    lblSKey.Text = "密钥";
                    lblSIP.Text = "WAN IP地址";
                    lblSMask.Text = "WAN IP掩码";
                    lblSGateWay.Text = "WAN IP网关";
                    lblSIPMode.Text = "地址分配方式";
                    #endregion
                    #region ---Wifi AP Parameters Input Zone---
                    lblAMode.Text = "模式选择";
                    lblAChannel.Text = "信道选择";
                    lblASSID.Text = "SSID号";
                    lblAAuth.Text = "加密方式";
                    lblAEncry.Text = "加密算法";
                    lblAKey.Text = "密钥";
                    lblAIP.Text = "LAN IP地址";
                    lblAMask.Text = "LAN IP掩码";
                    lblAGateWay.Text = "LAN IP网关";
                    lblAIPMode.Text = "DHCP服务";

                    #endregion
                    #region ---Wifi define Parameters Input Zone---

                    #endregion

                    break;
                default:
                    grbWifiPub.Text = "Wifi Pub Parameters Input Zone";
                    grbPSta.Text = "Wifi STA Parameters Input Zone";
                    grbPAP.Text = "Wifi AP Parameters Input Zone";
                    grbDefine.Text = "Wifi define Parameters Input Zone";

                    #region ---Wifi Pub Parameters Input Zone---
                    lblPType.Text = "Type";
                    lblPMode.Text = "Wifi Mode";
                    lblPHidessid.Text = "Hide SSID";
                    lblPServer.Text = "Net Mode";
                    lblPProtocol.Text = "Protocol";
                    lblPRemotePort.Text = "Protocol Port";
                    lblPRemoteIP.Text = "Host IP";
                    lblPMaxsk.Text = "Count(<32)";
                    lblPTcpto.Text = "Delay(<255)";
                    lblPMac.Text = "Mac";
                    #endregion
                    #region ---Wifi STA Parameters Input Zone---
                    lblSMode.Text = "Mode";
                    lblSChannel.Text = "Channel";
                    lblSSSID.Text = "SSID";
                    lblSAuth.Text = "Auth";
                    lblSEncry.Text = "Encry";
                    lblSKey.Text = "Key";
                    lblSIP.Text = "WAN IP";
                    lblSMask.Text = "WAN Mask";
                    lblSGateWay.Text = "WAN Gateway";
                    lblSIPMode.Text = "Allocation";
                    #endregion
                    #region ---Wifi AP Parameters Input Zone---
                    lblAMode.Text = "Mode";
                    lblAChannel.Text = "Channel";
                    lblASSID.Text = "SSID";
                    lblAAuth.Text = "Auth";
                    lblAEncry.Text = "Encry";
                    lblAKey.Text = "Key";
                    lblAIP.Text = "LAN IP";
                    lblAMask.Text = "LAN Mask";
                    lblAGateWay.Text = "LAN Gateway";
                    lblAIPMode.Text = "DHCP";

                    #endregion
                    #region ---Wifi define Parameters Input Zone---

                    #endregion
                    break;
            }
        }

        public override void ControlLoad(object sender, EventArgs e)
        {
            base.ControlLoad(sender, e);

            btnDefaultSTA_Click(sender ,e);
            btnDefaultAP_Click(sender, e);
            btnDefaultPub_Click(sender, e);
        }
        WifiPubParameters wpp_pub = new WifiPubParameters();
        WifiSsidParameters wsp_sta = new WifiSsidParameters();
        WifiSsidParameters wsp_ap = new WifiSsidParameters();
        public void ParseRsp(ProtocolStruct Data)
        {
            int len = Data.Length;
            switch (Data.Code)
            {
                case PassiveRcp.RCP_CMD_WIFI_DOWNLOAD:
                    if (Data.Length > 0 && Data.Type == 0)
                    {
                        if (Data.Payload[0] == 1)
                        {
                            MessageBox.Show("Upload Data Succeed!");
                        }
                        else if (Data.Payload[0] == 2)
                        {
                            MessageBox.Show("Download Data Succeed!");
                        }
                    }
                    break;
                case PassiveRcp.RCP_CMD_WIFI_PUB:
                    if (len > 0)
                    {
                        wpp_pub.AddRange(Data.Payload);
                        try
                        {
                            cmbPType.SelectedIndex = wpp_pub.Type;
                            cmbPMode.SelectedIndex = wpp_pub.Mode;
                            cmbPHide.SelectedIndex = wpp_pub.Hide;
                            txtTcpto.Text = wpp_pub.Tcpto.ToString();
                            txtMaxsk.Text = wpp_pub.Maxsk.ToString();
                            cmbPServer.SelectedIndex = wpp_pub.Server;
                            cmbProtocol.SelectedIndex = wpp_pub.Protocol;
                            txtPRemotePort.Text = wpp_pub.RemotePort.ToString();
                            txtPRemoteIP.Text = wpp_pub.RemoteIP;
                            txtPMac.Text = wpp_pub.Mac;
                        }
                        catch { }
                    }
                    break;
                case PassiveRcp.RCP_CMD_WIFI_STA:
                    if (len > 0)
                    {
                        try
                        {
                            wsp_sta.AddRange(Data.Payload);

                            cmbSMode.SelectedIndex = wsp_sta.Mode;
                            cmbSChannel.SelectedIndex = wsp_sta.Channel;
                            cmbSAuth.SelectedIndex = wsp_sta.Auth;
                            cmbSEncry.SelectedIndex = wsp_sta.Encry;
                            cmbSDHCP.SelectedIndex = wsp_sta.DHCP;

                            txtSSSID.Text = wsp_sta.SSID;
                            txtSKey.Text = wsp_sta.Key;
                            txtSIP.Text = wsp_sta.Ip;
                            txtSMask.Text = wsp_sta.Mask;
                            txtSGateway.Text = wsp_sta.Gateway;
                        }
                        catch { }
                    }
                    break;
                case PassiveRcp.RCP_CMD_WIFI_AP:
                    if (len > 0)
                    {
                        wsp_ap.AddRange(Data.Payload);

                        try
                        {
                            cmbAMode.SelectedIndex = wsp_ap.Mode;
                            cmbAChannel.SelectedIndex = wsp_ap.Channel;
                            cmbAAuth.SelectedIndex = wsp_ap.Auth;
                            cmbAEncry.SelectedIndex = wsp_ap.Encry;
                            cmbADHCP.SelectedIndex = wsp_ap.DHCP;

                            txtASSID.Text = wsp_ap.SSID;
                            txtAKey.Text = wsp_ap.Key;
                            txtAIP.Text = wsp_ap.Ip;
                            txtAMask.Text = wsp_ap.Mask;
                            txtAGateway.Text = wsp_ap.Gateway;
                        }
                        catch { }
                    }
                    break;
            }
        }

        private void btnWifi_Click(object sender, EventArgs e)
        {
            byte[] msg = Encoding.ASCII.GetBytes(txtWifi.Text + (chkD.Checked ? '\n'.ToString() : "") + (chkA.Checked ? '\r'.ToString() : ""));
            int intWifiType = Convert.ToInt32(cmbWifiType.SelectedIndex + 1);

            ByteBuilder bb = new ByteBuilder();
            bb.Append((byte)intWifiType);
            bb.Append(msg);
            if (!SystemPub.ADRcp.SendBytePkt(SystemPub.ADRcp.BuildCmdPacketByte(PassiveRcp.RCP_MSG_SENIOR_SET, PassiveRcp.RCP_CMD_WIFI_DOWNLOAD, bb.GetByteArray()))) { }
        }

        private void btnGetPub_Click(object sender, EventArgs e)
        {
            if (!SystemPub.ADRcp.SendBytePkt(SystemPub.ADRcp.BuildCmdPacketByte(PassiveRcp.RCP_MSG_SENIOR_GET, PassiveRcp.RCP_CMD_WIFI_PUB, null), 200)) { }
        }

        private void btnSetPub_Click(object sender, EventArgs e)
        {
            if (cmbPType.SelectedIndex != wpp_pub.Type) wpp_pub.Type = cmbPType.SelectedIndex;
            if (cmbPMode.SelectedIndex != wpp_pub.Mode) wpp_pub.Mode = cmbPMode.SelectedIndex;
            if (cmbPHide.SelectedIndex != wpp_pub.Hide) wpp_pub.Hide = cmbPHide.SelectedIndex;
            if (Convert.ToInt32(txtTcpto.Text) != wpp_pub.Tcpto) wpp_pub.Tcpto = Convert.ToInt32(txtTcpto.Text);
            if (Convert.ToInt32(txtMaxsk.Text) != wpp_pub.Maxsk) wpp_pub.Maxsk = Convert.ToInt32(txtMaxsk.Text);
            if (cmbPServer.SelectedIndex != wpp_pub.Server) wpp_pub.Server = cmbPServer.SelectedIndex;
            if (cmbProtocol.SelectedIndex != wpp_pub.Protocol) wpp_pub.Protocol = cmbProtocol.SelectedIndex;
            if (txtPRemotePort.Text != wpp_pub.RemotePort.ToString()) wpp_pub.RemotePort = Convert.ToInt32(txtPRemotePort.Text);
            if (txtPRemoteIP.Text != wpp_pub.RemoteIP) wpp_pub.RemoteIP = txtPRemoteIP.Text;
            if (txtPMac.Text != wpp_pub.Mac) wpp_pub.Mac = txtPMac.Text;
            if (!SystemPub.ADRcp.SendBytePkt(SystemPub.ADRcp.BuildCmdPacketByte(PassiveRcp.RCP_MSG_SENIOR_SET, PassiveRcp.RCP_CMD_WIFI_PUB, wpp_pub.ToArray()), 200)) { }
        }

        private void btnGetSTA_Click(object sender, EventArgs e)
        {
            if (!SystemPub.ADRcp.SendBytePkt(SystemPub.ADRcp.BuildCmdPacketByte(PassiveRcp.RCP_MSG_SENIOR_GET, PassiveRcp.RCP_CMD_WIFI_STA, null), 200)) { }
        }

        private void btnSetSTA_Click(object sender, EventArgs e)
        {
            if (cmbSMode.SelectedIndex != wsp_sta.Mode) wsp_sta.Mode = cmbSMode.SelectedIndex;
            if (cmbSChannel.SelectedIndex != wsp_sta.Channel) wsp_sta.Channel = cmbSChannel.SelectedIndex;
            if (cmbSAuth.SelectedIndex != wsp_sta.Auth) wsp_sta.Auth = cmbSAuth.SelectedIndex;
            if (cmbSEncry.SelectedIndex != wsp_sta.Encry) wsp_sta.Encry = cmbSEncry.SelectedIndex;
            if (cmbSDHCP.SelectedIndex != wsp_sta.DHCP) wsp_sta.DHCP = cmbSDHCP.SelectedIndex;

            if (txtSSSID.Text != wsp_sta.SSID) wsp_sta.SSID = txtSSSID.Text;
            if (txtSKey.Text != wsp_sta.Key) wsp_sta.Key = txtSKey.Text;
            if (txtSIP.Text != wsp_sta.Ip) wsp_sta.Ip = txtSIP.Text;
            if (txtSMask.Text != wsp_sta.Mask) wsp_sta.Mask = txtSMask.Text;
            if (txtSGateway.Text != wsp_sta.Gateway) wsp_sta.Gateway = txtSGateway.Text;

            if (!SystemPub.ADRcp.SendBytePkt(SystemPub.ADRcp.BuildCmdPacketByte(PassiveRcp.RCP_MSG_SENIOR_SET, PassiveRcp.RCP_CMD_WIFI_STA, wsp_sta.ToArray()), 200)) { }
        }

        private void btnGetAP_Click(object sender, EventArgs e)
        {
            if (!SystemPub.ADRcp.SendBytePkt(SystemPub.ADRcp.BuildCmdPacketByte(PassiveRcp.RCP_MSG_SENIOR_GET, PassiveRcp.RCP_CMD_WIFI_AP, null), 200)) { }
        }

        private void btnSetAP_Click(object sender, EventArgs e)
        {
            if (cmbAMode.SelectedIndex != wsp_ap.Mode) wsp_ap.Mode = cmbAMode.SelectedIndex;
            if (cmbAChannel.SelectedIndex != wsp_ap.Channel) wsp_ap.Channel = cmbAChannel.SelectedIndex;
            if (cmbAAuth.SelectedIndex != wsp_ap.Auth) wsp_ap.Auth = cmbAAuth.SelectedIndex;
            if (cmbAEncry.SelectedIndex != wsp_ap.Encry) wsp_ap.Encry = cmbAEncry.SelectedIndex;
            if (cmbADHCP.SelectedIndex != wsp_ap.DHCP) wsp_ap.DHCP = cmbADHCP.SelectedIndex;

            if (txtASSID.Text != wsp_ap.SSID) wsp_ap.SSID = txtASSID.Text;
            if (txtAKey.Text != wsp_ap.Key) wsp_ap.Key = txtAKey.Text;
            if (txtAIP.Text != wsp_ap.Ip) wsp_ap.Ip = txtAIP.Text;
            if (txtAMask.Text != wsp_ap.Mask) wsp_ap.Mask = txtAMask.Text;
            if (txtAGateway.Text != wsp_ap.Gateway) wsp_ap.Gateway = txtAGateway.Text;

            if (!SystemPub.ADRcp.SendBytePkt(SystemPub.ADRcp.BuildCmdPacketByte(PassiveRcp.RCP_MSG_SENIOR_SET, PassiveRcp.RCP_CMD_WIFI_AP, wsp_ap.ToArray()), 200)) { }
        }

        private void btnDefaultPub_Click(object sender, EventArgs e)
        {
            cmbPType.SelectedIndex = 0;
            cmbPMode.SelectedIndex = 0;
            cmbPHide.SelectedIndex = 0;
            cmbPServer.SelectedIndex = 0;
            cmbProtocol.SelectedIndex = 0;
            txtPRemotePort.Text = "49152";
            txtPRemoteIP.Text = "192.168.10.118";
            txtPMac.Text = wpp_pub.Mac;
        }

        private void btnDefaultSTA_Click(object sender, EventArgs e)
        {
            cmbSMode.SelectedIndex = 3;
            cmbSChannel.SelectedIndex = 0;
            cmbSAuth.SelectedIndex = 1;
            cmbSEncry.SelectedIndex = 2;
            cmbSDHCP.SelectedIndex = 0;

            txtSSSID.Text = "AD-WORK";
            txtSKey.Text = "aosid-work";
            txtSIP.Text = "192.168.10.115";
            txtSMask.Text = "255.255.255.0";
            txtSGateway.Text = "192.168.10.1";
        }

        private void btnDefaultAP_Click(object sender, EventArgs e)
        {
            cmbAMode.SelectedIndex = 3;
            cmbAChannel.SelectedIndex = 0;
            cmbAAuth.SelectedIndex = 0;
            cmbAEncry.SelectedIndex = 0;
            cmbADHCP.SelectedIndex = 1;

            txtASSID.Text = "AD-TEST";
            txtAKey.Text = "";
            txtAIP.Text = "10.10.100.254";
            txtAMask.Text = "255.255.255.0";
            txtAGateway.Text = "10.10.100.254";
        }

        private void cmbPMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            if(cmbPMode.Text == "AP")
            {
                grbPAP.Enabled = true;
                grbPSta.Enabled = false;
            }
            else
            {
                grbPAP.Enabled = false;
                grbPSta.Enabled = true;
            }
        }
        
        private void btnUpload_Click(object sender, EventArgs e)
        {
            byte[] msg = Encoding.ASCII.GetBytes(txtWifi.Text + (chkD.Checked ? '\n'.ToString() : "") + (chkA.Checked ? '\r'.ToString() : ""));

            ByteBuilder bb = new ByteBuilder();
            bb.Append((byte)1);
            bb.Append(msg);
            if (!SystemPub.ADRcp.SendBytePkt(SystemPub.ADRcp.BuildCmdPacketByte(PassiveRcp.RCP_MSG_SENIOR_SET, PassiveRcp.RCP_CMD_WIFI_DOWNLOAD, bb.GetByteArray()))) { }
        }

        private void btnDownLoad_Click(object sender, EventArgs e)
        {
            byte[] msg = Encoding.ASCII.GetBytes(txtWifi.Text + (chkD.Checked ? '\n'.ToString() : "") + (chkA.Checked ? '\r'.ToString() : ""));

            ByteBuilder bb = new ByteBuilder();
            bb.Append((byte)2);
            bb.Append(msg);
            if (!SystemPub.ADRcp.SendBytePkt(SystemPub.ADRcp.BuildCmdPacketByte(PassiveRcp.RCP_MSG_SENIOR_SET, PassiveRcp.RCP_CMD_WIFI_DOWNLOAD, bb.GetByteArray()))) { }
        }

    }
}
