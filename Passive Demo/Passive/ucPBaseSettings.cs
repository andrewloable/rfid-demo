using ADSDK.Bases;
using ADSDK.Bases.Controls;
using ADSDK.Device;
using ADSDK.Device.Reader;
using ADSDK.Device.Reader.Passive;
using ADSDK.Sets;
using System;
using System.Windows.Forms;

namespace Aosid
{
    public partial class ucPBaseSettings : BaseControl
    {
        public ucPBaseSettings()
        {
            InitializeComponent();
            LoadInit();
        }

        public override void ChangeLanguage()
        {
            int intSelectItem = 0;

            try
            {

                string[] m_def_en = new string[] {  "Wiegand Parameters Input Zone",
                                                    "Byte Offset:","Pulse Width:","Out Interval:","Pulse Period:",

                                                    "Basic Parameters Input Zone",
                                                    "Work Mode:","Command","Active","Passive",
                                                    "Output Mode:","Read Interval:","Power Size:",
                                                    "Trigger:","Close","Low Trigger",
                                                    "Same ID interval:",
                                                    "Buzzer:","DisEnable","Enabled",
                                                    "Card Type:","ISO18000-6B","EPC(GEN 2)Single-Tag","EPC(GEN 2)Multi-Tag","EPC(GEN 2)Multi-Data","ISO18000-6B + EPC(GEN 2)",

                                                    "Senior Parameters Input Zone",
                                                    "Antenna:","ANT 1","ANT 2","ANT 3","ANT 4",
                                                    "Encrypt authorized:","Do not use unless customized reader!","Encrypt:","DisEnable","Enabled",
                                                    "Password:","Other Memory:","Start Address:","Length:","Max Tags:",
			
                                                    "Freq Parameters Input Zone",
                                                    "Hopping Enabled:","DisEnable","Enabled",
			                                        "China","America","Europe","Fixed Freq:","Hopping Value:",

                                                    "OutPut Parameters Input Zone",
                                                    "Out Type:","Out Len:","Is Key Enter",

                                                    "Get Para","Set Para","Default All"

                };

                string[] m_def_cn = new string[] {"韦根参数输入区","数据偏移:","脉冲宽度:","输出周期:","脉冲周期:","基本参数输入区","工作模式:","应答方式","主动方式","被动方式","通讯模式:","读卡周期:","功率大小:","外部触发方式:","关闭","低电压触发","相同ID输出间隔:","嗡鸣器:","禁止","使能","读卡类别:","ISO18000-6B标签","EPC(GEN 2)单标签","EPC(GEN 2)多标签","EPC(GEN 2)单标签-多区域数据","ISO18000-6B标签 + EPC(GEN 2)标签","高级参数输入区","天线个数:","天线 1","天线 2","天线 3","天线 4","加密授权:","非定制读卡器慎用该功能!","加密使能:","禁止","使能","密码:","其他区域卡号:","起始地址:","长度:","最大读卡数量:","跳频参数输入区","跳频使能:","禁止","使能","中国","美标","欧标","定频值:","跳频值:","输出数据参数输入区","输出类型:","输出长度:","是否带回车符","获取参数","设置参数","默认所有参数" };
                string[] m_def_tw = new string[] { "維根參數輸入區", "數據偏移:", "脈衝寬度:", "輸出周期:", "脈衝周期:", "基本參數輸入區", "工作模式:", "應答方式", "主動方式", "被動方式", "通訊模式:", "讀卡周期:", "功率大小:", "外部觸發方式:", "關閉", "低電壓觸發", "相同ID輸出間隔:", "蜂嗚器:", "禁止", "使用", "讀卡類別:", "ISO18000-6B標簽", "EPC(GEN 2)單標簽", "EPC(GEN 2)多標簽", "EPC(GEN 2)單標簽-多區域數據", "ISO18000-6B標簽 + EPC(GEN 2)標簽", "高級參數輸入區", "天線個數:", "天線 1", "天線 2", "天線 3", "天線 4", "加密授權:", "非定制讀卡器慎用該功能！", "加密使用:", "禁止", "使用", "密碼:", "其他區域卡號:", "起始地址:", "長度:", "最大讀卡數量:", "跳頻參數輸入區", "跳頻使用:", "禁止", "使用", "中國", "美規", "歐規", "定頻值:", "跳頻值:", "輸出數據參數輸入區", "輸出類型:", "輸出長度:", "是否帶Enter", "獲取參數", "設置參數", "默認所有參數" };

                string[] MainValue = BaseSettings.LoadLanguage(@"passive/basesettings", m_def_en, m_def_cn, m_def_tw);
                int index = 0;

                #region ---Wiegand---
                grbWiegand.Text = MainValue[index++];
                lblByteOffset.Text = MainValue[index++];
                lblPulseWidth.Text = MainValue[index++];
                lblOutInterval.Text = MainValue[index++];
                lblPulsePeriod.Text = MainValue[index++];
                #endregion

                #region ---Basic Para---
                grbParaB.Text = MainValue[index++];
                lblWorkMode.Text = MainValue[index++];
                intSelectItem = cmbWorkMode.SelectedIndex;
                cmbWorkMode.Items.Clear();
                cmbWorkMode.Items.Add(MainValue[index++]);
                cmbWorkMode.Items.Add(MainValue[index++]);
                cmbWorkMode.Items.Add(MainValue[index++]);
                cmbWorkMode.SelectedIndex = intSelectItem;

                lblOutputMode.Text = MainValue[index++];
                lblReadInterval.Text = MainValue[index++];
                lblPowerSize.Text = MainValue[index++];
                lblTrigger.Text = MainValue[index++];
                intSelectItem = cmbTrigger.SelectedIndex;
                cmbTrigger.Items.Clear();
                cmbTrigger.Items.Add(MainValue[index++]);
                cmbTrigger.Items.Add(MainValue[index++]);
                cmbTrigger.SelectedIndex = intSelectItem;

                lblSameIDinterval.Text = MainValue[index++];
                lblBuzzer.Text = MainValue[index++];
                intSelectItem = cmbBuzzer.SelectedIndex;
                cmbBuzzer.Items.Clear();
                cmbBuzzer.Items.Add(MainValue[index++]);
                cmbBuzzer.Items.Add(MainValue[index++]);
                cmbBuzzer.SelectedIndex = intSelectItem;

                lblCardType.Text = MainValue[index++];
                intSelectItem = cmbCardType.SelectedIndex;
                cmbCardType.Items.Clear();
                cmbCardType.Items.Add(MainValue[index++]);
                cmbCardType.Items.Add(MainValue[index++]);
                cmbCardType.Items.Add(MainValue[index++]);
                cmbCardType.Items.Add(MainValue[index++]);
                cmbCardType.Items.Add(MainValue[index++]);
                cmbCardType.SelectedIndex = intSelectItem;
                #endregion

                #region ---Senior Para---
                grbSenior.Text = MainValue[index++];
                lblAntenna.Text = MainValue[index++];

                chkAntenna1.Text = MainValue[index++];
                chkAntenna2.Text = MainValue[index++];
                chkAntenna3.Text = MainValue[index++];
                chkAntenna4.Text = MainValue[index++];

                lblChangePwd.Text = MainValue[index++];
                lblChangePwdSymbol.Text = MainValue[index++];
                lblEncrypt.Text = MainValue[index++];
                intSelectItem = cmbEncrypt.SelectedIndex;
                cmbEncrypt.Items.Clear();
                cmbEncrypt.Items.Add(MainValue[index++]);
                cmbEncrypt.Items.Add(MainValue[index++]);
                cmbEncrypt.SelectedIndex = intSelectItem;

                lblPassword.Text = MainValue[index++];
                lblMemory.Text = MainValue[index++];
                lblStartAddress.Text = MainValue[index++];
                lblLength.Text = MainValue[index++];
                lblMaxTag.Text = MainValue[index++];
                #endregion

                #region ---Hopping---
                grbHopping.Text = MainValue[index++];
                lblFreqHopping.Text = MainValue[index++];
                intSelectItem = cmbFreqHopping.SelectedIndex;
                cmbFreqHopping.Items.Clear();
                cmbFreqHopping.Items.Add(MainValue[index++]);
                cmbFreqHopping.Items.Add(MainValue[index++]);
                cmbFreqHopping.SelectedIndex = intSelectItem;

                btnChina.Text = MainValue[index++];
                btnAmerica.Text = MainValue[index++];
                btnEurope.Text = MainValue[index++];
                lblFixedFreq.Text = MainValue[index++];
                lblHopping1.Text = MainValue[index++];
                #endregion

                #region ---OutPut Card---
                grbOutType.Text = MainValue[index++];
                lblOutMode.Text = MainValue[index++];
                lblOutLen.Text = MainValue[index++];
                chkEnter.Text = MainValue[index++];

                intSelectItem = cmbOutType.SelectedIndex;
                cmbOutType.Items.Clear();
                cmbOutType.Items.AddRange(new string[3] { "Decimal", "Hex", "Wiegand" });
                cmbOutType.SelectedIndex = intSelectItem;
                #endregion

                #region ---Button---
                btnGetPara.Text = MainValue[index++] + "(&G)";
                btnSetPara.Text = MainValue[index++] + "(&S)";
                btnDefaultAll.Text = MainValue[index++] + "(&A)";
                #endregion
            }
            catch { }
            grbOutType.Visible = UserSettings.Communication == UserSettings.CommType.USB;
        }
        
