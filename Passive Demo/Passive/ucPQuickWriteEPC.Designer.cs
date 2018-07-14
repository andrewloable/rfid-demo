namespace Aosid.Passive
{
    partial class ucPQuickWriteEPC
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
            this.lblWriteCardNO = new System.Windows.Forms.Label();
            this.utxtCardWg = new ADSDK.Bases.Components.FormatTextBox();
            this.lblWriteCardNOWG = new System.Windows.Forms.Label();
            this.chkAddHex = new System.Windows.Forms.CheckBox();
            this.lblEncryptState = new System.Windows.Forms.Label();
            this.btnAdd = new System.Windows.Forms.Button();
            this.btnDec = new System.Windows.Forms.Button();
            this.btnWriteTag = new System.Windows.Forms.Button();
            this.btnReadTag = new System.Windows.Forms.Button();
            this.chkIsEncrypt = new System.Windows.Forms.CheckBox();
            this.chkAdd = new System.Windows.Forms.CheckBox();
            this.utxtCardHex = new ADSDK.Bases.Components.FormatTextBox();
            this.cmbWiegand = new System.Windows.Forms.ComboBox();
            this.ltxtCardDecimal = new ADSDK.Bases.Components.LimitTextBox();
            this.lblWiegand = new System.Windows.Forms.Label();
            this.cmbPosition = new System.Windows.Forms.ComboBox();
            this.lblWriteCardNODec = new System.Windows.Forms.Label();
            this.lblPosition = new System.Windows.Forms.Label();
            this.lblWriteCardNOHex = new System.Windows.Forms.Label();
            this.lblWriteCard = new System.Windows.Forms.Label();
            this.txtWriteCard = new System.Windows.Forms.TextBox();
            this.lblWriteState = new System.Windows.Forms.Label();
            this.lblReadState = new System.Windows.Forms.Label();
            this.lblReadCard = new System.Windows.Forms.Label();
            this.txtReadCard = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // lblWriteCardNO
            // 
            this.lblWriteCardNO.AutoSize = true;
            this.lblWriteCardNO.Location = new System.Drawing.Point(14, 158);
            this.lblWriteCardNO.Name = "lblWriteCardNO";
            this.lblWriteCardNO.Size = new System.Drawing.Size(67, 17);
            this.lblWriteCardNO.TabIndex = 49;
            this.lblWriteCardNO.Text = "Write No.:";
            // 
            // utxtCardWg
            // 
            this.utxtCardWg.ErrorInvalid = false;
            this.utxtCardWg.InputChar = '0';
            this.utxtCardWg.InputMask = "00000,00000";
            this.utxtCardWg.Location = new System.Drawing.Point(417, 155);
            this.utxtCardWg.MaxLength = 11;
            this.utxtCardWg.Name = "utxtCardWg";
            this.utxtCardWg.Size = new System.Drawing.Size(120, 23);
            this.utxtCardWg.StdInputMask = ADSDK.Bases.Components.FormatTextBox.InputMaskType.Custom;
            this.utxtCardWg.TabIndex = 47;
            this.utxtCardWg.TabStop = false;
            this.utxtCardWg.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // lblWriteCardNOWG
            // 
            this.lblWriteCardNOWG.AutoSize = true;
            this.lblWriteCardNOWG.Location = new System.Drawing.Point(414, 135);
            this.lblWriteCardNOWG.Name = "lblWriteCardNOWG";
            this.lblWriteCardNOWG.Size = new System.Drawing.Size(96, 17);
            this.lblWriteCardNOWG.TabIndex = 48;
            this.lblWriteCardNOWG.Text = "Write No.(WG):";
            // 
            // chkAddHex
            // 
            this.chkAddHex.AutoSize = true;
            this.chkAddHex.Location = new System.Drawing.Point(543, 43);
            this.chkAddHex.Name = "chkAddHex";
            this.chkAddHex.Size = new System.Drawing.Size(77, 21);
            this.chkAddHex.TabIndex = 46;
            this.chkAddHex.TabStop = false;
            this.chkAddHex.Text = "Add Hex";
            this.chkAddHex.UseVisualStyleBackColor = true;
            // 
            // lblEncryptState
            // 
            this.lblEncryptState.AutoSize = true;
            this.lblEncryptState.Location = new System.Drawing.Point(791, 45);
            this.lblEncryptState.Name = "lblEncryptState";
            this.lblEncryptState.Size = new System.Drawing.Size(15, 17);
            this.lblEncryptState.TabIndex = 45;
            this.lblEncryptState.Text = "1";
            // 
            // btnAdd
            // 
            this.btnAdd.Location = new System.Drawing.Point(554, 151);
            this.btnAdd.Name = "btnAdd";
            this.btnAdd.Size = new System.Drawing.Size(120, 30);
            this.btnAdd.TabIndex = 33;
            this.btnAdd.TabStop = false;
            this.btnAdd.Text = "Add 1";
            this.btnAdd.UseVisualStyleBackColor = true;
            // 
            // btnDec
            // 
            this.btnDec.Location = new System.Drawing.Point(554, 184);
            this.btnDec.Name = "btnDec";
            this.btnDec.Size = new System.Drawing.Size(120, 30);
            this.btnDec.TabIndex = 34;
            this.btnDec.TabStop = false;
            this.btnDec.Text = "Decrease 1";
            this.btnDec.UseVisualStyleBackColor = true;
            // 
            // btnWriteTag
            // 
            this.btnWriteTag.Location = new System.Drawing.Point(686, 184);
            this.btnWriteTag.Name = "btnWriteTag";
            this.btnWriteTag.Size = new System.Drawing.Size(120, 30);
            this.btnWriteTag.TabIndex = 36;
            this.btnWriteTag.TabStop = false;
            this.btnWriteTag.Text = "Write Tag(F12)";
            this.btnWriteTag.UseVisualStyleBackColor = true;
            // 
            // btnReadTag
            // 
            this.btnReadTag.Location = new System.Drawing.Point(686, 151);
            this.btnReadTag.Name = "btnReadTag";
            this.btnReadTag.Size = new System.Drawing.Size(120, 30);
            this.btnReadTag.TabIndex = 35;
            this.btnReadTag.TabStop = false;
            this.btnReadTag.Text = "Read Tag(F9)";
            this.btnReadTag.UseVisualStyleBackColor = true;
            // 
            // chkIsEncrypt
            // 
            this.chkIsEncrypt.AutoSize = true;
            this.chkIsEncrypt.Location = new System.Drawing.Point(673, 43);
            this.chkIsEncrypt.Name = "chkIsEncrypt";
            this.chkIsEncrypt.Size = new System.Drawing.Size(101, 21);
            this.chkIsEncrypt.TabIndex = 28;
            this.chkIsEncrypt.TabStop = false;
            this.chkIsEncrypt.Text = "Auto Encrypt";
            this.chkIsEncrypt.UseVisualStyleBackColor = true;
            this.chkIsEncrypt.Visible = false;
            // 
            // chkAdd
            // 
            this.chkAdd.AutoSize = true;
            this.chkAdd.Location = new System.Drawing.Point(444, 43);
            this.chkAdd.Name = "chkAdd";
            this.chkAdd.Size = new System.Drawing.Size(93, 21);
            this.chkAdd.TabIndex = 27;
            this.chkAdd.TabStop = false;
            this.chkAdd.Text = "Auto Add 1";
            this.chkAdd.UseVisualStyleBackColor = true;
            // 
            // utxtCardHex
            // 
            this.utxtCardHex.ErrorInvalid = false;
            this.utxtCardHex.InputChar = '0';
            this.utxtCardHex.InputMask = "HH-HH-HH-HH";
            this.utxtCardHex.Location = new System.Drawing.Point(282, 155);
            this.utxtCardHex.MaxLength = 11;
            this.utxtCardHex.Name = "utxtCardHex";
            this.utxtCardHex.Size = new System.Drawing.Size(120, 23);
            this.utxtCardHex.StdInputMask = ADSDK.Bases.Components.FormatTextBox.InputMaskType.Custom;
            this.utxtCardHex.TabIndex = 32;
            this.utxtCardHex.TabStop = false;
            this.utxtCardHex.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // cmbWiegand
            // 
            this.cmbWiegand.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbWiegand.FormattingEnabled = true;
            this.cmbWiegand.Items.AddRange(new object[] {
            "Wiegand26",
            "Wiegand34"});
            this.cmbWiegand.Location = new System.Drawing.Point(142, 41);
            this.cmbWiegand.Name = "cmbWiegand";
            this.cmbWiegand.Size = new System.Drawing.Size(95, 25);
            this.cmbWiegand.TabIndex = 25;
            this.cmbWiegand.TabStop = false;
            // 
            // ltxtCardDecimal
            // 
            this.ltxtCardDecimal.IntText = 0;
            this.ltxtCardDecimal.LimitText = "1234567890";
            this.ltxtCardDecimal.Location = new System.Drawing.Point(142, 155);
            this.ltxtCardDecimal.MaxLength = 10;
            this.ltxtCardDecimal.Name = "ltxtCardDecimal";
            this.ltxtCardDecimal.Size = new System.Drawing.Size(120, 23);
            this.ltxtCardDecimal.TabIndex = 31;
            this.ltxtCardDecimal.TabStop = false;
            this.ltxtCardDecimal.Text = "00";
            this.ltxtCardDecimal.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // lblWiegand
            // 
            this.lblWiegand.AutoSize = true;
            this.lblWiegand.Location = new System.Drawing.Point(14, 45);
            this.lblWiegand.Name = "lblWiegand";
            this.lblWiegand.Size = new System.Drawing.Size(95, 17);
            this.lblWiegand.TabIndex = 37;
            this.lblWiegand.Text = "Wiegand Type:";
            // 
            // cmbPosition
            // 
            this.cmbPosition.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbPosition.FormattingEnabled = true;
            this.cmbPosition.Items.AddRange(new object[] {
            "-2",
            "-1",
            "0",
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9"});
            this.cmbPosition.Location = new System.Drawing.Point(370, 41);
            this.cmbPosition.Name = "cmbPosition";
            this.cmbPosition.Size = new System.Drawing.Size(60, 25);
            this.cmbPosition.TabIndex = 26;
            this.cmbPosition.TabStop = false;
            // 
            // lblWriteCardNODec
            // 
            this.lblWriteCardNODec.AutoSize = true;
            this.lblWriteCardNODec.Location = new System.Drawing.Point(139, 135);
            this.lblWriteCardNODec.Name = "lblWriteCardNODec";
            this.lblWriteCardNODec.Size = new System.Drawing.Size(99, 17);
            this.lblWriteCardNODec.TabIndex = 41;
            this.lblWriteCardNODec.Text = "Write No.(DEC):";
            // 
            // lblPosition
            // 
            this.lblPosition.AutoSize = true;
            this.lblPosition.Location = new System.Drawing.Point(264, 45);
            this.lblPosition.Name = "lblPosition";
            this.lblPosition.Size = new System.Drawing.Size(57, 17);
            this.lblPosition.TabIndex = 38;
            this.lblPosition.Text = "Position:";
            // 
            // lblWriteCardNOHex
            // 
            this.lblWriteCardNOHex.AutoSize = true;
            this.lblWriteCardNOHex.Location = new System.Drawing.Point(279, 135);
            this.lblWriteCardNOHex.Name = "lblWriteCardNOHex";
            this.lblWriteCardNOHex.Size = new System.Drawing.Size(99, 17);
            this.lblWriteCardNOHex.TabIndex = 42;
            this.lblWriteCardNOHex.Text = "Write No.(HEX):";
            // 
            // lblWriteCard
            // 
            this.lblWriteCard.AutoSize = true;
            this.lblWriteCard.Location = new System.Drawing.Point(14, 105);
            this.lblWriteCard.Name = "lblWriteCard";
            this.lblWriteCard.Size = new System.Drawing.Size(64, 17);
            this.lblWriteCard.TabIndex = 40;
            this.lblWriteCard.Text = "Write No:";
            // 
            // txtWriteCard
            // 
            this.txtWriteCard.Location = new System.Drawing.Point(142, 102);
            this.txtWriteCard.Name = "txtWriteCard";
            this.txtWriteCard.ReadOnly = true;
            this.txtWriteCard.Size = new System.Drawing.Size(480, 23);
            this.txtWriteCard.TabIndex = 30;
            this.txtWriteCard.TabStop = false;
            // 
            // lblWriteState
            // 
            this.lblWriteState.AutoSize = true;
            this.lblWriteState.Location = new System.Drawing.Point(636, 105);
            this.lblWriteState.Name = "lblWriteState";
            this.lblWriteState.Size = new System.Drawing.Size(15, 17);
            this.lblWriteState.TabIndex = 44;
            this.lblWriteState.Text = "1";
            // 
            // lblReadState
            // 
            this.lblReadState.AutoSize = true;
            this.lblReadState.Location = new System.Drawing.Point(636, 75);
            this.lblReadState.Name = "lblReadState";
            this.lblReadState.Size = new System.Drawing.Size(15, 17);
            this.lblReadState.TabIndex = 43;
            this.lblReadState.Text = "1";
            // 
            // lblReadCard
            // 
            this.lblReadCard.AutoSize = true;
            this.lblReadCard.Location = new System.Drawing.Point(14, 75);
            this.lblReadCard.Name = "lblReadCard";
            this.lblReadCard.Size = new System.Drawing.Size(63, 17);
            this.lblReadCard.TabIndex = 39;
            this.lblReadCard.Text = "Read No:";
            // 
            // txtReadCard
            // 
            this.txtReadCard.Location = new System.Drawing.Point(142, 72);
            this.txtReadCard.Name = "txtReadCard";
            this.txtReadCard.ReadOnly = true;
            this.txtReadCard.Size = new System.Drawing.Size(480, 23);
            this.txtReadCard.TabIndex = 29;
            this.txtReadCard.TabStop = false;
            // 
            // ucPQuickWriteEPC
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Inherit;
            this.Controls.Add(this.lblWriteCardNO);
            this.Controls.Add(this.utxtCardWg);
            this.Controls.Add(this.lblWriteCardNOWG);
            this.Controls.Add(this.chkAddHex);
            this.Controls.Add(this.lblEncryptState);
            this.Controls.Add(this.btnAdd);
            this.Controls.Add(this.btnDec);
            this.Controls.Add(this.btnWriteTag);
            this.Controls.Add(this.btnReadTag);
            this.Controls.Add(this.chkIsEncrypt);
            this.Controls.Add(this.chkAdd);
            this.Controls.Add(this.utxtCardHex);
            this.Controls.Add(this.cmbWiegand);
            this.Controls.Add(this.ltxtCardDecimal);
            this.Controls.Add(this.lblWiegand);
            this.Controls.Add(this.cmbPosition);
            this.Controls.Add(this.lblWriteCardNODec);
            this.Controls.Add(this.lblPosition);
            this.Controls.Add(this.lblWriteCardNOHex);
            this.Controls.Add(this.lblWriteCard);
            this.Controls.Add(this.txtWriteCard);
            this.Controls.Add(this.lblWriteState);
            this.Controls.Add(this.lblReadState);
            this.Controls.Add(this.lblReadCard);
            this.Controls.Add(this.txtReadCard);
            this.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.Name = "ucPQuickWriteEPC";
            this.Controls.SetChildIndex(this.txtReadCard, 0);
            this.Controls.SetChildIndex(this.lblReadCard, 0);
            this.Controls.SetChildIndex(this.lblReadState, 0);
            this.Controls.SetChildIndex(this.lblWriteState, 0);
            this.Controls.SetChildIndex(this.txtWriteCard, 0);
            this.Controls.SetChildIndex(this.lblWriteCard, 0);
            this.Controls.SetChildIndex(this.lblWriteCardNOHex, 0);
            this.Controls.SetChildIndex(this.lblPosition, 0);
            this.Controls.SetChildIndex(this.lblWriteCardNODec, 0);
            this.Controls.SetChildIndex(this.cmbPosition, 0);
            this.Controls.SetChildIndex(this.lblWiegand, 0);
            this.Controls.SetChildIndex(this.ltxtCardDecimal, 0);
            this.Controls.SetChildIndex(this.cmbWiegand, 0);
            this.Controls.SetChildIndex(this.utxtCardHex, 0);
            this.Controls.SetChildIndex(this.chkAdd, 0);
            this.Controls.SetChildIndex(this.chkIsEncrypt, 0);
            this.Controls.SetChildIndex(this.btnReadTag, 0);
            this.Controls.SetChildIndex(this.btnWriteTag, 0);
            this.Controls.SetChildIndex(this.btnDec, 0);
            this.Controls.SetChildIndex(this.btnAdd, 0);
            this.Controls.SetChildIndex(this.lblEncryptState, 0);
            this.Controls.SetChildIndex(this.chkAddHex, 0);
            this.Controls.SetChildIndex(this.lblWriteCardNOWG, 0);
            this.Controls.SetChildIndex(this.utxtCardWg, 0);
            this.Controls.SetChildIndex(this.lblWriteCardNO, 0);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lblWriteCardNO;
        private ADSDK.Bases.Components.FormatTextBox utxtCardWg;
        private System.Windows.Forms.Label lblWriteCardNOWG;
        private System.Windows.Forms.CheckBox chkAddHex;
        private System.Windows.Forms.Label lblEncryptState;
        private System.Windows.Forms.Button btnAdd;
        private System.Windows.Forms.Button btnDec;
        private System.Windows.Forms.Button btnWriteTag;
        private System.Windows.Forms.Button btnReadTag;
        private System.Windows.Forms.CheckBox chkIsEncrypt;
        private System.Windows.Forms.CheckBox chkAdd;
        private ADSDK.Bases.Components.FormatTextBox utxtCardHex;
        private System.Windows.Forms.ComboBox cmbWiegand;
        private ADSDK.Bases.Components.LimitTextBox ltxtCardDecimal;
        private System.Windows.Forms.Label lblWiegand;
        private System.Windows.Forms.ComboBox cmbPosition;
        private System.Windows.Forms.Label lblWriteCardNODec;
        private System.Windows.Forms.Label lblPosition;
        private System.Windows.Forms.Label lblWriteCardNOHex;
        private System.Windows.Forms.Label lblWriteCard;
        private System.Windows.Forms.TextBox txtWriteCard;
        private System.Windows.Forms.Label lblWriteState;
        private System.Windows.Forms.Label lblReadState;
        private System.Windows.Forms.Label lblReadCard;
        private System.Windows.Forms.TextBox txtReadCard;
    }
}
