namespace Aosid
{
    partial class frmSioConfig
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(frmSioConfig));
            this.pnlBody = new System.Windows.Forms.Panel();
            this.pnlCommMode = new System.Windows.Forms.Panel();
            this.pnlTCPIP = new System.Windows.Forms.Panel();
            this.grbRemotePort = new System.Windows.Forms.GroupBox();
            this.txtRemotePort = new System.Windows.Forms.TextBox();
            this.grbRemoteIP = new System.Windows.Forms.GroupBox();
            this.txtRemoteIP = new System.Windows.Forms.TextBox();
            this.pnlRS232 = new System.Windows.Forms.Panel();
            this.grbBaudRate = new System.Windows.Forms.GroupBox();
            this.cmbBaudRate = new System.Windows.Forms.ComboBox();
            this.grbPortName = new System.Windows.Forms.GroupBox();
            this.cmbPortName = new System.Windows.Forms.ComboBox();
            this.btnOK = new System.Windows.Forms.Button();
            this.pnlBody.SuspendLayout();
            this.pnlCommMode.SuspendLayout();
            this.pnlTCPIP.SuspendLayout();
            this.grbRemotePort.SuspendLayout();
            this.grbRemoteIP.SuspendLayout();
            this.pnlRS232.SuspendLayout();
            this.grbBaudRate.SuspendLayout();
            this.grbPortName.SuspendLayout();
            this.SuspendLayout();
            // 
            // pnlTitle
            // 
            this.pnlTitle.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.pnlTitle.Size = new System.Drawing.Size(222, 28);
            // 
            // pnlBody
            // 
            this.pnlBody.AutoSize = true;
            this.pnlBody.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pnlBody.Controls.Add(this.btnOK);
            this.pnlBody.Controls.Add(this.pnlCommMode);
            this.pnlBody.Dock = System.Windows.Forms.DockStyle.Top;
            this.pnlBody.Location = new System.Drawing.Point(0, 28);
            this.pnlBody.Name = "pnlBody";
            this.pnlBody.Padding = new System.Windows.Forms.Padding(5);
            this.pnlBody.Size = new System.Drawing.Size(222, 261);
            this.pnlBody.TabIndex = 0;
            // 
            // pnlCommMode
            // 
            this.pnlCommMode.AutoSize = true;
            this.pnlCommMode.Controls.Add(this.pnlTCPIP);
            this.pnlCommMode.Controls.Add(this.pnlRS232);
            this.pnlCommMode.Dock = System.Windows.Forms.DockStyle.Top;
            this.pnlCommMode.Location = new System.Drawing.Point(5, 5);
            this.pnlCommMode.Name = "pnlCommMode";
            this.pnlCommMode.Size = new System.Drawing.Size(210, 212);
            this.pnlCommMode.TabIndex = 0;
            this.pnlCommMode.Resize += new System.EventHandler(this.pnlCommMode_Resize);
            // 
            // pnlTCPIP
            // 
            this.pnlTCPIP.AutoSize = true;
            this.pnlTCPIP.Controls.Add(this.grbRemotePort);
            this.pnlTCPIP.Controls.Add(this.grbRemoteIP);
            this.pnlTCPIP.Dock = System.Windows.Forms.DockStyle.Top;
            this.pnlTCPIP.Location = new System.Drawing.Point(0, 108);
            this.pnlTCPIP.Name = "pnlTCPIP";
            this.pnlTCPIP.Padding = new System.Windows.Forms.Padding(3);
            this.pnlTCPIP.Size = new System.Drawing.Size(210, 104);
            this.pnlTCPIP.TabIndex = 2;
            this.pnlTCPIP.Visible = false;
            // 
            // grbRemotePort
            // 
            this.grbRemotePort.AutoSize = true;
            this.grbRemotePort.Controls.Add(this.txtRemotePort);
            this.grbRemotePort.Dock = System.Windows.Forms.DockStyle.Top;
            this.grbRemotePort.Location = new System.Drawing.Point(3, 52);
            this.grbRemotePort.MinimumSize = new System.Drawing.Size(120, 44);
            this.grbRemotePort.Name = "grbRemotePort";
            this.grbRemotePort.Padding = new System.Windows.Forms.Padding(5);
            this.grbRemotePort.Size = new System.Drawing.Size(204, 49);
            this.grbRemotePort.TabIndex = 1;
            this.grbRemotePort.TabStop = false;
            this.grbRemotePort.Text = "Remote Port";
            // 
            // txtRemotePort
            // 
            this.txtRemotePort.Dock = System.Windows.Forms.DockStyle.Top;
            this.txtRemotePort.Location = new System.Drawing.Point(5, 21);
            this.txtRemotePort.MaxLength = 5;
            this.txtRemotePort.Name = "txtRemotePort";
            this.txtRemotePort.Size = new System.Drawing.Size(194, 23);
            this.txtRemotePort.TabIndex = 3;
            this.txtRemotePort.Text = "49152";
            this.txtRemotePort.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // grbRemoteIP
            // 
            this.grbRemoteIP.AutoSize = true;
            this.grbRemoteIP.Controls.Add(this.txtRemoteIP);
            this.grbRemoteIP.Dock = System.Windows.Forms.DockStyle.Top;
            this.grbRemoteIP.Location = new System.Drawing.Point(3, 3);
            this.grbRemoteIP.MinimumSize = new System.Drawing.Size(120, 44);
            this.grbRemoteIP.Name = "grbRemoteIP";
            this.grbRemoteIP.Padding = new System.Windows.Forms.Padding(5);
            this.grbRemoteIP.Size = new System.Drawing.Size(204, 49);
            this.grbRemoteIP.TabIndex = 0;
            this.grbRemoteIP.TabStop = false;
            this.grbRemoteIP.Text = "Remote IP";
            // 
            // txtRemoteIP
            // 
            this.txtRemoteIP.Dock = System.Windows.Forms.DockStyle.Top;
            this.txtRemoteIP.Location = new System.Drawing.Point(5, 21);
            this.txtRemoteIP.MaxLength = 18;
            this.txtRemoteIP.Name = "txtRemoteIP";
            this.txtRemoteIP.Size = new System.Drawing.Size(194, 23);
            this.txtRemoteIP.TabIndex = 2;
            this.txtRemoteIP.Text = "192.168.1.115";
            this.txtRemoteIP.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // pnlRS232
            // 
            this.pnlRS232.AutoSize = true;
            this.pnlRS232.Controls.Add(this.grbBaudRate);
            this.pnlRS232.Controls.Add(this.grbPortName);
            this.pnlRS232.Dock = System.Windows.Forms.DockStyle.Top;
            this.pnlRS232.Location = new System.Drawing.Point(0, 0);
            this.pnlRS232.Name = "pnlRS232";
            this.pnlRS232.Padding = new System.Windows.Forms.Padding(3);
            this.pnlRS232.Size = new System.Drawing.Size(210, 108);
            this.pnlRS232.TabIndex = 1;
            // 
            // grbBaudRate
            // 
            this.grbBaudRate.AutoSize = true;
            this.grbBaudRate.Controls.Add(this.cmbBaudRate);
            this.grbBaudRate.Dock = System.Windows.Forms.DockStyle.Top;
            this.grbBaudRate.Location = new System.Drawing.Point(3, 54);
            this.grbBaudRate.MinimumSize = new System.Drawing.Size(120, 44);
            this.grbBaudRate.Name = "grbBaudRate";
            this.grbBaudRate.Padding = new System.Windows.Forms.Padding(5);
            this.grbBaudRate.Size = new System.Drawing.Size(204, 51);
            this.grbBaudRate.TabIndex = 1;
            this.grbBaudRate.TabStop = false;
            this.grbBaudRate.Text = "BaudRate";
            // 
            // cmbBaudRate
            // 
            this.cmbBaudRate.Dock = System.Windows.Forms.DockStyle.Top;
            this.cmbBaudRate.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbBaudRate.FormattingEnabled = true;
            this.cmbBaudRate.Items.AddRange(new object[] {
            "1200",
            "9600",
            "14400",
            "19200",
            "38400",
            "56000",
            "57600",
            "115200"});
            this.cmbBaudRate.Location = new System.Drawing.Point(5, 21);
            this.cmbBaudRate.Name = "cmbBaudRate";
            this.cmbBaudRate.Size = new System.Drawing.Size(194, 25);
            this.cmbBaudRate.TabIndex = 1;
            // 
            // grbPortName
            // 
            this.grbPortName.AutoSize = true;
            this.grbPortName.Controls.Add(this.cmbPortName);
            this.grbPortName.Dock = System.Windows.Forms.DockStyle.Top;
            this.grbPortName.Location = new System.Drawing.Point(3, 3);
            this.grbPortName.MinimumSize = new System.Drawing.Size(120, 44);
            this.grbPortName.Name = "grbPortName";
            this.grbPortName.Padding = new System.Windows.Forms.Padding(5);
            this.grbPortName.Size = new System.Drawing.Size(204, 51);
            this.grbPortName.TabIndex = 0;
            this.grbPortName.TabStop = false;
            this.grbPortName.Text = "PortName";
            // 
            // cmbPortName
            // 
            this.cmbPortName.Dock = System.Windows.Forms.DockStyle.Top;
            this.cmbPortName.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbPortName.FormattingEnabled = true;
            this.cmbPortName.Location = new System.Drawing.Point(5, 21);
            this.cmbPortName.Name = "cmbPortName";
            this.cmbPortName.Size = new System.Drawing.Size(194, 25);
            this.cmbPortName.TabIndex = 0;
            // 
            // btnOK
            // 
            this.btnOK.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.btnOK.Location = new System.Drawing.Point(54, 223);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(108, 28);
            this.btnOK.TabIndex = 8;
            this.btnOK.Text = "OK";
            this.btnOK.UseVisualStyleBackColor = true;
            this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
            // 
            // frmSioConfig
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(222, 340);
            this.Controls.Add(this.pnlBody);
            this.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "frmSioConfig";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "7";
            this.TitleVisable = true;
            this.Controls.SetChildIndex(this.pnlTitle, 0);
            this.Controls.SetChildIndex(this.pnlBody, 0);
            this.pnlBody.ResumeLayout(false);
            this.pnlBody.PerformLayout();
            this.pnlCommMode.ResumeLayout(false);
            this.pnlCommMode.PerformLayout();
            this.pnlTCPIP.ResumeLayout(false);
            this.pnlTCPIP.PerformLayout();
            this.grbRemotePort.ResumeLayout(false);
            this.grbRemotePort.PerformLayout();
            this.grbRemoteIP.ResumeLayout(false);
            this.grbRemoteIP.PerformLayout();
            this.pnlRS232.ResumeLayout(false);
            this.pnlRS232.PerformLayout();
            this.grbBaudRate.ResumeLayout(false);
            this.grbPortName.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Panel pnlBody;
        private System.Windows.Forms.Panel pnlCommMode;
        private System.Windows.Forms.Panel pnlTCPIP;
        private System.Windows.Forms.GroupBox grbRemotePort;
        private System.Windows.Forms.TextBox txtRemotePort;
        private System.Windows.Forms.GroupBox grbRemoteIP;
        private System.Windows.Forms.TextBox txtRemoteIP;
        private System.Windows.Forms.Panel pnlRS232;
        private System.Windows.Forms.GroupBox grbBaudRate;
        private System.Windows.Forms.ComboBox cmbBaudRate;
        private System.Windows.Forms.GroupBox grbPortName;
        private System.Windows.Forms.ComboBox cmbPortName;
        private System.Windows.Forms.Button btnOK;
    }
}