        public override void ControlLoad(object sender, EventArgs e)
        {
            base.ControlLoad(sender, e);
        }

        int encryptCount = 0;
        public override void PassOnKeys(object sender, KeyEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.F8:
                    encryptCount++;
                    if (encryptCount > 4)
                    {
                        encryptCount = 0;
                        if (!pnlChangePwd.Visible && !pnlPwd.Visible) { pnlChangePwd.Visible = true; return; }
                    }
                    break;

                case Keys.F9:
                    encryptCount++;
                    if (encryptCount > 4)
                    {
                        encryptCount = 0;
                        if (!grbOutType.Visible) { grbOutType.Visible = true; return; }
                    }
                    break;
            }
        }

        #region ---Hopping---
        enum STANDARD
        {
            China,
            America,
            Europe

        }

        const int HOPPING_START = 860;
        const int HOPPING_STOP = 960;
        const double HOPPING_STEP = 0.5;

        private void LoadStandard(STANDARD stand)
        {
            switch (stand)
            {
                case STANDARD.Europe:
                    cmbFixedFreq.SelectedIndex = (int)((865 - HOPPING_START) / HOPPING_STEP);
                    cmbHopping1.SelectedIndex = (int)((860 - HOPPING_START) / HOPPING_STEP);
                    cmbHopping6.SelectedIndex = (int)((870 - HOPPING_START) / HOPPING_STEP);
                    break;
                case STANDARD.America:
                    cmbFixedFreq.SelectedIndex = (int)((922 - HOPPING_START) / HOPPING_STEP);
                    cmbHopping1.SelectedIndex = (int)((902 - HOPPING_START) / HOPPING_STEP);
                    cmbHopping6.SelectedIndex = (int)((928 - HOPPING_START) / HOPPING_STEP);
                    break;
                case STANDARD.China:
                    cmbFixedFreq.SelectedIndex = (int)((915 - HOPPING_START) / HOPPING_STEP);
                    cmbHopping1.SelectedIndex = (int)((902 - HOPPING_START) / HOPPING_STEP);
                    cmbHopping6.SelectedIndex = (int)((925 - HOPPING_START) / HOPPING_STEP);
                    break;
                default:
                    cmbFixedFreq.SelectedIndex = (int)((915 - HOPPING_START) / HOPPING_STEP);
                    cmbHopping1.SelectedIndex = (int)((860 - HOPPING_START) / HOPPING_STEP);
                    cmbHopping6.SelectedIndex = (int)((960 - HOPPING_START) / HOPPING_STEP);
                    break;
            }
        }

