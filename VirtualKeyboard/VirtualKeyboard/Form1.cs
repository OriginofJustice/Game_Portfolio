using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;


namespace VirtualKeyboard
{
    [Serializable()]
    public partial class Form1 : Form
    {
        enum eLanguageType
        {
            TYPE_ENGLISH,
            TYPE_KOREAN
        }

        private eLanguageType m_languageType;
        private bool m_bShift = false;
        private MixString.CMixStirng m_MixString;
        public Form1()
        {
            InitializeComponent();
            m_languageType = eLanguageType.TYPE_ENGLISH;

            m_MixString = new MixString.CMixStirng();
            RefreshString();
        }

        private void RefreshString()
        {
            Result.Text = m_MixString.getString() + "_";
        }
#region SPE_KEY_EVENT
        //=======================================================================
        // Name :	pushShiftSpeString
        //
        // Desc :	shift키를 눌렀을때 특수문자들이 변하는 함수
        //=======================================================================
        private void pushShiftSpeString()
        {
            m_bShift = true;
            Shift_Push.Checked = true;
            English_StringChange(!Caps_check.Checked);
            SpeStringChange(Shift_Push.Checked);
            Korean_StringChange(Shift_Push.Checked);
        }

        //=======================================================================
        // Name :	unpushShiftSpeString
        //
        // Desc :	shift키를 때었을때 특수문자들이 변하는 함수
        //=======================================================================
        private void unpushShiftSpeString()
        {
            m_bShift = false;
            Shift_Push.Checked = false;
            English_StringChange(Caps_check.Checked);
            SpeStringChange(Shift_Push.Checked);
            Korean_StringChange(Shift_Push.Checked);
        }

        //=======================================================================
        // Name :	Key_Shift_Click
        //
        // Desc :	shift 키 이벤트 
        //=======================================================================
        private void Key_Shift_Click(object sender, EventArgs e)
        {
            if (m_bShift)
                unpushShiftSpeString();
            else
                pushShiftSpeString();
        }

        //=======================================================================
        // Name :	Change_Click
        //
        // Desc :	한글 영문 전환
        //=======================================================================
        private void Change_Click(object sender, EventArgs e)
        {
            if (m_languageType == eLanguageType.TYPE_ENGLISH)
            {
                Change.Text = "영어";
                m_languageType = eLanguageType.TYPE_KOREAN;
                m_bShift = false;
                Shift_Push.Checked = false;
                Korean_StringChange(false);
            }
            else
            {
                Change.Text = "한글";
                m_languageType = eLanguageType.TYPE_ENGLISH;
                Caps_Change();
            }
        }

        //=======================================================================
        // Name :	Key_Caps_Click
        //
        // Desc :	caps lock 키 이벤트 
        //=======================================================================
        private void Key_Caps_Click(object sender, EventArgs e)
        {
            Caps_check.Checked = !Caps_check.Checked;

            Caps_Change();
            if (!m_bShift)
                unpushShiftSpeString();
            else
                pushShiftSpeString();
        }

        private void Caps_Change()
        {
            // 영문일 경우에 한정해서 변경한다. 
            if (m_languageType == eLanguageType.TYPE_ENGLISH)
            {
                English_StringChange(Caps_check.Checked);
            }

        }
        private void SpeStringChange(bool bShift)
        {

            if (bShift)
            {
                Key_0.Text = ")";
                Key_1.Text = "!";
                Key_2.Text = "@";
                Key_3.Text = "#";
                Key_4.Text = "$";
                Key_5.Text = "%";
                Key_6.Text = "^";
                Key_7.Text = "&&";
                Key_8.Text = "*";
                Key_9.Text = "(";
                Key_apo2.Text = "~";
                Key_sub.Text = "_";
                Key_equ.Text = "+";
                Key_backsla.Text = "|";

                Key_Lbra.Text = "{";
                Key_Rbra.Text = "}";
                Key_col.Text = ":";
                Key_apo.Text = "\"";
                Key_rest.Text = "<";
                Key_div.Text = ">";
                Key_sla.Text = "?";
            }
            else
            {
                Key_0.Text = "0";
                Key_1.Text = "1";
                Key_2.Text = "2";
                Key_3.Text = "3";
                Key_4.Text = "4";
                Key_5.Text = "5";
                Key_6.Text = "6";
                Key_7.Text = "7";
                Key_8.Text = "8";
                Key_9.Text = "9";
                Key_apo2.Text = "`";
                Key_sub.Text = "-";
                Key_equ.Text = "=";
                Key_backsla.Text = "\\";

                Key_Lbra.Text = "[";
                Key_Rbra.Text = "]";
                Key_col.Text = ";";
                Key_apo.Text = "\'";
                Key_rest.Text = ",";
                Key_div.Text = ".";
                Key_sla.Text = "/";
            }
        }

