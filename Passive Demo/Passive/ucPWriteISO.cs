using ADSDK.Bases;
using ADSDK.Bases.Controls;
using ADSDK.Device;
using ADSDK.Device.Reader.Passive;
using System;
using System.Windows.Forms;

namespace Aosid
{
    public partial class ucPWriteISO : BaseControl
    {
        public ucPWriteISO()
        {
            InitializeComponent();
        }
        public override void ChangeLanguage()
        {
            try
            {

                string[] m_def_en = new string[] {  "ISO18000-6B Read",
                                                    "Address:","Length:","(Length not more 64)","Data:",
                                                    "ISO18000-6B Write",
                                                    "Address:","Length:","(Address start 18,Length not more 64)","Data:",
                                                    "ISO18000-6B Identify","Card No:", "Identify","Read","Write"
                                                };

                string[] m_def_cn = new string[] { "ISO18000-6B 读数据区", "地址:", "长度:", "(长度不大于64)", "数据:", "ISO18000-6B 写数据区", "地址:", "长度:", "(写地址从18开始,长度不大于64)", "数据:", "ISO18000-6B 卡号识别区", "卡号:", "识别", "读卡", "写卡" };

                string[] m_def_tw = new string[] { "ISO18000-6B 讀數據區", "地址:", "長度:", "(長度不大于64)", "數據:", "ISO18000-6B 寫數據區", "地址:", "長度:", "(寫地址從18開始.長度不能大于64)", "數據:", "ISO18000-6B 卡號識別區", "卡號:", "識別", "讀卡", "寫卡" };

                string[] MainValue = BaseSettings.LoadLanguage(@"passive/iso6b", m_def_en, m_def_cn, m_def_tw);
                int index = 0;

                grbRead.Text = MainValue[index++];
                lblReadAddress.Text = MainValue[index++];
                lblReadLength.Text = MainValue[index++];
                lblReadMark.Text = MainValue[index++];
                lblReadData.Text = MainValue[index++];

                grbWrite.Text = MainValue[index++];
                lblWriteAddress.Text = MainValue[index++];
                lblWriteLength.Text = MainValue[index++];
                lblWriteMark.Text = MainValue[index++];
                lblWriteData.Text = MainValue[index++];

                grbIdentify.Text = MainValue[index++];
                lblCard.Text = MainValue[index++];

                btnIdentify.Text = MainValue[index++] + "(&E)";
                btnRead.Text = MainValue[index++] + "(&A)";
                btnWrite.Text = MainValue[index++] + "(&R)";
            }
            catch { }
        }

        public override void ControlLoad(object sender, EventArgs e)
        {
            base.ControlLoad(sender, e);
           // ConvertControl.SetBtnStyle(btnIdentify,Color.Black,Color.Blue);
        }
        private void ltxtReadLength_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (Convert.ToInt32(ltxtReadLength.Text) < 1)
                {
                    ltxtReadLength.Text = "1";
                }
                else if (Convert.ToInt32(ltxtReadLength.Text) > 64)
                {
                    ltxtReadLength.Text = "64";
                }
            }
            catch { }
        }
        private void ltxtWriteLength_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (Convert.ToInt32(ltxtWriteLength.Text) > 0 && Convert.ToInt32(ltxtWriteLength.Text) <= 64)
                {
                    string strMessage = utxtWriteData.Value;
                    utxtWriteData.InputMask = GetUserTextBoxMask(Convert.ToInt32(ltxtWriteLength.Text));
                }
                else if (Convert.ToInt32(ltxtWriteLength.Text) > 12)
                {
                    ltxtWriteLength.Text = "64";
                }
                else
                {
                    ltxtWriteLength.Text = "2";
                }
            }
            catch { }
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
            if (!SystemPub.ADRcp.SendBytePkt(PassiveRcp.Identify6B(SystemPub.ADRcp.Address))) { }

            btnIdentify.Enabled = true;
        }
        private void btnRead_Click(object sender, EventArgs e)
        {
            btnRead.Enabled = false;
            utxtReadData.Value = "";
            Application.DoEvents();

            byte state = Convert.ToByte(ltxtReadAddress.Text);
            byte len = Convert.ToByte(ltxtReadLength.Text);
            if (!SystemPub.ADRcp.SendBytePkt(PassiveRcp.Read6B(SystemPub.ADRcp.Address, state, len))) { }

            btnRead.Enabled = true;
        }
        private void btnWrite_Click(object sender, EventArgs e)
        {
            btnWrite.Enabled = false;

            byte state = Convert.ToByte(ltxtWriteAddress.Text);
            byte len = Convert.ToByte(ltxtWriteLength.Text);
            byte[] sndData = ConvertData.HexStringToByteArray(utxtWriteData.Text.Replace("-", ""));

            if (!SystemPub.ADRcp.SendBytePkt(PassiveRcp.Write6B(SystemPub.ADRcp.Address, state, len, sndData))) { }

            btnWrite.Enabled = true;
        }
        public void ParseRsp(ProtocolStruct Data)
        {
            switch (Data.Code)
            {
                case PassiveRcp.RCP_CMD_ISO6B_IDEN:
                    if (Data.Length > 0 && Data.Type == 0)
                    {
                        utxtCard.InputMask = GetUserTextBoxMask(Convert.ToInt32(Data.Length - 1));
                        utxtCard.Value = ConvertData.ByteArrayToHexString(Data.Payload, 1, Data.Length - 1);
                    }
                    break;
                case PassiveRcp.RCP_CMD_ISO6B_RW:
                    if (Data.Length > 0 && Data.Type == 0)
                    {
                        utxtReadData.InputMask = GetUserTextBoxMask(Data.Length - 1);
                        utxtReadData.Value = ConvertData.ByteArrayToHexString(Data.Payload, 1, Data.Length - 1);
                    }
                    break;
            }
        }
    }
}