        private void btnEurope_Click(object sender, EventArgs e)
        {
            LoadStandard(STANDARD.Europe);
            //MessageStatus.Show("初始化欧标参数!", "Init Europe Standard!", (int)CommRtn.SUCCEED);
        }

        private void btnAmerica_Click(object sender, EventArgs e)
        {
            LoadStandard(STANDARD.America);
            //MessageStatus.Show("初始化美标参数!", "Init America Standard!", (int)CommRtn.SUCCEED);
        }

        private void btnChina_Click(object sender, EventArgs e)
        {
            LoadStandard(STANDARD.China);
            //MessageStatus.Show("初始化国标参数!", "Init China Standard!", (int)CommRtn.SUCCEED);
        }
        #endregion

        private void cmbCardType_SelectedIndexChanged(object sender, EventArgs e)
        {
            pnlMultData.Visible = false;
            pnlMaxTag.Visible = false;
            if (cmbCardType.SelectedIndex == 3)
            {
                pnlMultData.Visible = true;
            }
            else if (cmbCardType.SelectedIndex == 2)
            {
                pnlMaxTag.Visible = true;
            }
        }

        private void txtChangePwd_TextChanged(object sender, EventArgs e)
        {
            if (txtChangePwd.Text == "0987654321")
            {
                pnlPwd.Visible = true;
                pnlChangePwd.Visible = false;
            }
        }

