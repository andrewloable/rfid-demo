namespace Aosid
{
    partial class ucPReadDemo
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
            this.components = new System.ComponentModel.Container();
            this.pnlBtnDemo = new System.Windows.Forms.Panel();
            this.btnExport = new System.Windows.Forms.Button();
            this.btnUpLoad = new System.Windows.Forms.Button();
            this.btnClear = new System.Windows.Forms.Button();
            this.btnStart = new System.Windows.Forms.Button();
            this.tmrClock = new System.Windows.Forms.Timer(this.components);
            this.cdgvShow = new ADSDK.Device.Reader.CardsDataGridView();
            this.pnlBtnDemo.SuspendLayout();
            this.SuspendLayout();
            // 
            // pnlBtnDemo
            // 
            this.pnlBtnDemo.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pnlBtnDemo.Controls.Add(this.btnExport);
            this.pnlBtnDemo.Controls.Add(this.btnUpLoad);
            this.pnlBtnDemo.Controls.Add(this.btnClear);
            this.pnlBtnDemo.Controls.Add(this.btnStart);
            this.pnlBtnDemo.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.pnlBtnDemo.Location = new System.Drawing.Point(0, 445);
            this.pnlBtnDemo.Margin = new System.Windows.Forms.Padding(3, 5, 3, 5);
            this.pnlBtnDemo.Name = "pnlBtnDemo";
            this.pnlBtnDemo.Size = new System.Drawing.Size(990, 38);
            this.pnlBtnDemo.TabIndex = 10;
            // 
            // btnExport
            // 
            this.btnExport.Dock = System.Windows.Forms.DockStyle.Left;
            this.btnExport.Location = new System.Drawing.Point(540, 0);
            this.btnExport.Margin = new System.Windows.Forms.Padding(3, 5, 3, 5);
            this.btnExport.Name = "btnExport";
            this.btnExport.Size = new System.Drawing.Size(180, 36);
            this.btnExport.TabIndex = 8;
            this.btnExport.TabStop = false;
            this.btnExport.Text = "Export";
            this.btnExport.UseVisualStyleBackColor = true;
            this.btnExport.Click += new System.EventHandler(this.btnExport_Click);
            // 
            // btnUpLoad
            // 
            this.btnUpLoad.Dock = System.Windows.Forms.DockStyle.Left;
            this.btnUpLoad.Location = new System.Drawing.Point(360, 0);
            this.btnUpLoad.Margin = new System.Windows.Forms.Padding(3, 5, 3, 5);
            this.btnUpLoad.Name = "btnUpLoad";
            this.btnUpLoad.Size = new System.Drawing.Size(180, 36);
            this.btnUpLoad.TabIndex = 7;
            this.btnUpLoad.TabStop = false;
            this.btnUpLoad.Text = "Upload";
            this.btnUpLoad.UseVisualStyleBackColor = true;
            this.btnUpLoad.Visible = false;
            this.btnUpLoad.Click += new System.EventHandler(this.btnUpLoad_Click);
            // 
            // btnClear
            // 
            this.btnClear.Dock = System.Windows.Forms.DockStyle.Left;
            this.btnClear.Location = new System.Drawing.Point(180, 0);
            this.btnClear.Margin = new System.Windows.Forms.Padding(3, 5, 3, 5);
            this.btnClear.Name = "btnClear";
            this.btnClear.Size = new System.Drawing.Size(180, 36);
            this.btnClear.TabIndex = 6;
            this.btnClear.TabStop = false;
            this.btnClear.Text = "Cl&ear";
            this.btnClear.UseVisualStyleBackColor = true;
            this.btnClear.Click += new System.EventHandler(this.btnClear_Click);
            // 
            // btnStart
            // 
            this.btnStart.Dock = System.Windows.Forms.DockStyle.Left;
            this.btnStart.Location = new System.Drawing.Point(0, 0);
            this.btnStart.Margin = new System.Windows.Forms.Padding(3, 5, 3, 5);
            this.btnStart.Name = "btnStart";
            this.btnStart.Size = new System.Drawing.Size(180, 36);
            this.btnStart.TabIndex = 4;
            this.btnStart.TabStop = false;
            this.btnStart.Text = "&Start Read";
            this.btnStart.UseVisualStyleBackColor = true;
            this.btnStart.Click += new System.EventHandler(this.btnStart_Click);
            // 
            // tmrClock
            // 
            this.tmrClock.Enabled = true;
            this.tmrClock.Interval = 200;
            this.tmrClock.Tick += new System.EventHandler(this.tmrClock_Tick);
            // 
            // cdgvShow
            // 
            this.cdgvShow.BackColor = System.Drawing.Color.AliceBlue;
            this.cdgvShow.Dock = System.Windows.Forms.DockStyle.Fill;
            this.cdgvShow.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.cdgvShow.Location = new System.Drawing.Point(0, 0);
            this.cdgvShow.Name = "cdgvShow";
            this.cdgvShow.Size = new System.Drawing.Size(990, 445);
            this.cdgvShow.TabIndex = 11;
            this.cdgvShow.TabStop = false;
            this.cdgvShow.TitleImage = null;
            this.cdgvShow.TitleVisable = false;
            // 
            // ucPReadDemo
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Inherit;
            this.Controls.Add(this.cdgvShow);
            this.Controls.Add(this.pnlBtnDemo);
            this.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.Name = "ucPReadDemo";
            this.Size = new System.Drawing.Size(990, 483);
            this.TitleVisable = false;
            this.Enter += new System.EventHandler(this.ucReadDemo_Enter);
            this.Leave += new System.EventHandler(this.ucReadDemo_Leave);
            this.Controls.SetChildIndex(this.pnlBtnDemo, 0);
            this.Controls.SetChildIndex(this.cdgvShow, 0);
            this.pnlBtnDemo.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel pnlBtnDemo;
        private System.Windows.Forms.Button btnExport;
        private System.Windows.Forms.Button btnUpLoad;
        private System.Windows.Forms.Button btnClear;
        private ADSDK.Device.Reader.CardsDataGridView cdgvShow;
        private System.Windows.Forms.Button btnStart;
        private System.Windows.Forms.Timer tmrClock;
    }
}