        private void English_StringChange(bool bLarge)
        {
            if (m_languageType != eLanguageType.TYPE_ENGLISH)
                return;
            // 대문자로 바꾼다. 
            if (bLarge == true)
            {
                Key_a.Text = "A";
                Key_b.Text = "B";
                Key_c.Text = "C";
                Key_d.Text = "D";
                Key_e.Text = "E";
                Key_f.Text = "F";
                Key_g.Text = "G";
                Key_h.Text = "H";
                Key_i.Text = "I";
                Key_j.Text = "J";
                Key_k.Text = "K";
                Key_l.Text = "L";
                Key_m.Text = "M";
                Key_n.Text = "N";
                Key_o.Text = "O";
                Key_p.Text = "P";
                Key_q.Text = "Q";
                Key_r.Text = "R";
                Key_s.Text = "S";
                Key_t.Text = "T";
                Key_u.Text = "U";
                Key_v.Text = "V";
                Key_w.Text = "W";
                Key_x.Text = "X";
                Key_y.Text = "Y";
                Key_z.Text = "Z";

            }
            // 소문자로 바꾼다.
            else
            {
                Key_a.Text = "a";
                Key_b.Text = "b";
                Key_c.Text = "c";
                Key_d.Text = "d";
                Key_e.Text = "e";
                Key_f.Text = "f";
                Key_g.Text = "g";
                Key_h.Text = "h";
                Key_i.Text = "i";
                Key_j.Text = "j";
                Key_k.Text = "k";
                Key_l.Text = "l";
                Key_m.Text = "m";
                Key_n.Text = "n";
                Key_o.Text = "o";
                Key_p.Text = "p";
                Key_q.Text = "q";
                Key_r.Text = "r";
                Key_s.Text = "s";
                Key_t.Text = "t";
                Key_u.Text = "u";
                Key_v.Text = "v";
                Key_w.Text = "w";
                Key_x.Text = "x";
                Key_y.Text = "y";
                Key_z.Text = "z";
            }
        }

        private void Korean_StringChange(bool bLarge)
        {
            if (m_languageType != eLanguageType.TYPE_KOREAN)
                return;

            if (bLarge == true)
            {
                Key_a.Text = "ㅁ";
                Key_b.Text = "ㅠ";
                Key_c.Text = "ㅊ";
                Key_d.Text = "ㅇ";
                Key_e.Text = "ㄸ";
                Key_f.Text = "ㄹ";
                Key_g.Text = "ㅎ";
                Key_h.Text = "ㅗ";
                Key_i.Text = "ㅑ";
                Key_j.Text = "ㅓ";
                Key_k.Text = "ㅏ";
                Key_l.Text = "ㅣ";
                Key_m.Text = "ㅡ";
                Key_n.Text = "ㅜ";
                Key_o.Text = "ㅒ";
                Key_p.Text = "ㅖ";
                Key_q.Text = "ㅃ";
                Key_r.Text = "ㄲ";
                Key_s.Text = "ㄴ";
                Key_t.Text = "ㅆ";
                Key_u.Text = "ㅕ";
                Key_v.Text = "ㅍ";
                Key_w.Text = "ㅉ";
                Key_x.Text = "ㅌ";
                Key_y.Text = "ㅛ";
                Key_z.Text = "ㅋ";

            }
            // 소문자로 바꾼다.
            else
            {
                Key_a.Text = "ㅁ";
                Key_b.Text = "ㅠ";
                Key_c.Text = "ㅊ";
                Key_d.Text = "ㅇ";
                Key_e.Text = "ㄷ";
                Key_f.Text = "ㄹ";
                Key_g.Text = "ㅎ";
                Key_h.Text = "ㅗ";
                Key_i.Text = "ㅑ";
                Key_j.Text = "ㅓ";
                Key_k.Text = "ㅏ";
                Key_l.Text = "ㅣ";
                Key_m.Text = "ㅡ";
                Key_n.Text = "ㅜ";
                Key_o.Text = "ㅐ";
                Key_p.Text = "ㅔ";
                Key_q.Text = "ㅂ";
                Key_r.Text = "ㄱ";
                Key_s.Text = "ㄴ";
                Key_t.Text = "ㅅ";
                Key_u.Text = "ㅕ";
                Key_v.Text = "ㅍ";
                Key_w.Text = "ㅈ";
                Key_x.Text = "ㅌ";
                Key_y.Text = "ㅛ";
                Key_z.Text = "ㅋ";
            }
        }

