using ADSDK.Bases;
using ADSDK.Bases.Controls;
using ADSDK.Device;
using ADSDK.Device.Reader.Passive;
using ADSDK.Sets;
using System;
using System.Drawing;
using System.IO;
using System.IO.Ports;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace Aosid
{
    public partial class frmMain : BaseForm
    {
        frmWait fwt = new frmWait();

        ucPassive ucPassive1 = new ucPassive();

        public frmMain()
        {
            InitializeComponent();
            //  BaseSettings.FontCN = new Font("微软雅黑", 9F, FontStyle.Regular);
            //  BaseSettings.FontEN = new Font("微软雅黑", 8.5F, FontStyle.Regular);

            Rectangle rect = new Rectangle();
            rect = Screen.GetWorkingArea(this);
            if (this.Width > rect.Width) { this.Width = rect.Width - 20; }

        }

        #region ---Change Font---

        private string mFontPassword = "";
        private const string CHANGEFONT = "CHANGEFONT";
        private const string RECHANGEFONT = "RECHANGEFONT";
        private const string CHANGECOLOR = "CHANGECOLOR";
        private const string RECHANGECOLOR = "RECHANGECOLOR";

        private void ChangeTitle(Control ctl, Keys key)
        {
            bool mChangeFlag = false;
            mFontPassword += (char)key;
            mFontPassword = mFontPassword.ToUpper();
            if (mFontPassword.Contains(CHANGEFONT) || mFontPassword.Contains(RECHANGEFONT) || mFontPassword.Contains(CHANGECOLOR) || mFontPassword.Contains(RECHANGECOLOR))
            {
                if (mFontPassword.Contains(CHANGEFONT))
                {
                    //load new font
                    FontDialog ftd = new FontDialog();
                    ftd.Font = BaseSettings.AppsFont;
                    if (ftd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                    {
                        BaseSettings.AppsFont = ftd.Font;
                        mChangeFlag = true;
                    }
                    mFontPassword = "";
                }
                else if (mFontPassword.Contains(RECHANGEFONT))
                {
                    //restore default font
                    BaseSettings.FontCN = new Font("微软雅黑", 9F, FontStyle.Regular);
                    BaseSettings.FontEN = new Font("微软雅黑", 8.5F, FontStyle.Regular);
                    mChangeFlag = true;
                    mFontPassword = "";
                }
                else if (mFontPassword.Contains(CHANGECOLOR))
                {
                    ColorDialog crd = new ColorDialog();
                    crd.Color = BaseSettings.AppsColor;
                    if (crd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                    {
                        BaseSettings.AppsColor = crd.Color;
                        mChangeFlag = true;
                    }
                    mFontPassword = "";
                }
                else if (mFontPassword.Contains(RECHANGECOLOR))
                {
                    if (BaseSettings.AppsColor != Color.AliceBlue)
                    {
                        BaseSettings.AppsColor = Color.AliceBlue;
                        mChangeFlag = true;
                    }
                    mFontPassword = "";
                }
            }
            else
            {
                mFontPassword = "";
            }
            if (mChangeFlag) ChangeFont(ctl);
        }
        #endregion

        public override void ControlLoad(object sender, EventArgs e)
        {
            base.ControlLoad(sender, e);
            UInt16 languageid = Languages.UserDefaultUILanguage;
            switch (languageid)
            {
                case 0x0804:
                    BaseSettings.Language = 1;
                    break;
                case 0x0C04:
                case 0x0404:
                    BaseSettings.Language = 2;
                    break;
                default:
                    BaseSettings.Language = 0;
                    break;

            }
            //BaseSettings.Language = 2;
            LoadLanguage(BaseSettings.Language);

            SystemPub.ADRcp = new PassiveRcp();
            SystemPub.ADRcp.RcpLogEventReceived += RcpLogEventReceived;
            SystemPub.ADRcp.RxRspParsed += RxRspEventReceived;

            LoadCommType(UserSettings.Communication);

            //if (listViewMsg.Visible) tsmiMsg_Click(sender, e);
            
            SystemPub.Location = this.Location;
            SystemPub.Size =(this.Size);
            GetPortName();
        }

        public override void PassOnKeys(object sender, KeyEventArgs e)
        {
            ChangeTitle(this,e.KeyCode);
            switch (e.KeyCode)
            {
                case Keys.Escape:
                    return;
                case Keys.F2:
                    if (UserSettings.Communication == UserSettings.CommType.SERIAL)
                        LoadCommType(UserSettings.CommType.NET);
                    else if (UserSettings.Communication == UserSettings.CommType.NET)
                        LoadCommType(UserSettings.CommType.USB);
                    else if (UserSettings.Communication == UserSettings.CommType.USB)
                        LoadCommType(UserSettings.CommType.SERIAL);
                    break;
                case Keys.F8:
                case Keys.F9:
                case Keys.F12:
                    if (ucPassive1 != null) ucPassive1.PassOnKeys(sender, e);
                    break;
            }
            base.PassOnKeys(sender, e);
        }

        private void frmMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            SystemPub.ADSio.LogClose();
            if (SystemPub.ADSio.bConnected)
            {
                SystemPub.ADSio.DisConnect();
            }
        }

        #region ---Language---
        public override void ChangeLanguage()
        {
            switch (BaseSettings.AppsLanguage)
            {
                case BaseSettings.LngType.CHN:
                    this.Text = "读卡器演示程序 (版本:" + SystemPub.AssemblyVersion + ") - 简体中文 - " + UserSettings.Communication.ToString();

                    #region ---菜单栏----
                    tsmiCommSerial.Text = "串口通讯";
                    tsmiCommNet.Text = "TCPIP通讯";
                    tsmiCommUsb.Text = "USB通讯";
                    tsmiCommConfig.Text = "参数配置";

                    if (tsmiConnect.Text == "DIS&CONNECT")
                    {
                        tsmiConnect.Text = "断开(&C)";
                    }
                    else
                    {
                        tsmiConnect.Text =  "联机(&C)";
                    }
                    tsmiComm.Text = "通信参数配置(&S)";
                    tsmiRCPLogging.Text = "通信日志(&L)";
                    tsmiLogEnable.Text = "使用(&E)";
                    tsmiHelp.Text = "帮助(&H)";

                    tsmiMsg.Text = "实时信息显示";
                    tsmiAboutMe.Text = "关于  读卡器演示程序(&A)";
                    tsmiUserManual.Text = "用户手册(&U)";
                    #endregion
                    break;
                default:
                    this.Text = "RFID Demo (Version:" + SystemPub.AssemblyVersion + ") - English - " +
                                 UserSettings.Communication.ToString();

                    #region ---菜单栏----
                    tsmiCommSerial.Text = "Serial Interface";
                    tsmiCommNet.Text = "Net Work (TCPIP)";
                    tsmiCommUsb.Text = "USB Interface";
                    tsmiCommConfig.Text = "SETTINGS";

                    if (tsmiConnect.Text == "断开(&C)")
                    {
                        tsmiConnect.Text = "DIS&CONNECT";
                    }
                    else
                    {
                        tsmiConnect.Text = "&CONNECT";
                    }
                    tsmiComm.Text = "&SETTINGS";
                    tsmiRCPLogging.Text = "RCP &LOGGING";
                    tsmiLogEnable.Text = "Enable(&E)";
                    tsmiHelp.Text = "&HELP";

                    tsmiMsg.Text = "Display Realtime Message";
                    tsmiAboutMe.Text = "About  RFID Demo(&A)";
                    tsmiUserManual.Text = "User Manual";
                    #endregion
                    break;
            }
            ChangeFont(this);
            if (ucPassive1 != null) ucPassive1.ChangeLanguage();
        }

        private void LoadLanguage(int language)
        {
            BaseSettings.Language = (int)language;
            BaseSettings.SaveLanguage();


            tsmiLngEng.Checked = false;
            tsmiLngChn.Checked = false;
            switch (language)
            {
                case 0:
                    tsmiLngEng.Checked = true;
                    break;
                case 1:
                    tsmiLngChn.Checked = true;
                    break;
            }
            ChangeLanguage();
        }

        private void tsmiLngChn_Click(object sender, EventArgs e)
        {
            LoadLanguage(1);
        }

        private void tsmiLngEng_Click(object sender, EventArgs e)
        {
            LoadLanguage(0);
        }
        #endregion

        #region ---CommType---
        private void LoadCommType(UserSettings.CommType type)
        {
            UserSettings.CommType localtemp = UserSettings.Communication;
            tsmiCommSerial.Checked = false;
            tsmiCommNet.Checked = false;
            tsmiCommUsb.Checked = false;
            switch (type)
            {
                case UserSettings.CommType.SERIAL:
                    tsmiCommSerial.Checked = true;
                    break;
                case UserSettings.CommType.NET:
                    tsmiCommNet.Checked = true;
                    break;
                case UserSettings.CommType.USB:
                    tsmiCommUsb.Checked = true;
                    break;
                default:
                    break;
            }
            UserSettings.Communication = type;
            tsStatusPort.Text = UserSettings.HostName;
            tsStatusBr.Text = UserSettings.HostPort.ToString();
            tsStatusPortOpen.Text = "DISCONNECT";
            ChangeLanguage();
            InitCommunication();
        }

        private void ChangeCommType(object sender, EventArgs e)
        {
           // switch(((T)))
            if (((ToolStripMenuItem)sender).Name == "tsmiCommSerial")
            {
                LoadCommType(UserSettings.CommType.SERIAL);
            }
            else if (((ToolStripMenuItem)sender).Name == "tsmiCommNet")
            {
                LoadCommType(UserSettings.CommType.NET);
            }
            else if (((ToolStripMenuItem)sender).Name == "tsmiCommUsb")
            {
                LoadCommType(UserSettings.CommType.USB);
                MessageBox.Show(BaseSettings.AppsLanguage == BaseSettings.LngType.ENG ? "Please re plug USB devices, and repeat click connect, until a successful connection!!" : "请重新插拔USB设备,并重复点击联机,直到连接成功!", this.Text, MessageBoxButtons.OK);
            }

        }
        #endregion

        #region ---Help---
        private void tsmiMsg_Click(object sender, EventArgs e)
        {
            listViewMsg.Visible = !listViewMsg.Visible;
            tsmiMsg.Checked = listViewMsg.Visible;
            //if (!listViewMsg.Visible)
            //{
            //    this.Height -= 160;
            //}
            //else
            //{
            //    this.Height += 160;
            //}
        }
        private void SetCommConfig()
        {
            if (UserSettings.Communication == UserSettings.CommType.USB || SystemPub.ADSio.bConnected) return;
            //Point screenPoint = Control.MousePosition;//鼠标相对于屏幕左上角的坐标
            // Point formPoint = this.PointToClient(Control.MousePosition);//鼠标相对于窗体左上角的坐标
            //Point contextMenuPoint = contextMenuStrip1.PointToClient(Control.MousePosition); //鼠标相对于contextMenuStrip1左上角的坐标 

            frmSioConfig fsc = new frmSioConfig();
            fsc.StartPosition = FormStartPosition.CenterParent;
            //fsc.Location = screenPoint;
            fsc.ShowDialog();
            LoadCommType(UserSettings.Communication);

        }

        private void tsmiCommConfig_Click(object sender, EventArgs e)
        {
            SetCommConfig();

        }
        private void tsmiAboutMe_Click(object sender, EventArgs e)
        {
            frmAbout fat = new frmAbout();
            fat.ShowDialog();
        }
        #endregion

        #region ---Attention----
        private string aMsg = "";
        private void AttentionMouseLeave(object sender, EventArgs e)
        {
            aMsg = "";
            this.ttpAttention.Active = false;
        }

        private void tsStatusPortOpen_MouseEnter(object sender, EventArgs e)
        {
            aMsg = "Device connection state";
            if (BaseSettings.AppsLanguage == BaseSettings.LngType.CHN)
            {
                aMsg = "读卡器当前连接状态";
            }
            this.ttpAttention.Show(aMsg, this.statusBar, 10, -30);
            this.ttpAttention.Active = true;
        }

        private void tsStatusPort_MouseEnter(object sender, EventArgs e)
        {
            aMsg = "Device host name(portname,ip or device type)";
            if (BaseSettings.AppsLanguage == BaseSettings.LngType.CHN)
            {
                aMsg = "串口模式: 串口号" + Environment.NewLine +
                        "网络模式: IP地址";
            }
            this.ttpAttention.Show(aMsg, this.statusBar, 110, -30);
            this.ttpAttention.Active = true;
        }

        private void tsStatusBr_MouseEnter(object sender, EventArgs e)
        {
            aMsg = "Device host port(baudrate,ipport or device handle)";
            if (BaseSettings.AppsLanguage == BaseSettings.LngType.CHN)
            {
                aMsg = "串口模式: 波特率" + Environment.NewLine +
                        "网络模式: IP端口";
            }
            this.ttpAttention.Show(aMsg, this.statusBar, 230, -30);
            this.ttpAttention.Active = true;
        }

        private void tsFWVersion_MouseEnter(object sender, EventArgs e)
        {
            aMsg = "device type,version and address" + Environment.NewLine +
                                    "type P is 915MHz Reader" + Environment.NewLine +
                                    "type A is 2.4GHz Reader" + Environment.NewLine +
                                    "type R is R2000 Reader";
            if (BaseSettings.AppsLanguage == BaseSettings.LngType.CHN)
            {
                aMsg = "读卡器类别,软件版本以及地址" + Environment.NewLine +
                                    "类型 P 为915MHz读卡器(普通)" + Environment.NewLine +
                                    "类型 A 为2.4GHz读卡器(普通)" + Environment.NewLine +
                                    "类型 R 为915MHz读卡器(高级)";
            }
            this.ttpAttention.Show(aMsg, this.statusBar, 310, -80);
            this.ttpAttention.Active = true;
        }

        private void tsStatusInfo_MouseEnter(object sender, EventArgs e)
        {
            aMsg = "Communication Status";
            if (BaseSettings.AppsLanguage == BaseSettings.LngType.CHN)
            {
                aMsg = "当前通讯状态";
            }
            this.ttpAttention.Show(aMsg, this.mnuBar, 560, -30);
            this.ttpAttention.Active = true;
        }


        private void tsmiConnect_MouseEnter(object sender, EventArgs e)
        {
            aMsg = "Connect or Disconnect the reader";
            if (BaseSettings.AppsLanguage == BaseSettings.LngType.CHN)
            {
                aMsg = "连接或者断开读卡器";
            }
            this.ttpAttention.Show(aMsg, this.mnuBar, 10, 30);
            this.ttpAttention.Active = true;
        }

        private void tsmiComm_MouseEnter(object sender, EventArgs e)
        {
            aMsg = "Config communication parameters" + Environment.NewLine +
                    "Select communication type;" + Environment.NewLine +
                    "set portname,baudrate,ip address and ip port";
            if (BaseSettings.AppsLanguage == BaseSettings.LngType.CHN)
            {
                aMsg = "配置通讯参数" + Environment.NewLine +
                       "选择通讯类型,并配置相关参数" + Environment.NewLine +
                       "比如端口号,波特率,IP地址,IP端口等" + Environment.NewLine +
                       "通过下方状态栏查看设置参数";
            }
            this.ttpAttention.Show(aMsg, this.mnuBar, 10, 30);
            this.ttpAttention.Active = true;
        }

        private void tsmiRCPLogging_MouseEnter(object sender, EventArgs e)
        {
            aMsg = "Create a new file to save the operation log";
            if (BaseSettings.AppsLanguage == BaseSettings.LngType.CHN)
            {
                aMsg = "创建一个文件保存运行日志";
            }
            this.ttpAttention.Show(aMsg, this.mnuBar, 10, 30);
            this.ttpAttention.Active = true;
        }

        private void tsmiLanguage_MouseEnter(object sender, EventArgs e)
        {
            aMsg = "Switch the display language";
            if (BaseSettings.AppsLanguage == BaseSettings.LngType.CHN)
            {
                aMsg = "切换界面显示语言";
            }
            this.ttpAttention.Show(aMsg, this.mnuBar, 10, 30);
            this.ttpAttention.Active = true;
        }

        private void tsmiHelp_MouseEnter(object sender, EventArgs e)
        {
            aMsg = "Support";
            if (BaseSettings.AppsLanguage == BaseSettings.LngType.CHN)
            {
                aMsg = "软件帮助";
            }
            this.ttpAttention.Show(aMsg, this.mnuBar, 10, 30);
            this.ttpAttention.Active = true;
        }
        #endregion

        #region ---RPC Log---
        private void tsmiLogEnable_Click(object sender, EventArgs e)
        {
            if (!tsmiLogEnable.Checked)
            {
                string path = Application.StartupPath + @"\Data";
                if (!Directory.Exists(path))
                {
                    Directory.CreateDirectory(path);
                }
                SaveFileDialog saveFileDialogLog = new SaveFileDialog();
                saveFileDialogLog.InitialDirectory = path;
                saveFileDialogLog.Filter = "Log files (*.log)|*.log";
                saveFileDialogLog.FileName = "*.log";
                if (saveFileDialogLog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                {
                    SystemPub.ADSio.LogOpen(saveFileDialogLog.FileName);
                    tsmiLogEnable.Checked = true;
                }
            }
            else
            {
                tsmiLogEnable.Checked = false;
                SystemPub.ADSio.LogClose();
            }
        }
        #endregion

        #region ---DispalyMsg---
        private StringBuilder msgSb = new StringBuilder();
        private bool bDisposed = false;
        public void DisplayMsgString(string s)
        {
            if (bDisposed)
                return;

            if (!InvokeRequired)
            {
                __DisplayMsgString(s);
                return;
            }

            this.Invoke(new MethodInvoker(delegate()
            {
                __DisplayMsgString(s);
            }));
        }

        private void __DisplayMsgString(string s)
        {
            if (!bDisposed)
            {
                msgSb.Append(s);
                s = s.TrimEnd(new char[] { '\r', '\n', ')', ' ' });

                ListViewItem lvt = new ListViewItem(DateTime.Now.Hour.ToString("00") + ":" + DateTime.Now.Minute.ToString("00") + ":" + DateTime.Now.Second.ToString("00") + " " + DateTime.Now.Millisecond.ToString("000"));
                string[] msg = s.Split(new char[] { '>', '(' }, 3, StringSplitOptions.None);

                if (msg.Length == 1 && msg[0] == "") return;

                Color bc = Color.White;
                for (int i = 0; i < msg.Length; i++)
                {
                    if (i == 0)
                    {
                        switch (msg[0])
                        {
                            case "RCP CMD":
                                bc = Color.OldLace;
                                break;
                            case "RCP RSP":
                                bc = Color.Lavender;
                                break;
                            case "RCP AUTO":
                                bc = Color.LemonChiffon;
                                break;
                            case "ERROR":
                                bc = Color.LightGray;
                                break;
                        }
                    }

                    lvt.SubItems.Add(msg[i]);
                }

                lvt.BackColor = bc;
                lvt.Font = new Font(BaseSettings.AppsFont.FontFamily, 8);

                // listViewMsg.Visible = false;
                if (listViewMsg.Items.Count > 5000)
                {
                    for (int i = 0; i < 500; i++)
                    {
                        listViewMsg.Items.RemoveAt(0);
                    }
                }
                else
                {
                    listViewMsg.Items.Add(lvt).EnsureVisible();
                }
                listViewMsg.Update();
                //listViewMsg.Visible = true;
            }
        }

        private void tsMenuItemClear_Click(object sender, EventArgs e)
        {
            listViewMsg.Items.Clear();
            msgSb.Remove(0, msgSb.Length);
        }

        private void tsMenuItemCopy_Click(object sender, EventArgs e)
        {
            if (listViewMsg.SelectedItems != null && listViewMsg.SelectedItems.Count != 0)
            {
                string strmsg = "";
                for (int i = 0; i < listViewMsg.Columns.Count; i++)
                {
                    strmsg += listViewMsg.SelectedItems[0].SubItems[i].Text + "\t";
                }
                Clipboard.SetText(strmsg);
            }
        }

        private void tsMenuItemCopyAll_Click(object sender, EventArgs e)
        {
            msgSb.Remove(0, msgSb.Length);
            foreach (ListViewItem lvi in listViewMsg.Items)
            {
                string strmsg = "";
                for (int i = 0; i < listViewMsg.Columns.Count; i++)
                {
                    try
                    {
                        strmsg += lvi.SubItems[i].Text + "\t";
                    }
                    catch { }
                }
                msgSb.Append(strmsg + Environment.NewLine);
            }
            if (msgSb != null && msgSb.Length != 0) Clipboard.SetText(msgSb.ToString());
        }

        #endregion

        #region ---Communication---
        bool cAddNew = false;
        public string ReaderMode = "";
        private void InitCommunication()
        {
            UnInitCommunication();
            switch (UserSettings.Communication)
            {
                case UserSettings.CommType.NET:
                    SystemPub.ADSio = new ADNet();
                    break;
                case UserSettings.CommType.USB:
                    SystemPub.ADSio = new ADUsb();
                    break;
                default:
                    SystemPub.ADSio = new ADCom();
                    break;
            }
            SystemPub.ADSio.StatusConnected += Instance_Connected;

            SystemPub.ADRcp.Sio = SystemPub.ADSio;

            cAddNew = true;
        }

        private void UnInitCommunication()
        {
            if (!cAddNew) return;
            SystemPub.ADSio.StatusConnected -= Instance_Connected;
            cAddNew = false;
        }
        
        void Instance_Connected(object sender, ConnectEventArg e)
        {
            try
            {
                this.Invoke(new MethodInvoker(delegate()
                {
                    if (e.Status == CommState.O_CONNECT || e.Status == CommState.F_CONNECT)
                    {
                        tsmiConnect.Enabled = true;
                        if (fwt.IsAlive)
                        {
                            Thread.Sleep(2000);
                            fwt.Close();
                        }
                        Application.DoEvents();
                        if (e.Status == CommState.O_CONNECT)
                        {
                            if (UserSettings.Communication == UserSettings.CommType.USB)
                            {
                                try
                                {
                                    int intVer = Convert.ToInt32(e.Msg);

                                    tsStatusBr.Text = "V" + intVer / 256 + "." + intVer % 256 / 16 + intVer % 16;
                                }
                                catch { tsStatusBr.Text = ""; }
                            }
                            tsStatusPortOpen.Text = "CONNECT";
                            DisplayMsgString("CONNECT> Connect Succeed...   " + "(" + SystemPub.ADSio.ToString() + ")\r\n");
                            tsmiConnect.Text = BaseSettings.AppsLanguage == BaseSettings.LngType.CHN ? "断开(&C)" : "DIS&CONNECT";
                            StartReadInfo();
                        }
                        else if (e.Status == CommState.F_CONNECT)
                        {
                            m_bAlive = false;
                            DisplayMsgString("ERROR> " + e.Msg + "(" + SystemPub.ADSio.ToString() + ")\r\n");
                            tsmiConnect.Text = BaseSettings.AppsLanguage == BaseSettings.LngType.CHN ? "联机(&C)" : "&CONNECT";
                        }

                        tsmiComm.Enabled = !tsmiRCPLogging.Visible;
                    }
                    else if (e.Status == CommState.O_DISCNT || e.Status == CommState.F_DISCNT || e.Status == CommState.E_DISCNT)
                    {
                        tsmiConnect.Enabled = true;
                        if (e.Status == CommState.O_DISCNT)
                        {
                            m_bAlive = false;
                            DisplayMsgString("CONNECT> DisConnect succeed...  " + "(" + SystemPub.ADSio.ToString() + ")\r\n");
                        }
                        else if (e.Status == CommState.E_DISCNT)
                        {
                            DisplayMsgString("ERROR> Error communication to disconnect...  " + "(" + SystemPub.ADSio.ToString() + ")\r\n");
                        }
                        else
                        {
                            DisplayMsgString("ERROR> " + e.Msg + "(" + SystemPub.ADSio.ToString() + ")\r\n");
                        }

                        tsmiConnect.Text = BaseSettings.AppsLanguage == BaseSettings.LngType.CHN ? "联机(&C)" : "&CONNECT";

                        if (ucPassive1 != null) ucPassive1.Hide();
                        
                        pnlInformation.Controls.Clear();

                        if (UserSettings.Communication != UserSettings.CommType.USB && m_bAlive)
                        {
                            m_bAlive = false;
                            tsmiConnect_Click(new object(), new EventArgs());
                        }
                    }
                }));
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
        }

        void RcpLogEventReceived(object sender, StringEventArg e)
        {
            DisplayMsgString(e.Data);
        }

        void RxRspEventReceived(object sender, ProtocolEventArg e)
        {
            if (this.IsDisposed)
                return;

            if (!this.InvokeRequired)
            {
                __ParseRsp(e.Protocol);
                return;
            }

            this.Invoke(new MethodInvoker(delegate()
            {
                __ParseRsp(e.Protocol);
            }));
        }

        private void __ParseRsp(ProtocolStruct Data)
        {
            switch (Data.Code)
            {
                case PassiveRcp.RCP_CMD_INFO:
                    if (Data.Length > 0 && Data.Type == 0)
                    {
                        m_bAlive = true;
                        #region ---Parameter---
                        string strInfo = Encoding.ASCII.GetString(Data.Payload, 0, Data.Length);

                        SystemPub.ADRcp.Type = strInfo.Substring(17, 1);
                        SystemPub.ADRcp.Mode = strInfo.Substring(18, 1);
                        SystemPub.ADRcp.Version = strInfo.Substring(19, 5);
                        SystemPub.ADRcp.Address = Convert.ToInt32(strInfo.Substring(29, 5));

                        if (SystemPub.ADRcp.Type != "W" && SystemPub.ADRcp.Type != "T")
                            SystemPub.ADRcp.Type = "C";
                        ReaderMode = SystemPub.ADRcp.Mode + SystemPub.ADRcp.Type;

                        tsFWVersion.Text = BaseSettings.AppsLanguage == BaseSettings.LngType.ENG ?
                            "Type:" + ReaderMode + " - Version:" + SystemPub.ADRcp.Version + " - Address: " + SystemPub.ADRcp.Address :
                            "类型:" + ReaderMode + " - 版本:" + SystemPub.ADRcp.Version + " - 地址: " + SystemPub.ADRcp.Address;
                        #endregion

                        switch (ReaderMode.Substring(0, 1))
                        {
                            case "P":
                                ucPassive1.Show();
                                ucPassive1.Parent = pnlInformation;
                                ucPassive1.Dock = DockStyle.Fill;
                                SystemPub.ADRcp.Sio = SystemPub.ADSio;
                                break;
                        }
                    }
                    break;
            }

            switch (ReaderMode.Substring(0, 1))
            {
                case "P":
                    if (ucPassive1 != null) ucPassive1.ParseRsp(Data);
                    pDisplayStatusInfo(Data.Code, Data.Type, Data.Length);
                    break;
            }
        }

        private void pDisplayStatusInfo(byte code, byte type, byte len)
        {
            bool blnStatus = (type == 0x21 || type == 0x00 || type == 0x32);
            string strStatus = blnStatus ? "Success " : "Fail ";
            bool blnAction = len > 0;
            string strAction = len > 0 ? "Read " : "Write ";
            string strType = "";
            switch (code)
            {
                case PassiveRcp.RCP_CMD_INFO:
                    strType = blnAction ? "Information " : "Address ";
                    break;
                case PassiveRcp.RCP_CMD_ISO6B_RW:
                    strType = "ISO6B ";
                    break;
                case PassiveRcp.RCP_CMD_EPC_RW:
                    strType = "EPC ";
                    break;
                case PassiveRcp.RCP_CMD_ISO6B_IDEN:
                    strType = "ISO6B Identify ";
                    break;
                case PassiveRcp.RCP_CMD_EPC_IDEN:
                    strType = "EPC Identify";
                    break;
                case PassiveRcp.RCP_CMD_EPC_MULT:
                    strType = "Mult EPC Identify ";
                    break;
                case PassiveRcp.RCP_CMD_PARA:
                    strType = "BASE Parameters ";
                    break;
                case PassiveRcp.RCP_CMD_TCPIP:
                    strType = "TCPIP Parameters ";
                    break;
                case PassiveRcp.RCP_CMD_OUTCARD:
                    strType = "Output Type ";
                    break;
                case PassiveRcp.RCP_CMD_SECRET:
                    strType = "Secret ";
                    break;
                case PassiveRcp.RCP_CMD_SOFTRESET:
                    strType = "Soft reset ";
                    break;
                case PassiveRcp.RCP_CMD_INITSYRIS:
                    strType = "Init syris number ";
                    break;
                case PassiveRcp.RCP_CMD_REMOTE:
                    strType = "Remote IO ";
                    break;
                case PassiveRcp.RCP_CMD_TIME:
                    strType = "Time ";
                    break;
                default:
                    break;
            }
            if (blnStatus) tsStatusInfo.ForeColor = Color.Green; else tsStatusInfo.ForeColor = Color.Red;
            tsStatusInfo.Text = strStatus + strType + strAction;
        }

        #endregion

        #region ---ThreadReadInfo----
        private bool m_bStopComm = false;
        private bool m_bAlive = false;

        private Thread monThread = null;
        private int mReadInfoCount = 0;
        private void StartReadInfo()
        {
            ClearReaderInfo();

            if (monThread == null || monThread.IsAlive == false)
            {
                monThread = new Thread(new ThreadStart(ThreadReadInfo));
                monThread.Start();
            }
        }
        private void ClearReaderInfo()
        {
            mReadInfoCount = 0;
            if (!InvokeRequired)
            {
                tsStatusInfo.Text = "";
            }
            else
            {
                this.Invoke(new MethodInvoker(delegate()
                {
                    tsStatusInfo.Text = "";
                }));
            }
        }
        private void ThreadReadInfo()
        {
            while (!m_bAlive && SystemPub.ADSio.bConnected)
            {
                System.Threading.Thread.Sleep(20);

                // Protocol Parameters
                if (!SystemPub.ADRcp.SendBytePkt(SystemPub.ADRcp.BuildCmdPacketByte(PassiveRcp.RCP_MSG_GET, PassiveRcp.RCP_CMD_INFO, null)))
                {
                    mReadInfoCount++;
                    if (mReadInfoCount > 3)
                    {
                        mReadInfoCount = 0;
                        if (m_bStopComm) break;
                        SwitchPortAndBaud();
                    }
                    continue;
                }

                mReadInfoCount = 0;
                System.Threading.Thread.Sleep(100);

                this.tsStatusInfo.Text = "  Ready..";
            }

            System.Console.WriteLine(" End ThreadReadInfo()");
        }

        int mPortIndex = 0;
        string[] mPortNameArray;
        private void GetPortName()
        {
            mPortNameArray = SerialPort.GetPortNames();
            for (int i = 0; i < mPortNameArray.Length; i++)
            {
                if (UserSettings.PortName == mPortNameArray[i])
                {
                    mPortIndex = i;
                    return;
                }
            }
            mPortIndex = 0;
        }

        private string GetNextPortName()
        {
            if (mPortNameArray.Length <= 0) return "";
            mPortIndex++;
            if (mPortIndex >= mPortNameArray.Length) mPortIndex = 0;
            return mPortNameArray[mPortIndex];
        }

        private void SwitchPortAndBaud()
        {
            if (UserSettings.Communication == UserSettings.CommType.SERIAL)
            {
                this.Invoke(new MethodInvoker(delegate()
                {
                    SystemPub.ADSio.DisConnect();
                    if (UserSettings.HostPort == 9600)
                    {
                        UserSettings.BaudRate = 115200;
                    }
                    else
                    {
                        UserSettings.PortName = GetNextPortName();
                        UserSettings.BaudRate = 9600;
                    }
                    LoadCommType(UserSettings.Communication);
                    SystemPub.ADSio.Connect(UserSettings.HostName, UserSettings.HostPort);
                }));
            }
        }
        #endregion

        private void tsmiConnect_Click(object sender, EventArgs e)
        {
            tsmiConnect.Enabled = false;
            Application.DoEvents();
            if (SystemPub.ADSio.bConnected)
            {
                SystemPub.ADSio.DisConnect();
                m_bStopComm = true;
            }
            else
            {

                m_bStopComm = false;
                SystemPub.ADRcp.Sio = SystemPub.ADSio;
                SystemPub.ADSio.Connect(UserSettings.HostName, UserSettings.HostPort);
                Application.DoEvents();
                if (!SystemPub.ADSio.bConnected && UserSettings.Communication == UserSettings.CommType.NET) fwt.ShowDialog();
                Application.DoEvents();
            }
        }

        private void tmrClock_Tick(object sender, EventArgs e)
        {
            tsStatusPortOpen.Text = SystemPub.ADSio.bConnected ? "CONNECTED" : "DISCONNECTED";
            tsmiRCPLogging.Visible = m_bAlive;
            tsmiComm.Enabled = !tsmiRCPLogging.Visible;
        }

    }
}
