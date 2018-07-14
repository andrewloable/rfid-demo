using ADSDK.Bases;
using ADSDK.Bases.Controls;
using ADSDK.Sets;
using System;
using System.IO.Ports;
using System.Windows.Forms;

namespace Aosid
{
    public partial class frmSioConfig : BaseForm
    {
        public frmSioConfig()
        {
            InitializeComponent();
            foreach (string st in SerialPort.GetPortNames())
            {
                cmbPortName.Items.Add(st);
            }
            if (cmbPortName.Items.Count > 0) cmbPortName.SelectedIndex = 0;
        }

        #region ---Base Config---
        public override void PassOnKeys(object sender, KeyEventArgs e)
        {
            base.PassOnKeys(sender, e);
        }

        public override void ChangeLanguage()
        {
            switch (BaseSettings.AppsLanguage)
            {
                case BaseSettings.LngType.CHN:
                    this.Text = "通讯参数配置";

                    grbPortName.Text = "串口选择";
                    grbBaudRate.Text = "波特率选择";

                    grbRemoteIP.Text = "远程IP地址";
                    grbRemotePort.Text = "远程端口";
                    break;
                default:
                    this.Text = "Configuration";
                    grbPortName.Text = "PortName";
                    grbBaudRate.Text = "BaudRate";

                    grbRemoteIP.Text = "Remote IP";
                    grbRemotePort.Text = "Remote Port";
                    break;
            }
        }
        
        public override void ControlLoad(object sender, EventArgs e)
        {
            LoadCommunication(UserSettings.Communication);
            ChangeLanguage();
        }
        #endregion

        private void LoadCommunication(UserSettings.CommType type)
        {
            pnlTCPIP.Visible = false;
            pnlRS232.Visible = false;
            switch (type)
            {
                case UserSettings.CommType.SERIAL:
                    pnlRS232.Visible = true;
                    break;
                case UserSettings.CommType.NET:
                    pnlTCPIP.Visible = true;
                    break;
                case UserSettings.CommType.USB:

                    break;
                default:
                    break;
            }
            UserSettings.Communication = type;
            cmbPortName.Text = UserSettings.PortName;
            cmbBaudRate.Text = UserSettings.BaudRate.ToString();
            txtRemoteIP.Text = UserSettings.IP;
            txtRemotePort.Text = UserSettings.IPPort.ToString();
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            try
            {
                UserSettings.PortName =cmbPortName.Text;
            }
            catch { }
            UserSettings.BaudRate = Convert.ToInt32(cmbBaudRate.Text);
            UserSettings.IP = txtRemoteIP.Text;
            UserSettings.IPPort = Convert.ToInt32(txtRemotePort.Text);
        }

        private void pnlCommMode_Resize(object sender, EventArgs e)
        {
            btnOK.Top = pnlCommMode.Top + pnlCommMode.Height + 10;
            this.Height = pnlTitle.Height + pnlBody.Height;
        }
    }
}
