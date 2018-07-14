using ADSDK.Bases;
using ADSDK.Bases.Controls;
using System;
using System.Drawing;
using System.Windows.Forms;

namespace Aosid
{
    public partial class frmWait : BaseForm
    {
        public frmWait()
        {
            InitializeComponent();
        }

        public bool IsAlive = false;

        private void frmWait_Load(object sender, EventArgs e)
        {
            this.TitleVisable = false;
            this.label1.Font = new Font("微软雅黑", 12F, FontStyle.Italic|FontStyle.Bold);
            if(BaseSettings.AppsLanguage == BaseSettings.LngType.CHN)
            {
                this.label1.Text = "连接中......" + Environment.NewLine +
                                    "远程主机长时间无响应..." + Environment.NewLine +
                                    "请稍微等待一段时间,可能串口或者IP地址不正确!";
            }
            else
            {
                this.label1.Text = "Connecting..." + Environment.NewLine +
                                    "No response from the remote host long time..." + Environment.NewLine +
                                    "Please wait for a moment!";
            }
            IsAlive = true;
        }

        private void frmWait_FormClosing(object sender, FormClosingEventArgs e)
        {
            IsAlive = false;
        }

        public override void PassOnKeys(object sender, KeyEventArgs e)
        {
            //base.PassOnKeys(sender, e);
        }

    }
}
