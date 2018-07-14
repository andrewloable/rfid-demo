namespace Aosid
{
    partial class ucPWriteEPC
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
            this.btnWrite = new System.Windows.Forms.Button();
            this.btnRead = new System.Windows.Forms.Button();
            this.btnIdentify = new System.Windows.Forms.Button();
            this.grbWrite = new System.Windows.Forms.GroupBox();
            this.btnWriteAscii = new System.Windows.Forms.Button();
            this.txtWriteAscii = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.ltxtWriteAddress = new ADSDK.Bases.Components.LimitTextBox();
            this.ltxtWriteLength = new ADSDK.Bases.Components.LimitTextBox();
            this.utxtWriteData = new ADSDK.Bases.Components.FormatTextBox();
            this.cmbWriteBlock = new System.Windows.Forms.ComboBox();
            this.lblWriteBlock = new System.Windows.Forms.Label();
            this.lblWriteMark = new System.Windows.Forms.Label();
            this.lblWriteAddress = new System.Windows.Forms.Label();
            this.lblWriteLength = new System.Windows.Forms.Label();
            this.lblWriteData = new System.Windows.Forms.Label();
            this.grbRead = new System.Windows.Forms.GroupBox();
            this.utxtReadData = new ADSDK.Bases.Components.FormatTextBox();
            this.ltxtReadAddress = new ADSDK.Bases.Components.LimitTextBox();
            this.ltxtReadLength = new ADSDK.Bases.Components.LimitTextBox();
            this.cmbReadBlock = new System.Windows.Forms.ComboBox();
            this.lblReadBlock = new System.Windows.Forms.Label();
            this.lblReadMark = new System.Windows.Forms.Label();
            this.lblReadAddress = new System.Windows.Forms.Label();
            this.lblReadData = new System.Windows.Forms.Label();
            this.lblReadLength = new System.Windows.Forms.Label();
            this.grbIdentify = new System.Windows.Forms.GroupBox();
            this.utxtCard = new ADSDK.Bases.Components.FormatTextBox();
            this.lblCard = new System.Windows.Forms.Label();
            this.grbQuickWrite = new System.Windows.Forms.GroupBox();
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
            this.lblWriteCardNO = new System.Windows.Forms.Label();
            this.grbWrite.SuspendLayout();
            this.grbRead.SuspendLayout();
            this.grbIdentify.SuspendLayout();
            this.grbQuickWrite.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnWrite
            // 
            this.btnWrite.Location = new System.Drawing.Point(634, 45);
            this.btnWrite.Name = "btnWrite";
            this.btnWrite.Size = new System.Drawing.Size(120, 30);
            this.btnWrite.TabIndex = 4;
            this.btnWrite.TabStop = false;
            this.btnWrite.Text = "Writ&e";
            this.btnWrite.UseVisualStyleBackColor = true;
            this.btnWrite.Click += new System.EventHandler(this.btnWrite_Click);
            // 
            // btnRead
            // 
            this.btnRead.Location = new System.Drawing.Point(634, 45);
            this.btnRead.Name = "btnRead";
            this.btnRead.Size = new System.Drawing.Size(120, 30);
            this.btnRead.TabIndex = 4;
            this.btnRead.TabStop = false;
            this.btnRead.Text = "&Read";
            this.btnRead.UseVisualStyleBackColor = true;
            this.btnRead.Click += new System.EventHandler(this.btnRead_Click);
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
            // grbWrite
            // 
            this.grbWrite.Controls.Add(this.btnWriteAscii);
            this.grbWrite.Controls.Add(this.txtWriteAscii);
            this.grbWrite.Controls.Add(this.label1);
            this.grbWrite.Controls.Add(this.btnWrite);
            this.grbWrite.Controls.Add(this.ltxtWriteAddress);
            this.grbWrite.Controls.Add(this.ltxtWriteLength);
            this.grbWrite.Controls.Add(this.utxtWriteData);
            this.grbWrite.Controls.Add(this.cmbWriteBlock);
            this.grbWrite.Controls.Add(this.lblWriteBlock);
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
            this.grbWrite.Text = "EPC(GEN 2) Write";
            // 
            // btnWriteAscii
            // 
            this.btnWriteAscii.Location = new System.Drawing.Point(634, 75);
            this.btnWriteAscii.Name = "btnWriteAscii";
            this.btnWriteAscii.Size = new System.Drawing.Size(120, 30);
            this.btnWriteAscii.TabIndex = 16;
            this.btnWriteAscii.TabStop = false;
            this.btnWriteAscii.Text = "Writ&e";
            this.btnWriteAscii.UseVisualStyleBackColor = true;
            this.btnWriteAscii.Visible = false;
            this.btnWriteAscii.Click += new System.EventHandler(this.btnWriteAscii_Click);
            // 
            // txtWriteAscii
            // 
            this.txtWriteAscii.Location = new System.Drawing.Point(100, 79);
            this.txtWriteAscii.MaxLength = 8;
            this.txtWriteAscii.Name = "txtWriteAscii";
            this.txtWriteAscii.Size = new System.Drawing.Size(528, 23);
            this.txtWriteAscii.TabIndex = 15;
            this.txtWriteAscii.TabStop = false;
            this.txtWriteAscii.Visible = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 82);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(38, 17);
            this.label1.TabIndex = 14;
            this.label1.Text = "Data:";
            this.label1.Visible = false;
            // 
            // ltxtWriteAddress
            // 
            this.ltxtWriteAddress.IntText = 2;
            this.ltxtWriteAddress.LimitText = "1234567890";
            this.ltxtWriteAddress.Location = new System.Drawing.Point(280, 19);
            this.ltxtWriteAddress.MaxLength = 2;
            this.ltxtWriteAddress.Name = "ltxtWriteAddress";
            this.ltxtWriteAddress.Size = new System.Drawing.Size(85, 23);
            this.ltxtWriteAddress.TabIndex = 1;
            this.ltxtWriteAddress.TabStop = false;
            this.ltxtWriteAddress.Text = "2";
            this.ltxtWriteAddress.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // ltxtWriteLength
            // 
            this.ltxtWriteLength.IntText = 2;
            this.ltxtWriteLength.LimitText = "1234567890";
            this.ltxtWriteLength.Location = new System.Drawing.Point(458, 19);
            this.ltxtWriteLength.MaxLength = 2;
            this.ltxtWriteLength.Name = "ltxtWriteLength";
            this.ltxtWriteLength.Size = new System.Drawing.Size(85, 23);
            this.ltxtWriteLength.TabIndex = 2;
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
            this.utxtWriteData.TabIndex = 3;
            this.utxtWriteData.TabStop = false;
            this.utxtWriteData.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // cmbWriteBlock
            // 
            this.cmbWriteBlock.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbWriteBlock.FormattingEnabled = true;
            this.cmbWriteBlock.Items.AddRange(new object[] {
            "0-Reserved",
            "1-EPC",
            "2-TID",
            "3-User"});
            this.cmbWriteBlock.Location = new System.Drawing.Point(100, 18);
            this.cmbWriteBlock.Name = "cmbWriteBlock";
            this.cmbWriteBlock.Size = new System.Drawing.Size(86, 25);
            this.cmbWriteBlock.TabIndex = 0;
            this.cmbWriteBlock.TabStop = false;
            this.cmbWriteBlock.SelectedIndexChanged += new System.EventHandler(this.cmbWriteBlock_SelectedIndexChanged);
            // 
            // lblWriteBlock
            // 
            this.lblWriteBlock.AutoSize = true;
            this.lblWriteBlock.Location = new System.Drawing.Point(12, 22);
            this.lblWriteBlock.Name = "lblWriteBlock";
            this.lblWriteBlock.Size = new System.Drawing.Size(43, 17);
            this.lblWriteBlock.TabIndex = 5;
            this.lblWriteBlock.Text = "Block:";
            // 
            // lblWriteMark
            // 
            this.lblWriteMark.AutoSize = true;
            this.lblWriteMark.Location = new System.Drawing.Point(549, 22);
            this.lblWriteMark.Name = "lblWriteMark";
            this.lblWriteMark.Size = new System.Drawing.Size(223, 17);
            this.lblWriteMark.TabIndex = 8;
            this.lblWriteMark.Text = "(Address start 2,Length not more 48)";
            // 
            // lblWriteAddress
            // 
            this.lblWriteAddress.AutoSize = true;
            this.lblWriteAddress.Location = new System.Drawing.Point(194, 22);
            this.lblWriteAddress.Name = "lblWriteAddress";
            this.lblWriteAddress.Size = new System.Drawing.Size(59, 17);
            this.lblWriteAddress.TabIndex = 6;
            this.lblWriteAddress.Text = "Address:";
            // 
            // lblWriteLength
            // 
            this.lblWriteLength.AutoSize = true;
            this.lblWriteLength.Location = new System.Drawing.Point(371, 22);
            this.lblWriteLength.Name = "lblWriteLength";
            this.lblWriteLength.Size = new System.Drawing.Size(50, 17);
            this.lblWriteLength.TabIndex = 7;
            this.lblWriteLength.Text = "Length:";
            // 
            // lblWriteData
            // 
            this.lblWriteData.AutoSize = true;
            this.lblWriteData.Location = new System.Drawing.Point(12, 52);
            this.lblWriteData.Name = "lblWriteData";
            this.lblWriteData.Size = new System.Drawing.Size(38, 17);
            this.lblWriteData.TabIndex = 9;
            this.lblWriteData.Text = "Data:";
            // 
            // grbRead
            // 
            this.grbRead.Controls.Add(this.utxtReadData);
            this.grbRead.Controls.Add(this.btnRead);
            this.grbRead.Controls.Add(this.ltxtReadAddress);
            this.grbRead.Controls.Add(this.ltxtReadLength);
            this.grbRead.Controls.Add(this.cmbReadBlock);
            this.grbRead.Controls.Add(this.lblReadBlock);
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
            this.grbRead.Text = "EPC(GEN 2) Read";
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
            this.utxtReadData.TabIndex = 3;
            this.utxtReadData.TabStop = false;
            this.utxtReadData.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // ltxtReadAddress
            // 
            this.ltxtReadAddress.IntText = 2;
            this.ltxtReadAddress.LimitText = "1234567890";
            this.ltxtReadAddress.Location = new System.Drawing.Point(280, 19);
            this.ltxtReadAddress.MaxLength = 2;
            this.ltxtReadAddress.Name = "ltxtReadAddress";
            this.ltxtReadAddress.Size = new System.Drawing.Size(85, 23);
            this.ltxtReadAddress.TabIndex = 1;
            this.ltxtReadAddress.TabStop = false;
            this.ltxtReadAddress.Text = "2";
            this.ltxtReadAddress.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // ltxtReadLength
            // 
            this.ltxtReadLength.IntText = 2;
            this.ltxtReadLength.LimitText = "1234567890";
            this.ltxtReadLength.Location = new System.Drawing.Point(458, 19);
            this.ltxtReadLength.MaxLength = 2;
            this.ltxtReadLength.Name = "ltxtReadLength";
            this.ltxtReadLength.Size = new System.Drawing.Size(85, 23);
            this.ltxtReadLength.TabIndex = 2;
            this.ltxtReadLength.TabStop = false;
            this.ltxtReadLength.Text = "2";
            this.ltxtReadLength.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.ltxtReadLength.TextChanged += new System.EventHandler(this.ltxtReadLength_TextChanged);
            // 
            // cmbReadBlock
            // 
            this.cmbReadBlock.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbReadBlock.FormattingEnabled = true;
            this.cmbReadBlock.Items.AddRange(new object[] {
            "0-Reserved",
            "1-EPC",
            "2-TID",
            "3-User"});
            this.cmbReadBlock.Location = new System.Drawing.Point(100, 18);
            this.cmbReadBlock.Name = "cmbReadBlock";
            this.cmbReadBlock.Size = new System.Drawing.Size(86, 25);
            this.cmbReadBlock.TabIndex = 0;
            this.cmbReadBlock.TabStop = false;
            this.cmbReadBlock.SelectedIndexChanged += new System.EventHandler(this.cmbReadBlock_SelectedIndexChanged);
            // 
            // lblReadBlock
            // 
            this.lblReadBlock.AutoSize = true;
            this.lblReadBlock.Location = new System.Drawing.Point(12, 22);
            this.lblReadBlock.Name = "lblReadBlock";
            this.lblReadBlock.Size = new System.Drawing.Size(43, 17);
            this.lblReadBlock.TabIndex = 5;
            this.lblReadBlock.Text = "Block:";
            // 
            // lblReadMark
            // 
            this.lblReadMark.AutoSize = true;
            this.lblReadMark.Location = new System.Drawing.Point(549, 22);
            this.lblReadMark.Name = "lblReadMark";
            this.lblReadMark.Size = new System.Drawing.Size(131, 17);
            this.lblReadMark.TabIndex = 8;
            this.lblReadMark.Text = "(Length not more 48)";
            // 
            // lblReadAddress
            // 
            this.lblReadAddress.AutoSize = true;
            this.lblReadAddress.Location = new System.Drawing.Point(194, 22);
            this.lblReadAddress.Name = "lblReadAddress";
            this.lblReadAddress.Size = new System.Drawing.Size(59, 17);
            this.lblReadAddress.TabIndex = 6;
            this.lblReadAddress.Text = "Address:";
            // 
            // lblReadData
            // 
            this.lblReadData.AutoSize = true;
            this.lblReadData.Location = new System.Drawing.Point(12, 52);
            this.lblReadData.Name = "lblReadData";
            this.lblReadData.Size = new System.Drawing.Size(38, 17);
            this.lblReadData.TabIndex = 9;
            this.lblReadData.Text = "Data:";
            // 
            // lblReadLength
            // 
            this.lblReadLength.AutoSize = true;
            this.lblReadLength.Location = new System.Drawing.Point(371, 22);
            this.lblReadLength.Name = "lblReadLength";
            this.lblReadLength.Size = new System.Drawing.Size(50, 17);
            this.lblReadLength.TabIndex = 7;
            this.lblReadLength.Text = "Length:";
            // 
            // grbIdentify
            // 
            this.grbIdentify.Controls.Add(this.utxtCard);
            this.grbIdentify.Controls.Add(this.lblCard);
            this.grbIdentify.Controls.Add(this.btnIdentify);
            this.grbIdentify.Dock = System.Windows.Forms.DockStyle.Top;
            this.grbIdentify.Location = new System.Drawing.Point(0, 0);
            this.grbIdentify.Name = "grbIdentify";
            this.grbIdentify.Size = new System.Drawing.Size(990, 52);
            this.grbIdentify.TabIndex = 0;
            this.grbIdentify.TabStop = false;
            this.grbIdentify.Text = "EPC(GEN 2) Identify";
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
            // grbQuickWrite
            // 
            this.grbQuickWrite.AutoSize = true;
            this.grbQuickWrite.Controls.Add(this.lblWriteCardNO);
            this.grbQuickWrite.Controls.Add(this.utxtCardWg);
            this.grbQuickWrite.Controls.Add(this.lblWriteCardNOWG);
            this.grbQuickWrite.Controls.Add(this.chkAddHex);
            this.grbQuickWrite.Controls.Add(this.lblEncryptState);
            this.grbQuickWrite.Controls.Add(this.btnAdd);
            this.grbQuickWrite.Controls.Add(this.btnDec);
            this.grbQuickWrite.Controls.Add(this.btnWriteTag);
            this.grbQuickWrite.Controls.Add(this.btnReadTag);
            this.grbQuickWrite.Controls.Add(this.chkIsEncrypt);
            this.grbQuickWrite.Controls.Add(this.chkAdd);
            this.grbQuickWrite.Controls.Add(this.utxtCardHex);
            this.grbQuickWrite.Controls.Add(this.cmbWiegand);
            this.grbQuickWrite.Controls.Add(this.ltxtCardDecimal);
            this.grbQuickWrite.Controls.Add(this.lblWiegand);
            this.grbQuickWrite.Controls.Add(this.cmbPosition);
            this.grbQuickWrite.Controls.Add(this.lblWriteCardNODec);
            this.grbQuickWrite.Controls.Add(this.lblPosition);
            this.grbQuickWrite.Controls.Add(this.lblWriteCardNOHex);
            this.grbQuickWrite.Controls.Add(this.lblWriteCard);
            this.grbQuickWrite.Controls.Add(this.txtWriteCard);
            this.grbQuickWrite.Controls.Add(this.lblWriteState);
            this.grbQuickWrite.Controls.Add(this.lblReadState);
            this.grbQuickWrite.Controls.Add(this.lblReadCard);
            this.grbQuickWrite.Controls.Add(this.txtReadCard);
            this.grbQuickWrite.Dock = System.Windows.Forms.DockStyle.Top;
            this.grbQuickWrite.Location = new System.Drawing.Point(0, 216);
            this.grbQuickWrite.Name = "grbQuickWrite";
            this.grbQuickWrite.Size = new System.Drawing.Size(990, 213);
            this.grbQuickWrite.TabIndex = 3;
            this.grbQuickWrite.TabStop = false;
            this.grbQuickWrite.Text = "EPC(GEN 2) Write";
            this.grbQuickWrite.Visible = false;
            // 
            // utxtCardWg
            // 
            this.utxtCardWg.ErrorInvalid = false;
            this.utxtCardWg.InputChar = '0';
            this.utxtCardWg.InputMask = "00000,00000";
            this.utxtCardWg.Location = new System.Drawing.Point(415, 132);
            this.utxtCardWg.MaxLength = 11;
            this.utxtCardWg.Name = "utxtCardWg";
            this.utxtCardWg.Size = new System.Drawing.Size(120, 23);
            this.utxtCardWg.StdInputMask = ADSDK.Bases.Components.FormatTextBox.InputMaskType.Custom;
            this.utxtCardWg.TabIndex = 22;
            this.utxtCardWg.TabStop = false;
            this.utxtCardWg.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.utxtCardWg.TextChanged += new System.EventHandler(this.utxtCardWg_TextChanged);
            // 
            // lblWriteCardNOWG
            // 
            this.lblWriteCardNOWG.AutoSize = true;
            this.lblWriteCardNOWG.Location = new System.Drawing.Point(412, 112);
            this.lblWriteCardNOWG.Name = "lblWriteCardNOWG";
            this.lblWriteCardNOWG.Size = new System.Drawing.Size(96, 17);
            this.lblWriteCardNOWG.TabIndex = 23;
            this.lblWriteCardNOWG.Text = "Write No.(WG):";
            // 
            // chkAddHex
            // 
            this.chkAddHex.AutoSize = true;
            this.chkAddHex.Location = new System.Drawing.Point(541, 20);
            this.chkAddHex.Name = "chkAddHex";
            this.chkAddHex.Size = new System.Drawing.Size(77, 21);
            this.chkAddHex.TabIndex = 21;
            this.chkAddHex.TabStop = false;
            this.chkAddHex.Text = "Add Hex";
            this.chkAddHex.UseVisualStyleBackColor = true;
            this.chkAddHex.CheckedChanged += new System.EventHandler(this.chkAddHex_CheckedChanged);
            // 
            // lblEncryptState
            // 
            this.lblEncryptState.AutoSize = true;
            this.lblEncryptState.Location = new System.Drawing.Point(789, 22);
            this.lblEncryptState.Name = "lblEncryptState";
            this.lblEncryptState.Size = new System.Drawing.Size(15, 17);
            this.lblEncryptState.TabIndex = 20;
            this.lblEncryptState.Text = "1";
            // 
            // btnAdd
            // 
            this.btnAdd.Location = new System.Drawing.Point(552, 128);
            this.btnAdd.Name = "btnAdd";
            this.btnAdd.Size = new System.Drawing.Size(120, 30);
            this.btnAdd.TabIndex = 8;
            this.btnAdd.TabStop = false;
            this.btnAdd.Text = "Add 1";
            this.btnAdd.UseVisualStyleBackColor = true;
            this.btnAdd.Click += new System.EventHandler(this.btnAdd_Click);
            // 
            // btnDec
            // 
            this.btnDec.Location = new System.Drawing.Point(552, 161);
            this.btnDec.Name = "btnDec";
            this.btnDec.Size = new System.Drawing.Size(120, 30);
            this.btnDec.TabIndex = 9;
            this.btnDec.TabStop = false;
            this.btnDec.Text = "Decrease 1";
            this.btnDec.UseVisualStyleBackColor = true;
            this.btnDec.Click += new System.EventHandler(this.btnDec_Click);
            // 
            // btnWriteTag
            // 
            this.btnWriteTag.Location = new System.Drawing.Point(684, 161);
            this.btnWriteTag.Name = "btnWriteTag";
            this.btnWriteTag.Size = new System.Drawing.Size(120, 30);
            this.btnWriteTag.TabIndex = 11;
            this.btnWriteTag.TabStop = false;
            this.btnWriteTag.Text = "Write Tag(F12)";
            this.btnWriteTag.UseVisualStyleBackColor = true;
            this.btnWriteTag.Click += new System.EventHandler(this.btnWriteTag_Click);
            // 
            // btnReadTag
            // 
            this.btnReadTag.Location = new System.Drawing.Point(684, 128);
            this.btnReadTag.Name = "btnReadTag";
            this.btnReadTag.Size = new System.Drawing.Size(120, 30);
            this.btnReadTag.TabIndex = 10;
            this.btnReadTag.TabStop = false;
            this.btnReadTag.Text = "Read Tag(F9)";
            this.btnReadTag.UseVisualStyleBackColor = true;
            this.btnReadTag.Click += new System.EventHandler(this.btnReadTag_Click);
            // 
            // chkIsEncrypt
            // 
            this.chkIsEncrypt.AutoSize = true;
            this.chkIsEncrypt.Location = new System.Drawing.Point(671, 20);
            this.chkIsEncrypt.Name = "chkIsEncrypt";
            this.chkIsEncrypt.Size = new System.Drawing.Size(101, 21);
            this.chkIsEncrypt.TabIndex = 3;
            this.chkIsEncrypt.TabStop = false;
            this.chkIsEncrypt.Text = "Auto Encrypt";
            this.chkIsEncrypt.UseVisualStyleBackColor = true;
            this.chkIsEncrypt.Visible = false;
            this.chkIsEncrypt.CheckedChanged += new System.EventHandler(this.chkIsEncrypt_CheckedChanged);
            // 
            // chkAdd
            // 
            this.chkAdd.AutoSize = true;
            this.chkAdd.Location = new System.Drawing.Point(442, 20);
            this.chkAdd.Name = "chkAdd";
            this.chkAdd.Size = new System.Drawing.Size(93, 21);
            this.chkAdd.TabIndex = 2;
            this.chkAdd.TabStop = false;
            this.chkAdd.Text = "Auto Add 1";
            this.chkAdd.UseVisualStyleBackColor = true;
            this.chkAdd.CheckedChanged += new System.EventHandler(this.chkAdd_CheckedChanged);
            // 
            // utxtCardHex
            // 
            this.utxtCardHex.ErrorInvalid = false;
            this.utxtCardHex.InputChar = '0';
            this.utxtCardHex.InputMask = "HH-HH-HH-HH";
            this.utxtCardHex.Location = new System.Drawing.Point(280, 132);
            this.utxtCardHex.MaxLength = 11;
            this.utxtCardHex.Name = "utxtCardHex";
            this.utxtCardHex.Size = new System.Drawing.Size(120, 23);
            this.utxtCardHex.StdInputMask = ADSDK.Bases.Components.FormatTextBox.InputMaskType.Custom;
            this.utxtCardHex.TabIndex = 7;
            this.utxtCardHex.TabStop = false;
            this.utxtCardHex.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.utxtCardHex.TextChanged += new System.EventHandler(this.utxtCardHex_TextChanged);
            // 
            // cmbWiegand
            // 
            this.cmbWiegand.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbWiegand.FormattingEnabled = true;
            this.cmbWiegand.Items.AddRange(new object[] {
            "Wiegand26",
            "Wiegand34"});
            this.cmbWiegand.Location = new System.Drawing.Point(140, 18);
            this.cmbWiegand.Name = "cmbWiegand";
            this.cmbWiegand.Size = new System.Drawing.Size(95, 25);
            this.cmbWiegand.TabIndex = 0;
            this.cmbWiegand.TabStop = false;
            this.cmbWiegand.SelectedIndexChanged += new System.EventHandler(this.cmbWiegand_SelectedIndexChanged);
            // 
            // ltxtCardDecimal
            // 
            this.ltxtCardDecimal.IntText = 0;
            this.ltxtCardDecimal.LimitText = "1234567890";
            this.ltxtCardDecimal.Location = new System.Drawing.Point(140, 132);
            this.ltxtCardDecimal.MaxLength = 10;
            this.ltxtCardDecimal.Name = "ltxtCardDecimal";
            this.ltxtCardDecimal.Size = new System.Drawing.Size(120, 23);
            this.ltxtCardDecimal.TabIndex = 6;
            this.ltxtCardDecimal.TabStop = false;
            this.ltxtCardDecimal.Text = "00";
            this.ltxtCardDecimal.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.ltxtCardDecimal.TextChanged += new System.EventHandler(this.ltxtCardDecimal_TextChanged);
            // 
            // lblWiegand
            // 
            this.lblWiegand.AutoSize = true;
            this.lblWiegand.Location = new System.Drawing.Point(12, 22);
            this.lblWiegand.Name = "lblWiegand";
            this.lblWiegand.Size = new System.Drawing.Size(95, 17);
            this.lblWiegand.TabIndex = 12;
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
            this.cmbPosition.Location = new System.Drawing.Point(368, 18);
            this.cmbPosition.Name = "cmbPosition";
            this.cmbPosition.Size = new System.Drawing.Size(60, 25);
            this.cmbPosition.TabIndex = 1;
            this.cmbPosition.TabStop = false;
            this.cmbPosition.SelectedIndexChanged += new System.EventHandler(this.cmbPosition_SelectedIndexChanged);
            // 
            // lblWriteCardNODec
            // 
            this.lblWriteCardNODec.AutoSize = true;
            this.lblWriteCardNODec.Location = new System.Drawing.Point(137, 112);
            this.lblWriteCardNODec.Name = "lblWriteCardNODec";
            this.lblWriteCardNODec.Size = new System.Drawing.Size(99, 17);
            this.lblWriteCardNODec.TabIndex = 16;
            this.lblWriteCardNODec.Text = "Write No.(DEC):";
            // 
            // lblPosition
            // 
            this.lblPosition.AutoSize = true;
            this.lblPosition.Location = new System.Drawing.Point(262, 22);
            this.lblPosition.Name = "lblPosition";
            this.lblPosition.Size = new System.Drawing.Size(57, 17);
            this.lblPosition.TabIndex = 13;
            this.lblPosition.Text = "Position:";
            // 
            // lblWriteCardNOHex
            // 
            this.lblWriteCardNOHex.AutoSize = true;
            this.lblWriteCardNOHex.Location = new System.Drawing.Point(277, 112);
            this.lblWriteCardNOHex.Name = "lblWriteCardNOHex";
            this.lblWriteCardNOHex.Size = new System.Drawing.Size(99, 17);
            this.lblWriteCardNOHex.TabIndex = 17;
            this.lblWriteCardNOHex.Text = "Write No.(HEX):";
            // 
            // lblWriteCard
            // 
            this.lblWriteCard.AutoSize = true;
            this.lblWriteCard.Location = new System.Drawing.Point(12, 82);
            this.lblWriteCard.Name = "lblWriteCard";
            this.lblWriteCard.Size = new System.Drawing.Size(64, 17);
            this.lblWriteCard.TabIndex = 15;
            this.lblWriteCard.Text = "Write No:";
            // 
            // txtWriteCard
            // 
            this.txtWriteCard.Location = new System.Drawing.Point(140, 79);
            this.txtWriteCard.Name = "txtWriteCard";
            this.txtWriteCard.ReadOnly = true;
            this.txtWriteCard.Size = new System.Drawing.Size(480, 23);
            this.txtWriteCard.TabIndex = 5;
            this.txtWriteCard.TabStop = false;
            // 
            // lblWriteState
            // 
            this.lblWriteState.AutoSize = true;
            this.lblWriteState.Location = new System.Drawing.Point(634, 82);
            this.lblWriteState.Name = "lblWriteState";
            this.lblWriteState.Size = new System.Drawing.Size(15, 17);
            this.lblWriteState.TabIndex = 19;
            this.lblWriteState.Text = "1";
            // 
            // lblReadState
            // 
            this.lblReadState.AutoSize = true;
            this.lblReadState.Location = new System.Drawing.Point(634, 52);
            this.lblReadState.Name = "lblReadState";
            this.lblReadState.Size = new System.Drawing.Size(15, 17);
            this.lblReadState.TabIndex = 18;
            this.lblReadState.Text = "1";
            // 
            // lblReadCard
            // 
            this.lblReadCard.AutoSize = true;
            this.lblReadCard.Location = new System.Drawing.Point(12, 52);
            this.lblReadCard.Name = "lblReadCard";
            this.lblReadCard.Size = new System.Drawing.Size(63, 17);
            this.lblReadCard.TabIndex = 14;
            this.lblReadCard.Text = "Read No:";
            // 
            // txtReadCard
            // 
            this.txtReadCard.Location = new System.Drawing.Point(140, 49);
            this.txtReadCard.Name = "txtReadCard";
            this.txtReadCard.ReadOnly = true;
            this.txtReadCard.Size = new System.Drawing.Size(480, 23);
            this.txtReadCard.TabIndex = 4;
            this.txtReadCard.TabStop = false;
            // 
            // lblWriteCardNO
            // 
            this.lblWriteCardNO.AutoSize = true;
            this.lblWriteCardNO.Location = new System.Drawing.Point(12, 135);
            this.lblWriteCardNO.Name = "lblWriteCardNO";
            this.lblWriteCardNO.Size = new System.Drawing.Size(67, 17);
            this.lblWriteCardNO.TabIndex = 24;
            this.lblWriteCardNO.Text = "Write No.:";
            // 
            // ucPWriteEPC
            // 
            this.Controls.Add(this.grbQuickWrite);
            this.Controls.Add(this.grbWrite);
            this.Controls.Add(this.grbRead);
            this.Controls.Add(this.grbIdentify);
            this.Font = new System.Drawing.Font("微软雅黑", 9F);
            this.Name = "ucPWriteEPC";
            this.Size = new System.Drawing.Size(990, 438);
            this.TitleVisable = false;
            this.Controls.SetChildIndex(this.grbIdentify, 0);
            this.Controls.SetChildIndex(this.grbRead, 0);
            this.Controls.SetChildIndex(this.grbWrite, 0);
            this.Controls.SetChildIndex(this.grbQuickWrite, 0);
            this.grbWrite.ResumeLayout(false);
            this.grbWrite.PerformLayout();
            this.grbRead.ResumeLayout(false);
            this.grbRead.PerformLayout();
            this.grbIdentify.ResumeLayout(false);
            this.grbIdentify.PerformLayout();
            this.grbQuickWrite.ResumeLayout(false);
            this.grbQuickWrite.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnWrite;
        private System.Windows.Forms.Button btnRead;
        private System.Windows.Forms.Button btnIdentify;
        private System.Windows.Forms.GroupBox grbWrite;
        private System.Windows.Forms.ComboBox cmbWriteBlock;
        private System.Windows.Forms.Label lblWriteBlock;
        private System.Windows.Forms.Label lblWriteMark;
        private System.Windows.Forms.Label lblWriteAddress;
        private System.Windows.Forms.Label lblWriteLength;
        private System.Windows.Forms.Label lblWriteData;
        private System.Windows.Forms.GroupBox grbRead;
        private System.Windows.Forms.ComboBox cmbReadBlock;
        private System.Windows.Forms.Label lblReadBlock;
        private System.Windows.Forms.Label lblReadMark;
        private System.Windows.Forms.Label lblReadAddress;
        private System.Windows.Forms.Label lblReadData;
        private System.Windows.Forms.Label lblReadLength;
        private System.Windows.Forms.GroupBox grbIdentify;
        private System.Windows.Forms.Label lblCard;
        private ADSDK.Bases.Components.FormatTextBox utxtWriteData;
        private ADSDK.Bases.Components.LimitTextBox ltxtWriteLength;
        private ADSDK.Bases.Components.LimitTextBox ltxtWriteAddress;
        private ADSDK.Bases.Components.LimitTextBox ltxtReadAddress;
        private ADSDK.Bases.Components.LimitTextBox ltxtReadLength;
        private ADSDK.Bases.Components.FormatTextBox utxtReadData;
        private ADSDK.Bases.Components.FormatTextBox utxtCard;
        private System.Windows.Forms.GroupBox grbQuickWrite;
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
        private System.Windows.Forms.Button btnAdd;
        private System.Windows.Forms.Button btnDec;
        private System.Windows.Forms.Button btnWriteTag;
        private System.Windows.Forms.Button btnReadTag;
        private System.Windows.Forms.Label lblEncryptState;
        private System.Windows.Forms.CheckBox chkAddHex;
        private System.Windows.Forms.Button btnWriteAscii;
        private System.Windows.Forms.TextBox txtWriteAscii;
        private System.Windows.Forms.Label label1;
        private ADSDK.Bases.Components.FormatTextBox utxtCardWg;
        private System.Windows.Forms.Label lblWriteCardNOWG;
        private System.Windows.Forms.Label lblWriteCardNO;

    }
}
