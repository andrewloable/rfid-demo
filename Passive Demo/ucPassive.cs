using ADSDK.Bases;
using ADSDK.Bases.Controls;
using ADSDK.Device;
using ADSDK.Device.Reader.Passive;
using ADSDK.Sets;
using System;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace Aosid
{
    public partial class ucPassive : BaseControl
    {
        public ucPassive()
        {
            InitializeComponent();
        }

        #region ---PUBLIC----
        public override void ControlLoad(object sender, EventArgs e)
        {
            base.ControlLoad(sender, e);

            if (UserSettings.Communication == UserSettings.CommType.USB)
            {
                this.tabPassive.TabPages.Remove(this.tabSeniorSettings);
            }
        }
        public override void ChangeLanguage()
        {
            try
            {
                string[] m_def_en = new string[] {" READ DEMO ",
                    " BASE SETTINGS ",
                    " SENIOR SETTINGS ",
                    " ISO18000-6B READ&&WRITE ",
                    " EPC(GEN 2) READ&&WRITE ",
                    " WIFI SETTINGS "};

                string[] m_def_cn = new string[] { "读卡演示", "基本参数", "高级参数", "ISO18000-6B 读写操作", "EPC(GEN 2) 读写操作", "WIFI参数" };

                string[] m_def_tw = new string[] { "讀卡演示", "基本參數", "高級參數", "ISO18000-6B 讀寫操作", "EPC(GEN 2) 讀寫操作", "WIFI參數" };

                string[] MainValue = BaseSettings.LoadLanguage(@"passive/passive", m_def_en, m_def_cn, m_def_tw);
                int index = 0;

                tabReadDemo.Text = MainValue[index++];
                tabBaseSettings.Text = MainValue[index++];
                tabSeniorSettings.Text = MainValue[index++];
                tabWriteISO.Text = MainValue[index++];
                tabWriteEPC.Text = MainValue[index++];
                tabWifiSettings.Text = MainValue[index++];
            }
            catch { }

            ChangeFont(this);

            ucPBaseSettings1.ChangeLanguage();
            ucPSeniorSettings1.ChangeLanguage();
            ucPReadDemo1.ChangeLanguage();
            ucPWriteISO1.ChangeLanguage();
            ucPWriteEPC1.ChangeLanguage();
            ucPWifiSettings1.ChangeLanguage();
        }
        public override void PassOnKeys(object sender, KeyEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.Escape:
                    return;
                case Keys.F8:
                    if (tabBaseSettings == tabPassive.SelectedTab)
                        ucPBaseSettings1.PassOnKeys(sender, e);
                    else if (tabWriteEPC == tabPassive.SelectedTab)
                        ucPWriteEPC1.PassOnKeys(sender, e);
                    else if (tabSeniorSettings == tabPassive.SelectedTab)
                        ucPSeniorSettings1.PassOnKeys(sender, e);
                    break;
                case Keys.F9:
                    if (tabBaseSettings == tabPassive.SelectedTab)
                        ucPBaseSettings1.PassOnKeys(sender, e);
                    if (tabWriteEPC == tabPassive.SelectedTab)
                        ucPWriteEPC1.PassOnKeys(sender, e);
                    break;
                case Keys.F12:
                    if (tabWriteEPC == tabPassive.SelectedTab)
                        ucPWriteEPC1.PassOnKeys(sender, e);
                    break;
            }
        }
        #endregion

        #region ---local----
        public void ParseRsp(ProtocolStruct Data)
        {
            switch (Data.Code)
            {
                case PassiveRcp.RCP_CMD_INFO:
                    if (Data.Length > 0 && Data.Type == 0)
                    {
                        #region ---Parameter---
                        string strInfo = Encoding.ASCII.GetString(Data.Payload, 0, Data.Length);


                        if (Data.Payload[17] == 'W')
                        {
                            if (!this.tabPassive.TabPages.Contains(this.tabWifiSettings))
                            {
                                this.tabPassive.TabPages.Add(this.tabWifiSettings);
                                this.tabPassive.Refresh();
                            }
                        }
                        else
                        {
                            if (this.tabPassive.TabPages.Contains(this.tabWifiSettings))
                            {
                                this.tabPassive.TabPages.Remove(this.tabWifiSettings);
                                this.tabPassive.Refresh();
                            }
                        }

                        SystemPub.ADRcp.Mode = strInfo.Substring(18, 1);
                        SystemPub.ADRcp.Version = strInfo.Substring(19, 5);
                        SystemPub.ADRcp.Address = Convert.ToInt32(strInfo.Substring(29, 5));
                        #endregion

                        ResetOperation();
                    }
                    ucPSeniorSettings1.ParseRsp(Data);
                    break;
                case PassiveRcp.RCP_CMD_PARA:
                case PassiveRcp.RCP_CMD_OUTCARD:
                    ucPBaseSettings1.ParseRsp(Data);
                    break;
                case PassiveRcp.RCP_CMD_EPC_IDEN:
                case PassiveRcp.RCP_CMD_EPC_MULT:
                    if (tabWriteEPC == tabPassive.SelectedTab)
                        ucPWriteEPC1.ParseRsp(Data);
                    else
                        ucPReadDemo1.ParseRsp(Data);
                    break;
                case PassiveRcp.RCP_CMD_ISO6B_IDEN:
                    if (tabWriteISO == tabPassive.SelectedTab)
                        ucPWriteISO1.ParseRsp(Data);
                    else
                        ucPReadDemo1.ParseRsp(Data);
                    break;
                case PassiveRcp.RCP_CMD_ISO6B_RW:
                    ucPWriteISO1.ParseRsp(Data);
                    break;
                case PassiveRcp.RCP_CMD_SECRET:
                    if (tabWriteEPC == tabPassive.SelectedTab)
                        ucPWriteEPC1.ParseRsp(Data);
                    else
                        ucPSeniorSettings1.ParseRsp(Data);
                    break;
                case PassiveRcp.RCP_CMD_EPC_RW:
                    ucPWriteEPC1.ParseRsp(Data);
                    break;
                case PassiveRcp.RCP_CMD_TIME:
                case PassiveRcp.RCP_CMD_TCPIP:
                    ucPSeniorSettings1.ParseRsp(Data);
                    break;
                case PassiveRcp.RCP_CMD_WIFI_DOWNLOAD:
                case PassiveRcp.RCP_CMD_WIFI_PUB:
                case PassiveRcp.RCP_CMD_WIFI_STA:
                case PassiveRcp.RCP_CMD_WIFI_AP:
                    ucPWifiSettings1.ParseRsp(Data);
                    break;
                default:
                    break;
            }
        }

        private bool processing = false;

        private Thread SyncThread = null;
        private void ResetOperation()
        {
            Application.DoEvents();
            Thread.Sleep(200);
            if (processing) return;

            if (SyncThread == null || SyncThread.IsAlive == false)
            {
                SyncThread = new Thread(new ThreadStart(syncParameters));
                SyncThread.Start();
            }
        }

        private void syncParameters()
        {
            processing = true;
            System.Threading.Thread.Sleep(20);

            // Protocol Parameters
            if (!SystemPub.ADRcp.SendBytePkt(PassiveRcp.GetConfig(SystemPub.ADRcp.Address))) { }

            System.Threading.Thread.Sleep(20);

            if (UserSettings.Communication != UserSettings.CommType.USB)
            {
                if (!SystemPub.ADRcp.SendBytePkt(PassiveRcp.GetTcpip(SystemPub.ADRcp.Address))) { }
            }
            processing = false;
        }
        #endregion
    }
}