        private void cmbEncrypt_SelectedIndexChanged(object sender, EventArgs e)
        {
            lblPassword.Visible = utxtPassword.Visible = (cmbEncrypt.SelectedIndex == 1);
        }

        private void cmbFreqHopping_SelectedIndexChanged(object sender, EventArgs e)
        {
            pnlHoppingM.Visible = (cmbFreqHopping.SelectedIndex == 1);
            pnlHoppingF.Visible = (cmbFreqHopping.SelectedIndex == 0);
        }

        public void ParseRsp(ProtocolStruct Data)
        {
            switch (Data.Code)
            {
                case PassiveRcp.RCP_CMD_PARA:
                    if (Data.Length > 0 && Data.Type == 0)
                    {
                        PBasicParameters ppTemp = new PBasicParameters();
                        ppTemp.AddRange(Data.Payload);
                        ShowBasicParametersPnfo(ppTemp);
                        SystemPub.ADRcp.CommMode = ppTemp.WorkMode == 2 ? CommMode.ACTIVE : CommMode.PASSIVE;
                        if (UserSettings.Communication == UserSettings.CommType.USB)
                        {
                            if (!SystemPub.ADRcp.SendBytePkt(PassiveRcp.GetOutCard(SystemPub.ADRcp.Address))) { }
                        }
                    }
                    else if (Data.Type == 0)
                    {
                        SystemPub.ADRcp.CommMode = cmbWorkMode.SelectedIndex == 1 ? CommMode.ACTIVE : CommMode.PASSIVE;
                        if (UserSettings.Communication == UserSettings.CommType.USB || grbOutType.Visible)
                        {
                            if (!SystemPub.ADRcp.SendBytePkt(PassiveRcp.SetOutCard(SystemPub.ADRcp.Address, (byte)(cmbOutType.SelectedIndex + 1), (byte)((cmbOutLen.SelectedIndex*2) + 6), (byte)(chkEnter.Checked ? 1 : 0)))) { }
                        }
                    }
                    break;
                case PassiveRcp.RCP_CMD_OUTCARD:
                    if (Data.Length > 0)
                    {
                        cmbOutType.SelectedIndex = Data.Payload[0] - 1;
                        cmbOutLen.Text = Data.Payload[1].ToString();
                        chkEnter.Checked = Data.Payload[2] > 0 ? true : false;
                    }
                    break;
            }
        }

        private void LoadInit()
        {
            cmbFixedFreq.Items.Clear();
            cmbHopping1.Items.Clear();
            cmbHopping6.Items.Clear();

            string[] strList;
            strList = new string[(int)((HOPPING_STOP - HOPPING_START) / HOPPING_STEP) + 1];
            for (int i = 0; i < strList.Length; i++)
            {
                //strList[i] = (i.ToString("000") + "-" + (HOPPING_START + i * HOPPING_STEP).ToString("00.0"));
                strList[i] = ((HOPPING_START + i * HOPPING_STEP).ToString("00.0"));
            }

            cmbPowerSize.Items.Clear();
            //for (int i = 0; i <= 60; i++)
            for (int i = 0; i <= 30; i++)
            {
                cmbPowerSize.Items.Add(i);
            }

            cmbFixedFreq.Items.AddRange(strList);
            cmbHopping1.Items.AddRange(strList);
            cmbHopping6.Items.AddRange(strList);

            cmbMaxTag.Items.Clear();
            for (int i = 10; i < 65; i++)
            {
                cmbMaxTag.Items.Add(i);
            }
            DefaultOutType();
            DefaultBasicPara();
            DefaultSeniorPara();
        }

        private void DefaultOutType()
        {
            cmbOutType.SelectedIndex = 0;
            cmbOutLen.SelectedIndex = 2;
            chkEnter.Checked = true;
        }

