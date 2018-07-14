using ADSDK.Bases;
using ADSDK.Bases.Controls;
using ADSDK.Device;
using ADSDK.Device.Reader.Passive;
using ADSDK.Sets;
using System;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Aosid
{
    public partial class ucPWriteEPC : BaseControl
    {
        public enum WRITETYPE
        {
            DATA,
            CARD
        }

        public WRITETYPE ActionType = WRITETYPE.DATA;

        public ucPWriteEPC()
        {
            InitializeComponent();

            cmbReadBlock.SelectedIndex = 1;
            cmbWriteBlock.SelectedIndex = 1;
            lblWriteState.Text = lblReadState.Text = lblEncryptState.Text = "";
            LoadQuickWritePara();
        }

        public override void ChangeLanguage()
        {

            try
            {

                string[] m_def_en = new string[] {  "EPC(GEN 2) Read",
                                                    "Block:", "Address:","Length:","(Length not more 16)","Data:",
                                                    "EPC(GEN 2) Write",
                                                    "Block:", "Address:","Length:","(Length not more 16)","Data:",
                                                    "EPC(GEN 2) Identify","Card No:", 
                                                    "Identify","Read","Write",

                                                    "Quick Write Card Zone(Weigand Card)Max 4 Byte",
                                                    "Card Type:","Card Position:","Auto Add 1","Auto Encrypt",
                                                    "EPC(GEN 2)Write Card",
                                                    "Current Read Num:","Be Written Num:","Write Num:","Dec","Hex","WG",
                                                    "Read Tag","Write Tag","Decrease 1","Add 1",
                                                    "Auto Hex"
                };

                string[] m_def_cn = new string[] { "EPC(GEN 2) 读数据区", "分区选择:", "地址:", "长度:", "(长度不大于16)", "数据:", "EPC(GEN 2) 写数据区", "分区选择:", "地址:", "长度:", "(长度不大于16)", "数据:", "EPC(GEN 2) 卡号识别区", "卡号:", "识别", "读卡", "写卡", "快速写卡区(韦根卡号)最大4字节", "卡号类型:", "写入位置:", "是否自动加1", "是否自动加密", "EPC(GEN 2)写卡", "当前读取卡号:", "已写入卡号:", "待写入卡号:", "十进制", "十六进制", "韦根8位", "读取卡号", "写入卡号", "卡号减 1", "卡号加 1", "是否16进制自加" };

                string[] m_def_tw = new string[] { "EPC(GEN 2) 讀數據區", "分區選擇:", "地址:", "長度:", "(長度不大于16)", "數據:", "EPC(GEN 2) 寫數據區", "分區選擇:", "地址:", "長度:", "(長度不大于16)", "數據:", "EPC(GEN 2) 卡號識別區", "卡號:", "識別", "讀卡", "寫卡", "快速寫卡區(維根卡號)最大4字節", "卡號類型:", "寫入位置:", "是否自動加1", "是否自動加密", "EPC(GEN 2)寫卡", "當前讀取卡號:", "己寫入卡號:", "待寫入卡號:", "十進制", "十六進制", "維根8位", "讀取卡號", "寫入卡號", "卡號减 1", "卡號加 1", "是否16進制自加" };

                string[] MainValue = BaseSettings.LoadLanguage(@"passive/iso6c", m_def_en, m_def_cn, m_def_tw);
                int index = 0;

                grbRead.Text = MainValue[index++];
                lblReadBlock.Text = MainValue[index++];
                lblReadAddress.Text = MainValue[index++];
                lblReadLength.Text = MainValue[index++];
                lblReadMark.Text = MainValue[index++];
                lblReadData.Text = MainValue[index++];

                grbWrite.Text = MainValue[index++];
                lblWriteBlock.Text = MainValue[index++];
                lblWriteAddress.Text = MainValue[index++];
                lblWriteLength.Text = MainValue[index++];
                lblWriteMark.Text = MainValue[index++];
                lblWriteData.Text = MainValue[index++];

                grbIdentify.Text = MainValue[index++];
                lblCard.Text = MainValue[index++];


                btnIdentify.Text = MainValue[index++] + "(&E)";
                btnRead.Text = MainValue[index++] + "(&A)";
                btnWrite.Text = MainValue[index++] + "(&R)";

                #region ---Quick Write card---
                grbQuickWrite.Text = MainValue[index++];
                lblWiegand.Text = MainValue[index++];
                lblPosition.Text = MainValue[index++];
                chkAdd.Text = MainValue[index++];
                chkIsEncrypt.Text = MainValue[index++];

                grbWrite.Text = MainValue[index++];
                lblReadCard.Text = MainValue[index++];
                lblWriteCard.Text = MainValue[index++];

                lblWriteCardNO.Text = MainValue[index++];
                lblWriteCardNODec.Text = MainValue[index++];
                lblWriteCardNOHex.Text = MainValue[index++];
                lblWriteCardNOWG.Text = MainValue[index++];

                btnReadTag.Text = MainValue[index++] + "(F9)";
                btnWriteTag.Text = MainValue[index++] + "(F12)";
                btnDec.Text = MainValue[index++];
                btnAdd.Text = MainValue[index++];

                chkAddHex.Text = MainValue[index++];
                #endregion
            }
            catch { }
        }

        static int encryptCount = 0;
        public override void PassOnKeys(object sender, KeyEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.F8:
                    if (chkIsEncrypt.Checked)
                    {
                        SecretCard();
                    }
                    else
                    {
                        encryptCount++;
                        if (encryptCount > 4)
                        {
                            encryptCount = 0;
                            if (!grbQuickWrite.Visible) { grbQuickWrite.Visible = true; return; }
                            if (!chkIsEncrypt.Visible) { chkIsEncrypt.Visible = true; return; }
                        }
                    }
                    break;
                case Keys.F9:
                    if (grbQuickWrite.Visible && btnReadTag.Enabled)
                        btnReadTag_Click(sender, e);
                    break;
                case Keys.F12:
                    if (grbQuickWrite.Visible && btnWriteTag.Enabled)
                        btnWriteTag_Click(sender, e);
                    break;
            }
        }
        public override void ControlLoad(object sender, EventArgs e)
        {
            base.ControlLoad(sender, e);
        }
        private void ltxtWriteLength_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (Convert.ToInt32(ltxtWriteLength.Text) > 0 && Convert.ToInt32(ltxtWriteLength.Text) <= 16)
                {
                    string strMessage = utxtWriteData.Value;
                    utxtWriteData.InputMask = GetUserTextBoxMask(Convert.ToInt32(ltxtWriteLength.Text));
                }
                else if (Convert.ToInt32(ltxtWriteLength.Text) > 16)
                {
                    ltxtWriteLength.Text = "16";
                }
                else
                {
                    ltxtWriteLength.Text = "2";
                }
            }
            catch { }
        }
        private void ltxtReadLength_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (Convert.ToInt32(ltxtReadLength.Text) < 1)
                {
                    ltxtReadLength.Text = "1";
                }
                //else if (Convert.ToInt32(ltxtReadLength.Text) > 16)
                //{
                //    ltxtReadLength.Text = "16";
                //}
            }
            catch { }
        }
        private void cmbReadBlock_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cmbReadBlock.SelectedIndex == 1) ltxtReadAddress.IntText = 2;
        }
        private void cmbWriteBlock_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cmbWriteBlock.SelectedIndex == 1) ltxtWriteAddress.IntText = 2;
        }
        private string GetUserTextBoxMask(int count)
        {
            string strMask = "";
            if (count > 0)
            {
                strMask = "HH";
                for (int i = 0; i < count - 1; i++)
                {
                    strMask += "-HH";
                }
            }
            return strMask;
        }
        private void btnIdentify_Click(object sender, EventArgs e)
        {
            btnIdentify.Enabled = false;
            utxtCard.Value = "";
            Application.DoEvents();
            if (!SystemPub.ADRcp.SendBytePkt(PassiveRcp.Identify6C(SystemPub.ADRcp.Address))) { }

            btnIdentify.Enabled = true;
        }
        private void btnRead_Click(object sender, EventArgs e)
        {
            ActionType = WRITETYPE.DATA;
            btnRead.Enabled = false;
            utxtReadData.Value = "";
            Application.DoEvents();
            byte mem = Convert.ToByte(cmbReadBlock.SelectedIndex);
            byte state = Convert.ToByte(ltxtReadAddress.Text);
            byte len = Convert.ToByte(ltxtReadLength.Text);

            if (!SystemPub.ADRcp.SendBytePkt(PassiveRcp.Read6C(SystemPub.ADRcp.Address, mem, state, len))) { }
            btnRead.Enabled = true;
        }
        private void btnWrite_Click(object sender, EventArgs e)
        {
            ActionType = WRITETYPE.DATA;
            btnWrite.Enabled = false;

            byte mem = Convert.ToByte(cmbWriteBlock.SelectedIndex);
            byte state = Convert.ToByte(ltxtWriteAddress.Text);
            byte len = Convert.ToByte(ltxtWriteLength.Text);
            byte[] sndData = ConvertData.HexStringToByteArray(utxtWriteData.Text.Replace("-", ""));

            if (!SystemPub.ADRcp.SendBytePkt(PassiveRcp.Write6C(SystemPub.ADRcp.Address, mem, state, len, sndData))) { }

            btnWrite.Enabled = true;
        }
        public void ParseRsp(ProtocolStruct Data)
        {
            switch (Data.Code)
            {
                case PassiveRcp.RCP_CMD_EPC_IDEN:
                    if (Data.Length > 0 && Data.Type == 0)
                    {
                        utxtCard.InputMask = GetUserTextBoxMask(Convert.ToInt32(Data.Length - 1));
                        utxtCard.Value = ConvertData.ByteArrayToHexString(Data.Payload, 1, Data.Length - 1);

                    }
                    break;
                case PassiveRcp.RCP_CMD_EPC_RW:
                    if (Data.Length > 0 && Data.Type == 0)
                    {
                        if (ActionType == WRITETYPE.CARD)
                        {
                            GetCard(Data.Payload);
                        }
                        else
                        {
                            utxtReadData.InputMask = GetUserTextBoxMask(Data.Length - 1);
                            utxtReadData.Value = ConvertData.ByteArrayToHexString(Data.Payload, 1, Data.Length - 1);
                        }
                    }
                    else if (Data.Type == 0)
                    {
                        if (ActionType == WRITETYPE.CARD)
                        {
                            LngSendDataP = LngSendData;
                            txtWriteCard.Text = String.Format("{0} [HEX: {1} ]", ShowCard(LngSendDataP, false), ShowCard(LngSendDataP, true));
                            ShowState("写成功!", "Write Succeed!", lblWriteState, true);
                            ReadCard();
                        }
                    }
                    break;
                case PassiveRcp.RCP_CMD_SECRET:
                    if (Data.Type == 0)
                    {
                        ShowState("加密成功!", "Encrypt Succeed!", lblEncryptState, true);
                    }
                    else
                    {
                        ShowState("加密失败,按F8重新加密!", "Encrypt fail,press F8 to encrypt again!", lblEncryptState, false);
                    }
                    break;
            }
        }

        #region ---Quick Write Card----
        private void cmbWiegand_SelectedIndexChanged(object sender, EventArgs e)
        {
            blnChangeFlag = true;
            UserSettings.WriteMode = cmbWiegand.SelectedIndex;
            utxtCardHex.InputMask = UserSettings.WriteMode > 0 ? "HH-HH-HH-HH" : "HH-HH-HH";
            utxtCardWg.InputMask = UserSettings.WriteMode > 0 ? "00000,00000" : "000,00000";
            RefrashCard();
            blnChangeFlag = false;

        }

        private void cmbPosition_SelectedIndexChanged(object sender, EventArgs e)
        {
            UserSettings.WritePosition = cmbPosition.SelectedIndex;
        }

        private void chkAdd_CheckedChanged(object sender, EventArgs e)
        {
            UserSettings.WriteAutoAdd = chkAdd.Checked;
        }
        private void chkIsEncrypt_CheckedChanged(object sender, EventArgs e)
        {
            lblEncryptState.Text = "";
        }

        private void ltxtCardDecimal_TextChanged(object sender, EventArgs e)
        {
            if (!blnChangeFlag)
            {
                blnChangeFlag = true;
                LngSendData = ConvertData.DecStringToDecLong(ltxtCardDecimal.Text.Trim(), UserSettings.WriteMode>0);

                RefrashCard();
                blnChangeFlag = false;
            }
        }

        private void utxtCardHex_TextChanged(object sender, EventArgs e)
        {
            if (!blnChangeFlag)
            {
                blnChangeFlag = true;
                if(chkAddHex.Checked)
                    LngSendData = Convert.ToInt32(utxtCardHex.Text.Replace("-", ""));
                else
                    LngSendData = ConvertData.HexStringToDecLong(utxtCardHex.Text.Replace("-", ""), UserSettings.WriteMode > 0);

                RefrashCard();
                blnChangeFlag = false;
            }
        }

        private void utxtCardWg_TextChanged(object sender, EventArgs e)
        {
            if (!blnChangeFlag)
            {
                blnChangeFlag = true;
                string[] str = utxtCardWg.Text.Trim().Split(',');
                long lngfirst = Convert.ToInt64(str[0]);
                long lngsecond = Convert.ToInt64(str[1]);
                if (lngfirst > (UserSettings.WriteMode > 0 ? 65535 : 255)) lngfirst = (UserSettings.WriteMode > 0 ? 65535 : 255);
                if (lngsecond > 65535) lngsecond = 65535;
                LngSendData = lngfirst * 65536 + lngsecond;
                RefrashCard();
                blnChangeFlag = false;
            }
        }

        private void btnAdd_Click(object sender, EventArgs e)
        {
            LngSendData += 1;
            RefrashCard();
        }

        private void btnDec_Click(object sender, EventArgs e)
        {
            LngSendData -= 1;
            RefrashCard();
        }

        private void btnReadTag_Click(object sender, EventArgs e)
        {
            btnReadTag.Enabled = false;
            txtReadCard.Text = "";
            ShowState("", "", lblReadState, true);
            CheckCardPara();

            ReadCard();

            btnReadTag.Enabled = true;
        }

        private void btnWriteTag_Click(object sender, EventArgs e)
        {
            btnWriteTag.Enabled = false;
            txtWriteCard.Text = "";
            ShowState("", "", lblReadState, true);
            ShowState("", "", lblWriteState, true);
            CheckCardPara();

            WriteCard();

            btnWriteTag.Enabled = true;
        }

        int intAddr = 2;
        int intlen = 4;
        int intpoint = 0;

        private void LoadQuickWritePara()
        {
            cmbWiegand.SelectedIndex = UserSettings.WriteMode;
            cmbPosition.SelectedIndex = UserSettings.WritePosition;
            chkAdd.Checked = UserSettings.WriteAutoAdd;
           // LngSendData = ConvertData.HexStringToDecLong(UserSettings.WriteCard.Replace("-", ""), UserSettings.WriteMode > 0);
            try
            {
                LngSendData = Convert.ToInt32(UserSettings.WriteCard);
            }
            catch { }
            RefrashCard();
        }

        private void CheckCardPara()
        {
            int intPosition = Convert.ToInt32(cmbPosition.Text);
            intAddr = 2;
            if (intPosition >= 0)
            {
                intAddr = intPosition / 2 + 2;
            }
            else
            {
                intAddr = 2 - (Math.Abs(intPosition % 2) + Math.Abs(intPosition / 2));
            }

            intlen = 4;
            intpoint = Math.Abs(intPosition % 2);

            if (UserSettings.WriteMode > 0)
            {
                if (intpoint == 1) intlen = 6;
            }
        }
        /// <summary>
        /// Whether can be Auto Change Data
        /// </summary>
        bool blnChangeFlag = false;
        /// <summary>
        /// Standby Send Data
        /// </summary>
        long LngSendData = 0;
        /// <summary>
        /// Already Send Data
        /// </summary>
        long LngSendDataP = 0;
        /// <summary>
        /// Recv Data
        /// </summary>
        long LngRecvData = 0;

        public string ShowCard(long Card, bool isHex)
        {
            if (isHex)
            {
                if (chkAddHex.Checked)
                {
                    if (UserSettings.WriteMode > 0)
                        return Card.ToString("00000000");
                    else
                        return Card.ToString("000000");
                }
                else
                {
                    return ConvertData.DecLongToHexString(Card, UserSettings.WriteMode > 0);
                }
            }
            else
            {
                return ConvertData.DecLongToDecString(Card);
            }
        }

        private void ShowState(string messageCH, string messageEN, Label label, bool flag)
        {
            label.Text = BaseSettings.GetLanguageString(messageEN, messageCH);

            if (flag)
            {
                label.ForeColor = Color.Green;
            }
            else
            {
                label.ForeColor = Color.Red;
            }
            Application.DoEvents();
        }

        private void GetCard(byte[] data)
        {
            if (chkAddHex.Checked)
            {
                LngRecvData = Convert.ToInt32(ConvertData.ByteArrayToHexString(data, 1 + intpoint, (UserSettings.WriteMode > 0?4:3)));
            }
            else
            {
                if (UserSettings.WriteMode > 0)
                {
                    LngRecvData = (long)data[1 + intpoint] << 24;
                    LngRecvData += (long)data[2 + intpoint] << 16;
                    LngRecvData += (long)data[3 + intpoint] << 8;
                    LngRecvData += (long)data[4 + intpoint];
                }
                else
                {
                    LngRecvData = (long)data[1 + intpoint] << 16;
                    LngRecvData += (long)data[2 + intpoint] << 8;
                    LngRecvData += (long)data[3 + intpoint];
                }
            }

            txtReadCard.Text = String.Format("{0} [HEX: {1} ]", ShowCard(LngRecvData, false), ShowCard(LngRecvData, true));

            if (LngRecvData == LngSendDataP)
            {
                //UserSettings.WriteCard = ConvertData.DecLongToHexString(LngSendDataP, UserSettings.WriteMode > 0);
                UserSettings.WriteCard = LngSendDataP.ToString();

                if (chkAdd.Checked)
                {
                    LngSendData = LngSendDataP + 1;
                    RefrashCard();
                }
                if (chkIsEncrypt.Checked)
                {
                    SecretCard();
                }
                ShowState("比对成功!", "Comparison Succeed!", lblReadState, true);
            }
            else
            {
                ShowState("比对失败!", "Comparison Fail!", lblReadState, false);
            }
        }

        private void RefrashCard()
        {
            ltxtCardDecimal.Text = ShowCard(LngSendData, false);
            utxtCardHex.Value = ShowCard(LngSendData, true);

            long lngfirst = LngSendData / 65536;
            long lngsecond = LngSendData % 65536;
            long lngwg = lngfirst * 100000 +lngsecond;
            if (UserSettings.WriteMode > 0)
                utxtCardWg.Value = lngwg.ToString("0000000000");
            else
                utxtCardWg.Value = lngwg.ToString("00000000");

            txtReadCard.Text = String.Format("{0} [HEX: {1} ]", ShowCard(LngRecvData, false), ShowCard(LngRecvData, true));
            txtWriteCard.Text = String.Format("{0} [HEX: {1} ]", ShowCard(LngSendDataP, false), ShowCard(LngSendDataP, true));
        }

        private void SecretCard()
        {
            if (!SystemPub.ADRcp.SendBytePkt(PassiveRcp.SetSecret(SystemPub.ADRcp.Address))) { }
        }

        private void WriteCard()
        {
            ActionType = WRITETYPE.CARD;
            try
            {
                byte[] SendDataBuff = ConvertData.DecLongToByteArray(LngSendData, UserSettings.WriteMode > 0);

                if (chkAddHex.Checked)
                {
                    if (UserSettings.WriteMode > 0)
                        SendDataBuff = ConvertData.HexStringToByteArray(LngSendData.ToString("00000000"));
                    else
                        SendDataBuff = ConvertData.HexStringToByteArray(LngSendData.ToString("000000"));
                }
                else
                {
                    SendDataBuff = ConvertData.DecLongToByteArray(LngSendData, UserSettings.WriteMode > 0);
                }

                byte[] SendData = new byte[intlen];
                for (int i = intpoint; i < intlen; i++)
                {
                    try
                    {
                        SendData[i] = SendDataBuff[i - intpoint];
                    }
                    catch { }
                }

                if (!SystemPub.ADRcp.SendBytePkt(PassiveRcp.Write6C(SystemPub.ADRcp.Address, 1, (byte)intAddr, (byte)intlen, SendData))) { }
            }
            catch { }
        }

        private void ReadCard()
        {
            ActionType = WRITETYPE.CARD;
            if (!SystemPub.ADRcp.SendBytePkt(PassiveRcp.Read6C(SystemPub.ADRcp.Address, 1, (byte)intAddr, (byte)intlen))) { }
        }

        #endregion

        private void chkAddHex_CheckedChanged(object sender, EventArgs e)
        {
            RefrashCard();
        }

        private void btnWriteAscii_Click(object sender, EventArgs e)
        {
            ActionType = WRITETYPE.DATA;
            btnWriteAscii.Enabled = false;

            byte[] bytData = Encoding.GetEncoding("gb2312").GetBytes(txtWriteAscii.Text.Trim());
            byte[] sndData = new byte[12];
            for (int i = 0; i < 8; i++)
            {
                sndData[i] = bytData[i];
            }
            for (int i = 8; i < 12; i++)
            {
                sndData[i] = 0;
            }

            if (!SystemPub.ADRcp.SendBytePkt(PassiveRcp.Write6C(SystemPub.ADRcp.Address, 1, 2, 12, sndData))) { }

            btnWriteAscii.Enabled = true;
        }
    }
}
