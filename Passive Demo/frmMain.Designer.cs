namespace Aosid
{
    partial class frmMain
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(frmMain));
            this.ttpAttention = new System.Windows.Forms.ToolTip(this.components);
            this.pnlBody = new System.Windows.Forms.Panel();
            this.pnlInformation = new System.Windows.Forms.Panel();
            this.listViewMsg = new System.Windows.Forms.ListView();
            this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader3 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader4 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.contextMenuStrip = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.tsMenuItemClear = new System.Windows.Forms.ToolStripMenuItem();
            this.tsMenuItemCopy = new System.Windows.Forms.ToolStripMenuItem();
            this.tsMenuItemCopyAll = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuBar = new System.Windows.Forms.MenuStrip();
            this.tsmiConnect = new System.Windows.Forms.ToolStripMenuItem();
            this.tsmiComm = new System.Windows.Forms.ToolStripMenuItem();
            this.tsmiCommSerial = new System.Windows.Forms.ToolStripMenuItem();
            this.tsmiCommNet = new System.Windows.Forms.ToolStripMenuItem();
            this.tsmiCommUsb = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.tsmiCommConfig = new System.Windows.Forms.ToolStripMenuItem();
            this.tsmiRCPLogging = new System.Windows.Forms.ToolStripMenuItem();
            this.tsmiLogEnable = new System.Windows.Forms.ToolStripMenuItem();
            this.tsmiLanguage = new System.Windows.Forms.ToolStripMenuItem();
            this.tsmiLngChn = new System.Windows.Forms.ToolStripMenuItem();
            this.tsmiLngEng = new System.Windows.Forms.ToolStripMenuItem();
            this.tsmiHelp = new System.Windows.Forms.ToolStripMenuItem();
            this.tsmiMsg = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.tsmiUserManual = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.tsmiAboutMe = new System.Windows.Forms.ToolStripMenuItem();
            this.statusBar = new System.Windows.Forms.StatusStrip();
            this.tsStatusPortOpen = new System.Windows.Forms.ToolStripStatusLabel();
            this.tsStatusPort = new System.Windows.Forms.ToolStripStatusLabel();
            this.tsStatusBr = new System.Windows.Forms.ToolStripStatusLabel();
            this.tsFWVersion = new System.Windows.Forms.ToolStripStatusLabel();
            this.tsStatusInfo = new System.Windows.Forms.ToolStripStatusLabel();
            this.tmrClock = new System.Windows.Forms.Timer(this.components);
            this.pnlBody.SuspendLayout();
            this.contextMenuStrip.SuspendLayout();
            this.mnuBar.SuspendLayout();
            this.statusBar.SuspendLayout();
            this.SuspendLayout();
            // 
            // pnlTitle
            // 
            this.pnlTitle.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.pnlTitle.Size = new System.Drawing.Size(960, 28);
            // 
            // ttpAttention
            // 
            this.ttpAttention.AutomaticDelay = 0;
            this.ttpAttention.AutoPopDelay = 3000;
            this.ttpAttention.InitialDelay = 300;
            this.ttpAttention.ReshowDelay = 0;
            this.ttpAttention.UseFading = false;
            // 
            // pnlBody
            // 
            this.pnlBody.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pnlBody.Controls.Add(this.pnlInformation);
            this.pnlBody.Controls.Add(this.listViewMsg);
            this.pnlBody.Controls.Add(this.mnuBar);
            this.pnlBody.Controls.Add(this.statusBar);
            this.pnlBody.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pnlBody.Location = new System.Drawing.Point(0, 28);
            this.pnlBody.Name = "pnlBody";
            this.pnlBody.Size = new System.Drawing.Size(960, 672);
            this.pnlBody.TabIndex = 4;
            // 
            // pnlInformation
            // 
            this.pnlInformation.AutoScroll = true;
            this.pnlInformation.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pnlInformation.Location = new System.Drawing.Point(0, 25);
            this.pnlInformation.Name = "pnlInformation";
            this.pnlInformation.Size = new System.Drawing.Size(958, 461);
            this.pnlInformation.TabIndex = 47;
            // 
            // listViewMsg
            // 
            this.listViewMsg.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1,
            this.columnHeader2,
            this.columnHeader3,
            this.columnHeader4});
            this.listViewMsg.ContextMenuStrip = this.contextMenuStrip;
            this.listViewMsg.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.listViewMsg.Font = new System.Drawing.Font("Arial", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.listViewMsg.FullRowSelect = true;
            this.listViewMsg.Location = new System.Drawing.Point(0, 486);
            this.listViewMsg.MultiSelect = false;
            this.listViewMsg.Name = "listViewMsg";
            this.listViewMsg.Size = new System.Drawing.Size(958, 160);
            this.listViewMsg.TabIndex = 48;
            this.listViewMsg.UseCompatibleStateImageBehavior = false;
            this.listViewMsg.View = System.Windows.Forms.View.Details;
            // 
            // columnHeader1
            // 
            this.columnHeader1.Text = "Time";
            this.columnHeader1.Width = 80;
            // 
            // columnHeader2
            // 
            this.columnHeader2.Text = "Type";
            this.columnHeader2.Width = 100;
            // 
            // columnHeader3
            // 
            this.columnHeader3.Text = "RCP Packet (HEX)";
            this.columnHeader3.Width = 500;
            // 
            // columnHeader4
            // 
            this.columnHeader4.Text = "Details";
            this.columnHeader4.Width = 300;
            // 
            // contextMenuStrip
            // 
            this.contextMenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsMenuItemClear,
            this.tsMenuItemCopy,
            this.tsMenuItemCopyAll});
            this.contextMenuStrip.Name = "contextMenuStrip1";
            this.contextMenuStrip.ShowImageMargin = false;
            this.contextMenuStrip.Size = new System.Drawing.Size(100, 70);
            // 
            // tsMenuItemClear
            // 
            this.tsMenuItemClear.Name = "tsMenuItemClear";
            this.tsMenuItemClear.Size = new System.Drawing.Size(99, 22);
            this.tsMenuItemClear.Text = "C&lear";
            this.tsMenuItemClear.Click += new System.EventHandler(this.tsMenuItemClear_Click);
            // 
            // tsMenuItemCopy
            // 
            this.tsMenuItemCopy.Name = "tsMenuItemCopy";
            this.tsMenuItemCopy.Size = new System.Drawing.Size(99, 22);
            this.tsMenuItemCopy.Text = "&Copy";
            this.tsMenuItemCopy.Click += new System.EventHandler(this.tsMenuItemCopy_Click);
            // 
            // tsMenuItemCopyAll
            // 
            this.tsMenuItemCopyAll.Name = "tsMenuItemCopyAll";
            this.tsMenuItemCopyAll.Size = new System.Drawing.Size(99, 22);
            this.tsMenuItemCopyAll.Text = "Copy &All";
            this.tsMenuItemCopyAll.Click += new System.EventHandler(this.tsMenuItemCopyAll_Click);
            // 
            // mnuBar
            // 
            this.mnuBar.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsmiConnect,
            this.tsmiComm,
            this.tsmiRCPLogging,
            this.tsmiLanguage,
            this.tsmiHelp});
            this.mnuBar.Location = new System.Drawing.Point(0, 0);
            this.mnuBar.Name = "mnuBar";
            this.mnuBar.Size = new System.Drawing.Size(958, 25);
            this.mnuBar.TabIndex = 45;
            this.mnuBar.Text = "menuStrip1";
            this.mnuBar.MouseLeave += new System.EventHandler(this.AttentionMouseLeave);
            // 
            // tsmiConnect
            // 
            this.tsmiConnect.Name = "tsmiConnect";
            this.tsmiConnect.Size = new System.Drawing.Size(99, 21);
            this.tsmiConnect.Text = "Connect(联机)";
            this.tsmiConnect.Click += new System.EventHandler(this.tsmiConnect_Click);
            this.tsmiConnect.MouseEnter += new System.EventHandler(this.tsmiConnect_MouseEnter);
            // 
            // tsmiComm
            // 
            this.tsmiComm.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsmiCommSerial,
            this.tsmiCommNet,
            this.tsmiCommUsb,
            this.toolStripSeparator2,
            this.tsmiCommConfig});
            this.tsmiComm.Name = "tsmiComm";
            this.tsmiComm.Size = new System.Drawing.Size(93, 21);
            this.tsmiComm.Text = "Comm.(通信)";
            this.tsmiComm.MouseEnter += new System.EventHandler(this.tsmiComm_MouseEnter);
            // 
            // tsmiCommSerial
            // 
            this.tsmiCommSerial.Name = "tsmiCommSerial";
            this.tsmiCommSerial.Size = new System.Drawing.Size(148, 22);
            this.tsmiCommSerial.Text = "SERIALPORT";
            this.tsmiCommSerial.Click += new System.EventHandler(this.ChangeCommType);
            // 
            // tsmiCommNet
            // 
            this.tsmiCommNet.Name = "tsmiCommNet";
            this.tsmiCommNet.Size = new System.Drawing.Size(148, 22);
            this.tsmiCommNet.Text = "NET(TCPIP)";
            this.tsmiCommNet.Click += new System.EventHandler(this.ChangeCommType);
            // 
            // tsmiCommUsb
            // 
            this.tsmiCommUsb.Name = "tsmiCommUsb";
            this.tsmiCommUsb.Size = new System.Drawing.Size(148, 22);
            this.tsmiCommUsb.Text = "USB";
            this.tsmiCommUsb.Click += new System.EventHandler(this.ChangeCommType);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(145, 6);
            // 
            // tsmiCommConfig
            // 
            this.tsmiCommConfig.Name = "tsmiCommConfig";
            this.tsmiCommConfig.Size = new System.Drawing.Size(148, 22);
            this.tsmiCommConfig.Text = "SETTINGS";
            this.tsmiCommConfig.Click += new System.EventHandler(this.tsmiCommConfig_Click);
            // 
            // tsmiRCPLogging
            // 
            this.tsmiRCPLogging.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsmiLogEnable});
            this.tsmiRCPLogging.Name = "tsmiRCPLogging";
            this.tsmiRCPLogging.Size = new System.Drawing.Size(127, 21);
            this.tsmiRCPLogging.Text = "RCP Logging(日志)";
            this.tsmiRCPLogging.Visible = false;
            this.tsmiRCPLogging.MouseEnter += new System.EventHandler(this.tsmiRCPLogging_MouseEnter);
            // 
            // tsmiLogEnable
            // 
            this.tsmiLogEnable.Name = "tsmiLogEnable";
            this.tsmiLogEnable.Size = new System.Drawing.Size(141, 22);
            this.tsmiLogEnable.Text = "Log Enable";
            this.tsmiLogEnable.Click += new System.EventHandler(this.tsmiLogEnable_Click);
            // 
            // tsmiLanguage
            // 
            this.tsmiLanguage.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsmiLngChn,
            this.tsmiLngEng});
            this.tsmiLanguage.Name = "tsmiLanguage";
            this.tsmiLanguage.Size = new System.Drawing.Size(118, 21);
            this.tsmiLanguage.Text = "LANGUAGE(语言)";
            this.tsmiLanguage.MouseEnter += new System.EventHandler(this.tsmiLanguage_MouseEnter);
            // 
            // tsmiLngChn
            // 
            this.tsmiLngChn.Name = "tsmiLngChn";
            this.tsmiLngChn.Size = new System.Drawing.Size(124, 22);
            this.tsmiLngChn.Text = "简体中文";
            this.tsmiLngChn.Click += new System.EventHandler(this.tsmiLngChn_Click);
            // 
            // tsmiLngEng
            // 
            this.tsmiLngEng.Name = "tsmiLngEng";
            this.tsmiLngEng.Size = new System.Drawing.Size(124, 22);
            this.tsmiLngEng.Text = "English";
            this.tsmiLngEng.Click += new System.EventHandler(this.tsmiLngEng_Click);
            // 
            // tsmiHelp
            // 
            this.tsmiHelp.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsmiMsg,
            this.toolStripSeparator3,
            this.tsmiUserManual,
            this.toolStripSeparator1,
            this.tsmiAboutMe});
            this.tsmiHelp.Name = "tsmiHelp";
            this.tsmiHelp.Size = new System.Drawing.Size(79, 21);
            this.tsmiHelp.Text = "Help(帮助)";
            this.tsmiHelp.MouseEnter += new System.EventHandler(this.tsmiHelp_MouseEnter);
            // 
            // tsmiMsg
            // 
            this.tsmiMsg.Name = "tsmiMsg";
            this.tsmiMsg.Size = new System.Drawing.Size(200, 22);
            this.tsmiMsg.Text = "实时信息";
            this.tsmiMsg.Click += new System.EventHandler(this.tsmiMsg_Click);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(197, 6);
            // 
            // tsmiUserManual
            // 
            this.tsmiUserManual.Name = "tsmiUserManual";
            this.tsmiUserManual.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.F1)));
            this.tsmiUserManual.Size = new System.Drawing.Size(200, 22);
            this.tsmiUserManual.Text = "User Manual";
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(197, 6);
            // 
            // tsmiAboutMe
            // 
            this.tsmiAboutMe.Name = "tsmiAboutMe";
            this.tsmiAboutMe.Size = new System.Drawing.Size(200, 22);
            this.tsmiAboutMe.Text = "&About ";
            this.tsmiAboutMe.Click += new System.EventHandler(this.tsmiAboutMe_Click);
            // 
            // statusBar
            // 
            this.statusBar.AutoSize = false;
            this.statusBar.Font = new System.Drawing.Font("Arial", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.statusBar.GripStyle = System.Windows.Forms.ToolStripGripStyle.Visible;
            this.statusBar.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsStatusPortOpen,
            this.tsStatusPort,
            this.tsStatusBr,
            this.tsFWVersion,
            this.tsStatusInfo});
            this.statusBar.Location = new System.Drawing.Point(0, 646);
            this.statusBar.Name = "statusBar";
            this.statusBar.Size = new System.Drawing.Size(958, 24);
            this.statusBar.SizingGrip = false;
            this.statusBar.TabIndex = 44;
            this.statusBar.Text = "statusStrip1";
            this.statusBar.MouseLeave += new System.EventHandler(this.AttentionMouseLeave);
            // 
            // tsStatusPortOpen
            // 
            this.tsStatusPortOpen.AutoSize = false;
            this.tsStatusPortOpen.BorderSides = ((System.Windows.Forms.ToolStripStatusLabelBorderSides)((System.Windows.Forms.ToolStripStatusLabelBorderSides.Left | System.Windows.Forms.ToolStripStatusLabelBorderSides.Right)));
            this.tsStatusPortOpen.Font = new System.Drawing.Font("Arial", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tsStatusPortOpen.Name = "tsStatusPortOpen";
            this.tsStatusPortOpen.Size = new System.Drawing.Size(100, 19);
            this.tsStatusPortOpen.Text = "CLOSE   ";
            this.tsStatusPortOpen.MouseEnter += new System.EventHandler(this.tsStatusPortOpen_MouseEnter);
            // 
            // tsStatusPort
            // 
            this.tsStatusPort.AutoSize = false;
            this.tsStatusPort.BorderSides = ((System.Windows.Forms.ToolStripStatusLabelBorderSides)((System.Windows.Forms.ToolStripStatusLabelBorderSides.Left | System.Windows.Forms.ToolStripStatusLabelBorderSides.Right)));
            this.tsStatusPort.Font = new System.Drawing.Font("Arial", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tsStatusPort.Name = "tsStatusPort";
            this.tsStatusPort.Size = new System.Drawing.Size(120, 19);
            this.tsStatusPort.Text = "COM?";
            this.tsStatusPort.Click += new System.EventHandler(this.tsmiCommConfig_Click);
            this.tsStatusPort.MouseEnter += new System.EventHandler(this.tsStatusPort_MouseEnter);
            // 
            // tsStatusBr
            // 
            this.tsStatusBr.AutoSize = false;
            this.tsStatusBr.BorderSides = ((System.Windows.Forms.ToolStripStatusLabelBorderSides)((System.Windows.Forms.ToolStripStatusLabelBorderSides.Left | System.Windows.Forms.ToolStripStatusLabelBorderSides.Right)));
            this.tsStatusBr.Font = new System.Drawing.Font("Arial", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tsStatusBr.Name = "tsStatusBr";
            this.tsStatusBr.Size = new System.Drawing.Size(80, 19);
            this.tsStatusBr.Text = "115200";
            this.tsStatusBr.Click += new System.EventHandler(this.tsmiCommConfig_Click);
            this.tsStatusBr.MouseEnter += new System.EventHandler(this.tsStatusBr_MouseEnter);
            // 
            // tsFWVersion
            // 
            this.tsFWVersion.AutoSize = false;
            this.tsFWVersion.BorderSides = ((System.Windows.Forms.ToolStripStatusLabelBorderSides)((System.Windows.Forms.ToolStripStatusLabelBorderSides.Left | System.Windows.Forms.ToolStripStatusLabelBorderSides.Right)));
            this.tsFWVersion.Name = "tsFWVersion";
            this.tsFWVersion.Size = new System.Drawing.Size(260, 19);
            this.tsFWVersion.Text = "Firmware Version";
            this.tsFWVersion.MouseEnter += new System.EventHandler(this.tsFWVersion_MouseEnter);
            // 
            // tsStatusInfo
            // 
            this.tsStatusInfo.BorderSides = System.Windows.Forms.ToolStripStatusLabelBorderSides.Left;
            this.tsStatusInfo.Name = "tsStatusInfo";
            this.tsStatusInfo.Size = new System.Drawing.Size(383, 19);
            this.tsStatusInfo.Spring = true;
            this.tsStatusInfo.Text = "  Status..";
            this.tsStatusInfo.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.tsStatusInfo.MouseEnter += new System.EventHandler(this.tsStatusInfo_MouseEnter);
            // 
            // tmrClock
            // 
            this.tmrClock.Enabled = true;
            this.tmrClock.Interval = 200;
            this.tmrClock.Tick += new System.EventHandler(this.tmrClock_Tick);
            // 
            // frmMain
            // 
            this.ClientSize = new System.Drawing.Size(960, 700);
            this.Controls.Add(this.pnlBody);
            this.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.mnuBar;
            this.Name = "frmMain";
            this.StopResize = false;
            this.Text = "RFID Demo";
            this.TitleVisable = true;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.frmMain_FormClosing);
            this.Controls.SetChildIndex(this.pnlTitle, 0);
            this.Controls.SetChildIndex(this.pnlBody, 0);
            this.pnlBody.ResumeLayout(false);
            this.pnlBody.PerformLayout();
            this.contextMenuStrip.ResumeLayout(false);
            this.mnuBar.ResumeLayout(false);
            this.mnuBar.PerformLayout();
            this.statusBar.ResumeLayout(false);
            this.statusBar.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ToolTip ttpAttention;
        private System.Windows.Forms.Panel pnlBody;
        private System.Windows.Forms.StatusStrip statusBar;
        private System.Windows.Forms.ToolStripStatusLabel tsStatusPortOpen;
        private System.Windows.Forms.ToolStripStatusLabel tsStatusPort;
        private System.Windows.Forms.ToolStripStatusLabel tsStatusBr;
        private System.Windows.Forms.ToolStripStatusLabel tsFWVersion;
        private System.Windows.Forms.ToolStripStatusLabel tsStatusInfo;
        private System.Windows.Forms.MenuStrip mnuBar;
        private System.Windows.Forms.ToolStripMenuItem tsmiLanguage;
        private System.Windows.Forms.ToolStripMenuItem tsmiLngChn;
        private System.Windows.Forms.ToolStripMenuItem tsmiLngEng;
        private System.Windows.Forms.ToolStripMenuItem tsmiComm;
        private System.Windows.Forms.ToolStripMenuItem tsmiCommSerial;
        private System.Windows.Forms.ToolStripMenuItem tsmiCommNet;
        private System.Windows.Forms.ToolStripMenuItem tsmiCommUsb;
        private System.Windows.Forms.ToolStripMenuItem tsmiRCPLogging;
        private System.Windows.Forms.ToolStripMenuItem tsmiLogEnable;
        private System.Windows.Forms.ToolStripMenuItem tsmiHelp;
        private System.Windows.Forms.ToolStripMenuItem tsmiUserManual;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem tsmiAboutMe;
        private System.Windows.Forms.ToolStripMenuItem tsmiCommConfig;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.Panel pnlInformation;
        private System.Windows.Forms.ToolStripMenuItem tsmiConnect;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip;
        private System.Windows.Forms.ToolStripMenuItem tsMenuItemClear;
        private System.Windows.Forms.ToolStripMenuItem tsMenuItemCopy;
        private System.Windows.Forms.ToolStripMenuItem tsMenuItemCopyAll;
        private System.Windows.Forms.ListView listViewMsg;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.ColumnHeader columnHeader2;
        private System.Windows.Forms.ColumnHeader columnHeader3;
        private System.Windows.Forms.ColumnHeader columnHeader4;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripMenuItem tsmiMsg;
        private System.Windows.Forms.Timer tmrClock;

    }
}