        private void DefaultBasicPara()
        {
            cmbPowerSize.SelectedIndex = 30;
            cmbWorkMode.SelectedIndex = 2 - 1;
            nudReadInterval.Value = 10;
            cmbTrigger.SelectedIndex = 0;
            cmbOutputMode.SelectedIndex = 6 - 1;
            nudByteOffset.Value = 0;
            nudOutInterval.Value = 30;
            nudPulseWidth.Value = 10;
            nudPulsePeriod.Value = 15;
            cmbCardType.SelectedIndex = 1;
            nudSameIDinterval.Value = 1;
            cmbBuzzer.SelectedIndex = 1;
        }

        private void DefaultSeniorPara()
        {
            cmbMaxTag.SelectedIndex = 32 - 10;
            cmbEncrypt.SelectedIndex = 0;
            cmbFreqHopping.SelectedIndex = 1;
            LoadStandard(STANDARD.China);
            chkAntenna1.Checked = true;
            chkAntenna2.Checked = false;
            chkAntenna3.Checked = false;
            chkAntenna4.Checked = false;
            cmbArea.SelectedIndex = 0;
            cmbStartWord.SelectedIndex = 0;
            cmbLength.SelectedIndex = 1;
        }
        private void SecretCard()
        {
            if (!SystemPub.ADRcp.SendBytePkt(PassiveRcp.SetSecret(SystemPub.ADRcp.Address))) { }
        }