        private void Key_Backsapce_Click(object sender, EventArgs e)
        {
            m_MixString.BackSpace();
            RefreshString();
        }

        private void Space_Click(object sender, EventArgs e)
        {
            m_MixString.Space();
            RefreshString();
        }

#endregion

        #region  NUMBER_KEY_EVENT
        private void Key_1_Click(object sender, EventArgs e)
        {
            m_MixString.asciiCodeInput(Key_1.Text.ToCharArray()[0]);
            RefreshString();
        }

        private void Key_2_Click(object sender, EventArgs e)
        {
            m_MixString.asciiCodeInput(Key_2.Text.ToCharArray()[0]);
            RefreshString();
        }

        private void Key_3_Click(object sender, EventArgs e)
        {
            m_MixString.asciiCodeInput(Key_3.Text.ToCharArray()[0]);
            RefreshString();
        }

        private void Key_4_Click(object sender, EventArgs e)
        {
            m_MixString.asciiCodeInput(Key_4.Text.ToCharArray()[0]);
            RefreshString();
        }

        private void Key_5_Click(object sender, EventArgs e)
        {
            m_MixString.asciiCodeInput(Key_5.Text.ToCharArray()[0]);
            RefreshString();
        }

        private void Key_6_Click(object sender, EventArgs e)
        {
            m_MixString.asciiCodeInput(Key_6.Text.ToCharArray()[0]);
            RefreshString();
        }

        private void Key_7_Click(object sender, EventArgs e)
        {
            m_MixString.asciiCodeInput(Key_7.Text.ToCharArray()[0]);
            RefreshString();
        }

        private void Key_8_Click(object sender, EventArgs e)
        {
            m_MixString.asciiCodeInput(Key_8.Text.ToCharArray()[0]);
            RefreshString();
        }

        private void Key_9_Click(object sender, EventArgs e)
        {
            m_MixString.asciiCodeInput(Key_9.Text.ToCharArray()[0]);
            RefreshString();
        }

        private void Key_0_Click(object sender, EventArgs e)
        {
            m_MixString.asciiCodeInput(Key_0.Text.ToCharArray()[0]);
            RefreshString();
        }

        private void Key_apo2_Click(object sender, EventArgs e)
        {
            m_MixString.asciiCodeInput(Key_apo2.Text.ToCharArray()[0]);
            RefreshString();
        }

        private void Key_sub_Click(object sender, EventArgs e)
        {
            m_MixString.asciiCodeInput(Key_sub.Text.ToCharArray()[0]);
            RefreshString();
        }

        private void Key_equ_Click(object sender, EventArgs e)
        {
            m_MixString.asciiCodeInput(Key_equ.Text.ToCharArray()[0]);
            RefreshString();
        }

        private void Key_backsla_Click(object sender, EventArgs e)
        {
            m_MixString.asciiCodeInput(Key_backsla.Text.ToCharArray()[0]);
            RefreshString();
        }

        private void Key_Lbra_Click(object sender, EventArgs e)
        {
            m_MixString.asciiCodeInput(Key_Lbra.Text.ToCharArray()[0]);
            RefreshString();
        }

        private void Key_Rbra_Click(object sender, EventArgs e)
        {
            m_MixString.asciiCodeInput(Key_Rbra.Text.ToCharArray()[0]);
            RefreshString();
        }

