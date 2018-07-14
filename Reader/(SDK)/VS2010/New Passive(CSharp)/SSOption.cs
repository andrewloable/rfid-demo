using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using NewPassive.Properties;

public class SSOption
{
    #region ---Language Choose---
    public const int CHN = 0;   //0，Chinese
    public const int ENG = 1;   //1，English
    public const int Serial = 0;   //0，Serial
    public const int Net = 1;   //1，Net
    /// <summary>
    /// Choose Language
    /// </summary>
    public static int Language
    {
        set
        {
            Settings.Default.Language = value;
            Settings.Default.Save();
        }
        get
        {
            return Settings.Default.Language;
        }
    }
    /// <summary>
    /// Language Font
    /// </summary>
    public static Font LngFont
    {
        get
        {
            if (Language == CHN)
            {
                return Settings.Default.FontChn;
            }
            else
            {
                return Settings.Default.FontEng;
            }
        }
    }
    #endregion

    /// <summary>
    /// Choose Communication
    /// </summary>
    public static int Communication
    {
        set
        {
            Settings.Default.Communication = value;
            Settings.Default.Save();
        }
        get
        {
            return Settings.Default.Communication;
        }
    }

    public static string IP
    {
        set
        {
            Settings.Default.IP = value;
            Settings.Default.Save();
        }
        get
        {
            return Settings.Default.IP;
        }
    }

    public static int IPPort
    {
        set
        {
            Settings.Default.IPPort = value;
            Settings.Default.Save();
        }
        get
        {
            return Settings.Default.IPPort;
        }
    }

    public static int PortName
    {
        set
        {
            Settings.Default.PortName = value;
            Settings.Default.Save();
        }
        get
        {
            return Settings.Default.PortName;
        }
    }

    public static int BaudRate
    {
        set
        {
            Settings.Default.BaudRate = value;
            Settings.Default.Save();
        }
        get
        {
            return Settings.Default.BaudRate;
        }
    }

    public static long WriteCard
    {
        set
        {
            Settings.Default.WriteCard = value;
            Settings.Default.Save();
        }
        get
        {
            return Settings.Default.WriteCard;
        }
    }

    public static int WriteMode
    {
        set
        {
            Settings.Default.WriteMode = value;
            Settings.Default.Save();
        }
        get
        {
            return Settings.Default.WriteMode;
        }
    }

    public static int WriteType
    {
        set
        {
            Settings.Default.WriteType = value;
            Settings.Default.Save();
        }
        get
        {
            return Settings.Default.WriteType;
        }
    }

    public static int WritePosition
    {
        set
        {
            Settings.Default.WritePosition = value;
            Settings.Default.Save();
        }
        get
        {
            return Settings.Default.WritePosition;
        }
    }

    public static bool WriteAutoAdd
    {
        set
        {
            Settings.Default.WriteAutoAdd = value;
            Settings.Default.Save();
        }
        get
        {
            return Settings.Default.WriteAutoAdd;
        }
    }
}
