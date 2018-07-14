using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Text;
using System.Windows.Forms;
using System.Collections;
using System.Text.RegularExpressions;

namespace ADSDK.Control
{
    /// <summary>
    /// UserTextBox Control based on TextBox
    /// 
    /// Author: Endy Chan (thinkso.chan@gmail.com)
    /// 
    /// History:
    ///		Initial Release 3/23/2012
    ///		
    /// InputMask Char definition below
    ///		0	digit required
    ///		1	digit required
    ///		2	digit required
    ///		3	digit required
    ///		4	digit required
    ///		5	digit required
    ///		9	digit optional
    ///		L	lower case letter (a-z) required
    ///		l	lower case letter optional
    ///		U	upper case letter (A-Z) required
    ///		u	upper case letter optional
    ///		A	any case letter required
    ///		a	any case letter optional
    ///		D	letter or digit required
    ///		d	letter or digit optional
    ///		H	hex or digit required
    ///		h	hex or digit optional
    ///		C	any char including punctuation
    ///		\	escape char Used for literal mask chars ex: \0 for literal 0 in mask
    /// </summary>
    public partial class UserRichTextBox : RichTextBox
    {
        private string m_mask;			// input mask
        private string m_format;		// display format (mask with input chars replaced by input char)
        private InputMaskType m_maskType;
        private char m_inpChar;
        private bool m_maskChg;
        private bool m_stdmaskChg;
        private Hashtable m_regexps;
        private Hashtable m_posNdx;		// hold position translation map
        private int m_caret;
        private bool m_errInvalid;		// Error on invalid Text/Value input? -> true throws error, false ignore
        private int m_reqdCnt;			// required char count
        private int m_optCnt;			// optional char count

        // allowed mask chars
        private const char MASK_KEY = '@';

        // predefined masks
        private const string MAC = "HH-HH-HH-HH-HH-HH";
        private const string IP = "200.200.200.200";
        private const string TEL = "(9900)9900-00000099";
        private const string MOBILE = "000-0000-0000";

        public enum InputMaskType
        {
            None,
            MAC,
            IP,
            TEL,
            MOBILE,
            Custom
        }