        private void Key_col_Click(object sender, EventArgs e)
        {
            m_MixString.asciiCodeInput(Key_col.Text.ToCharArray()[0]);
            RefreshString();
        }

        private void Key_apo_Click(object sender, EventArgs e)
        {
            m_MixString.asciiCodeInput(Key_apo.Text.ToCharArray()[0]);
            RefreshString();
        }

        private void Key_rest_Click(object sender, EventArgs e)
        {
            m_MixString.asciiCodeInput(Key_rest.Text.ToCharArray()[0]);
            RefreshString();
        }

        private void Key_div_Click(object sender, EventArgs e)
        {
            m_MixString.asciiCodeInput(Key_div.Text.ToCharArray()[0]);
            RefreshString();
        }

        private void Key_sla_Click(object sender, EventArgs e)
        {
            m_MixString.asciiCodeInput(Key_sla.Text.ToCharArray()[0]);
            RefreshString();
        }
        #endregion








        #region KEY_EVENT
        private void Key_q_Click(object sender, EventArgs e)
        {
            switch (m_languageType)
            {
                case eLanguageType.TYPE_ENGLISH:
                    m_MixString.asciiCodeInput(Key_q.Text.ToCharArray()[0]);
                    break;
                case eLanguageType.TYPE_KOREAN:
                    if (m_bShift)
                        m_MixString.AddKoreanJaum(8);
                    else
                        m_MixString.AddKoreanJaum(7);
                    break;

            }

            RefreshString();
        }

        private void Key_w_Click(object sender, EventArgs e)
        {
            switch (m_languageType)
            {
                case eLanguageType.TYPE_ENGLISH:
                    m_MixString.asciiCodeInput(Key_w.Text.ToCharArray()[0]);
                    break;
                case eLanguageType.TYPE_KOREAN:
                    if (m_bShift)
                        m_MixString.AddKoreanJaum(13);
                    else
                        m_MixString.AddKoreanJaum(12);
                    break;
            }

            RefreshString();
        }

        private void Key_e_Click(object sender, EventArgs e)
        {
            switch (m_languageType)
            {
                case eLanguageType.TYPE_ENGLISH:
                    m_MixString.asciiCodeInput(Key_e.Text.ToCharArray()[0]);
                    break;
                case eLanguageType.TYPE_KOREAN:
                    if (m_bShift)
                        m_MixString.AddKoreanJaum(4);
                    else
                        m_MixString.AddKoreanJaum(3);
                    break;

            }

            RefreshString();
        }

        private void Key_r_Click(object sender, EventArgs e)
        {
            switch (m_languageType)
            {
                case eLanguageType.TYPE_ENGLISH:
                    m_MixString.asciiCodeInput(Key_r.Text.ToCharArray()[0]);
                    break;
                case eLanguageType.TYPE_KOREAN:
                    if (m_bShift)
                        m_MixString.AddKoreanJaum(1);
                    else
                        m_MixString.AddKoreanJaum(0);
                    break;

            }

            RefreshString();
        }

        private void Key_t_Click(object sender, EventArgs e)
        {
            switch (m_languageType)
            {
                case eLanguageType.TYPE_ENGLISH:
                    m_MixString.asciiCodeInput(Key_t.Text.ToCharArray()[0]);
                    break;
                case eLanguageType.TYPE_KOREAN:
                    if (m_bShift)
                        m_MixString.AddKoreanJaum(10);
                    else
                        m_MixString.AddKoreanJaum(9);
                    break;

            }

            RefreshString();
        }

        private void Key_y_Click(object sender, EventArgs e)
        {
            switch (m_languageType)
            {
                case eLanguageType.TYPE_ENGLISH:
                    m_MixString.asciiCodeInput(Key_y.Text.ToCharArray()[0]);
                    break;
                case eLanguageType.TYPE_KOREAN:
                    m_MixString.AddKoreanMoum(12);
                    break;

            }

            RefreshString();
        }

