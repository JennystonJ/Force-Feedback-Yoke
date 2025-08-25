namespace MSFSForceFeedbackController
{
    partial class MainForm
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            components = new System.ComponentModel.Container();
            label2 = new Label();
            label3 = new Label();
            tabControl1 = new TabControl();
            tabPageElevator = new TabPage();
            groupBox4 = new GroupBox();
            label27 = new Label();
            nudEngineCenterStrength = new NumericUpDown();
            tbEngineCenterStrength = new TrackBar();
            label28 = new Label();
            label13 = new Label();
            nudElevatorAirSpeedStiffness = new NumericUpDown();
            tbElevatorAirSpeedStiffness = new TrackBar();
            label14 = new Label();
            label12 = new Label();
            nudEngineOffWeight = new NumericUpDown();
            tbEngineOffWeight = new TrackBar();
            label11 = new Label();
            groupBox2 = new GroupBox();
            label4 = new Label();
            nudElevatorMaxForce = new NumericUpDown();
            label5 = new Label();
            tbElevatorMaxForce = new TrackBar();
            lblPercent = new Label();
            nudElevatorGain = new NumericUpDown();
            lblGain = new Label();
            tbElevatorGain = new TrackBar();
            cbElevatorFFBEnable = new CheckBox();
            groupBox1 = new GroupBox();
            label8 = new Label();
            nudElevatorRange = new NumericUpDown();
            lblRange = new Label();
            tabPageAileron = new TabPage();
            groupBox7 = new GroupBox();
            label21 = new Label();
            numericUpDown9 = new NumericUpDown();
            trackBar6 = new TrackBar();
            label22 = new Label();
            groupBox6 = new GroupBox();
            label17 = new Label();
            numericUpDown7 = new NumericUpDown();
            label18 = new Label();
            trackBar4 = new TrackBar();
            label19 = new Label();
            numericUpDown8 = new NumericUpDown();
            label20 = new Label();
            trackBar5 = new TrackBar();
            cbAileronFFBEnable = new CheckBox();
            groupBox5 = new GroupBox();
            label15 = new Label();
            nudAileronRange = new NumericUpDown();
            label16 = new Label();
            tabPage3 = new TabPage();
            tableLayoutPanel1 = new TableLayoutPanel();
            btnStartStop = new Button();
            btnConnectSim = new Button();
            groupBox3 = new GroupBox();
            cbDisableInput = new CheckBox();
            btnVisualizer = new Button();
            lblElevatorFeedbackIndicator = new Label();
            tiElevatorFeedback = new TravelIndicator();
            label6 = new Label();
            label25 = new Label();
            label26 = new Label();
            lblAileronFeedbackIndicator = new Label();
            tiAileronFeedback = new TravelIndicator();
            label24 = new Label();
            label23 = new Label();
            tiElevator = new TravelIndicator();
            tiAileron = new TravelIndicator();
            nudEngineRPM = new NumericUpDown();
            label1 = new Label();
            label10 = new Label();
            rbTest = new RadioButton();
            rbFromSim = new RadioButton();
            nudAirSpeed = new NumericUpDown();
            label9 = new Label();
            lblElevatorIndicator = new Label();
            lblAileronIndicator = new Label();
            label7 = new Label();
            testForceUpdateTimer = new System.Windows.Forms.Timer(components);
            tabControl1.SuspendLayout();
            tabPageElevator.SuspendLayout();
            groupBox4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)nudEngineCenterStrength).BeginInit();
            ((System.ComponentModel.ISupportInitialize)tbEngineCenterStrength).BeginInit();
            ((System.ComponentModel.ISupportInitialize)nudElevatorAirSpeedStiffness).BeginInit();
            ((System.ComponentModel.ISupportInitialize)tbElevatorAirSpeedStiffness).BeginInit();
            ((System.ComponentModel.ISupportInitialize)nudEngineOffWeight).BeginInit();
            ((System.ComponentModel.ISupportInitialize)tbEngineOffWeight).BeginInit();
            groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)nudElevatorMaxForce).BeginInit();
            ((System.ComponentModel.ISupportInitialize)tbElevatorMaxForce).BeginInit();
            ((System.ComponentModel.ISupportInitialize)nudElevatorGain).BeginInit();
            ((System.ComponentModel.ISupportInitialize)tbElevatorGain).BeginInit();
            groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)nudElevatorRange).BeginInit();
            tabPageAileron.SuspendLayout();
            groupBox7.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)numericUpDown9).BeginInit();
            ((System.ComponentModel.ISupportInitialize)trackBar6).BeginInit();
            groupBox6.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)numericUpDown7).BeginInit();
            ((System.ComponentModel.ISupportInitialize)trackBar4).BeginInit();
            ((System.ComponentModel.ISupportInitialize)numericUpDown8).BeginInit();
            ((System.ComponentModel.ISupportInitialize)trackBar5).BeginInit();
            groupBox5.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)nudAileronRange).BeginInit();
            tableLayoutPanel1.SuspendLayout();
            groupBox3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)nudEngineRPM).BeginInit();
            ((System.ComponentModel.ISupportInitialize)nudAirSpeed).BeginInit();
            SuspendLayout();
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(147, 580);
            label2.Margin = new Padding(4, 0, 4, 0);
            label2.Name = "label2";
            label2.Size = new Size(221, 32);
            label2.TabIndex = 4;
            label2.Text = "Periodic Amplitude:";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(176, 597);
            label3.Margin = new Padding(4, 0, 4, 0);
            label3.Name = "label3";
            label3.Size = new Size(221, 32);
            label3.TabIndex = 5;
            label3.Text = "Periodic Frequency:";
            // 
            // tabControl1
            // 
            tabControl1.Controls.Add(tabPageElevator);
            tabControl1.Controls.Add(tabPageAileron);
            tabControl1.Controls.Add(tabPage3);
            tabControl1.Dock = DockStyle.Left;
            tabControl1.Location = new Point(6, 6);
            tabControl1.Margin = new Padding(6);
            tabControl1.Name = "tabControl1";
            tabControl1.SelectedIndex = 0;
            tabControl1.Size = new Size(774, 733);
            tabControl1.TabIndex = 9;
            // 
            // tabPageElevator
            // 
            tabPageElevator.AutoScroll = true;
            tabPageElevator.BackColor = SystemColors.Control;
            tabPageElevator.Controls.Add(groupBox4);
            tabPageElevator.Controls.Add(groupBox2);
            tabPageElevator.Controls.Add(groupBox1);
            tabPageElevator.Controls.Add(label2);
            tabPageElevator.Controls.Add(label3);
            tabPageElevator.Location = new Point(8, 46);
            tabPageElevator.Margin = new Padding(6);
            tabPageElevator.Name = "tabPageElevator";
            tabPageElevator.Padding = new Padding(6);
            tabPageElevator.Size = new Size(758, 679);
            tabPageElevator.TabIndex = 0;
            tabPageElevator.Text = "Elevator";
            // 
            // groupBox4
            // 
            groupBox4.AutoSize = true;
            groupBox4.Controls.Add(label27);
            groupBox4.Controls.Add(nudEngineCenterStrength);
            groupBox4.Controls.Add(tbEngineCenterStrength);
            groupBox4.Controls.Add(label28);
            groupBox4.Controls.Add(label13);
            groupBox4.Controls.Add(nudElevatorAirSpeedStiffness);
            groupBox4.Controls.Add(tbElevatorAirSpeedStiffness);
            groupBox4.Controls.Add(label14);
            groupBox4.Controls.Add(label12);
            groupBox4.Controls.Add(nudEngineOffWeight);
            groupBox4.Controls.Add(tbEngineOffWeight);
            groupBox4.Controls.Add(label11);
            groupBox4.Location = new Point(9, 467);
            groupBox4.Margin = new Padding(4);
            groupBox4.Name = "groupBox4";
            groupBox4.Padding = new Padding(4);
            groupBox4.Size = new Size(709, 337);
            groupBox4.TabIndex = 17;
            groupBox4.TabStop = false;
            groupBox4.Text = "Effects";
            // 
            // label27
            // 
            label27.AutoSize = true;
            label27.Location = new Point(610, 111);
            label27.Margin = new Padding(4, 0, 4, 0);
            label27.Name = "label27";
            label27.Size = new Size(34, 32);
            label27.TabIndex = 32;
            label27.Text = "%";
            // 
            // nudEngineCenterStrength
            // 
            nudEngineCenterStrength.Location = new Point(473, 111);
            nudEngineCenterStrength.Margin = new Padding(4);
            nudEngineCenterStrength.Name = "nudEngineCenterStrength";
            nudEngineCenterStrength.Size = new Size(130, 39);
            nudEngineCenterStrength.TabIndex = 30;
            nudEngineCenterStrength.ValueChanged += nudEngineCenterStrength_ValueChanged;
            // 
            // tbEngineCenterStrength
            // 
            tbEngineCenterStrength.Location = new Point(263, 111);
            tbEngineCenterStrength.Margin = new Padding(4);
            tbEngineCenterStrength.Maximum = 100;
            tbEngineCenterStrength.Name = "tbEngineCenterStrength";
            tbEngineCenterStrength.Size = new Size(202, 90);
            tbEngineCenterStrength.TabIndex = 31;
            tbEngineCenterStrength.Scroll += tbEngineCenterStrength_Scroll;
            // 
            // label28
            // 
            label28.AutoSize = true;
            label28.Location = new Point(20, 111);
            label28.Margin = new Padding(4, 0, 4, 0);
            label28.Name = "label28";
            label28.Size = new Size(251, 32);
            label28.TabIndex = 29;
            label28.Text = "RPM Center Strength: ";
            // 
            // label13
            // 
            label13.AutoSize = true;
            label13.Location = new Point(605, 207);
            label13.Margin = new Padding(4, 0, 4, 0);
            label13.Name = "label13";
            label13.Size = new Size(34, 32);
            label13.TabIndex = 28;
            label13.Text = "%";
            // 
            // nudElevatorAirSpeedStiffness
            // 
            nudElevatorAirSpeedStiffness.Location = new Point(473, 204);
            nudElevatorAirSpeedStiffness.Margin = new Padding(4);
            nudElevatorAirSpeedStiffness.Name = "nudElevatorAirSpeedStiffness";
            nudElevatorAirSpeedStiffness.Size = new Size(130, 39);
            nudElevatorAirSpeedStiffness.TabIndex = 26;
            nudElevatorAirSpeedStiffness.ValueChanged += nudElevatorAirSpeedStiffness_ValueChanged;
            // 
            // tbElevatorAirSpeedStiffness
            // 
            tbElevatorAirSpeedStiffness.Location = new Point(263, 207);
            tbElevatorAirSpeedStiffness.Margin = new Padding(4);
            tbElevatorAirSpeedStiffness.Maximum = 100;
            tbElevatorAirSpeedStiffness.Name = "tbElevatorAirSpeedStiffness";
            tbElevatorAirSpeedStiffness.Size = new Size(202, 90);
            tbElevatorAirSpeedStiffness.TabIndex = 27;
            tbElevatorAirSpeedStiffness.Scroll += tbElevatorAirSpeedStiffness_Scroll;
            // 
            // label14
            // 
            label14.AutoSize = true;
            label14.Location = new Point(20, 207);
            label14.Margin = new Padding(4, 0, 4, 0);
            label14.Name = "label14";
            label14.Size = new Size(218, 32);
            label14.TabIndex = 25;
            label14.Text = "Air Speed Stiffness:";
            // 
            // label12
            // 
            label12.AutoSize = true;
            label12.Location = new Point(610, 34);
            label12.Margin = new Padding(4, 0, 4, 0);
            label12.Name = "label12";
            label12.Size = new Size(34, 32);
            label12.TabIndex = 24;
            label12.Text = "%";
            // 
            // nudEngineOffWeight
            // 
            nudEngineOffWeight.Location = new Point(473, 34);
            nudEngineOffWeight.Margin = new Padding(4);
            nudEngineOffWeight.Name = "nudEngineOffWeight";
            nudEngineOffWeight.Size = new Size(130, 39);
            nudEngineOffWeight.TabIndex = 22;
            nudEngineOffWeight.ValueChanged += nudEngineOffWeight_ValueChanged;
            // 
            // tbEngineOffWeight
            // 
            tbEngineOffWeight.Location = new Point(263, 34);
            tbEngineOffWeight.Margin = new Padding(4);
            tbEngineOffWeight.Maximum = 100;
            tbEngineOffWeight.Name = "tbEngineOffWeight";
            tbEngineOffWeight.Size = new Size(202, 90);
            tbEngineOffWeight.TabIndex = 23;
            tbEngineOffWeight.Scroll += tbEngineOffWeight_Scroll;
            // 
            // label11
            // 
            label11.AutoSize = true;
            label11.Location = new Point(20, 34);
            label11.Margin = new Padding(4, 0, 4, 0);
            label11.Name = "label11";
            label11.Size = new Size(223, 32);
            label11.TabIndex = 0;
            label11.Text = "Engine Off Weight: ";
            // 
            // groupBox2
            // 
            groupBox2.AutoSize = true;
            groupBox2.Controls.Add(label4);
            groupBox2.Controls.Add(nudElevatorMaxForce);
            groupBox2.Controls.Add(label5);
            groupBox2.Controls.Add(tbElevatorMaxForce);
            groupBox2.Controls.Add(lblPercent);
            groupBox2.Controls.Add(nudElevatorGain);
            groupBox2.Controls.Add(lblGain);
            groupBox2.Controls.Add(tbElevatorGain);
            groupBox2.Controls.Add(cbElevatorFFBEnable);
            groupBox2.Location = new Point(9, 139);
            groupBox2.Margin = new Padding(4);
            groupBox2.Name = "groupBox2";
            groupBox2.Padding = new Padding(4);
            groupBox2.Size = new Size(709, 324);
            groupBox2.TabIndex = 16;
            groupBox2.TabStop = false;
            groupBox2.Text = "Basic Settings";
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new Point(487, 196);
            label4.Margin = new Padding(4, 0, 4, 0);
            label4.Name = "label4";
            label4.Size = new Size(34, 32);
            label4.TabIndex = 21;
            label4.Text = "%";
            // 
            // nudElevatorMaxForce
            // 
            nudElevatorMaxForce.Location = new Point(349, 194);
            nudElevatorMaxForce.Margin = new Padding(4);
            nudElevatorMaxForce.Name = "nudElevatorMaxForce";
            nudElevatorMaxForce.Size = new Size(130, 39);
            nudElevatorMaxForce.TabIndex = 19;
            nudElevatorMaxForce.ValueChanged += nudElevatorMaxForce_ValueChanged;
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Location = new Point(15, 194);
            label5.Margin = new Padding(11, 0, 4, 0);
            label5.Name = "label5";
            label5.Size = new Size(129, 32);
            label5.TabIndex = 18;
            label5.Text = "Max Force:";
            // 
            // tbElevatorMaxForce
            // 
            tbElevatorMaxForce.Location = new Point(145, 194);
            tbElevatorMaxForce.Margin = new Padding(4);
            tbElevatorMaxForce.Maximum = 100;
            tbElevatorMaxForce.Name = "tbElevatorMaxForce";
            tbElevatorMaxForce.Size = new Size(202, 90);
            tbElevatorMaxForce.TabIndex = 20;
            tbElevatorMaxForce.Scroll += tbElevatorMaxForce_Scroll;
            // 
            // lblPercent
            // 
            lblPercent.AutoSize = true;
            lblPercent.Location = new Point(487, 100);
            lblPercent.Margin = new Padding(4, 0, 4, 0);
            lblPercent.Name = "lblPercent";
            lblPercent.Size = new Size(34, 32);
            lblPercent.TabIndex = 17;
            lblPercent.Text = "%";
            // 
            // nudElevatorGain
            // 
            nudElevatorGain.Location = new Point(349, 98);
            nudElevatorGain.Margin = new Padding(4);
            nudElevatorGain.Name = "nudElevatorGain";
            nudElevatorGain.Size = new Size(130, 39);
            nudElevatorGain.TabIndex = 15;
            nudElevatorGain.ValueChanged += nudElevatorGain_ValueChanged;
            // 
            // lblGain
            // 
            lblGain.AutoSize = true;
            lblGain.Location = new Point(15, 98);
            lblGain.Margin = new Padding(11, 0, 4, 0);
            lblGain.Name = "lblGain";
            lblGain.Size = new Size(67, 32);
            lblGain.TabIndex = 0;
            lblGain.Text = "Gain:";
            // 
            // tbElevatorGain
            // 
            tbElevatorGain.Location = new Point(145, 98);
            tbElevatorGain.Margin = new Padding(4);
            tbElevatorGain.Maximum = 100;
            tbElevatorGain.Name = "tbElevatorGain";
            tbElevatorGain.Size = new Size(202, 90);
            tbElevatorGain.TabIndex = 16;
            tbElevatorGain.Scroll += tbElevatorGain_Scroll;
            // 
            // cbElevatorFFBEnable
            // 
            cbElevatorFFBEnable.AutoSize = true;
            cbElevatorFFBEnable.Location = new Point(15, 38);
            cbElevatorFFBEnable.Margin = new Padding(11, 4, 4, 4);
            cbElevatorFFBEnable.Name = "cbElevatorFFBEnable";
            cbElevatorFFBEnable.Size = new Size(290, 36);
            cbElevatorFFBEnable.TabIndex = 15;
            cbElevatorFFBEnable.Text = "Force Feedback Enable";
            cbElevatorFFBEnable.UseVisualStyleBackColor = true;
            cbElevatorFFBEnable.CheckedChanged += cbElevatorFFBEnable_CheckedChanged;
            // 
            // groupBox1
            // 
            groupBox1.AutoSize = true;
            groupBox1.Controls.Add(label8);
            groupBox1.Controls.Add(nudElevatorRange);
            groupBox1.Controls.Add(lblRange);
            groupBox1.Location = new Point(9, 11);
            groupBox1.Margin = new Padding(4);
            groupBox1.Name = "groupBox1";
            groupBox1.Padding = new Padding(4);
            groupBox1.Size = new Size(709, 120);
            groupBox1.TabIndex = 8;
            groupBox1.TabStop = false;
            groupBox1.Text = "Travel";
            // 
            // label8
            // 
            label8.AutoSize = true;
            label8.Location = new Point(247, 43);
            label8.Margin = new Padding(4, 0, 4, 0);
            label8.Name = "label8";
            label8.Size = new Size(56, 32);
            label8.TabIndex = 22;
            label8.Text = "mm";
            // 
            // nudElevatorRange
            // 
            nudElevatorRange.DecimalPlaces = 2;
            nudElevatorRange.Location = new Point(110, 41);
            nudElevatorRange.Margin = new Padding(4);
            nudElevatorRange.Maximum = new decimal(new int[] { 100000, 0, 0, 0 });
            nudElevatorRange.Name = "nudElevatorRange";
            nudElevatorRange.Size = new Size(130, 39);
            nudElevatorRange.TabIndex = 2;
            nudElevatorRange.ValueChanged += nudElevatorRange_ValueChanged;
            // 
            // lblRange
            // 
            lblRange.AutoSize = true;
            lblRange.Location = new Point(15, 43);
            lblRange.Margin = new Padding(11, 0, 4, 0);
            lblRange.Name = "lblRange";
            lblRange.Size = new Size(86, 32);
            lblRange.TabIndex = 1;
            lblRange.Text = "Range:";
            // 
            // tabPageAileron
            // 
            tabPageAileron.AutoScroll = true;
            tabPageAileron.BackColor = SystemColors.Control;
            tabPageAileron.Controls.Add(groupBox7);
            tabPageAileron.Controls.Add(groupBox6);
            tabPageAileron.Controls.Add(groupBox5);
            tabPageAileron.Location = new Point(8, 46);
            tabPageAileron.Margin = new Padding(6);
            tabPageAileron.Name = "tabPageAileron";
            tabPageAileron.Padding = new Padding(6);
            tabPageAileron.Size = new Size(758, 679);
            tabPageAileron.TabIndex = 1;
            tabPageAileron.Text = "Aileron";
            // 
            // groupBox7
            // 
            groupBox7.AutoSize = true;
            groupBox7.Controls.Add(label21);
            groupBox7.Controls.Add(numericUpDown9);
            groupBox7.Controls.Add(trackBar6);
            groupBox7.Controls.Add(label22);
            groupBox7.Location = new Point(9, 467);
            groupBox7.Margin = new Padding(4);
            groupBox7.Name = "groupBox7";
            groupBox7.Padding = new Padding(4);
            groupBox7.Size = new Size(719, 303);
            groupBox7.TabIndex = 18;
            groupBox7.TabStop = false;
            groupBox7.Text = "Effects";
            // 
            // label21
            // 
            label21.AutoSize = true;
            label21.Location = new Point(589, 34);
            label21.Margin = new Padding(4, 0, 4, 0);
            label21.Name = "label21";
            label21.Size = new Size(34, 32);
            label21.TabIndex = 28;
            label21.Text = "%";
            // 
            // numericUpDown9
            // 
            numericUpDown9.Location = new Point(451, 32);
            numericUpDown9.Margin = new Padding(4);
            numericUpDown9.Name = "numericUpDown9";
            numericUpDown9.Size = new Size(130, 39);
            numericUpDown9.TabIndex = 26;
            // 
            // trackBar6
            // 
            trackBar6.Location = new Point(241, 34);
            trackBar6.Margin = new Padding(4);
            trackBar6.Maximum = 100;
            trackBar6.Name = "trackBar6";
            trackBar6.Size = new Size(202, 90);
            trackBar6.TabIndex = 27;
            // 
            // label22
            // 
            label22.AutoSize = true;
            label22.Location = new Point(17, 34);
            label22.Margin = new Padding(4, 0, 4, 0);
            label22.Name = "label22";
            label22.Size = new Size(218, 32);
            label22.TabIndex = 25;
            label22.Text = "Air Speed Stiffness:";
            // 
            // groupBox6
            // 
            groupBox6.AutoSize = true;
            groupBox6.Controls.Add(label17);
            groupBox6.Controls.Add(numericUpDown7);
            groupBox6.Controls.Add(label18);
            groupBox6.Controls.Add(trackBar4);
            groupBox6.Controls.Add(label19);
            groupBox6.Controls.Add(numericUpDown8);
            groupBox6.Controls.Add(label20);
            groupBox6.Controls.Add(trackBar5);
            groupBox6.Controls.Add(cbAileronFFBEnable);
            groupBox6.Location = new Point(9, 139);
            groupBox6.Margin = new Padding(4);
            groupBox6.Name = "groupBox6";
            groupBox6.Padding = new Padding(4);
            groupBox6.Size = new Size(719, 463);
            groupBox6.TabIndex = 17;
            groupBox6.TabStop = false;
            groupBox6.Text = "Basic Settings";
            // 
            // label17
            // 
            label17.AutoSize = true;
            label17.Location = new Point(487, 196);
            label17.Margin = new Padding(4, 0, 4, 0);
            label17.Name = "label17";
            label17.Size = new Size(34, 32);
            label17.TabIndex = 21;
            label17.Text = "%";
            // 
            // numericUpDown7
            // 
            numericUpDown7.Location = new Point(349, 194);
            numericUpDown7.Margin = new Padding(4);
            numericUpDown7.Name = "numericUpDown7";
            numericUpDown7.Size = new Size(130, 39);
            numericUpDown7.TabIndex = 19;
            // 
            // label18
            // 
            label18.AutoSize = true;
            label18.Location = new Point(15, 194);
            label18.Margin = new Padding(11, 0, 4, 0);
            label18.Name = "label18";
            label18.Size = new Size(129, 32);
            label18.TabIndex = 18;
            label18.Text = "Max Force:";
            // 
            // trackBar4
            // 
            trackBar4.Location = new Point(145, 194);
            trackBar4.Margin = new Padding(4);
            trackBar4.Maximum = 100;
            trackBar4.Name = "trackBar4";
            trackBar4.Size = new Size(202, 90);
            trackBar4.TabIndex = 20;
            // 
            // label19
            // 
            label19.AutoSize = true;
            label19.Location = new Point(487, 100);
            label19.Margin = new Padding(4, 0, 4, 0);
            label19.Name = "label19";
            label19.Size = new Size(34, 32);
            label19.TabIndex = 17;
            label19.Text = "%";
            // 
            // numericUpDown8
            // 
            numericUpDown8.Location = new Point(349, 98);
            numericUpDown8.Margin = new Padding(4);
            numericUpDown8.Name = "numericUpDown8";
            numericUpDown8.Size = new Size(130, 39);
            numericUpDown8.TabIndex = 15;
            // 
            // label20
            // 
            label20.AutoSize = true;
            label20.Location = new Point(15, 98);
            label20.Margin = new Padding(11, 0, 4, 0);
            label20.Name = "label20";
            label20.Size = new Size(67, 32);
            label20.TabIndex = 0;
            label20.Text = "Gain:";
            // 
            // trackBar5
            // 
            trackBar5.Location = new Point(145, 98);
            trackBar5.Margin = new Padding(4);
            trackBar5.Maximum = 100;
            trackBar5.Name = "trackBar5";
            trackBar5.Size = new Size(202, 90);
            trackBar5.TabIndex = 16;
            // 
            // cbAileronFFBEnable
            // 
            cbAileronFFBEnable.AutoSize = true;
            cbAileronFFBEnable.Location = new Point(15, 38);
            cbAileronFFBEnable.Margin = new Padding(11, 4, 4, 4);
            cbAileronFFBEnable.Name = "cbAileronFFBEnable";
            cbAileronFFBEnable.Size = new Size(290, 36);
            cbAileronFFBEnable.TabIndex = 15;
            cbAileronFFBEnable.Text = "Force Feedback Enable";
            cbAileronFFBEnable.UseVisualStyleBackColor = true;
            // 
            // groupBox5
            // 
            groupBox5.AutoSize = true;
            groupBox5.Controls.Add(label15);
            groupBox5.Controls.Add(nudAileronRange);
            groupBox5.Controls.Add(label16);
            groupBox5.Location = new Point(9, 11);
            groupBox5.Margin = new Padding(4);
            groupBox5.Name = "groupBox5";
            groupBox5.Padding = new Padding(4);
            groupBox5.Size = new Size(719, 201);
            groupBox5.TabIndex = 9;
            groupBox5.TabStop = false;
            groupBox5.Text = "Travel";
            // 
            // label15
            // 
            label15.AutoSize = true;
            label15.Location = new Point(247, 43);
            label15.Margin = new Padding(4, 0, 4, 0);
            label15.Name = "label15";
            label15.Size = new Size(102, 32);
            label15.TabIndex = 22;
            label15.Text = "Degrees";
            // 
            // nudAileronRange
            // 
            nudAileronRange.DecimalPlaces = 2;
            nudAileronRange.Location = new Point(110, 41);
            nudAileronRange.Margin = new Padding(4);
            nudAileronRange.Maximum = new decimal(new int[] { 270, 0, 0, 0 });
            nudAileronRange.Minimum = new decimal(new int[] { 90, 0, 0, 0 });
            nudAileronRange.Name = "nudAileronRange";
            nudAileronRange.Size = new Size(130, 39);
            nudAileronRange.TabIndex = 2;
            nudAileronRange.Value = new decimal(new int[] { 180, 0, 0, 0 });
            nudAileronRange.ValueChanged += nudAileronRange_ValueChanged;
            // 
            // label16
            // 
            label16.AutoSize = true;
            label16.Location = new Point(15, 43);
            label16.Margin = new Padding(11, 0, 4, 0);
            label16.Name = "label16";
            label16.Size = new Size(86, 32);
            label16.TabIndex = 1;
            label16.Text = "Range:";
            // 
            // tabPage3
            // 
            tabPage3.Location = new Point(8, 46);
            tabPage3.Margin = new Padding(4);
            tabPage3.Name = "tabPage3";
            tabPage3.Padding = new Padding(4);
            tabPage3.Size = new Size(758, 679);
            tabPage3.TabIndex = 2;
            tabPage3.Text = "tabPage3";
            tabPage3.UseVisualStyleBackColor = true;
            // 
            // tableLayoutPanel1
            // 
            tableLayoutPanel1.ColumnCount = 2;
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 20.3836937F));
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Absolute, 633F));
            tableLayoutPanel1.Controls.Add(btnStartStop, 1, 1);
            tableLayoutPanel1.Controls.Add(btnConnectSim, 0, 1);
            tableLayoutPanel1.Controls.Add(tabControl1, 0, 0);
            tableLayoutPanel1.Controls.Add(groupBox3, 1, 0);
            tableLayoutPanel1.Location = new Point(0, 0);
            tableLayoutPanel1.Margin = new Padding(4);
            tableLayoutPanel1.Name = "tableLayoutPanel1";
            tableLayoutPanel1.RowCount = 2;
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Percent, 50F));
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Absolute, 70F));
            tableLayoutPanel1.Size = new Size(1419, 815);
            tableLayoutPanel1.TabIndex = 14;
            // 
            // btnStartStop
            // 
            btnStartStop.Anchor = AnchorStyles.Right;
            btnStartStop.Location = new Point(1261, 758);
            btnStartStop.Margin = new Padding(4, 4, 13, 4);
            btnStartStop.Name = "btnStartStop";
            btnStartStop.Size = new Size(145, 43);
            btnStartStop.TabIndex = 18;
            btnStartStop.Text = "Start FFB";
            btnStartStop.UseVisualStyleBackColor = true;
            btnStartStop.Click += btnStartStop_Click;
            // 
            // btnConnectSim
            // 
            btnConnectSim.Anchor = AnchorStyles.Left;
            btnConnectSim.Location = new Point(13, 758);
            btnConnectSim.Margin = new Padding(13, 4, 4, 4);
            btnConnectSim.Name = "btnConnectSim";
            btnConnectSim.Size = new Size(281, 43);
            btnConnectSim.TabIndex = 19;
            btnConnectSim.Text = "Connect Simulator";
            btnConnectSim.UseVisualStyleBackColor = true;
            btnConnectSim.Click += btnConnectSim_Click;
            // 
            // groupBox3
            // 
            groupBox3.Controls.Add(cbDisableInput);
            groupBox3.Controls.Add(btnVisualizer);
            groupBox3.Controls.Add(lblElevatorFeedbackIndicator);
            groupBox3.Controls.Add(tiElevatorFeedback);
            groupBox3.Controls.Add(label6);
            groupBox3.Controls.Add(label25);
            groupBox3.Controls.Add(label26);
            groupBox3.Controls.Add(lblAileronFeedbackIndicator);
            groupBox3.Controls.Add(tiAileronFeedback);
            groupBox3.Controls.Add(label24);
            groupBox3.Controls.Add(label23);
            groupBox3.Controls.Add(tiElevator);
            groupBox3.Controls.Add(tiAileron);
            groupBox3.Controls.Add(nudEngineRPM);
            groupBox3.Controls.Add(label1);
            groupBox3.Controls.Add(label10);
            groupBox3.Controls.Add(rbTest);
            groupBox3.Controls.Add(rbFromSim);
            groupBox3.Controls.Add(nudAirSpeed);
            groupBox3.Controls.Add(label9);
            groupBox3.Controls.Add(lblElevatorIndicator);
            groupBox3.Controls.Add(lblAileronIndicator);
            groupBox3.Controls.Add(label7);
            groupBox3.Dock = DockStyle.Fill;
            groupBox3.Location = new Point(790, 4);
            groupBox3.Margin = new Padding(4);
            groupBox3.Name = "groupBox3";
            groupBox3.Padding = new Padding(4);
            groupBox3.Size = new Size(625, 737);
            groupBox3.TabIndex = 17;
            groupBox3.TabStop = false;
            groupBox3.Text = "Monitor";
            // 
            // cbDisableInput
            // 
            cbDisableInput.AutoSize = true;
            cbDisableInput.Location = new Point(274, 690);
            cbDisableInput.Name = "cbDisableInput";
            cbDisableInput.Size = new Size(187, 36);
            cbDisableInput.TabIndex = 36;
            cbDisableInput.Text = "Disable Input";
            cbDisableInput.UseVisualStyleBackColor = true;
            cbDisableInput.CheckedChanged += cbDisableInput_CheckedChanged;
            // 
            // btnVisualizer
            // 
            btnVisualizer.Location = new Point(467, 684);
            btnVisualizer.Name = "btnVisualizer";
            btnVisualizer.Size = new Size(150, 46);
            btnVisualizer.TabIndex = 35;
            btnVisualizer.Text = "Visualizer";
            btnVisualizer.UseVisualStyleBackColor = true;
            btnVisualizer.Click += btnVisualizer_Click;
            // 
            // lblElevatorFeedbackIndicator
            // 
            lblElevatorFeedbackIndicator.Location = new Point(526, 213);
            lblElevatorFeedbackIndicator.Margin = new Padding(4, 0, 4, 0);
            lblElevatorFeedbackIndicator.Name = "lblElevatorFeedbackIndicator";
            lblElevatorFeedbackIndicator.Size = new Size(97, 43);
            lblElevatorFeedbackIndicator.TabIndex = 34;
            lblElevatorFeedbackIndicator.Text = "0.0%";
            lblElevatorFeedbackIndicator.TextAlign = ContentAlignment.MiddleRight;
            // 
            // tiElevatorFeedback
            // 
            tiElevatorFeedback.CenterLineColor = SystemColors.ControlDarkDark;
            tiElevatorFeedback.Location = new Point(225, 224);
            tiElevatorFeedback.Margin = new Padding(4);
            tiElevatorFeedback.Maximum = 100;
            tiElevatorFeedback.Minimum = -100;
            tiElevatorFeedback.Name = "tiElevatorFeedback";
            tiElevatorFeedback.Size = new Size(293, 30);
            tiElevatorFeedback.TabIndex = 33;
            tiElevatorFeedback.Type = TravelIndicator.TravelIndicatorType.Centered;
            tiElevatorFeedback.Value = 0;
            // 
            // label6
            // 
            label6.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left;
            label6.AutoSize = true;
            label6.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point);
            label6.Location = new Point(0, 171);
            label6.Margin = new Padding(4, 0, 4, 0);
            label6.Name = "label6";
            label6.Size = new Size(107, 32);
            label6.TabIndex = 30;
            label6.Text = "Elevator";
            label6.TextAlign = ContentAlignment.MiddleLeft;
            // 
            // label25
            // 
            label25.AutoSize = true;
            label25.Location = new Point(98, 220);
            label25.Margin = new Padding(4, 0, 4, 0);
            label25.Name = "label25";
            label25.Size = new Size(120, 32);
            label25.TabIndex = 32;
            label25.Text = "Feedback:";
            label25.TextAlign = ContentAlignment.MiddleLeft;
            // 
            // label26
            // 
            label26.AutoSize = true;
            label26.Location = new Point(98, 166);
            label26.Margin = new Padding(11, 0, 4, 0);
            label26.MinimumSize = new Size(0, 43);
            label26.Name = "label26";
            label26.Size = new Size(103, 43);
            label26.TabIndex = 31;
            label26.Text = "Position:";
            label26.TextAlign = ContentAlignment.MiddleLeft;
            // 
            // lblAileronFeedbackIndicator
            // 
            lblAileronFeedbackIndicator.Location = new Point(526, 100);
            lblAileronFeedbackIndicator.Margin = new Padding(4, 0, 4, 0);
            lblAileronFeedbackIndicator.Name = "lblAileronFeedbackIndicator";
            lblAileronFeedbackIndicator.Size = new Size(97, 30);
            lblAileronFeedbackIndicator.TabIndex = 29;
            lblAileronFeedbackIndicator.Text = "0.0%";
            lblAileronFeedbackIndicator.TextAlign = ContentAlignment.MiddleRight;
            // 
            // tiAileronFeedback
            // 
            tiAileronFeedback.CenterLineColor = SystemColors.ControlDarkDark;
            tiAileronFeedback.Location = new Point(225, 100);
            tiAileronFeedback.Margin = new Padding(4);
            tiAileronFeedback.Maximum = 100;
            tiAileronFeedback.Minimum = -100;
            tiAileronFeedback.Name = "tiAileronFeedback";
            tiAileronFeedback.Size = new Size(293, 30);
            tiAileronFeedback.TabIndex = 28;
            tiAileronFeedback.Type = TravelIndicator.TravelIndicatorType.Centered;
            tiAileronFeedback.Value = 0;
            // 
            // label24
            // 
            label24.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left;
            label24.AutoSize = true;
            label24.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point);
            label24.Location = new Point(0, 49);
            label24.Margin = new Padding(4, 0, 4, 0);
            label24.Name = "label24";
            label24.Size = new Size(98, 32);
            label24.TabIndex = 15;
            label24.Text = "Aileron";
            label24.TextAlign = ContentAlignment.MiddleLeft;
            // 
            // label23
            // 
            label23.AutoSize = true;
            label23.Location = new Point(98, 96);
            label23.Margin = new Padding(4, 0, 4, 0);
            label23.Name = "label23";
            label23.Size = new Size(120, 32);
            label23.TabIndex = 27;
            label23.Text = "Feedback:";
            label23.TextAlign = ContentAlignment.MiddleLeft;
            // 
            // tiElevator
            // 
            tiElevator.CenterLineColor = SystemColors.ControlDarkDark;
            tiElevator.Location = new Point(225, 171);
            tiElevator.Margin = new Padding(4);
            tiElevator.Maximum = 32767;
            tiElevator.Minimum = -32767;
            tiElevator.Name = "tiElevator";
            tiElevator.Size = new Size(293, 30);
            tiElevator.TabIndex = 26;
            tiElevator.Type = TravelIndicator.TravelIndicatorType.Centered;
            tiElevator.Value = 0;
            // 
            // tiAileron
            // 
            tiAileron.CenterLineColor = SystemColors.ControlDarkDark;
            tiAileron.Location = new Point(225, 49);
            tiAileron.Margin = new Padding(4);
            tiAileron.Maximum = 32767;
            tiAileron.Minimum = -32767;
            tiAileron.Name = "tiAileron";
            tiAileron.Size = new Size(293, 30);
            tiAileron.TabIndex = 25;
            tiAileron.Type = TravelIndicator.TravelIndicatorType.Centered;
            tiAileron.Value = 0;
            // 
            // nudEngineRPM
            // 
            nudEngineRPM.Location = new Point(195, 382);
            nudEngineRPM.Margin = new Padding(4);
            nudEngineRPM.Maximum = new decimal(new int[] { 999999, 0, 0, 0 });
            nudEngineRPM.Name = "nudEngineRPM";
            nudEngineRPM.Size = new Size(123, 39);
            nudEngineRPM.TabIndex = 24;
            nudEngineRPM.ValueChanged += nudEngineRPM_ValueChanged;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(24, 386);
            label1.Margin = new Padding(4, 0, 4, 0);
            label1.Name = "label1";
            label1.Size = new Size(148, 32);
            label1.TabIndex = 23;
            label1.Text = "Engine RPM:";
            // 
            // label10
            // 
            label10.AutoSize = true;
            label10.Location = new Point(24, 343);
            label10.Margin = new Padding(4, 0, 4, 0);
            label10.Name = "label10";
            label10.Size = new Size(122, 32);
            label10.TabIndex = 22;
            label10.Text = "Air Speed:";
            // 
            // rbTest
            // 
            rbTest.AutoSize = true;
            rbTest.Location = new Point(351, 297);
            rbTest.Margin = new Padding(4);
            rbTest.Name = "rbTest";
            rbTest.Size = new Size(87, 36);
            rbTest.TabIndex = 21;
            rbTest.TabStop = true;
            rbTest.Text = "Test";
            rbTest.UseVisualStyleBackColor = true;
            rbTest.CheckedChanged += rbTest_CheckedChanged;
            // 
            // rbFromSim
            // 
            rbFromSim.AutoSize = true;
            rbFromSim.Location = new Point(195, 297);
            rbFromSim.Margin = new Padding(4);
            rbFromSim.Name = "rbFromSim";
            rbFromSim.Size = new Size(147, 36);
            rbFromSim.TabIndex = 20;
            rbFromSim.TabStop = true;
            rbFromSim.Text = "From Sim";
            rbFromSim.UseVisualStyleBackColor = true;
            rbFromSim.CheckedChanged += rbFromSim_CheckedChanged;
            // 
            // nudAirSpeed
            // 
            nudAirSpeed.DecimalPlaces = 2;
            nudAirSpeed.Location = new Point(195, 341);
            nudAirSpeed.Margin = new Padding(4);
            nudAirSpeed.Maximum = new decimal(new int[] { 9999, 0, 0, 0 });
            nudAirSpeed.Name = "nudAirSpeed";
            nudAirSpeed.Size = new Size(123, 39);
            nudAirSpeed.TabIndex = 19;
            nudAirSpeed.ValueChanged += nudAirSpeed_ValueChanged;
            // 
            // label9
            // 
            label9.AutoSize = true;
            label9.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point);
            label9.Location = new Point(24, 299);
            label9.Margin = new Padding(4, 0, 4, 0);
            label9.Name = "label9";
            label9.Size = new Size(166, 32);
            label9.TabIndex = 15;
            label9.Text = "Sim Variables";
            // 
            // lblElevatorIndicator
            // 
            lblElevatorIndicator.Location = new Point(526, 166);
            lblElevatorIndicator.Margin = new Padding(4, 0, 4, 0);
            lblElevatorIndicator.Name = "lblElevatorIndicator";
            lblElevatorIndicator.Size = new Size(97, 43);
            lblElevatorIndicator.TabIndex = 18;
            lblElevatorIndicator.Text = "0.0%";
            lblElevatorIndicator.TextAlign = ContentAlignment.MiddleRight;
            // 
            // lblAileronIndicator
            // 
            lblAileronIndicator.Location = new Point(526, 49);
            lblAileronIndicator.Margin = new Padding(4, 0, 4, 0);
            lblAileronIndicator.Name = "lblAileronIndicator";
            lblAileronIndicator.Size = new Size(97, 30);
            lblAileronIndicator.TabIndex = 17;
            lblAileronIndicator.Text = "0.0%";
            lblAileronIndicator.TextAlign = ContentAlignment.MiddleRight;
            // 
            // label7
            // 
            label7.AutoSize = true;
            label7.Location = new Point(98, 43);
            label7.Margin = new Padding(11, 0, 4, 0);
            label7.MinimumSize = new Size(0, 43);
            label7.Name = "label7";
            label7.Size = new Size(103, 43);
            label7.TabIndex = 16;
            label7.Text = "Position:";
            label7.TextAlign = ContentAlignment.MiddleLeft;
            // 
            // testForceUpdateTimer
            // 
            testForceUpdateTimer.Interval = 20;
            testForceUpdateTimer.Tick += testForceUpdateTimer_Tick;
            // 
            // MainForm
            // 
            AutoScaleDimensions = new SizeF(13F, 32F);
            AutoScaleMode = AutoScaleMode.Font;
            AutoSizeMode = AutoSizeMode.GrowAndShrink;
            ClientSize = new Size(1419, 815);
            Controls.Add(tableLayoutPanel1);
            FormBorderStyle = FormBorderStyle.FixedSingle;
            Margin = new Padding(6);
            MaximizeBox = false;
            Name = "MainForm";
            Text = "MSFS Force Feedback Controller";
            Load += MainForm_Load;
            tabControl1.ResumeLayout(false);
            tabPageElevator.ResumeLayout(false);
            tabPageElevator.PerformLayout();
            groupBox4.ResumeLayout(false);
            groupBox4.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)nudEngineCenterStrength).EndInit();
            ((System.ComponentModel.ISupportInitialize)tbEngineCenterStrength).EndInit();
            ((System.ComponentModel.ISupportInitialize)nudElevatorAirSpeedStiffness).EndInit();
            ((System.ComponentModel.ISupportInitialize)tbElevatorAirSpeedStiffness).EndInit();
            ((System.ComponentModel.ISupportInitialize)nudEngineOffWeight).EndInit();
            ((System.ComponentModel.ISupportInitialize)tbEngineOffWeight).EndInit();
            groupBox2.ResumeLayout(false);
            groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)nudElevatorMaxForce).EndInit();
            ((System.ComponentModel.ISupportInitialize)tbElevatorMaxForce).EndInit();
            ((System.ComponentModel.ISupportInitialize)nudElevatorGain).EndInit();
            ((System.ComponentModel.ISupportInitialize)tbElevatorGain).EndInit();
            groupBox1.ResumeLayout(false);
            groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)nudElevatorRange).EndInit();
            tabPageAileron.ResumeLayout(false);
            tabPageAileron.PerformLayout();
            groupBox7.ResumeLayout(false);
            groupBox7.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)numericUpDown9).EndInit();
            ((System.ComponentModel.ISupportInitialize)trackBar6).EndInit();
            groupBox6.ResumeLayout(false);
            groupBox6.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)numericUpDown7).EndInit();
            ((System.ComponentModel.ISupportInitialize)trackBar4).EndInit();
            ((System.ComponentModel.ISupportInitialize)numericUpDown8).EndInit();
            ((System.ComponentModel.ISupportInitialize)trackBar5).EndInit();
            groupBox5.ResumeLayout(false);
            groupBox5.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)nudAileronRange).EndInit();
            tableLayoutPanel1.ResumeLayout(false);
            groupBox3.ResumeLayout(false);
            groupBox3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)nudEngineRPM).EndInit();
            ((System.ComponentModel.ISupportInitialize)nudAirSpeed).EndInit();
            ResumeLayout(false);
        }

        #endregion

        private Button btnConnect;
        private Label label2;
        private Label label3;
        private TabControl tabControl1;
        private TabPage tabPageElevator;
        private TabPage tabPageAileron;
        private TabPage tabPage3;
        private TableLayoutPanel tableLayoutPanel1;
        private TableLayoutPanel tableLayoutPanel2;
        private TableLayoutPanel tableLayoutPanel3;
        private TableLayoutPanel tableLayoutPanel4;
        private GroupBox groupBox1;
        private NumericUpDown nudElevatorMin;
        private Label lblRange;
        private NumericUpDown nudElevatorRange;
        private CheckBox cbElevatorFFBEnable;
        private TrackBar tbElevatorGain;
        private GroupBox groupBox2;
        private NumericUpDown nudElevatorGain;
        private Label lblGain;
        private Label lblPercent;
        private GroupBox groupBox3;
        private Label label7;
        private Label lblElevatorIndicator;
        private Label lblAileronIndicator;
        private Label label4;
        private NumericUpDown nudElevatorMaxForce;
        private Label label5;
        private TrackBar tbElevatorMaxForce;
        private Label label8;
        private Label label9;
        private RadioButton rbTest;
        private RadioButton rbFromSim;
        private NumericUpDown nudAirSpeed;
        private Label label10;
        private GroupBox groupBox4;
        private Label label11;
        private Label label12;
        private NumericUpDown nudEngineOffWeight;
        private TrackBar tbEngineOffWeight;
        private Label label13;
        private NumericUpDown nudElevatorAirSpeedStiffness;
        private TrackBar tbElevatorAirSpeedStiffness;
        private Label label14;
        private GroupBox groupBox5;
        private Label label15;
        private NumericUpDown nudAileronRange;
        private Label label16;
        private GroupBox groupBox6;
        private Label label17;
        private NumericUpDown numericUpDown7;
        private Label label18;
        private TrackBar trackBar4;
        private Label label19;
        private NumericUpDown numericUpDown8;
        private Label label20;
        private TrackBar trackBar5;
        private CheckBox cbAileronFFBEnable;
        private GroupBox groupBox7;
        private Label label21;
        private NumericUpDown numericUpDown9;
        private TrackBar trackBar6;
        private Label label22;
        private NumericUpDown nudEngineRPM;
        private Label label1;
        private Button btnStartStop;
        private Button btnConnectSim;
        private TravelIndicator tiAileron;
        private TravelIndicator tiElevator;
        private Label label24;
        private Label label23;
        private TravelIndicator tiAileronFeedback;
        private Label lblAileronFeedbackIndicator;
        private TravelIndicator tiElevatorFeedback;
        private Label label6;
        private Label label25;
        private Label label26;
        private Label lblElevatorFeedbackIndicator;
        private Button btnVisualizer;
        private CheckBox cbDisableInput;
        private System.Windows.Forms.Timer testForceUpdateTimer;
        private Label label27;
        private NumericUpDown nudEngineCenterStrength;
        private TrackBar tbEngineCenterStrength;
        private Label label28;
    }
}