        public UserRichTextBox()
        {
            // set default mask, input char
            m_maskType = InputMaskType.None;
            m_inpChar = '0';
            m_mask = "";
            m_format = "";
            m_caret = 0;
            m_errInvalid = false;
            base.Multiline = false;
        }

        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden), Browsable(false)]
        public string Value
        {
            get
            {
                if (m_maskType == InputMaskType.None)
                    return base.Text;
                else
                {
                    // return text with literals/spaces striped
                    string ret = "";
                    string m = InputMask;
                    string t = base.Text;
                    if (IsValidString(t))
                    {
                        // strip literals/spaces
                        int tPos = 0;
                        for (int i = 0 ; i < m.Length ; i++)
                        {
                            if (IsMaskChar(m[i]) && t[tPos] != ' ')// && t[tPos] != m_inpChar)
                                ret += t[tPos];
                            else if (m[i] == '\\')
                                i++;

                            tPos++;
                        }
                    }

                    return ret;
                }
            }
            set
            {
                if (m_maskType == InputMaskType.None)
                    base.Text = value;
                else
                {
                    //	Merge input chars with literals
                    string t = "";	// text being assembled from input Value and m_format string
                    int ipos = 0;	// input value position
                    int dif = value.Length - m_reqdCnt;
                    if (value == "")
                        base.Text = m_format;
                    else if (value.Length >= m_reqdCnt && value.Length <= m_reqdCnt + m_optCnt)
                    {
                        for (int fpos = 0 ; fpos < m_format.Length ; fpos++)
                        {
                            if (ipos < value.Length && m_format[fpos] == m_inpChar)
                            {
                                // input char (not literal)
                                if (((string)RegExps[InputMask[(int)m_posNdx[fpos]]]).IndexOf(' ') != -1)
                                {
                                    // optional
                                    if (dif > 0)
                                    {
                                        t += value[ipos++];
                                        dif--;
                                    }
                                    else
                                        t += m_format[fpos];
                                }
                                else
                                    t += value[ipos++];
                            }
                            else
                                t += m_format[fpos];
                        }
                    }
                    else if (m_errInvalid)
                        throw new ApplicationException("Input String Does Not Match Input Mask");

                    // validate input
                    if (IsValidString(t))
                        base.Text = t;
                    else if (m_errInvalid)
                        throw new ApplicationException("Input String Does Not Match Input Mask");
                }
            }
        }

        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden), Browsable(false)]
        public bool IsValid
        {
            get { return IsValidString(base.Text); }
        }

        [Description("Throw Error On Invalid Text/Value Property"), Category("Behavior")]
        public bool ErrorInvalid
        {
            get { return m_errInvalid; }
            set { m_errInvalid = value; }
        }

        [DesignerSerializationVisibility(DesignerSerializationVisibility.Visible)]
        public override bool Multiline
        {
            get { return base.Multiline; }
            set { base.Multiline = value; }
            // ignore set
        }

        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public new int SelectionStart
        {
            get { return base.SelectionStart; }
            set { base.SelectionStart = value; }
        }

        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public override int SelectionLength
        {
            get { return base.SelectionLength; }
        }

        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public override string Text
        {
            get { return base.Text; }
            set
            {
                if (m_maskType == InputMaskType.None)
                    base.Text = value;
                else
                {
                    // if input string length doesn't match format length
                    //	then we have a problem! this means that Text input
                    //	string MUST have optional missing chars
                    if (value == "")
                        base.Text = m_format;
                    else if (IsValidString(value) && value.Length == m_format.Length)
                    {
                        // must check optional input chars
                        bool ok = true;
                        int fpos = 0;
                        while (ok && fpos < m_format.Length)
                        {
                            if (m_format[fpos] == m_inpChar
                                && !IsValidChar(value[fpos], (int)m_posNdx[fpos]))
                                ok &= value[fpos] == m_inpChar;
                            fpos++;
                        }

                        if (ok)
                            base.Text = value;
                    }
                    else if (m_errInvalid)
                        throw new ApplicationException("Input String Does Not Match Input Mask");
                }
            }
        }

        [Description("Sets the Input Char default '_'"), Category("Behavior"),
        RefreshProperties(RefreshProperties.All)]
        public char InputChar
        {
            // "_" default
            get { return m_inpChar; }
            set
            {
                m_inpChar = value;
                InputMask = m_mask;
            }
        }

        [Description("Sets Predefined Input Mask"), Category("Behavior"),
        RefreshProperties(RefreshProperties.All)]
        public InputMaskType StdInputMask
        {
            get { return m_maskType; }
            set
            {
                m_stdmaskChg = true;
                m_maskType = value;

                // set mask string
                if (!m_maskChg)
                {
                    switch (value)
                    {
                        case InputMaskType.None:
                            InputMask = "";
                            break;
                        case InputMaskType.MAC:
                            InputMask = MAC;
                            if (base.Multiline) base.Multiline = false;
                            break;
                        case InputMaskType.IP:
                            InputMask = IP;
                            if (base.Multiline) base.Multiline = false;
                            break;
                        case InputMaskType.TEL:
                            InputMask = TEL;
                            if (base.Multiline) base.Multiline = false;
                            break;
                        case InputMaskType.MOBILE:
                            InputMask = MOBILE;
                            if (base.Multiline) base.Multiline = false;
                            break;
                        case InputMaskType.Custom:
                            // User responsible for setting InputMask
                            break;
                        default:
                            throw new ApplicationException("Invalid InputMaskType");
                    }
                }
                m_stdmaskChg = false;
            }
        }

        [Description("Sets the Input Mask"), Category("Behavior"),
        RefreshProperties(RefreshProperties.All)]
        public string InputMask
        {
            get { return m_mask; }
            set
            {
                m_maskChg = true;
                m_mask = value;

                if (!m_stdmaskChg)
                {
                    // sync InputMask with StdInputMask
                    switch (value)
                    {
                        case "":
                            StdInputMask = InputMaskType.None;
                            break;
                        case MAC:
                            StdInputMask = InputMaskType.MAC;
                            break;
                        case IP:
                            StdInputMask = InputMaskType.IP;
                            break;
                        case TEL:
                            StdInputMask = InputMaskType.TEL;
                            break;
                        default:
                            StdInputMask = InputMaskType.Custom;
                            break;
                    }
                }
                SetupMask();

                // runtime handling, reset text if current text is not valid
                if (DesignMode == true || base.Text.Length == 0 || !IsValidString(base.Text))
                    base.Text = m_format;
                else
                {
                    // reformat current text with new mask
                    this.Value = this.Value;
                }

                base.MaxLength = m_format.Length;
                m_maskChg = false;
            }
        }

        public override int MaxLength
        {
            get { return base.MaxLength; }
            set
            {
                // prevent setting if Mask is defined
                if (m_maskChg || m_stdmaskChg || StdInputMask == InputMaskType.None)
                    base.MaxLength = value;
            }
        }

        // private methods
        private bool IsValidString(string s)
        {
            bool ret = true;
            int pos = 0;
            // validate considering optional chars
            while (ret && pos < m_format.Length)
            {
                if (m_format[pos] == m_inpChar)
                {
                    // check input is valid including "optional" -> space in regexp
                    if (pos >= s.Length)
                    {
                        // must be optional input
                        ret = ((string)RegExps[InputMask[(int)m_posNdx[pos]]]).IndexOf(' ') != -1;
                    }
                    else
                    {
                        // valid or optional
                        ret = IsValidChar(s[pos], (int)m_posNdx[pos]);
                        if (!ret)
                            ret |= ((string)RegExps[InputMask[(int)m_posNdx[pos]]]).IndexOf(' ') != -1
                                && (s[pos] == ' ' || s[pos] == m_inpChar);
                    }
                }
                else
                {
                    // check literal match
                    if (pos < s.Length)
                        ret = s[pos] == m_format[pos];
                }
                pos++;
            }
            return ret;
        }

        private Hashtable RegExps
        {
            get
            {
                if (m_regexps == null)
                {
                    m_regexps = new Hashtable();

                    // build regexps
                    m_regexps.Add('0', @"[0-9]");		// digit required
                    m_regexps.Add('9', @"[0-9 ]");		// digit/space not required

                    m_regexps.Add('1', @"[0-1]");		// digit required
                    m_regexps.Add('2', @"[0-2]");		// digit required
                    m_regexps.Add('3', @"[0-3]");		// digit required
                    m_regexps.Add('4', @"[0-4]");		// digit required
                    m_regexps.Add('5', @"[0-5]");		// digit required

                    m_regexps.Add('L', @"[a-z]");		// letter a-z required
                    m_regexps.Add('l', @"[a-z ]");		// letter a-z not required

                    m_regexps.Add('U', @"[A-Z]");		// letter A-Z required
                    m_regexps.Add('u', @"[A-Z ]");		// letter A-Z not required

                    m_regexps.Add('A', @"[a-zA-Z]");	// letter required
                    m_regexps.Add('a', @"[a-zA-Z ]");	// letter not required

                    m_regexps.Add('D', @"[a-zA-Z0-9]");		// letter or digit required
                    m_regexps.Add('d', @"[a-zA-Z0-9 ]");	// letter or digit not required

                    m_regexps.Add('C', @".");		// any char

                    m_regexps.Add('H', @"[a-fA-F0-9]");		// letter or digit required
                    m_regexps.Add('h', @"[a-fA-F0-9 ]");	// letter or digit not required

                    // IMPORTANT: You MUST add and new mask chars to this regexp!
                    m_regexps.Add('@', @"[0123459LlUuAaDdCHh]");	// used for input char testing
                }

                return m_regexps;
            }
        }

        protected override void OnMouseUp(MouseEventArgs e)
        {
            if (StdInputMask == InputMaskType.None)
            {
                base.OnMouseUp(e);
                return;
            }

            // reset selection to include input chars
            int strt = base.SelectionStart;
            int orig = strt;
            int len = base.SelectionLength;

            // reset selection start
            if (strt == base.MaxLength || m_format[strt] != m_inpChar)
            {
                // reset start
                if (Next(strt) == strt)
                    strt = Prev(strt);
                else
                    strt = Next(strt);

                base.SelectionStart = strt;
            }

            // reset selection length
            if (len < 1)
                base.SelectionLength = 1;
            else if (m_format[orig + len - 1] != m_inpChar)
            {
                len += Next(strt + len) - (strt + len);
                base.SelectionLength = len;
            }

            m_caret = strt;
            base.OnMouseUp(e);
        }

        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            // return true to discontinue processing
            if (StdInputMask == InputMaskType.None)
                return base.ProcessCmdKey(ref msg, keyData);

            // NOTES: 
            //	1) break; causes warnings below
            //	2) m_caret tracks caret location, always the start of selected char
            int strt = base.SelectionStart;
            int len = base.SelectionLength;
            int end = strt + base.SelectionLength - 1;
            string s = base.Text;
            int p;

            // handle startup, runs once
            if (m_format[strt] != m_inpChar)
            {
                strt = Next(-1);
                len = 1;
            }

            switch (keyData)
            {
                case Keys.Left:
                case Keys.Up:
                    p = Prev(strt);
                    if (p != strt)
                    {
                        base.SelectionStart = p;
                        base.SelectionLength = 1;
                    }
                    m_caret = p;
                    return true;
                case Keys.Left | Keys.Shift:
                case Keys.Up | Keys.Shift:
                    if ((strt < m_caret) || (strt == m_caret && len <= 1))
                    {
                        // enlarge left
                        p = Prev(strt);
                        base.SelectionStart -= (strt - p);
                        base.SelectionLength = len + (strt - p);
                    }
                    else
                    {
                        // shrink right
                        base.SelectionLength = len - (end - Prev(end));
                    }
                    return true;
                case Keys.Right:
                case Keys.Down:
                    p = Next(strt);
                    if (p != strt)
                    {
                        base.SelectionStart = p;
                        base.SelectionLength = 1;
                    }
                    m_caret = p;
                    return true;
                case Keys.Right | Keys.Shift:
                case Keys.Down | Keys.Shift:
                    if (strt < m_caret)
                    {
                        // shrink left
                        p = Next(strt);
                        base.SelectionStart += (p - strt);
                        base.SelectionLength = len - (p - strt);
                    }
                    else if (strt == m_caret)
                    {
                        // enlarge right
                        p = Next(end);
                        base.SelectionLength = len + (p - end);
                    }
                    return true;
                case Keys.Delete:
                    // delete selection, replace with input format
                    base.Text = s.Substring(0, strt) + m_format.Substring(strt, len) + s.Substring(strt + len);
                    base.SelectionStart = strt;
                    base.SelectionLength = 1;
                    m_caret = strt;
                    return true;
                case Keys.Home:
                    base.SelectionStart = Next(-1);
                    base.SelectionLength = 1;
                    m_caret = base.SelectionStart;
                    return true;
                case Keys.Home | Keys.Shift:
                    if (strt <= m_caret && len <= 1)
                    {
                        // enlarge left
                        p = Next(-1);
                        base.SelectionStart -= (strt - p);
                        base.SelectionLength = len + (strt - p);
                    }
                    else
                    {
                        // shrink right
                        p = Next(-1);
                        base.SelectionStart = p;
                        base.SelectionLength = (m_caret - p) + 1;
                    }
                    return true;
                case Keys.End:
                    base.SelectionStart = Prev(base.MaxLength);
                    base.SelectionLength = 1;
                    m_caret = base.SelectionStart;
                    return true;
                case Keys.End | Keys.Shift:
                    if (strt < m_caret)
                    {
                        // shrink left
                        p = Prev(base.MaxLength);
                        base.SelectionStart = m_caret;
                        base.SelectionLength = (p - m_caret + 1);
                    }
                    else if (strt == m_caret)
                    {
                        // enlarge right
                        p = Prev(base.MaxLength);
                        base.SelectionLength = len + (p - end);
                    }
                    return true;
                case Keys.V | Keys.Control:
                case Keys.Insert | Keys.Shift:
                    // attempt paste
                    // NOTES:
                    //	1) Paste is likely to have literals since it must be copied from somewhere
                    IDataObject iData = Clipboard.GetDataObject();

                    // assemble new text
                    string t = s.Substring(0, strt)
                        + (string)iData.GetData(DataFormats.Text)
                        + s.Substring(strt + len);

                    // check if data to be pasted is convertable to inputType
                    if (IsValidString(t))
                        base.Text = t;
                    else if (m_errInvalid)
                        throw new ApplicationException("Input String Does Not Match Input Mask");

                    return true;
                default:
                    return base.ProcessCmdKey(ref msg, keyData);
            }
        }

        // event handlers
        protected override void OnKeyPress(KeyPressEventArgs e)
        {
            if (StdInputMask == InputMaskType.None)
            {
                base.OnKeyPress(e);
                return;
            }

            int strt = base.SelectionStart;
            int len = base.SelectionLength;
            int p;

            // Handle Backspace -> replace previous char with inpchar and select
            if (e.KeyChar == 0x08)
            {
                string s = base.Text;
                p = Prev(strt);
                if (p != strt)
                {
                    base.Text = s.Substring(0, p) + m_inpChar.ToString() + s.Substring(p + 1);
                    base.SelectionStart = p;
                    base.SelectionLength = 1;

                }
                m_caret = p;
                e.Handled = true;
                return;
            }

            // handle startup, runs once
            if (m_format[strt] != m_inpChar)
            {
                strt = Next(-1);
                len = 1;
            }

            // update display if valid char entered
            if (IsValidChar(e.KeyChar, (int)m_posNdx[strt]))
            {
                // assemble new text
                string t = "";
                t = base.Text.Substring(0, strt);
                t += e.KeyChar.ToString();

                if (strt + len != base.MaxLength)
                {
                    t += m_format.Substring(strt + 1, len - 1);
                    t += base.Text.Substring(strt + len);
                }
                else
                    t += m_format.Substring(strt + 1);

                base.Text = t;

                // select next input char
                strt = Next(strt);
                base.SelectionStart = strt;
                m_caret = strt;
                base.SelectionLength = 1;
            }
            e.Handled = true;
        }

        private bool IsValidChar(char input, int pos)
        {
            // validate input char against mask
            return Regex.IsMatch(input.ToString(), (string)RegExps[InputMask[pos]]);
        }

        private bool IsMaskChar(char input)
        {
            // check char
            return Regex.IsMatch(input.ToString(), (string)RegExps[MASK_KEY]);
        }

        private void SetupMask()
        {
            // used to build position translation map from mask string
            //	and input format
            string s = InputMask;
            m_format = "";

            // reset index
            if (m_posNdx == null)
                m_posNdx = new Hashtable();
            else
                m_posNdx.Clear();

            int cnt = 0;
            m_reqdCnt = 0;
            m_optCnt = 0;

            for (int i = 0 ; i < s.Length ; i++)
            {
                if (IsMaskChar(s[i]))
                {
                    m_posNdx.Add(cnt, i);
                    m_format += m_inpChar;
                    // update optional/required char counts
                    if (((string)RegExps[InputMask[i]]).IndexOf(' ') != -1)
                        m_optCnt++;
                    else
                        m_reqdCnt++;
                }
                else if (s[i] == '\\')
                {
                    // escape char
                    i++;
                    m_format += s[i].ToString();
                }
                else
                    m_format += s[i].ToString();

                cnt++;
            }
        }
        /// <summary>
        /// return previous input char position
        /// returns current position if no input chars to the left
        /// caller must decide what to do with this
        /// </summary>
        /// <param name="startPos"></param>
        /// <returns></returns>
        private int Prev(int startPos)
        {
            int strt = startPos;
            int ret = strt;

            while (strt > 0)
            {
                strt--;
                if (m_format[strt] == m_inpChar)
                    return strt;
            }
            return ret;
        }

        /// <summary>
        /// return next input char position
        /// returns current position if no input chars to the left
        /// caller must decide what to do with this
        /// </summary>
        /// <param name="startPos"></param>
        /// <returns></returns>
        private int Next(int startPos)
        {
            int strt = startPos;
            int ret = strt;

            while (strt < base.MaxLength - 1)
            {
                strt++;
                if (m_format[strt] == m_inpChar)
                    return strt;
            }

            return ret;
        }
    }
}