        private void Key_u_Click(object sender, EventArgs e)
        {
            switch (m_languageType)
            {
                case eLanguageType.TYPE_ENGLISH:
                    m_MixString.asciiCodeInput(Key_u.Text.ToCharArray()[0]);
                    break;
                case eLanguageType.TYPE_KOREAN:
                    m_MixString.AddKoreanMoum(6);
                    break;

            }

            RefreshString();
        }

        private void Key_i_Click(object sender, EventArgs e)
        {
            switch (m_languageType)
            {
                case eLanguageType.TYPE_ENGLISH:
                    m_MixString.asciiCodeInput(Key_i.Text.ToCharArray()[0]);
                    break;
                case eLanguageType.TYPE_KOREAN:
                    m_MixString.AddKoreanMoum(2);
                    break;

            }

            RefreshString();
        }

        private void Key_o_Click(object sender, EventArgs e)
        {
            switch (m_languageType)
            {
                case eLanguageType.TYPE_ENGLISH:
                    m_MixString.asciiCodeInput(Key_o.Text.ToCharArray()[0]);
                    break;
                case eLanguageType.TYPE_KOREAN:
                    if (m_bShift)
                        m_MixString.AddKoreanMoum(3);
                    else
                        m_MixString.AddKoreanMoum(1);
                    break;

            }

            RefreshString();
        }

        private void Key_p_Click(object sender, EventArgs e)
        {
            switch (m_languageType)
            {
                case eLanguageType.TYPE_ENGLISH:
                    m_MixString.asciiCodeInput(Key_p.Text.ToCharArray()[0]);
                    break;
                case eLanguageType.TYPE_KOREAN:
                    if (m_bShift)
                        m_MixString.AddKoreanMoum(7);
                    else
                        m_MixString.AddKoreanMoum(5);
                    break;

            }

            RefreshString();
        }

        private void Key_a_Click(object sender, EventArgs e)
        {
            switch (m_languageType)
            {
                case eLanguageType.TYPE_ENGLISH:
                    m_MixString.asciiCodeInput(Key_a.Text.ToCharArray()[0]);
                    break;
                case eLanguageType.TYPE_KOREAN:
                    m_MixString.AddKoreanJaum(6);
                    break;

            }

            RefreshString();
        }

        private void Key_s_Click(object sender, EventArgs e)
        {
            switch (m_languageType)
            {
                case eLanguageType.TYPE_ENGLISH:
                    m_MixString.asciiCodeInput(Key_s.Text.ToCharArray()[0]);
                    break;
                case eLanguageType.TYPE_KOREAN:
                    m_MixString.AddKoreanJaum(2);
                    break;

            }

            RefreshString();
        }

        private void Key_d_Click(object sender, EventArgs e)
        {
            switch (m_languageType)
            {
                case eLanguageType.TYPE_ENGLISH:
                    m_MixString.asciiCodeInput(Key_d.Text.ToCharArray()[0]);
                    break;
                case eLanguageType.TYPE_KOREAN:
                    m_MixString.AddKoreanJaum(11);
                    break;

            }

            RefreshString();
        }

        private void Key_f_Click(object sender, EventArgs e)
        {
            switch (m_languageType)
            {
                case eLanguageType.TYPE_ENGLISH:
                    m_MixString.asciiCodeInput(Key_f.Text.ToCharArray()[0]);
                    break;
                case eLanguageType.TYPE_KOREAN:
                    m_MixString.AddKoreanJaum(5);
                    break;

            }

            RefreshString();
        }

        private void Key_g_Click(object sender, EventArgs e)
        {
            switch (m_languageType)
            {
                case eLanguageType.TYPE_ENGLISH:
                    m_MixString.asciiCodeInput(Key_g.Text.ToCharArray()[0]);
                    break;
                case eLanguageType.TYPE_KOREAN:
                    m_MixString.AddKoreanJaum(18);
                    break;

            }

            RefreshString();
        }

        private void Key_h_Click(object sender, EventArgs e)
        {
            switch (m_languageType)
            {
                case eLanguageType.TYPE_ENGLISH:
                    m_MixString.asciiCodeInput(Key_h.Text.ToCharArray()[0]);
                    break;
                case eLanguageType.TYPE_KOREAN:
                    m_MixString.AddKoreanMoum(8);
                    break;

            }

            RefreshString();
        }

