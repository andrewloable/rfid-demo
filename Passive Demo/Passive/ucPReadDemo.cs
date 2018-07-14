using ADSDK.Bases;
using ADSDK.Bases.Controls;
using ADSDK.Device;
using ADSDK.Device.Reader;
using ADSDK.Device.Reader.Passive;
using ADSDK.Sets;
using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Ports;
using System.Text;
using System.Windows.Forms;

namespace Aosid
{
    public partial class ucPReadDemo : BaseControl
    {
        bool IsStart = false;
        public ucPReadDemo()
        {
            InitializeComponent();
        }

        public override void ChangeLanguage()
        {
            try
            {

                string[] m_def_en = new string[] {  "Clear",
                                                    "Upload",
                                                    "Export",
                                                    "Stop Read",
                                                    "Start Read"};

                string[] m_def_cn = new string[] {"清除","上传","导出","停止读卡","启动读卡"};

                string[] m_def_tw = new string[] { "清除", "上傳", "導出", "停止讀卡", "啟動讀卡" };

                string[] MainValue = BaseSettings.LoadLanguage(@"passive/readdemo", m_def_en, m_def_cn, m_def_tw);
                int index = 0;

                btnClear.Text = MainValue[index++] + "(&C)";
                btnUpLoad.Text = MainValue[index++] + "(&U)";
                btnExport.Text = MainValue[index++] + "(&E)";
                if (IsStart)
                {
                    btnStart.Text = MainValue[index++] + "(&S)";
                    index++;
                }
                else
                {
                    index++;
                    btnStart.Text = MainValue[index++] + "(&S)";
                }

            }
            catch { }

            cdgvShow.ChangeLanguage();
        }

        public override void PassOnKeys(object sender, KeyEventArgs e)
        {
            base.PassOnKeys(sender, e);
        }

        public override void ControlLoad(object sender, EventArgs e)
        {
            base.ControlLoad(sender, e);
        }

        private void ucReadDemo_Leave(object sender, EventArgs e)
        {
            if (IsStart)
                btnStart_Click(sender, e);
        }

        private void ucReadDemo_Enter(object sender, EventArgs e)
        {
            ChangeLanguage();
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            IsStart = !IsStart;
            ChangeLanguage();
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            cdgvShow.Clear();
        }

        private void btnUpLoad_Click(object sender, EventArgs e)
        {
            SerialPort spUpload = new SerialPort("COM3", 9600);
            try
            {
                StringBuilder strbuf = new StringBuilder();
                spUpload.Open();
                foreach (DataGridViewRow lvi in cdgvShow.View.Rows)
                {
                    strbuf.Append(lvi.Cells["colHexCard"].ToString().Substring(0, 13));
                }
                byte[] bytTemp = System.Text.Encoding.Default.GetBytes(strbuf.ToString());
                byte[] bytSend = new byte[bytTemp.Length * 2 + 2];
                for (int i = 0; i < bytTemp.Length; i++)
                {
                    bytSend[(i + 1) * 2 - 1] = bytTemp[i];
                }
                bytSend[bytSend.Length - 2] = 0x0d;
                spUpload.Write(bytSend, 0, bytSend.Length);
                btnClear_Click(sender, e);
            }
            catch { }
            if (spUpload.IsOpen) spUpload.Close();
        }

        private void btnExport_Click(object sender, EventArgs e)
        {
            try
            {
                string path = Application.StartupPath + "\\Data";
                if (!Directory.Exists(path))
                {
                    Directory.CreateDirectory(path);
                }
                StreamWriter sw = new StreamWriter(path + @"\outdata.txt",true);
               
                foreach (DataGridViewRow lvi in cdgvShow.View.Rows)
                {
                    string strbuf = lvi.Cells["colHexCard"].Value.ToString();
                    sw.WriteLine(strbuf); sw.Flush();
                }
                sw.Close();
                sw = null;
            }
            catch { }
            MessageBox.Show("Save OK!");
        }
        public void ParseRsp(ProtocolStruct Data)
        {
            switch (Data.Code)
            {
                case PassiveRcp.RCP_CMD_EPC_MULT:
                case PassiveRcp.RCP_CMD_EPC_IDEN:
                case PassiveRcp.RCP_CMD_ISO6B_IDEN:
                    if (Data.Length > 0 &&( Data.Type == 0 ||Data.Type == 0x32))
                    {
                        List<CardParameters> tempArray = new List<CardParameters>();
                        List<byte> bytTempArray = new List<byte>(Data.ToArray());
                        if (PDataManage.InputManage(ref bytTempArray, ref tempArray))
                        {
                            cdgvShow.Add(tempArray);
                        }
                    }
                    break;
                case 0x22:
                    Data.Code = 0x10;
                    Data.Type = 0x32;
                      List<CardParameters> tempArray2 = new List<CardParameters>();
                        List<byte> bytTempArray2 = new List<byte>(Data.ToArray());
                        if (PDataManage.InputManage(ref bytTempArray2, ref tempArray2))
                        {
                            cdgvShow.Add(tempArray2);
                        }
                    break;
            }
        }

        private void tmrClock_Tick(object sender, EventArgs e)
        {
            if(SystemPub.ADRcp.CommMode == ADSDK.Device.CommMode.ACTIVE)
            {
                if (btnStart.Visible) btnStart.Visible = false;
            }
            else
            {
                if (!btnStart.Visible) btnStart.Visible = true;
            }

            if(IsStart)
            {
                if (UserSettings.Communication == UserSettings.CommType.USB)
                {
                    if (!SystemPub.ADRcp.SendBytePkt(PassiveRcp.Identify6C(SystemPub.ADRcp.Address))) { }
                }
                else
                {
                    if (!SystemPub.ADRcp.SendBytePkt(PassiveRcp.Identify6CMult(SystemPub.ADRcp.Address))) { }
                }
            }
        }
    }
}