        private bool ShowBasicParametersPnfo(PBasicParameters info)
        {
            try
            {
                cmbPowerSize.SelectedIndex = info.PowerSize;

                cmbFreqHopping.SelectedIndex = info.HoppingEnable;

                cmbFixedFreq.SelectedIndex = info.FixedFreq;

                cmbHopping1.SelectedIndex = info.Hopping1;

                cmbHopping6.SelectedIndex = info.Hopping6;

                cmbWorkMode.SelectedIndex = info.WorkMode - 1;

                nudReadInterval.Value = info.ReadInterval;

                cmbTrigger.SelectedIndex = info.Trigger > 0 ? 1 : 0;

                cmbOutputMode.SelectedIndex = info.OutputMode - 1;

                nudByteOffset.Value = info.ByteOffset;

                nudOutInterval.Value = info.OutInterval;

                nudPulseWidth.Value = info.PulseWidth;

                nudPulsePeriod.Value = info.PulsePeriod;

                int intAntenna = info.Antenna;

                chkAntenna1.Checked = Convert.ToBoolean(intAntenna & 1);
                chkAntenna2.Checked = Convert.ToBoolean(intAntenna & 2);
                chkAntenna3.Checked = Convert.ToBoolean(intAntenna & 4);
                chkAntenna4.Checked = Convert.ToBoolean(intAntenna & 8);

                switch (info.CardType)
                {
                    case 1:
                        cmbCardType.SelectedIndex = 0;
                        break;
                    case 16:
                        cmbCardType.SelectedIndex = 1;
                        break;
                    case 32:
                        cmbCardType.SelectedIndex = 2;
                        break;
                    case 64:
                        cmbCardType.SelectedIndex = 3;
                        break;
                    case 17:
                        cmbCardType.SelectedIndex = 4;
                        break;
                    default:
                        MessageBox.Show("CardType Set Error!", this.Text, MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
                        break;
                }

                nudSameIDinterval.Value = info.SameIDinterval;

                cmbBuzzer.SelectedIndex = info.Buzzer;

                cmbArea.SelectedIndex = info.Area >= 2 ? (info.Area - 2) : 0;

                cmbStartWord.SelectedIndex = info.StartWord;

                cmbLength.SelectedIndex = info.Length - 1;

                cmbEncrypt.SelectedIndex = info.Encrypt;

                utxtPassword.Text = info.Password.ToString("0000");

                cmbMaxTag.SelectedIndex = info.MaxTag - 10;
                return true;

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString(), this.Text, MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            return false;
        }

        private PBasicParameters GetBasicParametersPnfo()
        {
            PBasicParameters bpiTemp = new PBasicParameters();

            bpiTemp.PowerSize = (byte)cmbPowerSize.SelectedIndex;

            bpiTemp.HoppingEnable = (byte)cmbFreqHopping.SelectedIndex;
            bpiTemp.FixedFreq = (byte)cmbFixedFreq.SelectedIndex;

            int intStep = (cmbHopping6.SelectedIndex - cmbHopping1.SelectedIndex) / 5;
            if (intStep < 1) intStep = 1;
            bpiTemp.Hopping1 = (byte)cmbHopping1.SelectedIndex;
            bpiTemp.Hopping2 = (byte)(cmbHopping1.SelectedIndex + intStep);
            bpiTemp.Hopping3 = (byte)(cmbHopping1.SelectedIndex + intStep * 2);
            bpiTemp.Hopping4 = (byte)(cmbHopping1.SelectedIndex + intStep * 3);
            bpiTemp.Hopping5 = (byte)(cmbHopping1.SelectedIndex + intStep * 4);
            bpiTemp.Hopping6 = (byte)cmbHopping6.SelectedIndex;

            bpiTemp.WorkMode = (byte)(cmbWorkMode.SelectedIndex + 1);
            bpiTemp.ReadInterval = (byte)nudReadInterval.Value;
            bpiTemp.Trigger = (byte)(cmbTrigger.SelectedIndex > 0 ? 2 : 0);

            //lstByte.Add( Convert.ToByte(5));
            bpiTemp.OutputMode = (byte)(cmbOutputMode.SelectedIndex + 1);

            bpiTemp.ByteOffset = (byte)nudByteOffset.Value;
            bpiTemp.OutInterval = (byte)nudOutInterval.Value;
            bpiTemp.PulseWidth = (byte)nudPulseWidth.Value;
            bpiTemp.PulsePeriod = (byte)nudPulsePeriod.Value;
            int intAntenna = 0;

            if (chkAntenna1.Checked) intAntenna = intAntenna | 1;
            if (chkAntenna2.Checked) intAntenna = intAntenna | 2;
            if (chkAntenna3.Checked) intAntenna = intAntenna | 4;
            if (chkAntenna4.Checked) intAntenna = intAntenna | 8;

            bpiTemp.Antenna = (byte)intAntenna;


            switch (cmbCardType.SelectedIndex)
            {
                case 0:
                    bpiTemp.CardType = 1;
                    break;
                case 1:
                    bpiTemp.CardType = 16;
                    break;
                case 2:
                    bpiTemp.CardType = 32;
                    break;
                case 3:
                    bpiTemp.CardType = 64;
                    break;
                case 4:
                    bpiTemp.CardType = 17;
                    break;
                default:
                    bpiTemp.CardType = 16;
                    break;
            }
            bpiTemp.SameIDinterval = (byte)nudSameIDinterval.Value;
            bpiTemp.Buzzer = (byte)cmbBuzzer.SelectedIndex;

            bpiTemp.Area = (byte)(cmbArea.SelectedIndex + 2);
            bpiTemp.StartWord = (byte)cmbStartWord.SelectedIndex;
            bpiTemp.Length = (byte)(cmbLength.SelectedIndex + 1);

            bpiTemp.Encrypt = (byte)cmbEncrypt.SelectedIndex;
            bpiTemp.Password = Convert.ToInt32(utxtPassword.Text);

            bpiTemp.MaxTag = (byte)(cmbMaxTag.SelectedIndex + 10);

            return bpiTemp;
        }

        private void btnGetPara_Click(object sender, EventArgs e)
        {
            if (!SystemPub.ADRcp.SendBytePkt(PassiveRcp.GetConfig(SystemPub.ADRcp.Address))) { }
        }

        private void btnSetPara_Click(object sender, EventArgs e)
        {
            if (!SystemPub.ADRcp.SendBytePkt(PassiveRcp.SetConfig(SystemPub.ADRcp.Address, GetBasicParametersPnfo().ToArray()))) { }
        }

        private void btnDefaultAll_Click(object sender, EventArgs e)
        {
            DefaultOutType();
            DefaultBasicPara();
            DefaultSeniorPara();
        }

        private void btnSetProgarm_Click(object sender, EventArgs e)
        {
            if (!SystemPub.ADRcp.SendBytePkt(PassiveRcp.SetUsbPara(65535,new byte[]{5,32}))) { }
        }

        private void btnSetKeyboard_Click(object sender, EventArgs e)
        {
            if (!SystemPub.ADRcp.SendBytePkt(PassiveRcp.SetUsbPara(65535, new byte[] { 5, 5 }))) { }
        }

    }
}