        private void Key_j_Click(object sender, EventArgs e)
        {
            switch (m_languageType)
            {
                case eLanguageType.TYPE_ENGLISH:
                    m_MixString.asciiCodeInput(Key_j.Text.ToCharArray()[0]);
                    break;
                case eLanguageType.TYPE_KOREAN:
                    m_MixString.AddKoreanMoum(4);
                    break;

            }

            RefreshString();
        }

        private void Key_k_Click(object sender, EventArgs e)
        {
            switch (m_languageType)
            {
                case eLanguageType.TYPE_ENGLISH:
                    m_MixString.asciiCodeInput(Key_k.Text.ToCharArray()[0]);
                    break;
                case eLanguageType.TYPE_KOREAN:
                    m_MixString.AddKoreanMoum(0);
                    break;

            }

            RefreshString();
        }

        private void Key_l_Click(object sender, EventArgs e)
        {
            switch (m_languageType)
            {
                case eLanguageType.TYPE_ENGLISH:
                    m_MixString.asciiCodeInput(Key_l.Text.ToCharArray()[0]);
                    break;
                case eLanguageType.TYPE_KOREAN:
                    m_MixString.AddKoreanMoum(20);
                    break;

            }

            RefreshString();
        }

        private void Key_z_Click(object sender, EventArgs e)
        {
            switch (m_languageType)
            {
                case eLanguageType.TYPE_ENGLISH:
                    m_MixString.asciiCodeInput(Key_z.Text.ToCharArray()[0]);
                    break;
                case eLanguageType.TYPE_KOREAN:
                    m_MixString.AddKoreanJaum(15);
                    break;

            }

            RefreshString();
        }

        private void Key_x_Click(object sender, EventArgs e)
        {
            switch (m_languageType)
            {
                case eLanguageType.TYPE_ENGLISH:
                    m_MixString.asciiCodeInput(Key_x.Text.ToCharArray()[0]);
                    break;
                case eLanguageType.TYPE_KOREAN:
                    m_MixString.AddKoreanJaum(16);
                    break;

            }

            RefreshString();
        }

        private void Key_c_Click(object sender, EventArgs e)
        {
            switch (m_languageType)
            {
                case eLanguageType.TYPE_ENGLISH:
                    m_MixString.asciiCodeInput(Key_c.Text.ToCharArray()[0]);
                    break;
                case eLanguageType.TYPE_KOREAN:
                    m_MixString.AddKoreanJaum(14);
                    break;

            }

            RefreshString();
        }

        private void Key_v_Click(object sender, EventArgs e)
        {
            switch (m_languageType)
            {
                case eLanguageType.TYPE_ENGLISH:
                    m_MixString.asciiCodeInput(Key_v.Text.ToCharArray()[0]);
                    break;
                case eLanguageType.TYPE_KOREAN:
                    m_MixString.AddKoreanJaum(17);
                    break;

            }

            RefreshString();
        }

        private void Key_b_Click(object sender, EventArgs e)
        {
            switch (m_languageType)
            {
                case eLanguageType.TYPE_ENGLISH:
                    m_MixString.asciiCodeInput(Key_b.Text.ToCharArray()[0]);
                    break;
                case eLanguageType.TYPE_KOREAN:
                    m_MixString.AddKoreanMoum(17);
                    break;

            }

            RefreshString();
        }

        private void Key_n_Click(object sender, EventArgs e)
        {
            switch (m_languageType)
            {
                case eLanguageType.TYPE_ENGLISH:
                    m_MixString.asciiCodeInput(Key_n.Text.ToCharArray()[0]);
                    break;
                case eLanguageType.TYPE_KOREAN:
                    m_MixString.AddKoreanMoum(13);
                    break;

            }

            RefreshString();
        }

        private void Key_m_Click(object sender, EventArgs e)
        {
            switch (m_languageType)
            {
                case eLanguageType.TYPE_ENGLISH:
                    m_MixString.asciiCodeInput(Key_m.Text.ToCharArray()[0]);
                    break;
                case eLanguageType.TYPE_KOREAN:
                    m_MixString.AddKoreanMoum(18);
                    break;

            }

            RefreshString();
        }

        #endregion

    }
}
