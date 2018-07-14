namespace Aosid
{
    partial class ucPSeniorSettings
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.btnDefault = new System.Windows.Forms.Button();
            this.btnSetPara = new System.Windows.Forms.Button();
            this.btnGetPara = new System.Windows.Forms.Button();
            this.grbTime = new System.Windows.Forms.GroupBox();
            this.txtReaderTime = new System.Windows.Forms.TextBox();
            this.lblReaderTime = new System.Windows.Forms.Label();
            this.txtNowTime = new System.Windows.Forms.TextBox();
            this.lblNowTime = new System.Windows.Forms.Label();
            this.btnGetTime = new System.Windows.Forms.Button();
            this.btnSetTime = new System.Windows.Forms.Button();
            this.grbSoft = new System.Windows.Forms.GroupBox();
            this.btnReset = new System.Windows.Forms.Button();
            this.btnIO2Close = new System.Windows.Forms.Button();
            this.btnIO2Open = new System.Windows.Forms.Button();
            this.btnIO1Close = new System.Windows.Forms.Button();
            this.btnIO1Open = new System.Windows.Forms.Button();
            this.grbSYRIS = new System.Windows.Forms.GroupBox();
            this.btnInitSyris = new System.Windows.Forms.Button();
            this.cmbSyrisID = new System.Windows.Forms.ComboBox();
            this.lblSyrisID = new System.Windows.Forms.Label();
            this.txtSyrisSN = new System.Windows.Forms.TextBox();
            this.lblSyrisSN = new System.Windows.Forms.Label();
            this.grbAddress = new System.Windows.Forms.GroupBox();
            this.utxtNewAddr = new ADSDK.Bases.Components.FormatTextBox();
            this.btnAddress = new System.Windows.Forms.Button();
            this.lblOldAddr = new System.Windows.Forms.Label();
            this.txtOldAddr = new System.Windows.Forms.TextBox();
            this.lblNewAddr = new System.Windows.Forms.Label();
            this.grbTCPIP = new System.Windows.Forms.GroupBox();
            this.pnlRemote = new System.Windows.Forms.Panel();
            this.txtRemotePort = new System.Windows.Forms.TextBox();
            this.lblRemotePort = new System.Windows.Forms.Label();
            this.txtRemoteIP = new System.Windows.Forms.TextBox();
            this.lblRemoteIP = new System.Windows.Forms.Label();
            this.cmbIsServer = new System.Windows.Forms.ComboBox();
            this.lblIsServer = new System.Windows.Forms.Label();
            this.txtTCPMac = new System.Windows.Forms.TextBox();
            this.lblTCPMac = new System.Windows.Forms.Label();
            this.txtTCPGateway = new System.Windows.Forms.TextBox();
            this.lblTCPGateway = new System.Windows.Forms.Label();
            this.txtTCPMask = new System.Windows.Forms.TextBox();
            this.lblTCPMask = new System.Windows.Forms.Label();
            this.txtTCPPort = new System.Windows.Forms.TextBox();
            this.lblTCPPort = new System.Windows.Forms.Label();
            this.txtTCPIP = new System.Windows.Forms.TextBox();
            this.lblTCPIP = new System.Windows.Forms.Label();
            this.tmrClock = new System.Windows.Forms.Timer(this.components);
            this.grbTime.SuspendLayout();
            this.grbSoft.SuspendLayout();
            this.grbSYRIS.SuspendLayout();
            this.grbAddress.SuspendLayout();
            this.grbTCPIP.SuspendLayout();
            this.pnlRemote.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnDefault
            // 
            this.btnDefault.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.btnDefault.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.btnDefault.Location = new System.Drawing.Point(634, 75);
            this.btnDefault.Name = "btnDefault";
            this.btnDefault.Size = new System.Drawing.Size(120, 30);
            this.btnDefault.TabIndex = 8;
            this.btnDefault.TabStop = false;
            this.btnDefault.Text = "&Default TCPIP";
            this.btnDefault.UseVisualStyleBackColor = false;
            this.btnDefault.Click += new System.EventHandler(this.btnDefaultTcpip_Click);
            // 
            // btnSetPara
            // 
            this.btnSetPara.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.btnSetPara.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.btnSetPara.Location = new System.Drawing.Point(634, 45);
            this.btnSetPara.Name = "btnSetPara";
            this.btnSetPara.Size = new System.Drawing.Size(120, 30);
            this.btnSetPara.TabIndex = 7;
            this.btnSetPara.TabStop = false;
            this.btnSetPara.Text = "&Set TCPIP";
            this.btnSetPara.UseVisualStyleBackColor = false;
            this.btnSetPara.Click += new System.EventHandler(this.btnSetTcpip_Click);
            // 
            // btnGetPara
            // 
            this.btnGetPara.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.btnGetPara.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.btnGetPara.Location = new System.Drawing.Point(634, 15);
            this.btnGetPara.Name = "btnGetPara";
            this.btnGetPara.Size = new System.Drawing.Size(120, 30);
            this.btnGetPara.TabIndex = 6;
            this.btnGetPara.TabStop = false;
            this.btnGetPara.Text = "&Get TCPIP";
            this.btnGetPara.UseVisualStyleBackColor = false;
            this.btnGetPara.Click += new System.EventHandler(this.btnGetTcpip_Click);
            // 
            // grbTime
            // 
            this.grbTime.Controls.Add(this.txtReaderTime);
            this.grbTime.Controls.Add(this.lblReaderTime);
            this.grbTime.Controls.Add(this.txtNowTime);
            this.grbTime.Controls.Add(this.lblNowTime);
            this.grbTime.Controls.Add(this.btnGetTime);
            this.grbTime.Controls.Add(this.btnSetTime);
            this.grbTime.Dock = System.Windows.Forms.DockStyle.Top;
            this.grbTime.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.grbTime.Location = new System.Drawing.Point(0, 246);
            this.grbTime.Name = "grbTime";
            this.grbTime.Size = new System.Drawing.Size(990, 52);
            this.grbTime.TabIndex = 3;
            this.grbTime.TabStop = false;
            this.grbTime.Text = "Time Config";
            // 
            // txtReaderTime
            // 
            this.txtReaderTime.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.txtReaderTime.Location = new System.Drawing.Point(442, 19);
            this.txtReaderTime.Margin = new System.Windows.Forms.Padding(4);
            this.txtReaderTime.MaxLength = 8;
            this.txtReaderTime.Name = "txtReaderTime";
            this.txtReaderTime.ReadOnly = true;
            this.txtReaderTime.Size = new System.Drawing.Size(160, 23);
            this.txtReaderTime.TabIndex = 1;
            this.txtReaderTime.TabStop = false;
            this.txtReaderTime.Text = "- -";
            this.txtReaderTime.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // lblReaderTime
            // 
            this.lblReaderTime.AutoSize = true;
            this.lblReaderTime.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.lblReaderTime.Location = new System.Drawing.Point(312, 22);
            this.lblReaderTime.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblReaderTime.Name = "lblReaderTime";
            this.lblReaderTime.Size = new System.Drawing.Size(85, 17);
            this.lblReaderTime.TabIndex = 5;
            this.lblReaderTime.Text = "Reader Time:";
            // 
            // txtNowTime
            // 
            this.txtNowTime.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.txtNowTime.Location = new System.Drawing.Point(142, 19);
            this.txtNowTime.Margin = new System.Windows.Forms.Padding(4);
            this.txtNowTime.MaxLength = 8;
            this.txtNowTime.Name = "txtNowTime";
            this.txtNowTime.ReadOnly = true;
            this.txtNowTime.Size = new System.Drawing.Size(160, 23);
            this.txtNowTime.TabIndex = 0;
            this.txtNowTime.TabStop = false;
            this.txtNowTime.Text = "- -";
            this.txtNowTime.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // lblNowTime
            // 
            this.lblNowTime.AutoSize = true;
            this.lblNowTime.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.lblNowTime.Location = new System.Drawing.Point(12, 22);
            this.lblNowTime.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblNowTime.Name = "lblNowTime";
            this.lblNowTime.Size = new System.Drawing.Size(70, 17);
            this.lblNowTime.TabIndex = 4;
            this.lblNowTime.Text = "Now Time:";
            // 
            // btnGetTime
            // 
            this.btnGetTime.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.btnGetTime.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.btnGetTime.Location = new System.Drawing.Point(634, 15);
            this.btnGetTime.Name = "btnGetTime";
            this.btnGetTime.Size = new System.Drawing.Size(58, 30);
            this.btnGetTime.TabIndex = 2;
            this.btnGetTime.TabStop = false;
            this.btnGetTime.Text = "Get";
            this.btnGetTime.UseVisualStyleBackColor = false;
            this.btnGetTime.Click += new System.EventHandler(this.btnGetTime_Click);
            // 
            // btnSetTime
            // 
            this.btnSetTime.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.btnSetTime.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.btnSetTime.Location = new System.Drawing.Point(696, 15);
            this.btnSetTime.Name = "btnSetTime";
            this.btnSetTime.Size = new System.Drawing.Size(58, 30);
            this.btnSetTime.TabIndex = 3;
            this.btnSetTime.TabStop = false;
            this.btnSetTime.Text = "Set";
            this.btnSetTime.UseVisualStyleBackColor = false;
            this.btnSetTime.Click += new System.EventHandler(this.btnSetTime_Click);
            // 
            // grbSoft
            // 
            this.grbSoft.Controls.Add(this.btnReset);
            this.grbSoft.Controls.Add(this.btnIO2Close);
            this.grbSoft.Controls.Add(this.btnIO2Open);
            this.grbSoft.Controls.Add(this.btnIO1Close);
            this.grbSoft.Controls.Add(this.btnIO1Open);
            this.grbSoft.Dock = System.Windows.Forms.DockStyle.Top;
            this.grbSoft.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.grbSoft.Location = new System.Drawing.Point(0, 298);
            this.grbSoft.Name = "grbSoft";
            this.grbSoft.Size = new System.Drawing.Size(990, 52);
            this.grbSoft.TabIndex = 4;
            this.grbSoft.TabStop = false;
            this.grbSoft.Text = "Soft Config";
            // 
            // btnReset
            // 
            this.btnReset.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.btnReset.Dock = System.Windows.Forms.DockStyle.Left;
            this.btnReset.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.btnReset.Location = new System.Drawing.Point(483, 19);
            this.btnReset.Name = "btnReset";
            this.btnReset.Size = new System.Drawing.Size(120, 30);
            this.btnReset.TabIndex = 4;
            this.btnReset.TabStop = false;
            this.btnReset.Text = "SoftReset";
            this.btnReset.UseVisualStyleBackColor = false;
            this.btnReset.Click += new System.EventHandler(this.btnReset_Click);
            // 
            // btnIO2Close
            // 
            this.btnIO2Close.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.btnIO2Close.Dock = System.Windows.Forms.DockStyle.Left;
            this.btnIO2Close.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.btnIO2Close.Location = new System.Drawing.Point(363, 19);
            this.btnIO2Close.Name = "btnIO2Close";
            this.btnIO2Close.Size = new System.Drawing.Size(120, 30);
            this.btnIO2Close.TabIndex = 3;
            this.btnIO2Close.TabStop = false;
            this.btnIO2Close.Text = "IO2 Close";
            this.btnIO2Close.UseVisualStyleBackColor = false;
            this.btnIO2Close.Click += new System.EventHandler(this.btnIO2Close_Click);
            // 
            // btnIO2Open
            // 
            this.btnIO2Open.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.btnIO2Open.Dock = System.Windows.Forms.DockStyle.Left;
            this.btnIO2Open.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.btnIO2Open.Location = new System.Drawing.Point(243, 19);
            this.btnIO2Open.Name = "btnIO2Open";
            this.btnIO2Open.Size = new System.Drawing.Size(120, 30);
            this.btnIO2Open.TabIndex = 2;
            this.btnIO2Open.TabStop = false;
            this.btnIO2Open.Text = "IO2 Open";
            this.btnIO2Open.UseVisualStyleBackColor = false;
            this.btnIO2Open.Click += new System.EventHandler(this.btnIO2Open_Click);
            // 
            // btnIO1Close
            // 
            this.btnIO1Close.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.btnIO1Close.Dock = System.Windows.Forms.DockStyle.Left;
            this.btnIO1Close.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.btnIO1Close.Location = new System.Drawing.Point(123, 19);
            this.btnIO1Close.Name = "btnIO1Close";
            this.btnIO1Close.Size = new System.Drawing.Size(120, 30);
            this.btnIO1Close.TabIndex = 1;
            this.btnIO1Close.TabStop = false;
            this.btnIO1Close.Text = "IO1 Close";
            this.btnIO1Close.UseVisualStyleBackColor = false;
            this.btnIO1Close.Click += new System.EventHandler(this.btnIO1Close_Click);
            // 
            // btnIO1Open
            // 
            this.btnIO1Open.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.btnIO1Open.Dock = System.Windows.Forms.DockStyle.Left;
            this.btnIO1Open.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.btnIO1Open.Location = new System.Drawing.Point(3, 19);
            this.btnIO1Open.Name = "btnIO1Open";
            this.btnIO1Open.Size = new System.Drawing.Size(120, 30);
            this.btnIO1Open.TabIndex = 0;
            this.btnIO1Open.TabStop = false;
            this.btnIO1Open.Text = "IO1 Open";
            this.btnIO1Open.UseVisualStyleBackColor = false;
            this.btnIO1Open.Click += new System.EventHandler(this.btnIO1Open_Click);
            // 
            // grbSYRIS
            // 
            this.grbSYRIS.Controls.Add(this.btnInitSyris);
            this.grbSYRIS.Controls.Add(this.cmbSyrisID);
            this.grbSYRIS.Controls.Add(this.lblSyrisID);
            this.grbSYRIS.Controls.Add(this.txtSyrisSN);
            this.grbSYRIS.Controls.Add(this.lblSyrisSN);
            this.grbSYRIS.Dock = System.Windows.Forms.DockStyle.Top;
            this.grbSYRIS.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.grbSYRIS.Location = new System.Drawing.Point(0, 194);
            this.grbSYRIS.Name = "grbSYRIS";
            this.grbSYRIS.Size = new System.Drawing.Size(990, 52);
            this.grbSYRIS.TabIndex = 2;
            this.grbSYRIS.TabStop = false;
            this.grbSYRIS.Text = "SYRIS Config";
            // 
            // btnInitSyris
            // 
            this.btnInitSyris.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.btnInitSyris.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.btnInitSyris.Location = new System.Drawing.Point(634, 15);
            this.btnInitSyris.Name = "btnInitSyris";
            this.btnInitSyris.Size = new System.Drawing.Size(120, 30);
            this.btnInitSyris.TabIndex = 2;
            this.btnInitSyris.TabStop = false;
            this.btnInitSyris.Text = "Init Syris";
            this.btnInitSyris.UseVisualStyleBackColor = false;
            this.btnInitSyris.Click += new System.EventHandler(this.btnInitSyris_Click);
            // 
            // cmbSyrisID
            // 
            this.cmbSyrisID.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbSyrisID.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.cmbSyrisID.FormattingEnabled = true;
            this.cmbSyrisID.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8"});
            this.cmbSyrisID.Location = new System.Drawing.Point(442, 18);
            this.cmbSyrisID.Name = "cmbSyrisID";
            this.cmbSyrisID.Size = new System.Drawing.Size(160, 25);
            this.cmbSyrisID.TabIndex = 1;
            this.cmbSyrisID.TabStop = false;
            // 
            // lblSyrisID
            // 
            this.lblSyrisID.AutoSize = true;
            this.lblSyrisID.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.lblSyrisID.Location = new System.Drawing.Point(312, 22);
            this.lblSyrisID.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblSyrisID.Name = "lblSyrisID";
            this.lblSyrisID.Size = new System.Drawing.Size(55, 17);
            this.lblSyrisID.TabIndex = 4;
            this.lblSyrisID.Text = "Syris ID:";
            // 
            // txtSyrisSN
            // 
            this.txtSyrisSN.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.txtSyrisSN.Location = new System.Drawing.Point(142, 19);
            this.txtSyrisSN.Margin = new System.Windows.Forms.Padding(4);
            this.txtSyrisSN.MaxLength = 8;
            this.txtSyrisSN.Name = "txtSyrisSN";
            this.txtSyrisSN.Size = new System.Drawing.Size(160, 23);
            this.txtSyrisSN.TabIndex = 0;
            this.txtSyrisSN.TabStop = false;
            this.txtSyrisSN.Text = "00000001";
            this.txtSyrisSN.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // lblSyrisSN
            // 
            this.lblSyrisSN.AutoSize = true;
            this.lblSyrisSN.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.lblSyrisSN.Location = new System.Drawing.Point(12, 22);
            this.lblSyrisSN.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblSyrisSN.Name = "lblSyrisSN";
            this.lblSyrisSN.Size = new System.Drawing.Size(59, 17);
            this.lblSyrisSN.TabIndex = 3;
            this.lblSyrisSN.Text = "Syris SN:";
            // 
            // grbAddress
            // 
            this.grbAddress.Controls.Add(this.utxtNewAddr);
            this.grbAddress.Controls.Add(this.btnAddress);
            this.grbAddress.Controls.Add(this.lblOldAddr);
            this.grbAddress.Controls.Add(this.txtOldAddr);
            this.grbAddress.Controls.Add(this.lblNewAddr);
            this.grbAddress.Dock = System.Windows.Forms.DockStyle.Top;
            this.grbAddress.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.grbAddress.Location = new System.Drawing.Point(0, 142);
            this.grbAddress.Name = "grbAddress";
            this.grbAddress.Size = new System.Drawing.Size(990, 52);
            this.grbAddress.TabIndex = 1;
            this.grbAddress.TabStop = false;
            this.grbAddress.Text = "Address Config";
            // 
            // utxtNewAddr
            // 
            this.utxtNewAddr.ErrorInvalid = false;
            this.utxtNewAddr.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.utxtNewAddr.InputChar = '0';
            this.utxtNewAddr.InputMask = "00000";
            this.utxtNewAddr.Location = new System.Drawing.Point(442, 19);
            this.utxtNewAddr.MaxLength = 5;
            this.utxtNewAddr.Name = "utxtNewAddr";
            this.utxtNewAddr.Size = new System.Drawing.Size(160, 23);
            this.utxtNewAddr.StdInputMask = ADSDK.Bases.Components.FormatTextBox.InputMaskType.Custom;
            this.utxtNewAddr.TabIndex = 1;
            this.utxtNewAddr.TabStop = false;
            this.utxtNewAddr.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // btnAddress
            // 
            this.btnAddress.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.btnAddress.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.btnAddress.Location = new System.Drawing.Point(634, 15);
            this.btnAddress.Name = "btnAddress";
            this.btnAddress.Size = new System.Drawing.Size(120, 30);
            this.btnAddress.TabIndex = 2;
            this.btnAddress.TabStop = false;
            this.btnAddress.Text = "Set Address";
            this.btnAddress.UseVisualStyleBackColor = false;
            this.btnAddress.Click += new System.EventHandler(this.btnAddress_Click);
            // 
            // lblOldAddr
            // 
            this.lblOldAddr.AutoSize = true;
            this.lblOldAddr.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.lblOldAddr.Location = new System.Drawing.Point(12, 22);
            this.lblOldAddr.Name = "lblOldAddr";
            this.lblOldAddr.Size = new System.Drawing.Size(84, 17);
            this.lblOldAddr.TabIndex = 3;
            this.lblOldAddr.Text = "Old Address:";
            // 
            // txtOldAddr
            // 
            this.txtOldAddr.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.txtOldAddr.Location = new System.Drawing.Point(142, 19);
            this.txtOldAddr.Name = "txtOldAddr";
            this.txtOldAddr.ReadOnly = true;
            this.txtOldAddr.Size = new System.Drawing.Size(160, 23);
            this.txtOldAddr.TabIndex = 0;
            this.txtOldAddr.TabStop = false;
            this.txtOldAddr.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // lblNewAddr
            // 
            this.lblNewAddr.AutoSize = true;
            this.lblNewAddr.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.lblNewAddr.Location = new System.Drawing.Point(312, 22);
            this.lblNewAddr.Name = "lblNewAddr";
            this.lblNewAddr.Size = new System.Drawing.Size(89, 17);
            this.lblNewAddr.TabIndex = 4;
            this.lblNewAddr.Text = "New Address:";
            // 
            // grbTCPIP
            // 
            this.grbTCPIP.BackColor = System.Drawing.Color.Transparent;
            this.grbTCPIP.Controls.Add(this.btnDefault);
            this.grbTCPIP.Controls.Add(this.pnlRemote);
            this.grbTCPIP.Controls.Add(this.btnSetPara);
            this.grbTCPIP.Controls.Add(this.cmbIsServer);
            this.grbTCPIP.Controls.Add(this.btnGetPara);
            this.grbTCPIP.Controls.Add(this.lblIsServer);
            this.grbTCPIP.Controls.Add(this.txtTCPMac);
            this.grbTCPIP.Controls.Add(this.lblTCPMac);
            this.grbTCPIP.Controls.Add(this.txtTCPGateway);
            this.grbTCPIP.Controls.Add(this.lblTCPGateway);
            this.grbTCPIP.Controls.Add(this.txtTCPMask);
            this.grbTCPIP.Controls.Add(this.lblTCPMask);
            this.grbTCPIP.Controls.Add(this.txtTCPPort);
            this.grbTCPIP.Controls.Add(this.lblTCPPort);
            this.grbTCPIP.Controls.Add(this.txtTCPIP);
            this.grbTCPIP.Controls.Add(this.lblTCPIP);
            this.grbTCPIP.Dock = System.Windows.Forms.DockStyle.Top;
            this.grbTCPIP.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.grbTCPIP.Location = new System.Drawing.Point(0, 0);
            this.grbTCPIP.Name = "grbTCPIP";
            this.grbTCPIP.Size = new System.Drawing.Size(990, 142);
            this.grbTCPIP.TabIndex = 0;
            this.grbTCPIP.TabStop = false;
            this.grbTCPIP.Text = "TCPIP Config";
            // 
            // pnlRemote
            // 
            this.pnlRemote.Controls.Add(this.txtRemotePort);
            this.pnlRemote.Controls.Add(this.lblRemotePort);
            this.pnlRemote.Controls.Add(this.txtRemoteIP);
            this.pnlRemote.Controls.Add(this.lblRemoteIP);
            this.pnlRemote.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.pnlRemote.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.pnlRemote.Location = new System.Drawing.Point(3, 103);
            this.pnlRemote.Name = "pnlRemote";
            this.pnlRemote.Size = new System.Drawing.Size(984, 36);
            this.pnlRemote.TabIndex = 9;
            // 
            // txtRemotePort
            // 
            this.txtRemotePort.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.txtRemotePort.Location = new System.Drawing.Point(442, 7);
            this.txtRemotePort.Margin = new System.Windows.Forms.Padding(4);
            this.txtRemotePort.MaxLength = 5;
            this.txtRemotePort.Name = "txtRemotePort";
            this.txtRemotePort.Size = new System.Drawing.Size(160, 23);
            this.txtRemotePort.TabIndex = 1;
            this.txtRemotePort.TabStop = false;
            this.txtRemotePort.Text = "49152";
            this.txtRemotePort.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // lblRemotePort
            // 
            this.lblRemotePort.AutoSize = true;
            this.lblRemotePort.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.lblRemotePort.Location = new System.Drawing.Point(309, 10);
            this.lblRemotePort.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblRemotePort.Name = "lblRemotePort";
            this.lblRemotePort.Size = new System.Drawing.Size(84, 17);
            this.lblRemotePort.TabIndex = 3;
            this.lblRemotePort.Text = "Remote Port:";
            // 
            // txtRemoteIP
            // 
            this.txtRemoteIP.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.txtRemoteIP.Location = new System.Drawing.Point(139, 7);
            this.txtRemoteIP.Margin = new System.Windows.Forms.Padding(4);
            this.txtRemoteIP.MaxLength = 15;
            this.txtRemoteIP.Name = "txtRemoteIP";
            this.txtRemoteIP.Size = new System.Drawing.Size(160, 23);
            this.txtRemoteIP.TabIndex = 0;
            this.txtRemoteIP.TabStop = false;
            this.txtRemoteIP.Text = "192.168.1.100";
            this.txtRemoteIP.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // lblRemoteIP
            // 
            this.lblRemoteIP.AutoSize = true;
            this.lblRemoteIP.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.lblRemoteIP.Location = new System.Drawing.Point(12, 10);
            this.lblRemoteIP.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblRemoteIP.Name = "lblRemoteIP";
            this.lblRemoteIP.Size = new System.Drawing.Size(71, 17);
            this.lblRemoteIP.TabIndex = 2;
            this.lblRemoteIP.Text = "Remote IP:";
            // 
            // cmbIsServer
            // 
            this.cmbIsServer.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbIsServer.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.cmbIsServer.FormattingEnabled = true;
            this.cmbIsServer.Items.AddRange(new object[] {
            "Server",
            "Client"});
            this.cmbIsServer.Location = new System.Drawing.Point(442, 78);
            this.cmbIsServer.Name = "cmbIsServer";
            this.cmbIsServer.Size = new System.Drawing.Size(160, 25);
            this.cmbIsServer.TabIndex = 5;
            this.cmbIsServer.TabStop = false;
            this.cmbIsServer.SelectedIndexChanged += new System.EventHandler(this.cmbIsServer_SelectedIndexChanged);
            // 
            // lblIsServer
            // 
            this.lblIsServer.AutoSize = true;
            this.lblIsServer.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.lblIsServer.Location = new System.Drawing.Point(312, 82);
            this.lblIsServer.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblIsServer.Name = "lblIsServer";
            this.lblIsServer.Size = new System.Drawing.Size(58, 17);
            this.lblIsServer.TabIndex = 15;
            this.lblIsServer.Text = "IsServer:";
            // 
            // txtTCPMac
            // 
            this.txtTCPMac.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.txtTCPMac.Location = new System.Drawing.Point(142, 79);
            this.txtTCPMac.Margin = new System.Windows.Forms.Padding(4);
            this.txtTCPMac.MaxLength = 17;
            this.txtTCPMac.Name = "txtTCPMac";
            this.txtTCPMac.Size = new System.Drawing.Size(160, 23);
            this.txtTCPMac.TabIndex = 4;
            this.txtTCPMac.TabStop = false;
            this.txtTCPMac.Text = "5E-45-A2-6C-30-1E";
            this.txtTCPMac.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // lblTCPMac
            // 
            this.lblTCPMac.AutoSize = true;
            this.lblTCPMac.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.lblTCPMac.Location = new System.Drawing.Point(12, 82);
            this.lblTCPMac.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblTCPMac.Name = "lblTCPMac";
            this.lblTCPMac.Size = new System.Drawing.Size(88, 17);
            this.lblTCPMac.TabIndex = 14;
            this.lblTCPMac.Text = "Mac Address:";
            // 
            // txtTCPGateway
            // 
            this.txtTCPGateway.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.txtTCPGateway.Location = new System.Drawing.Point(442, 49);
            this.txtTCPGateway.Margin = new System.Windows.Forms.Padding(4);
            this.txtTCPGateway.MaxLength = 15;
            this.txtTCPGateway.Name = "txtTCPGateway";
            this.txtTCPGateway.Size = new System.Drawing.Size(160, 23);
            this.txtTCPGateway.TabIndex = 3;
            this.txtTCPGateway.TabStop = false;
            this.txtTCPGateway.Text = "192.168.1.1";
            this.txtTCPGateway.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // lblTCPGateway
            // 
            this.lblTCPGateway.AutoSize = true;
            this.lblTCPGateway.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.lblTCPGateway.Location = new System.Drawing.Point(312, 52);
            this.lblTCPGateway.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblTCPGateway.Name = "lblTCPGateway";
            this.lblTCPGateway.Size = new System.Drawing.Size(63, 17);
            this.lblTCPGateway.TabIndex = 13;
            this.lblTCPGateway.Text = "GateWay:";
            // 
            // txtTCPMask
            // 
            this.txtTCPMask.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.txtTCPMask.Location = new System.Drawing.Point(142, 49);
            this.txtTCPMask.Margin = new System.Windows.Forms.Padding(4);
            this.txtTCPMask.MaxLength = 15;
            this.txtTCPMask.Name = "txtTCPMask";
            this.txtTCPMask.Size = new System.Drawing.Size(160, 23);
            this.txtTCPMask.TabIndex = 2;
            this.txtTCPMask.TabStop = false;
            this.txtTCPMask.Text = "255.255.255.0";
            this.txtTCPMask.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // lblTCPMask
            // 
            this.lblTCPMask.AutoSize = true;
            this.lblTCPMask.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.lblTCPMask.Location = new System.Drawing.Point(12, 52);
            this.lblTCPMask.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblTCPMask.Name = "lblTCPMask";
            this.lblTCPMask.Size = new System.Drawing.Size(87, 17);
            this.lblTCPMask.TabIndex = 12;
            this.lblTCPMask.Text = "Subnet Mask:";
            // 
            // txtTCPPort
            // 
            this.txtTCPPort.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.txtTCPPort.Location = new System.Drawing.Point(442, 19);
            this.txtTCPPort.Margin = new System.Windows.Forms.Padding(4);
            this.txtTCPPort.MaxLength = 5;
            this.txtTCPPort.Name = "txtTCPPort";
            this.txtTCPPort.Size = new System.Drawing.Size(160, 23);
            this.txtTCPPort.TabIndex = 1;
            this.txtTCPPort.TabStop = false;
            this.txtTCPPort.Text = "49152";
            this.txtTCPPort.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // lblTCPPort
            // 
            this.lblTCPPort.AutoSize = true;
            this.lblTCPPort.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.lblTCPPort.Location = new System.Drawing.Point(312, 22);
            this.lblTCPPort.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblTCPPort.Name = "lblTCPPort";
            this.lblTCPPort.Size = new System.Drawing.Size(50, 17);
            this.lblTCPPort.TabIndex = 11;
            this.lblTCPPort.Text = "IP Port:";
            // 
            // txtTCPIP
            // 
            this.txtTCPIP.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.txtTCPIP.Location = new System.Drawing.Point(142, 19);
            this.txtTCPIP.Margin = new System.Windows.Forms.Padding(4);
            this.txtTCPIP.MaxLength = 15;
            this.txtTCPIP.Name = "txtTCPIP";
            this.txtTCPIP.Size = new System.Drawing.Size(160, 23);
            this.txtTCPIP.TabIndex = 0;
            this.txtTCPIP.TabStop = false;
            this.txtTCPIP.Text = "192.168.1.115";
            this.txtTCPIP.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // lblTCPIP
            // 
            this.lblTCPIP.AutoSize = true;
            this.lblTCPIP.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.lblTCPIP.Location = new System.Drawing.Point(12, 22);
            this.lblTCPIP.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblTCPIP.Name = "lblTCPIP";
            this.lblTCPIP.Size = new System.Drawing.Size(74, 17);
            this.lblTCPIP.TabIndex = 10;
            this.lblTCPIP.Text = "IP Address:";
            // 
            // tmrClock
            // 
            this.tmrClock.Enabled = true;
            this.tmrClock.Interval = 500;
            this.tmrClock.Tick += new System.EventHandler(this.tmrClock_Tick);
            // 
            // ucPSeniorSettings
            // 
            this.Controls.Add(this.grbSoft);
            this.Controls.Add(this.grbTime);
            this.Controls.Add(this.grbSYRIS);
            this.Controls.Add(this.grbAddress);
            this.Controls.Add(this.grbTCPIP);
            this.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.Name = "ucPSeniorSettings";
            this.Size = new System.Drawing.Size(990, 438);
            this.TitleVisable = false;
            this.Controls.SetChildIndex(this.grbTCPIP, 0);
            this.Controls.SetChildIndex(this.grbAddress, 0);
            this.Controls.SetChildIndex(this.grbSYRIS, 0);
            this.Controls.SetChildIndex(this.grbTime, 0);
            this.Controls.SetChildIndex(this.grbSoft, 0);
            this.grbTime.ResumeLayout(false);
            this.grbTime.PerformLayout();
            this.grbSoft.ResumeLayout(false);
            this.grbSYRIS.ResumeLayout(false);
            this.grbSYRIS.PerformLayout();
            this.grbAddress.ResumeLayout(false);
            this.grbAddress.PerformLayout();
            this.grbTCPIP.ResumeLayout(false);
            this.grbTCPIP.PerformLayout();
            this.pnlRemote.ResumeLayout(false);
            this.pnlRemote.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnDefault;
        private System.Windows.Forms.Button btnSetPara;
        private System.Windows.Forms.Button btnGetPara;
        private System.Windows.Forms.GroupBox grbTCPIP;
        private System.Windows.Forms.TextBox txtTCPMac;
        private System.Windows.Forms.Label lblTCPMac;
        private System.Windows.Forms.TextBox txtTCPGateway;
        private System.Windows.Forms.Label lblTCPGateway;
        private System.Windows.Forms.TextBox txtTCPMask;
        private System.Windows.Forms.Label lblTCPMask;
        private System.Windows.Forms.TextBox txtTCPPort;
        private System.Windows.Forms.Label lblTCPPort;
        private System.Windows.Forms.TextBox txtTCPIP;
        private System.Windows.Forms.Label lblTCPIP;
        private System.Windows.Forms.GroupBox grbTime;
        private System.Windows.Forms.GroupBox grbSoft;
        private System.Windows.Forms.Button btnReset;
        private System.Windows.Forms.Button btnIO1Open;
        private System.Windows.Forms.Button btnIO1Close;
        private System.Windows.Forms.Button btnIO2Open;
        private System.Windows.Forms.Button btnIO2Close;
        private System.Windows.Forms.GroupBox grbSYRIS;
        private System.Windows.Forms.Button btnInitSyris;
        private System.Windows.Forms.ComboBox cmbSyrisID;
        private System.Windows.Forms.Label lblSyrisID;
        private System.Windows.Forms.TextBox txtSyrisSN;
        private System.Windows.Forms.Label lblSyrisSN;
        private System.Windows.Forms.GroupBox grbAddress;
        private ADSDK.Bases.Components.FormatTextBox utxtNewAddr;
        private System.Windows.Forms.Button btnAddress;
        private System.Windows.Forms.Label lblOldAddr;
        private System.Windows.Forms.TextBox txtOldAddr;
        private System.Windows.Forms.Label lblNewAddr;
        private System.Windows.Forms.Button btnGetTime;
        private System.Windows.Forms.Button btnSetTime;
        private System.Windows.Forms.TextBox txtReaderTime;
        private System.Windows.Forms.Label lblReaderTime;
        private System.Windows.Forms.TextBox txtNowTime;
        private System.Windows.Forms.Label lblNowTime;
        private System.Windows.Forms.ComboBox cmbIsServer;
        private System.Windows.Forms.Label lblIsServer;
        private System.Windows.Forms.Panel pnlRemote;
        private System.Windows.Forms.TextBox txtRemotePort;
        private System.Windows.Forms.Label lblRemotePort;
        private System.Windows.Forms.TextBox txtRemoteIP;
        private System.Windows.Forms.Label lblRemoteIP;
        private System.Windows.Forms.Timer tmrClock;
    }
}
