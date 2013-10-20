namespace VirtualKeyboard
{
    partial class Form1
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다.
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마십시오.
        /// </summary>
        private void InitializeComponent()
        {
            this.Result = new System.Windows.Forms.Label();
            this.Space = new System.Windows.Forms.Button();
            this.Change = new System.Windows.Forms.Button();
            this.Key_Shift = new System.Windows.Forms.Button();
            this.Key_Caps = new System.Windows.Forms.Button();
            this.Key_z = new System.Windows.Forms.Button();
            this.Key_x = new System.Windows.Forms.Button();
            this.Key_v = new System.Windows.Forms.Button();
            this.Key_c = new System.Windows.Forms.Button();
            this.Key_rest = new System.Windows.Forms.Button();
            this.Key_m = new System.Windows.Forms.Button();
            this.Key_n = new System.Windows.Forms.Button();
            this.Key_b = new System.Windows.Forms.Button();
            this.Key_sla = new System.Windows.Forms.Button();
            this.Key_div = new System.Windows.Forms.Button();
            this.Key_Shift2 = new System.Windows.Forms.Button();
            this.Key_col = new System.Windows.Forms.Button();
            this.Key_l = new System.Windows.Forms.Button();
            this.Key_k = new System.Windows.Forms.Button();
            this.Key_j = new System.Windows.Forms.Button();
            this.Key_h = new System.Windows.Forms.Button();
            this.Key_g = new System.Windows.Forms.Button();
            this.Key_f = new System.Windows.Forms.Button();
            this.Key_d = new System.Windows.Forms.Button();
            this.Key_s = new System.Windows.Forms.Button();
            this.Key_a = new System.Windows.Forms.Button();
            this.Key_apo = new System.Windows.Forms.Button();
            this.Key_Lbra = new System.Windows.Forms.Button();
            this.Key_p = new System.Windows.Forms.Button();
            this.Key_o = new System.Windows.Forms.Button();
            this.Key_i = new System.Windows.Forms.Button();
            this.Key_u = new System.Windows.Forms.Button();
            this.Key_y = new System.Windows.Forms.Button();
            this.Key_t = new System.Windows.Forms.Button();
            this.Key_r = new System.Windows.Forms.Button();
            this.Key_e = new System.Windows.Forms.Button();
            this.Key_w = new System.Windows.Forms.Button();
            this.Key_q = new System.Windows.Forms.Button();
            this.Key_Rbra = new System.Windows.Forms.Button();
            this.Key_equ = new System.Windows.Forms.Button();
            this.Key_sub = new System.Windows.Forms.Button();
            this.Key_0 = new System.Windows.Forms.Button();
            this.Key_9 = new System.Windows.Forms.Button();
            this.Key_8 = new System.Windows.Forms.Button();
            this.Key_7 = new System.Windows.Forms.Button();
            this.Key_6 = new System.Windows.Forms.Button();
            this.Key_5 = new System.Windows.Forms.Button();
            this.Key_4 = new System.Windows.Forms.Button();
            this.Key_3 = new System.Windows.Forms.Button();
            this.Key_2 = new System.Windows.Forms.Button();
            this.Key_1 = new System.Windows.Forms.Button();
            this.Key_backsla = new System.Windows.Forms.Button();
            this.Key_Backsapce = new System.Windows.Forms.Button();
            this.Key_apo2 = new System.Windows.Forms.Button();
            this.Shift_Push = new System.Windows.Forms.CheckBox();
            this.Caps_check = new System.Windows.Forms.CheckBox();
            this.SuspendLayout();
            // 
            // Result
            // 
            this.Result.AutoSize = true;
            this.Result.Font = new System.Drawing.Font("굴림", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.Result.Location = new System.Drawing.Point(73, 48);
            this.Result.Name = "Result";
            this.Result.Size = new System.Drawing.Size(77, 16);
            this.Result.TabIndex = 0;
            this.Result.Text = "Keyboard";
            // 
            // Space
            // 
            this.Space.Location = new System.Drawing.Point(113, 209);
            this.Space.Name = "Space";
            this.Space.Size = new System.Drawing.Size(324, 23);
            this.Space.TabIndex = 1;
            this.Space.Text = "Space";
            this.Space.UseVisualStyleBackColor = true;
            this.Space.Click += new System.EventHandler(this.Space_Click);
            // 
            // Change
            // 
            this.Change.Location = new System.Drawing.Point(443, 209);
            this.Change.Name = "Change";
            this.Change.Size = new System.Drawing.Size(49, 23);
            this.Change.TabIndex = 2;
            this.Change.Text = "한글";
            this.Change.UseVisualStyleBackColor = true;
            this.Change.Click += new System.EventHandler(this.Change_Click);
            // 
            // Key_Shift
            // 
            this.Key_Shift.Location = new System.Drawing.Point(19, 185);
            this.Key_Shift.Name = "Key_Shift";
            this.Key_Shift.Size = new System.Drawing.Size(88, 23);
            this.Key_Shift.TabIndex = 3;
            this.Key_Shift.Text = "Shift";
            this.Key_Shift.UseVisualStyleBackColor = true;
            this.Key_Shift.Click += new System.EventHandler(this.Key_Shift_Click);
            // 
            // Key_Caps
            // 
            this.Key_Caps.Location = new System.Drawing.Point(19, 156);
            this.Key_Caps.Name = "Key_Caps";
            this.Key_Caps.Size = new System.Drawing.Size(77, 23);
            this.Key_Caps.TabIndex = 4;
            this.Key_Caps.Text = "Caps Lock";
            this.Key_Caps.UseVisualStyleBackColor = true;
            this.Key_Caps.Click += new System.EventHandler(this.Key_Caps_Click);
            // 
            // Key_z
            // 
            this.Key_z.Location = new System.Drawing.Point(113, 185);
            this.Key_z.Name = "Key_z";
            this.Key_z.Size = new System.Drawing.Size(27, 23);
            this.Key_z.TabIndex = 5;
            this.Key_z.Text = "z";
            this.Key_z.UseVisualStyleBackColor = true;
            this.Key_z.Click += new System.EventHandler(this.Key_z_Click);
            // 
            // Key_x
            // 
            this.Key_x.Location = new System.Drawing.Point(146, 185);
            this.Key_x.Name = "Key_x";
            this.Key_x.Size = new System.Drawing.Size(27, 23);
            this.Key_x.TabIndex = 6;
            this.Key_x.Text = "x";
            this.Key_x.UseVisualStyleBackColor = true;
            this.Key_x.Click += new System.EventHandler(this.Key_x_Click);
            // 
            // Key_v
            // 
            this.Key_v.Location = new System.Drawing.Point(212, 185);
            this.Key_v.Name = "Key_v";
            this.Key_v.Size = new System.Drawing.Size(27, 23);
            this.Key_v.TabIndex = 8;
            this.Key_v.Text = "v";
            this.Key_v.UseVisualStyleBackColor = true;
            this.Key_v.Click += new System.EventHandler(this.Key_v_Click);
            // 
            // Key_c
            // 
            this.Key_c.Location = new System.Drawing.Point(179, 185);
            this.Key_c.Name = "Key_c";
            this.Key_c.Size = new System.Drawing.Size(27, 23);
            this.Key_c.TabIndex = 7;
            this.Key_c.Text = "c";
            this.Key_c.UseVisualStyleBackColor = true;
            this.Key_c.Click += new System.EventHandler(this.Key_c_Click);
            // 
            // Key_rest
            // 
            this.Key_rest.Location = new System.Drawing.Point(344, 185);
            this.Key_rest.Name = "Key_rest";
            this.Key_rest.Size = new System.Drawing.Size(27, 23);
            this.Key_rest.TabIndex = 12;
            this.Key_rest.Text = ",";
            this.Key_rest.UseVisualStyleBackColor = true;
            this.Key_rest.Click += new System.EventHandler(this.Key_rest_Click);
            // 
            // Key_m
            // 
            this.Key_m.Location = new System.Drawing.Point(311, 185);
            this.Key_m.Name = "Key_m";
            this.Key_m.Size = new System.Drawing.Size(27, 23);
            this.Key_m.TabIndex = 11;
            this.Key_m.Text = "m";
            this.Key_m.UseVisualStyleBackColor = true;
            this.Key_m.Click += new System.EventHandler(this.Key_m_Click);
            // 
            // Key_n
            // 
            this.Key_n.Location = new System.Drawing.Point(278, 185);
            this.Key_n.Name = "Key_n";
            this.Key_n.Size = new System.Drawing.Size(27, 23);
            this.Key_n.TabIndex = 10;
            this.Key_n.Text = "n";
            this.Key_n.UseVisualStyleBackColor = true;
            this.Key_n.Click += new System.EventHandler(this.Key_n_Click);
            // 
            // Key_b
            // 
            this.Key_b.Location = new System.Drawing.Point(245, 185);
            this.Key_b.Name = "Key_b";
            this.Key_b.Size = new System.Drawing.Size(27, 23);
            this.Key_b.TabIndex = 9;
            this.Key_b.Text = "b";
            this.Key_b.UseVisualStyleBackColor = true;
            this.Key_b.Click += new System.EventHandler(this.Key_b_Click);
            // 
            // Key_sla
            // 
            this.Key_sla.Location = new System.Drawing.Point(410, 185);
            this.Key_sla.Name = "Key_sla";
            this.Key_sla.Size = new System.Drawing.Size(27, 23);
            this.Key_sla.TabIndex = 14;
            this.Key_sla.Text = "/";
            this.Key_sla.UseVisualStyleBackColor = true;
            this.Key_sla.Click += new System.EventHandler(this.Key_sla_Click);
            // 
            // Key_div
            // 
            this.Key_div.Location = new System.Drawing.Point(377, 185);
            this.Key_div.Name = "Key_div";
            this.Key_div.Size = new System.Drawing.Size(27, 23);
            this.Key_div.TabIndex = 13;
            this.Key_div.Text = ".";
            this.Key_div.UseVisualStyleBackColor = true;
            this.Key_div.Click += new System.EventHandler(this.Key_div_Click);
            // 
            // Key_Shift2
            // 
            this.Key_Shift2.Location = new System.Drawing.Point(443, 185);
            this.Key_Shift2.Name = "Key_Shift2";
            this.Key_Shift2.Size = new System.Drawing.Size(88, 23);
            this.Key_Shift2.TabIndex = 15;
            this.Key_Shift2.Text = "Shift";
            this.Key_Shift2.UseVisualStyleBackColor = true;
            this.Key_Shift2.Click += new System.EventHandler(this.Key_Shift_Click);
            // 
            // Key_col
            // 
            this.Key_col.Location = new System.Drawing.Point(399, 156);
            this.Key_col.Name = "Key_col";
            this.Key_col.Size = new System.Drawing.Size(27, 23);
            this.Key_col.TabIndex = 25;
            this.Key_col.Text = ";";
            this.Key_col.UseVisualStyleBackColor = true;
            this.Key_col.Click += new System.EventHandler(this.Key_col_Click);
            // 
            // Key_l
            // 
            this.Key_l.Location = new System.Drawing.Point(366, 156);
            this.Key_l.Name = "Key_l";
            this.Key_l.Size = new System.Drawing.Size(27, 23);
            this.Key_l.TabIndex = 24;
            this.Key_l.Text = "l";
            this.Key_l.UseVisualStyleBackColor = true;
            this.Key_l.Click += new System.EventHandler(this.Key_l_Click);
            // 
            // Key_k
            // 
            this.Key_k.Location = new System.Drawing.Point(333, 156);
            this.Key_k.Name = "Key_k";
            this.Key_k.Size = new System.Drawing.Size(27, 23);
            this.Key_k.TabIndex = 23;
            this.Key_k.Text = "k";
            this.Key_k.UseVisualStyleBackColor = true;
            this.Key_k.Click += new System.EventHandler(this.Key_k_Click);
            // 
            // Key_j
            // 
            this.Key_j.Location = new System.Drawing.Point(300, 156);
            this.Key_j.Name = "Key_j";
            this.Key_j.Size = new System.Drawing.Size(27, 23);
            this.Key_j.TabIndex = 22;
            this.Key_j.Text = "j";
            this.Key_j.UseVisualStyleBackColor = true;
            this.Key_j.Click += new System.EventHandler(this.Key_j_Click);
            // 
            // Key_h
            // 
            this.Key_h.Location = new System.Drawing.Point(267, 156);
            this.Key_h.Name = "Key_h";
            this.Key_h.Size = new System.Drawing.Size(27, 23);
            this.Key_h.TabIndex = 21;
            this.Key_h.Text = "h";
            this.Key_h.UseVisualStyleBackColor = true;
            this.Key_h.Click += new System.EventHandler(this.Key_h_Click);
            // 
            // Key_g
            // 
            this.Key_g.Location = new System.Drawing.Point(234, 156);
            this.Key_g.Name = "Key_g";
            this.Key_g.Size = new System.Drawing.Size(27, 23);
            this.Key_g.TabIndex = 20;
            this.Key_g.Text = "g";
            this.Key_g.UseVisualStyleBackColor = true;
            this.Key_g.Click += new System.EventHandler(this.Key_g_Click);
            // 
            // Key_f
            // 
            this.Key_f.Location = new System.Drawing.Point(201, 156);
            this.Key_f.Name = "Key_f";
            this.Key_f.Size = new System.Drawing.Size(27, 23);
            this.Key_f.TabIndex = 19;
            this.Key_f.Text = "f";
            this.Key_f.UseVisualStyleBackColor = true;
            this.Key_f.Click += new System.EventHandler(this.Key_f_Click);
            // 
            // Key_d
            // 
            this.Key_d.Location = new System.Drawing.Point(168, 156);
            this.Key_d.Name = "Key_d";
            this.Key_d.Size = new System.Drawing.Size(27, 23);
            this.Key_d.TabIndex = 18;
            this.Key_d.Text = "d";
            this.Key_d.UseVisualStyleBackColor = true;
            this.Key_d.Click += new System.EventHandler(this.Key_d_Click);
            // 
            // Key_s
            // 
            this.Key_s.Location = new System.Drawing.Point(135, 156);
            this.Key_s.Name = "Key_s";
            this.Key_s.Size = new System.Drawing.Size(27, 23);
            this.Key_s.TabIndex = 17;
            this.Key_s.Text = "s";
            this.Key_s.UseVisualStyleBackColor = true;
            this.Key_s.Click += new System.EventHandler(this.Key_s_Click);
            // 
            // Key_a
            // 
            this.Key_a.Location = new System.Drawing.Point(102, 156);
            this.Key_a.Name = "Key_a";
            this.Key_a.Size = new System.Drawing.Size(27, 23);
            this.Key_a.TabIndex = 16;
            this.Key_a.Text = "a";
            this.Key_a.UseVisualStyleBackColor = true;
            this.Key_a.Click += new System.EventHandler(this.Key_a_Click);
            // 
            // Key_apo
            // 
            this.Key_apo.Location = new System.Drawing.Point(432, 156);
            this.Key_apo.Name = "Key_apo";
            this.Key_apo.Size = new System.Drawing.Size(27, 23);
            this.Key_apo.TabIndex = 26;
            this.Key_apo.Text = "\'";
            this.Key_apo.UseVisualStyleBackColor = true;
            this.Key_apo.Click += new System.EventHandler(this.Key_apo_Click);
            // 
            // Key_Lbra
            // 
            this.Key_Lbra.Location = new System.Drawing.Point(410, 127);
            this.Key_Lbra.Name = "Key_Lbra";
            this.Key_Lbra.Size = new System.Drawing.Size(27, 23);
            this.Key_Lbra.TabIndex = 37;
            this.Key_Lbra.Text = "[";
            this.Key_Lbra.UseVisualStyleBackColor = true;
            this.Key_Lbra.Click += new System.EventHandler(this.Key_Lbra_Click);
            // 
            // Key_p
            // 
            this.Key_p.Location = new System.Drawing.Point(377, 127);
            this.Key_p.Name = "Key_p";
            this.Key_p.Size = new System.Drawing.Size(27, 23);
            this.Key_p.TabIndex = 36;
            this.Key_p.Text = "p";
            this.Key_p.UseVisualStyleBackColor = true;
            this.Key_p.Click += new System.EventHandler(this.Key_p_Click);
            // 
            // Key_o
            // 
            this.Key_o.Location = new System.Drawing.Point(344, 127);
            this.Key_o.Name = "Key_o";
            this.Key_o.Size = new System.Drawing.Size(27, 23);
            this.Key_o.TabIndex = 35;
            this.Key_o.Text = "o";
            this.Key_o.UseVisualStyleBackColor = true;
            this.Key_o.Click += new System.EventHandler(this.Key_o_Click);
            // 
            // Key_i
            // 
            this.Key_i.Location = new System.Drawing.Point(311, 127);
            this.Key_i.Name = "Key_i";
            this.Key_i.Size = new System.Drawing.Size(27, 23);
            this.Key_i.TabIndex = 34;
            this.Key_i.Text = "i";
            this.Key_i.UseVisualStyleBackColor = true;
            this.Key_i.Click += new System.EventHandler(this.Key_i_Click);
            // 
            // Key_u
            // 
            this.Key_u.Location = new System.Drawing.Point(278, 127);
            this.Key_u.Name = "Key_u";
            this.Key_u.Size = new System.Drawing.Size(27, 23);
            this.Key_u.TabIndex = 33;
            this.Key_u.Text = "u";
            this.Key_u.UseVisualStyleBackColor = true;
            this.Key_u.Click += new System.EventHandler(this.Key_u_Click);
            // 
            // Key_y
            // 
            this.Key_y.Location = new System.Drawing.Point(245, 127);
            this.Key_y.Name = "Key_y";
            this.Key_y.Size = new System.Drawing.Size(27, 23);
            this.Key_y.TabIndex = 32;
            this.Key_y.Text = "y";
            this.Key_y.UseVisualStyleBackColor = true;
            this.Key_y.Click += new System.EventHandler(this.Key_y_Click);
            // 
            // Key_t
            // 
            this.Key_t.Location = new System.Drawing.Point(212, 127);
            this.Key_t.Name = "Key_t";
            this.Key_t.Size = new System.Drawing.Size(27, 23);
            this.Key_t.TabIndex = 31;
            this.Key_t.Text = "t";
            this.Key_t.UseVisualStyleBackColor = true;
            this.Key_t.Click += new System.EventHandler(this.Key_t_Click);
            // 
            // Key_r
            // 
            this.Key_r.Location = new System.Drawing.Point(179, 127);
            this.Key_r.Name = "Key_r";
            this.Key_r.Size = new System.Drawing.Size(27, 23);
            this.Key_r.TabIndex = 30;
            this.Key_r.Text = "r";
            this.Key_r.UseVisualStyleBackColor = true;
            this.Key_r.Click += new System.EventHandler(this.Key_r_Click);
            // 
            // Key_e
            // 
            this.Key_e.Location = new System.Drawing.Point(146, 127);
            this.Key_e.Name = "Key_e";
            this.Key_e.Size = new System.Drawing.Size(27, 23);
            this.Key_e.TabIndex = 29;
            this.Key_e.Text = "e";
            this.Key_e.UseVisualStyleBackColor = true;
            this.Key_e.Click += new System.EventHandler(this.Key_e_Click);
            // 
            // Key_w
            // 
            this.Key_w.Location = new System.Drawing.Point(113, 127);
            this.Key_w.Name = "Key_w";
            this.Key_w.Size = new System.Drawing.Size(27, 23);
            this.Key_w.TabIndex = 28;
            this.Key_w.Text = "w";
            this.Key_w.UseVisualStyleBackColor = true;
            this.Key_w.Click += new System.EventHandler(this.Key_w_Click);
            // 
            // Key_q
            // 
            this.Key_q.Location = new System.Drawing.Point(80, 127);
            this.Key_q.Name = "Key_q";
            this.Key_q.Size = new System.Drawing.Size(27, 23);
            this.Key_q.TabIndex = 27;
            this.Key_q.Text = "q";
            this.Key_q.UseVisualStyleBackColor = true;
            this.Key_q.Click += new System.EventHandler(this.Key_q_Click);
            // 
            // Key_Rbra
            // 
            this.Key_Rbra.Location = new System.Drawing.Point(443, 127);
            this.Key_Rbra.Name = "Key_Rbra";
            this.Key_Rbra.Size = new System.Drawing.Size(27, 23);
            this.Key_Rbra.TabIndex = 38;
            this.Key_Rbra.Text = "]";
            this.Key_Rbra.UseVisualStyleBackColor = true;
            this.Key_Rbra.Click += new System.EventHandler(this.Key_Rbra_Click);
            // 
            // Key_equ
            // 
            this.Key_equ.Location = new System.Drawing.Point(432, 98);
            this.Key_equ.Name = "Key_equ";
            this.Key_equ.Size = new System.Drawing.Size(27, 23);
            this.Key_equ.TabIndex = 50;
            this.Key_equ.Text = "=";
            this.Key_equ.UseVisualStyleBackColor = true;
            this.Key_equ.Click += new System.EventHandler(this.Key_equ_Click);
            // 
            // Key_sub
            // 
            this.Key_sub.Location = new System.Drawing.Point(399, 98);
            this.Key_sub.Name = "Key_sub";
            this.Key_sub.Size = new System.Drawing.Size(27, 23);
            this.Key_sub.TabIndex = 49;
            this.Key_sub.Text = "-";
            this.Key_sub.UseVisualStyleBackColor = true;
            this.Key_sub.Click += new System.EventHandler(this.Key_sub_Click);
            // 
            // Key_0
            // 
            this.Key_0.Location = new System.Drawing.Point(366, 98);
            this.Key_0.Name = "Key_0";
            this.Key_0.Size = new System.Drawing.Size(27, 23);
            this.Key_0.TabIndex = 48;
            this.Key_0.Text = "0";
            this.Key_0.UseVisualStyleBackColor = true;
            this.Key_0.Click += new System.EventHandler(this.Key_0_Click);
            // 
            // Key_9
            // 
            this.Key_9.Location = new System.Drawing.Point(333, 98);
            this.Key_9.Name = "Key_9";
            this.Key_9.Size = new System.Drawing.Size(27, 23);
            this.Key_9.TabIndex = 47;
            this.Key_9.Text = "9";
            this.Key_9.UseVisualStyleBackColor = true;
            this.Key_9.Click += new System.EventHandler(this.Key_9_Click);
            // 
            // Key_8
            // 
            this.Key_8.Location = new System.Drawing.Point(300, 98);
            this.Key_8.Name = "Key_8";
            this.Key_8.Size = new System.Drawing.Size(27, 23);
            this.Key_8.TabIndex = 46;
            this.Key_8.Text = "8";
            this.Key_8.UseVisualStyleBackColor = true;
            this.Key_8.Click += new System.EventHandler(this.Key_8_Click);
            // 
            // Key_7
            // 
            this.Key_7.Location = new System.Drawing.Point(267, 98);
            this.Key_7.Name = "Key_7";
            this.Key_7.Size = new System.Drawing.Size(27, 23);
            this.Key_7.TabIndex = 45;
            this.Key_7.Text = "7";
            this.Key_7.UseVisualStyleBackColor = true;
            this.Key_7.Click += new System.EventHandler(this.Key_7_Click);
            // 
            // Key_6
            // 
            this.Key_6.Location = new System.Drawing.Point(234, 98);
            this.Key_6.Name = "Key_6";
            this.Key_6.Size = new System.Drawing.Size(27, 23);
            this.Key_6.TabIndex = 44;
            this.Key_6.Text = "6";
            this.Key_6.UseVisualStyleBackColor = true;
            this.Key_6.Click += new System.EventHandler(this.Key_6_Click);
            // 
            // Key_5
            // 
            this.Key_5.Location = new System.Drawing.Point(201, 98);
            this.Key_5.Name = "Key_5";
            this.Key_5.Size = new System.Drawing.Size(27, 23);
            this.Key_5.TabIndex = 43;
            this.Key_5.Text = "5";
            this.Key_5.UseVisualStyleBackColor = true;
            this.Key_5.Click += new System.EventHandler(this.Key_5_Click);
            // 
            // Key_4
            // 
            this.Key_4.Location = new System.Drawing.Point(168, 98);
            this.Key_4.Name = "Key_4";
            this.Key_4.Size = new System.Drawing.Size(27, 23);
            this.Key_4.TabIndex = 42;
            this.Key_4.Text = "4";
            this.Key_4.UseVisualStyleBackColor = true;
            this.Key_4.Click += new System.EventHandler(this.Key_4_Click);
            // 
            // Key_3
            // 
            this.Key_3.Location = new System.Drawing.Point(135, 98);
            this.Key_3.Name = "Key_3";
            this.Key_3.Size = new System.Drawing.Size(27, 23);
            this.Key_3.TabIndex = 41;
            this.Key_3.Text = "3";
            this.Key_3.UseVisualStyleBackColor = true;
            this.Key_3.Click += new System.EventHandler(this.Key_3_Click);
            // 
            // Key_2
            // 
            this.Key_2.Location = new System.Drawing.Point(102, 98);
            this.Key_2.Name = "Key_2";
            this.Key_2.Size = new System.Drawing.Size(27, 23);
            this.Key_2.TabIndex = 40;
            this.Key_2.Text = "2";
            this.Key_2.UseVisualStyleBackColor = true;
            this.Key_2.Click += new System.EventHandler(this.Key_2_Click);
            // 
            // Key_1
            // 
            this.Key_1.Location = new System.Drawing.Point(69, 98);
            this.Key_1.Name = "Key_1";
            this.Key_1.Size = new System.Drawing.Size(27, 23);
            this.Key_1.TabIndex = 39;
            this.Key_1.Text = "1";
            this.Key_1.UseVisualStyleBackColor = true;
            this.Key_1.Click += new System.EventHandler(this.Key_1_Click);
            // 
            // Key_backsla
            // 
            this.Key_backsla.Location = new System.Drawing.Point(465, 98);
            this.Key_backsla.Name = "Key_backsla";
            this.Key_backsla.Size = new System.Drawing.Size(27, 23);
            this.Key_backsla.TabIndex = 51;
            this.Key_backsla.Text = "\\";
            this.Key_backsla.UseVisualStyleBackColor = true;
            this.Key_backsla.Click += new System.EventHandler(this.Key_backsla_Click);
            // 
            // Key_Backsapce
            // 
            this.Key_Backsapce.Location = new System.Drawing.Point(498, 98);
            this.Key_Backsapce.Name = "Key_Backsapce";
            this.Key_Backsapce.Size = new System.Drawing.Size(33, 23);
            this.Key_Backsapce.TabIndex = 52;
            this.Key_Backsapce.Text = "←";
            this.Key_Backsapce.UseVisualStyleBackColor = true;
            this.Key_Backsapce.Click += new System.EventHandler(this.Key_Backsapce_Click);
            // 
            // Key_apo2
            // 
            this.Key_apo2.Location = new System.Drawing.Point(36, 98);
            this.Key_apo2.Name = "Key_apo2";
            this.Key_apo2.Size = new System.Drawing.Size(27, 23);
            this.Key_apo2.TabIndex = 53;
            this.Key_apo2.Text = "`";
            this.Key_apo2.UseVisualStyleBackColor = true;
            this.Key_apo2.Click += new System.EventHandler(this.Key_apo2_Click);
            // 
            // Shift_Push
            // 
            this.Shift_Push.AutoSize = true;
            this.Shift_Push.Enabled = false;
            this.Shift_Push.Location = new System.Drawing.Point(546, 98);
            this.Shift_Push.Name = "Shift_Push";
            this.Shift_Push.Size = new System.Drawing.Size(81, 16);
            this.Shift_Push.TabIndex = 54;
            this.Shift_Push.Text = "Shift Push";
            this.Shift_Push.UseVisualStyleBackColor = true;
            // 
            // Caps_check
            // 
            this.Caps_check.AutoSize = true;
            this.Caps_check.Enabled = false;
            this.Caps_check.Location = new System.Drawing.Point(546, 120);
            this.Caps_check.Name = "Caps_check";
            this.Caps_check.Size = new System.Drawing.Size(85, 16);
            this.Caps_check.TabIndex = 55;
            this.Caps_check.Text = "Caps Lock";
            this.Caps_check.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(663, 247);
            this.Controls.Add(this.Caps_check);
            this.Controls.Add(this.Shift_Push);
            this.Controls.Add(this.Key_apo2);
            this.Controls.Add(this.Key_Backsapce);
            this.Controls.Add(this.Key_backsla);
            this.Controls.Add(this.Key_equ);
            this.Controls.Add(this.Key_sub);
            this.Controls.Add(this.Key_0);
            this.Controls.Add(this.Key_9);
            this.Controls.Add(this.Key_8);
            this.Controls.Add(this.Key_7);
            this.Controls.Add(this.Key_6);
            this.Controls.Add(this.Key_5);
            this.Controls.Add(this.Key_4);
            this.Controls.Add(this.Key_3);
            this.Controls.Add(this.Key_2);
            this.Controls.Add(this.Key_1);
            this.Controls.Add(this.Key_Rbra);
            this.Controls.Add(this.Key_Lbra);
            this.Controls.Add(this.Key_p);
            this.Controls.Add(this.Key_o);
            this.Controls.Add(this.Key_i);
            this.Controls.Add(this.Key_u);
            this.Controls.Add(this.Key_y);
            this.Controls.Add(this.Key_t);
            this.Controls.Add(this.Key_r);
            this.Controls.Add(this.Key_e);
            this.Controls.Add(this.Key_w);
            this.Controls.Add(this.Key_q);
            this.Controls.Add(this.Key_apo);
            this.Controls.Add(this.Key_col);
            this.Controls.Add(this.Key_l);
            this.Controls.Add(this.Key_k);
            this.Controls.Add(this.Key_j);
            this.Controls.Add(this.Key_h);
            this.Controls.Add(this.Key_g);
            this.Controls.Add(this.Key_f);
            this.Controls.Add(this.Key_d);
            this.Controls.Add(this.Key_s);
            this.Controls.Add(this.Key_a);
            this.Controls.Add(this.Key_Shift2);
            this.Controls.Add(this.Key_sla);
            this.Controls.Add(this.Key_div);
            this.Controls.Add(this.Key_rest);
            this.Controls.Add(this.Key_m);
            this.Controls.Add(this.Key_n);
            this.Controls.Add(this.Key_b);
            this.Controls.Add(this.Key_v);
            this.Controls.Add(this.Key_c);
            this.Controls.Add(this.Key_x);
            this.Controls.Add(this.Key_z);
            this.Controls.Add(this.Key_Caps);
            this.Controls.Add(this.Key_Shift);
            this.Controls.Add(this.Change);
            this.Controls.Add(this.Space);
            this.Controls.Add(this.Result);
            this.Name = "Form1";
            this.Text = "Virtual Keyboard";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label Result;
        private System.Windows.Forms.Button Space;
        private System.Windows.Forms.Button Change;
        private System.Windows.Forms.Button Key_Shift;
        private System.Windows.Forms.Button Key_Caps;
        private System.Windows.Forms.Button Key_z;
        private System.Windows.Forms.Button Key_x;
        private System.Windows.Forms.Button Key_v;
        private System.Windows.Forms.Button Key_c;
        private System.Windows.Forms.Button Key_rest;
        private System.Windows.Forms.Button Key_m;
        private System.Windows.Forms.Button Key_n;
        private System.Windows.Forms.Button Key_b;
        private System.Windows.Forms.Button Key_sla;
        private System.Windows.Forms.Button Key_div;
        private System.Windows.Forms.Button Key_Shift2;
        private System.Windows.Forms.Button Key_col;
        private System.Windows.Forms.Button Key_l;
        private System.Windows.Forms.Button Key_k;
        private System.Windows.Forms.Button Key_j;
        private System.Windows.Forms.Button Key_h;
        private System.Windows.Forms.Button Key_g;
        private System.Windows.Forms.Button Key_f;
        private System.Windows.Forms.Button Key_d;
        private System.Windows.Forms.Button Key_s;
        private System.Windows.Forms.Button Key_a;
        private System.Windows.Forms.Button Key_apo;
        private System.Windows.Forms.Button Key_Lbra;
        private System.Windows.Forms.Button Key_p;
        private System.Windows.Forms.Button Key_o;
        private System.Windows.Forms.Button Key_i;
        private System.Windows.Forms.Button Key_u;
        private System.Windows.Forms.Button Key_y;
        private System.Windows.Forms.Button Key_t;
        private System.Windows.Forms.Button Key_r;
        private System.Windows.Forms.Button Key_e;
        private System.Windows.Forms.Button Key_w;
        private System.Windows.Forms.Button Key_q;
        private System.Windows.Forms.Button Key_Rbra;
        private System.Windows.Forms.Button Key_equ;
        private System.Windows.Forms.Button Key_sub;
        private System.Windows.Forms.Button Key_0;
        private System.Windows.Forms.Button Key_9;
        private System.Windows.Forms.Button Key_8;
        private System.Windows.Forms.Button Key_7;
        private System.Windows.Forms.Button Key_6;
        private System.Windows.Forms.Button Key_5;
        private System.Windows.Forms.Button Key_4;
        private System.Windows.Forms.Button Key_3;
        private System.Windows.Forms.Button Key_2;
        private System.Windows.Forms.Button Key_1;
        private System.Windows.Forms.Button Key_backsla;
        private System.Windows.Forms.Button Key_Backsapce;
        private System.Windows.Forms.Button Key_apo2;
        private System.Windows.Forms.CheckBox Shift_Push;
        private System.Windows.Forms.CheckBox Caps_check;


    }
}

