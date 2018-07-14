namespace Aosid
{
    partial class ucPWriteISO
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
            this.grbIdentify = new System.Windows.Forms.GroupBox();
            this.btnIdentify = new System.Windows.Forms.Button();
            this.utxtCard = new ADSDK.Bases.Components.FormatTextBox();
            this.lblCard = new System.Windows.Forms.Label();
            this.grbWrite = new System.Windows.Forms.GroupBox();
            this.btnWrite = new System.Windows.Forms.Button();
            this.ltxtWriteAddress = new ADSDK.Bases.Components.LimitTextBox();
            this.ltxtWriteLength = new ADSDK.Bases.Components.LimitTextBox();
            this.utxtWriteData = new ADSDK.Bases.Components.FormatTextBox();
            this.lblWriteMark = new System.Windows.Forms.Label();
            this.lblWriteAddress = new System.Windows.Forms.Label();
            this.lblWriteLength = new System.Windows.Forms.Label();
            this.lblWriteData = new System.Windows.Forms.Label();
            this.grbRead = new System.Windows.Forms.GroupBox();
            this.utxtReadData = new ADSDK.Bases.Components.FormatTextBox();
            this.btnRead = new System.Windows.Forms.Button();
            this.ltxtReadAddress = new ADSDK.Bases.Components.LimitTextBox();
            this.ltxtReadLength = new ADSDK.Bases.Components.LimitTextBox();
            this.lblReadMark = new System.Windows.Forms.Label();
            this.lblReadAddress = new System.Windows.Forms.Label();
            this.lblReadData = new System.Windows.Forms.Label();
            this.lblReadLength = new System.Windows.Forms.Label();
            this.grbIdentify.SuspendLayout();
            this.grbWrite.SuspendLayout();
            this.grbRead.SuspendLayout();
            this.SuspendLayout();
            // 
            // grbIdentify
            // 
            this.grbIdentify.Controls.Add(this.btnIdentify);
            this.grbIdentify.Controls.Add(this.utxtCard);
            this.grbIdentify.Controls.Add(this.lblCard);
            this.grbIdentify.Dock = System.Windows.Forms.DockStyle.Top;
            this.grbIdentify.Location = new System.Drawing.Point(0, 0);
            this.grbIdentify.Name = "grbIdentify";
            this.grbIdentify.Size = new System.Drawing.Size(990, 52);
            this.grbIdentify.TabIndex = 0;
            this.grbIdentify.TabStop = false;
            this.grbIdentify.Text = "ISO18000-6B Identify";
            // 
            // btnIdentify
            // 
            this.btnIdentify.Location = new System.Drawing.Point(634, 15);
            this.btnIdentify.Name = "btnIdentify";
            this.btnIdentify.Size = new System.Drawing.Size(120, 30);
            this.btnIdentify.TabIndex = 1;
            this.btnIdentify.TabStop = false;
            this.btnIdentify.Text = "&Identify";
            this.btnIdentify.UseVisualStyleBackColor = true;
            this.btnIdentify.Click += new System.EventHandler(this.btnIdentify_Click);
            // 
            // utxtCard
            // 
            this.utxtCard.ErrorInvalid = false;
            this.utxtCard.InputChar = '0';
            this.utxtCard.InputMask = "HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH-HH";
            this.utxtCard.Location = new System.Drawing.Point(100, 19);
            this.utxtCard.MaxLength = 35;
            this.utxtCard.Name = "utxtCard";
            this.utxtCard.Size = new System.Drawing.Size(528, 23);
            this.utxtCard.StdInputMask = ADSDK.Bases.Components.FormatTextBox.InputMaskType.Custom;
            this.utxtCard.TabIndex = 0;
            this.utxtCard.TabStop = false;
            this.utxtCard.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // lblCard
            // 
            this.lblCard.AutoSize = true;
            this.lblCard.Location = new System.Drawing.Point(12, 22);
            this.lblCard.Name = "lblCard";
            this.lblCard.Size = new System.Drawing.Size(61, 17);
            this.lblCard.TabIndex = 2;
            this.lblCard.Text = "Card No:";
            // 
            // grbWrite
            // 
            this.grbWrite.Controls.Add(this.btnWrite);
            this.grbWrite.Controls.Add(this.ltxtWriteAddress);
            this.grbWrite.Controls.Add(this.ltxtWriteLength);
            this.grbWrite.Controls.Add(this.utxtWriteData);
            this.grbWrite.Controls.Add(this.lblWriteMark);
            this.grbWrite.Controls.Add(this.lblWriteAddress);
            this.grbWrite.Controls.Add(this.lblWriteLength);
            this.grbWrite.Controls.Add(this.lblWriteData);
            this.grbWrite.Dock = System.Windows.Forms.DockStyle.Top;
            this.grbWrite.Location = new System.Drawing.Point(0, 134);
            this.grbWrite.Name = "grbWrite";
            this.grbWrite.Size = new System.Drawing.Size(990, 82);
            this.grbWrite.TabIndex = 2;
            this.grbWrite.TabStop = false;
            this.grbWrite.Text = "ISO18000-6B";
            // 
            // btnWrite
            // 
            this.btnWrite.Location = new System.Drawing.Point(634, 45);
            this.btnWrite.Name = "btnWrite";
            this.btnWrite.Size = new System.Drawing.Size(120, 30);
            this.btnWrite.TabIndex = 3;
            this.btnWrite.TabStop = false;
            this.btnWrite.Text = "Writ&e";
            this.btnWrite.UseVisualStyleBackColor = true;
            this.btnWrite.Click += new System.EventHandler(this.btnWrite_Click);
            // 
            // ltxtWriteAddress
            // 
            this.ltxtWriteAddress.IntText = 0;
            this.ltxtWriteAddress.LimitText = "1234567890";
            this.ltxtWriteAddress.Location = new System.Drawing.Point(98, 19);
            this.ltxtWriteAddress.MaxLength = 2;
            this.ltxtWriteAddress.Name = "ltxtWriteAddress";
            this.ltxtWriteAddress.Size = new System.Drawing.Size(85, 23);
            this.ltxtWriteAddress.TabIndex = 0;
            this.ltxtWriteAddress.TabStop = false;
            this.ltxtWriteAddress.Text = "0";
            this.ltxtWriteAddress.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // ltxtWriteLength
            // 
            this.ltxtWriteLength.IntText = 2;
            this.ltxtWriteLength.LimitText = "1234567890";
            this.ltxtWriteLength.Location = new System.Drawing.Point(258, 19);
            this.ltxtWriteLength.MaxLength = 2;
            this.ltxtWriteLength.Name = "ltxtWriteLength";
            this.ltxtWriteLength.Size = new System.Drawing.Size(85, 23);
            this.ltxtWriteLength.TabIndex = 1;
            this.ltxtWriteLength.TabStop = false;
            this.ltxtWriteLength.Text = "2";
            this.ltxtWriteLength.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.ltxtWriteLength.TextChanged += new System.EventHandler(this.ltxtWriteLength_TextChanged);
            // 
            // utxtWriteData
            // 
            this.utxtWriteData.ErrorInvalid = false;
            this.utxtWriteData.InputChar = '0';
            this.utxtWriteData.InputMask = "HH-HH";
            this.utxtWriteData.Location = new System.Drawing.Point(100, 49);
            this.utxtWriteData.MaxLength = 5;
            this.utxtWriteData.Name = "utxtWriteData";
            this.utxtWriteData.Size = new System.Drawing.Size(528, 23);
            this.utxtWriteData.StdInputMask = ADSDK.Bases.Components.FormatTextBox.InputMaskType.Custom;
            this.utxtWriteData.TabIndex = 2;
            this.utxtWriteData.TabStop = false;
            this.utxtWriteData.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // lblWriteMark
            // 
            this.lblWriteMark.AutoSize = true;
            this.lblWriteMark.Location = new System.Drawing.Point(349, 22);
            this.lblWriteMark.Name = "lblWriteMark";
            this.lblWriteMark.Size = new System.Drawing.Size(223, 17);
            this.lblWriteMark.TabIndex = 6;
            this.lblWriteMark.Text = "(Address start 2,Length not more 64)";
            // 
            // lblWriteAddress
            // 
            this.lblWriteAddress.AutoSize = true;
            this.lblWriteAddress.Location = new System.Drawing.Point(12, 22);
            this.lblWriteAddress.Name = "lblWriteAddress";
            this.lblWriteAddress.Size = new System.Drawing.Size(59, 17);
            this.lblWriteAddress.TabIndex = 4;
            this.lblWriteAddress.Text = "Address:";
            // 
            // lblWriteLength
            // 
            this.lblWriteLength.AutoSize = true;
            this.lblWriteLength.Location = new System.Drawing.Point(189, 22);
            this.lblWriteLength.Name = "lblWriteLength";
            this.lblWriteLength.Size = new System.Drawing.Size(50, 17);
            this.lblWriteLength.TabIndex = 5;
            this.lblWriteLength.Text = "Length:";
            // 
            // lblWriteData
            // 
            this.lblWriteData.AutoSize = true;
            this.lblWriteData.Location = new System.Drawing.Point(12, 52);
            this.lblWriteData.Name = "lblWriteData";
            this.lblWriteData.Size = new System.Drawing.Size(38, 17);
            this.lblWriteData.TabIndex = 7;
            this.lblWriteData.Text = "Data:";
            // 
            // grbRead
            // 
            this.grbRead.Controls.Add(this.utxtReadData);
            this.grbRead.Controls.Add(this.btnRead);
            this.grbRead.Controls.Add(this.ltxtReadAddress);
            this.grbRead.Controls.Add(this.ltxtReadLength);
            this.grbRead.Controls.Add(this.lblReadMark);
            this.grbRead.Controls.Add(this.lblReadAddress);
            this.grbRead.Controls.Add(this.lblReadData);
            this.grbRead.Controls.Add(this.lblReadLength);
            this.grbRead.Dock = System.Windows.Forms.DockStyle.Top;
            this.grbRead.Location = new System.Drawing.Point(0, 52);
            this.grbRead.Name = "grbRead";
            this.grbRead.Size = new System.Drawing.Size(990, 82);
            this.grbRead.TabIndex = 1;
            this.grbRead.TabStop = false;
            this.grbRead.Text = "ISO18000-6B Read";
            // 
            // utxtReadData
            // 
            this.utxtReadData.ErrorInvalid = false;
            this.utxtReadData.InputChar = '0';
            this.utxtReadData.InputMask = "";
            this.utxtReadData.Location = new System.Drawing.Point(100, 49);
            this.utxtReadData.MaxLength = 0;
            this.utxtReadData.Name = "utxtReadData";
            this.utxtReadData.Size = new System.Drawing.Size(528, 23);
            this.utxtReadData.StdInputMask = ADSDK.Bases.Components.FormatTextBox.InputMaskType.None;
            this.utxtReadData.TabIndex = 2;
            this.utxtReadData.TabStop = false;
            this.utxtReadData.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // btnRead
            // 
            this.btnRead.Location = new System.Drawing.Point(634, 45);
            this.btnRead.Name = "btnRead";
            this.btnRead.Size = new System.Drawing.Size(120, 30);
            this.btnRead.TabIndex = 3;
            this.btnRead.TabStop = false;
            this.btnRead.Text = "&Read";
            this.btnRead.UseVisualStyleBackColor = true;
            this.btnRead.Click += new System.EventHandler(this.btnRead_Click);
            // 
            // ltxtReadAddress
            // 
            this.ltxtReadAddress.IntText = 0;
            this.ltxtReadAddress.LimitText = "1234567890";
            this.ltxtReadAddress.Location = new System.Drawing.Point(98, 19);
            this.ltxtReadAddress.MaxLength = 2;
            this.ltxtReadAddress.Name = "ltxtReadAddress";
            this.ltxtReadAddress.Size = new System.Drawing.Size(85, 23);
            this.ltxtReadAddress.TabIndex = 0;
            this.ltxtReadAddress.TabStop = false;
            this.ltxtReadAddress.Text = "0";
            this.ltxtReadAddress.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // ltxtReadLength
            // 
            this.ltxtReadLength.IntText = 2;
            this.ltxtReadLength.LimitText = "1234567890";
            this.ltxtReadLength.Location = new System.Drawing.Point(258, 19);
            this.ltxtReadLength.MaxLength = 2;
            this.ltxtReadLength.Name = "ltxtReadLength";
            this.ltxtReadLength.Size = new System.Drawing.Size(85, 23);
            this.ltxtReadLength.TabIndex = 1;
            this.ltxtReadLength.TabStop = false;
            this.ltxtReadLength.Text = "2";
            this.ltxtReadLength.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.ltxtReadLength.TextChanged += new System.EventHandler(this.ltxtReadLength_TextChanged);
            // 
            // lblReadMark
            // 
            this.lblReadMark.AutoSize = true;
            this.lblReadMark.Location = new System.Drawing.Point(349, 22);
            this.lblReadMark.Name = "lblReadMark";
            this.lblReadMark.Size = new System.Drawing.Size(131, 17);
            this.lblReadMark.TabIndex = 6;
            this.lblReadMark.Text = "(Length not more 64)";
            // 
            // lblReadAddress
            // 
            this.lblReadAddress.AutoSize = true;
            this.lblReadAddress.Location = new System.Drawing.Point(12, 22);
            this.lblReadAddress.Name = "lblReadAddress";
            this.lblReadAddress.Size = new System.Drawing.Size(59, 17);
            this.lblReadAddress.TabIndex = 4;
            this.lblReadAddress.Text = "Address:";
            // 
            // lblReadData
            // 
            this.lblReadData.AutoSize = true;
            this.lblReadData.Location = new System.Drawing.Point(12, 52);
            this.lblReadData.Name = "lblReadData";
            this.lblReadData.Size = new System.Drawing.Size(38, 17);
            this.lblReadData.TabIndex = 7;
            this.lblReadData.Text = "Data:";
            // 
            // lblReadLength
            // 
            this.lblReadLength.AutoSize = true;
            this.lblReadLength.Location = new System.Drawing.Point(189, 22);
            this.lblReadLength.Name = "lblReadLength";
            this.lblReadLength.Size = new System.Drawing.Size(50, 17);
            this.lblReadLength.TabIndex = 5;
            this.lblReadLength.Text = "Length:";
            // 
            // ucWriteISO
            // 
            this.Controls.Add(this.grbWrite);
            this.Controls.Add(this.grbRead);
            this.Controls.Add(this.grbIdentify);
            this.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.Name = "ucWriteISO";
            this.Size = new System.Drawing.Size(990, 438);
            this.TitleVisable = false;
            this.Controls.SetChildIndex(this.grbIdentify, 0);
            this.Controls.SetChildIndex(this.grbRead, 0);
            this.Controls.SetChildIndex(this.grbWrite, 0);
            this.grbIdentify.ResumeLayout(false);
            this.grbIdentify.PerformLayout();
            this.grbWrite.ResumeLayout(false);
            this.grbWrite.PerformLayout();
            this.grbRead.ResumeLayout(false);
            this.grbRead.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox grbIdentify;
        private ADSDK.Bases.Components.FormatTextBox utxtCard;
        private System.Windows.Forms.Label lblCard;
        private System.Windows.Forms.GroupBox grbWrite;
        private ADSDK.Bases.Components.LimitTextBox ltxtWriteAddress;
        private ADSDK.Bases.Components.LimitTextBox ltxtWriteLength;
        private ADSDK.Bases.Components.FormatTextBox utxtWriteData;
        private System.Windows.Forms.Label lblWriteMark;
        private System.Windows.Forms.Label lblWriteAddress;
        private System.Windows.Forms.Label lblWriteLength;
        private System.Windows.Forms.Label lblWriteData;
        private System.Windows.Forms.GroupBox grbRead;
        private ADSDK.Bases.Components.FormatTextBox utxtReadData;
        private ADSDK.Bases.Components.LimitTextBox ltxtReadAddress;
        private ADSDK.Bases.Components.LimitTextBox ltxtReadLength;
        private System.Windows.Forms.Label lblReadMark;
        private System.Windows.Forms.Label lblReadAddress;
        private System.Windows.Forms.Label lblReadData;
        private System.Windows.Forms.Label lblReadLength;
        private System.Windows.Forms.Button btnIdentify;
        private System.Windows.Forms.Button btnWrite;
        private System.Windows.Forms.Button btnRead;
    }
}
