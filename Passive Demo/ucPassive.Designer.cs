namespace Aosid
{
    partial class ucPassive
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

        #region 组件设计器生成的代码

        /// <summary> 
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.tabPassive = new System.Windows.Forms.TabControl();
            this.tabReadDemo = new System.Windows.Forms.TabPage();
            this.ucPReadDemo1 = new Aosid.ucPReadDemo();
            this.tabBaseSettings = new System.Windows.Forms.TabPage();
            this.ucPBaseSettings1 = new Aosid.ucPBaseSettings();
            this.tabSeniorSettings = new System.Windows.Forms.TabPage();
            this.ucPSeniorSettings1 = new Aosid.ucPSeniorSettings();
            this.tabWriteISO = new System.Windows.Forms.TabPage();
            this.ucPWriteISO1 = new Aosid.ucPWriteISO();
            this.tabWriteEPC = new System.Windows.Forms.TabPage();
            this.ucPWriteEPC1 = new Aosid.ucPWriteEPC();
            this.tabWifiSettings = new System.Windows.Forms.TabPage();
            this.ucPWifiSettings1 = new Aosid.ucPWifiSettings();
            this.tabPassive.SuspendLayout();
            this.tabReadDemo.SuspendLayout();
            this.tabBaseSettings.SuspendLayout();
            this.tabSeniorSettings.SuspendLayout();
            this.tabWriteISO.SuspendLayout();
            this.tabWriteEPC.SuspendLayout();
            this.tabWifiSettings.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabPassive
            // 
            this.tabPassive.Controls.Add(this.tabReadDemo);
            this.tabPassive.Controls.Add(this.tabBaseSettings);
            this.tabPassive.Controls.Add(this.tabSeniorSettings);
            this.tabPassive.Controls.Add(this.tabWriteISO);
            this.tabPassive.Controls.Add(this.tabWriteEPC);
            this.tabPassive.Controls.Add(this.tabWifiSettings);
            this.tabPassive.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabPassive.Location = new System.Drawing.Point(0, 0);
            this.tabPassive.Name = "tabPassive";
            this.tabPassive.SelectedIndex = 0;
            this.tabPassive.Size = new System.Drawing.Size(958, 513);
            this.tabPassive.TabIndex = 1;
            // 
            // tabReadDemo
            // 
            this.tabReadDemo.Controls.Add(this.ucPReadDemo1);
            this.tabReadDemo.Location = new System.Drawing.Point(4, 26);
            this.tabReadDemo.Name = "tabReadDemo";
            this.tabReadDemo.Padding = new System.Windows.Forms.Padding(3);
            this.tabReadDemo.Size = new System.Drawing.Size(950, 483);
            this.tabReadDemo.TabIndex = 1;
            this.tabReadDemo.Text = "Read Demo";
            this.tabReadDemo.UseVisualStyleBackColor = true;
            // 
            // ucPReadDemo1
            // 
            this.ucPReadDemo1.BackColor = System.Drawing.Color.AliceBlue;
            this.ucPReadDemo1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ucPReadDemo1.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.ucPReadDemo1.ImeMode = System.Windows.Forms.ImeMode.On;
            this.ucPReadDemo1.Location = new System.Drawing.Point(3, 3);
            this.ucPReadDemo1.Name = "ucPReadDemo1";
            this.ucPReadDemo1.Size = new System.Drawing.Size(944, 477);
            this.ucPReadDemo1.TabIndex = 0;
            this.ucPReadDemo1.TitleImage = null;
            this.ucPReadDemo1.TitleVisable = false;
            // 
            // tabBaseSettings
            // 
            this.tabBaseSettings.Controls.Add(this.ucPBaseSettings1);
            this.tabBaseSettings.Location = new System.Drawing.Point(4, 22);
            this.tabBaseSettings.Name = "tabBaseSettings";
            this.tabBaseSettings.Padding = new System.Windows.Forms.Padding(3);
            this.tabBaseSettings.Size = new System.Drawing.Size(192, 74);
            this.tabBaseSettings.TabIndex = 0;
            this.tabBaseSettings.Text = "Base Parameters";
            this.tabBaseSettings.UseVisualStyleBackColor = true;
            // 
            // ucPBaseSettings1
            // 
            this.ucPBaseSettings1.BackColor = System.Drawing.Color.AliceBlue;
            this.ucPBaseSettings1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ucPBaseSettings1.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.ucPBaseSettings1.ImeMode = System.Windows.Forms.ImeMode.On;
            this.ucPBaseSettings1.Location = new System.Drawing.Point(3, 3);
            this.ucPBaseSettings1.Name = "ucPBaseSettings1";
            this.ucPBaseSettings1.Size = new System.Drawing.Size(186, 68);
            this.ucPBaseSettings1.TabIndex = 0;
            this.ucPBaseSettings1.TitleImage = null;
            this.ucPBaseSettings1.TitleVisable = false;
            // 
            // tabSeniorSettings
            // 
            this.tabSeniorSettings.Controls.Add(this.ucPSeniorSettings1);
            this.tabSeniorSettings.Location = new System.Drawing.Point(4, 22);
            this.tabSeniorSettings.Name = "tabSeniorSettings";
            this.tabSeniorSettings.Size = new System.Drawing.Size(192, 74);
            this.tabSeniorSettings.TabIndex = 4;
            this.tabSeniorSettings.Text = "Senior Parameters";
            this.tabSeniorSettings.UseVisualStyleBackColor = true;
            // 
            // ucPSeniorSettings1
            // 
            this.ucPSeniorSettings1.BackColor = System.Drawing.Color.AliceBlue;
            this.ucPSeniorSettings1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ucPSeniorSettings1.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.ucPSeniorSettings1.ImeMode = System.Windows.Forms.ImeMode.On;
            this.ucPSeniorSettings1.Location = new System.Drawing.Point(0, 0);
            this.ucPSeniorSettings1.Name = "ucPSeniorSettings1";
            this.ucPSeniorSettings1.Size = new System.Drawing.Size(192, 74);
            this.ucPSeniorSettings1.TabIndex = 0;
            this.ucPSeniorSettings1.TitleImage = null;
            this.ucPSeniorSettings1.TitleVisable = false;
            // 
            // tabWriteISO
            // 
            this.tabWriteISO.Controls.Add(this.ucPWriteISO1);
            this.tabWriteISO.Location = new System.Drawing.Point(4, 22);
            this.tabWriteISO.Name = "tabWriteISO";
            this.tabWriteISO.Size = new System.Drawing.Size(192, 74);
            this.tabWriteISO.TabIndex = 2;
            this.tabWriteISO.Text = "ISO18000-6B";
            this.tabWriteISO.UseVisualStyleBackColor = true;
            // 
            // ucPWriteISO1
            // 
            this.ucPWriteISO1.BackColor = System.Drawing.Color.AliceBlue;
            this.ucPWriteISO1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ucPWriteISO1.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.ucPWriteISO1.ImeMode = System.Windows.Forms.ImeMode.On;
            this.ucPWriteISO1.Location = new System.Drawing.Point(0, 0);
            this.ucPWriteISO1.Name = "ucPWriteISO1";
            this.ucPWriteISO1.Size = new System.Drawing.Size(192, 74);
            this.ucPWriteISO1.TabIndex = 0;
            this.ucPWriteISO1.TitleImage = null;
            this.ucPWriteISO1.TitleVisable = false;
            // 
            // tabWriteEPC
            // 
            this.tabWriteEPC.Controls.Add(this.ucPWriteEPC1);
            this.tabWriteEPC.Location = new System.Drawing.Point(4, 22);
            this.tabWriteEPC.Name = "tabWriteEPC";
            this.tabWriteEPC.Size = new System.Drawing.Size(192, 74);
            this.tabWriteEPC.TabIndex = 3;
            this.tabWriteEPC.Text = "EPC(GEN 2)";
            this.tabWriteEPC.UseVisualStyleBackColor = true;
            // 
            // ucPWriteEPC1
            // 
            this.ucPWriteEPC1.BackColor = System.Drawing.Color.AliceBlue;
            this.ucPWriteEPC1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ucPWriteEPC1.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.ucPWriteEPC1.ImeMode = System.Windows.Forms.ImeMode.On;
            this.ucPWriteEPC1.Location = new System.Drawing.Point(0, 0);
            this.ucPWriteEPC1.Name = "ucPWriteEPC1";
            this.ucPWriteEPC1.Size = new System.Drawing.Size(192, 74);
            this.ucPWriteEPC1.TabIndex = 0;
            this.ucPWriteEPC1.TitleImage = null;
            this.ucPWriteEPC1.TitleVisable = false;
            // 
            // tabWifiSettings
            // 
            this.tabWifiSettings.Controls.Add(this.ucPWifiSettings1);
            this.tabWifiSettings.Location = new System.Drawing.Point(4, 26);
            this.tabWifiSettings.Name = "tabWifiSettings";
            this.tabWifiSettings.Size = new System.Drawing.Size(950, 483);
            this.tabWifiSettings.TabIndex = 5;
            this.tabWifiSettings.Text = "WIFI SETTINGS";
            this.tabWifiSettings.UseVisualStyleBackColor = true;
            // 
            // ucPWifiSettings1
            // 
            this.ucPWifiSettings1.BackColor = System.Drawing.Color.AliceBlue;
            this.ucPWifiSettings1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ucPWifiSettings1.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.ucPWifiSettings1.ImeMode = System.Windows.Forms.ImeMode.On;
            this.ucPWifiSettings1.Location = new System.Drawing.Point(0, 0);
            this.ucPWifiSettings1.Name = "ucPWifiSettings1";
            this.ucPWifiSettings1.Size = new System.Drawing.Size(950, 483);
            this.ucPWifiSettings1.TabIndex = 0;
            this.ucPWifiSettings1.TitleImage = null;
            this.ucPWifiSettings1.TitleVisable = false;
            // 
            // ucPassive
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Inherit;
            this.Controls.Add(this.tabPassive);
            this.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.Name = "ucPassive";
            this.Size = new System.Drawing.Size(958, 513);
            this.TitleVisable = false;
            this.Controls.SetChildIndex(this.tabPassive, 0);
            this.tabPassive.ResumeLayout(false);
            this.tabReadDemo.ResumeLayout(false);
            this.tabBaseSettings.ResumeLayout(false);
            this.tabSeniorSettings.ResumeLayout(false);
            this.tabWriteISO.ResumeLayout(false);
            this.tabWriteEPC.ResumeLayout(false);
            this.tabWifiSettings.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabPassive;
        private System.Windows.Forms.TabPage tabBaseSettings;
        private ucPBaseSettings ucPBaseSettings1;
        private System.Windows.Forms.TabPage tabSeniorSettings;
        private ucPSeniorSettings ucPSeniorSettings1;
        private System.Windows.Forms.TabPage tabWriteISO;
        private ucPWriteISO ucPWriteISO1;
        private System.Windows.Forms.TabPage tabWriteEPC;
        private ucPWriteEPC ucPWriteEPC1;
        private System.Windows.Forms.TabPage tabReadDemo;
        private ucPReadDemo ucPReadDemo1;
        private System.Windows.Forms.TabPage tabWifiSettings;
        private ucPWifiSettings ucPWifiSettings1;
    }
}
