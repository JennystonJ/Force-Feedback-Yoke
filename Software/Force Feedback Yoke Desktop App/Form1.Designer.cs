namespace Force_Feedback_Yoke_Desktop_App
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            mainTableLayoutPanel = new TableLayoutPanel();
            menuTableLayoutPanel = new TableLayoutPanel();
            pitchMonitorPanel = new TableLayoutPanel();
            lblPitchUserForce = new Label();
            lblPitchForce = new Label();
            lblPitchPosition = new Label();
            label9 = new Label();
            lblPitchUserForceValue = new Label();
            lblPitchForceValue = new Label();
            lblPitchPosValue = new Label();
            rollMonitorPanel = new TableLayoutPanel();
            lblRollUserTorque = new Label();
            lblRollTorque = new Label();
            lblRollPosition = new Label();
            lblRollMonitor = new Label();
            lblRollUserTorqueValue = new Label();
            lblRollTorqueValue = new Label();
            lblRollPosValue = new Label();
            lblStatus = new Label();
            lblMonitor = new Label();
            btnHome = new Button();
            btnYokeData = new Button();
            lblMenu = new Label();
            btnProfiles = new Button();
            flowLayoutPanel1 = new FlowLayoutPanel();
            btnConnect = new Button();
            btnFfbOn = new Button();
            tablessControlContent = new Force_Feedback_Yoke_Desktop_App.Controls.TablessControl();
            homePage = new TabPage();
            homeTableLayoutPanel = new TableLayoutPanel();
            lblCurrentProfile = new Label();
            btnConnectSim = new Button();
            lblConnectSimStatus = new Label();
            cboProfile = new ComboBox();
            cbProfileAutoSelect = new CheckBox();
            profilesPage = new TabPage();
            tableLayoutPanel2 = new TableLayoutPanel();
            listBox1 = new ListBox();
            yokeDataPage = new TabPage();
            BottomToolStripPanel = new ToolStripPanel();
            TopToolStripPanel = new ToolStripPanel();
            RightToolStripPanel = new ToolStripPanel();
            LeftToolStripPanel = new ToolStripPanel();
            mainTableLayoutPanel.SuspendLayout();
            menuTableLayoutPanel.SuspendLayout();
            pitchMonitorPanel.SuspendLayout();
            rollMonitorPanel.SuspendLayout();
            flowLayoutPanel1.SuspendLayout();
            tablessControlContent.SuspendLayout();
            homePage.SuspendLayout();
            homeTableLayoutPanel.SuspendLayout();
            profilesPage.SuspendLayout();
            tableLayoutPanel2.SuspendLayout();
            SuspendLayout();
            // 
            // mainTableLayoutPanel
            // 
            mainTableLayoutPanel.BackColor = Color.Gray;
            mainTableLayoutPanel.ColumnCount = 2;
            mainTableLayoutPanel.ColumnStyles.Add(new ColumnStyle(SizeType.Absolute, 448F));
            mainTableLayoutPanel.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100F));
            mainTableLayoutPanel.Controls.Add(menuTableLayoutPanel, 0, 0);
            mainTableLayoutPanel.Controls.Add(tablessControlContent, 1, 0);
            mainTableLayoutPanel.Dock = DockStyle.Fill;
            mainTableLayoutPanel.Location = new Point(0, 0);
            mainTableLayoutPanel.Margin = new Padding(4, 4, 4, 4);
            mainTableLayoutPanel.Name = "mainTableLayoutPanel";
            mainTableLayoutPanel.RowCount = 1;
            mainTableLayoutPanel.RowStyles.Add(new RowStyle(SizeType.Percent, 100F));
            mainTableLayoutPanel.Size = new Size(1647, 1129);
            mainTableLayoutPanel.TabIndex = 0;
            // 
            // menuTableLayoutPanel
            // 
            menuTableLayoutPanel.AutoSize = true;
            menuTableLayoutPanel.AutoSizeMode = AutoSizeMode.GrowAndShrink;
            menuTableLayoutPanel.BackColor = Color.DimGray;
            menuTableLayoutPanel.ColumnCount = 1;
            menuTableLayoutPanel.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100F));
            menuTableLayoutPanel.Controls.Add(pitchMonitorPanel, 0, 5);
            menuTableLayoutPanel.Controls.Add(rollMonitorPanel, 0, 6);
            menuTableLayoutPanel.Controls.Add(lblStatus, 0, 7);
            menuTableLayoutPanel.Controls.Add(lblMonitor, 0, 4);
            menuTableLayoutPanel.Controls.Add(btnHome, 0, 1);
            menuTableLayoutPanel.Controls.Add(btnYokeData, 0, 3);
            menuTableLayoutPanel.Controls.Add(lblMenu, 0, 0);
            menuTableLayoutPanel.Controls.Add(btnProfiles, 0, 2);
            menuTableLayoutPanel.Controls.Add(flowLayoutPanel1, 0, 8);
            menuTableLayoutPanel.Dock = DockStyle.Fill;
            menuTableLayoutPanel.Location = new Point(0, 0);
            menuTableLayoutPanel.Margin = new Padding(0);
            menuTableLayoutPanel.Name = "menuTableLayoutPanel";
            menuTableLayoutPanel.RowCount = 9;
            menuTableLayoutPanel.RowStyles.Add(new RowStyle());
            menuTableLayoutPanel.RowStyles.Add(new RowStyle());
            menuTableLayoutPanel.RowStyles.Add(new RowStyle());
            menuTableLayoutPanel.RowStyles.Add(new RowStyle());
            menuTableLayoutPanel.RowStyles.Add(new RowStyle());
            menuTableLayoutPanel.RowStyles.Add(new RowStyle());
            menuTableLayoutPanel.RowStyles.Add(new RowStyle());
            menuTableLayoutPanel.RowStyles.Add(new RowStyle());
            menuTableLayoutPanel.RowStyles.Add(new RowStyle());
            menuTableLayoutPanel.RowStyles.Add(new RowStyle(SizeType.Absolute, 19F));
            menuTableLayoutPanel.Size = new Size(448, 1129);
            menuTableLayoutPanel.TabIndex = 0;
            // 
            // pitchMonitorPanel
            // 
            pitchMonitorPanel.AutoSize = true;
            pitchMonitorPanel.ColumnCount = 3;
            pitchMonitorPanel.ColumnStyles.Add(new ColumnStyle());
            pitchMonitorPanel.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100F));
            pitchMonitorPanel.ColumnStyles.Add(new ColumnStyle());
            pitchMonitorPanel.Controls.Add(lblPitchUserForce, 0, 3);
            pitchMonitorPanel.Controls.Add(lblPitchForce, 0, 2);
            pitchMonitorPanel.Controls.Add(lblPitchPosition, 0, 1);
            pitchMonitorPanel.Controls.Add(label9, 0, 0);
            pitchMonitorPanel.Controls.Add(lblPitchUserForceValue, 2, 3);
            pitchMonitorPanel.Controls.Add(lblPitchForceValue, 2, 2);
            pitchMonitorPanel.Controls.Add(lblPitchPosValue, 2, 1);
            pitchMonitorPanel.Dock = DockStyle.Fill;
            pitchMonitorPanel.Location = new Point(0, 582);
            pitchMonitorPanel.Margin = new Padding(0);
            pitchMonitorPanel.Name = "pitchMonitorPanel";
            pitchMonitorPanel.Padding = new Padding(9, 0, 0, 0);
            pitchMonitorPanel.RowCount = 4;
            pitchMonitorPanel.RowStyles.Add(new RowStyle());
            pitchMonitorPanel.RowStyles.Add(new RowStyle(SizeType.Percent, 33.33333F));
            pitchMonitorPanel.RowStyles.Add(new RowStyle(SizeType.Percent, 33.3333359F));
            pitchMonitorPanel.RowStyles.Add(new RowStyle(SizeType.Percent, 33.3333359F));
            pitchMonitorPanel.RowStyles.Add(new RowStyle(SizeType.Absolute, 19F));
            pitchMonitorPanel.Size = new Size(448, 220);
            pitchMonitorPanel.TabIndex = 10;
            // 
            // lblPitchUserForce
            // 
            lblPitchUserForce.AutoSize = true;
            lblPitchUserForce.BackColor = Color.Transparent;
            lblPitchUserForce.Dock = DockStyle.Bottom;
            lblPitchUserForce.Font = new Font("Microsoft Sans Serif", 9F, FontStyle.Regular, GraphicsUnit.Point, 0);
            lblPitchUserForce.ForeColor = Color.WhiteSmoke;
            lblPitchUserForce.Location = new Point(13, 165);
            lblPitchUserForce.Margin = new Padding(4, 0, 4, 0);
            lblPitchUserForce.Name = "lblPitchUserForce";
            lblPitchUserForce.Padding = new Padding(11, 13, 11, 13);
            lblPitchUserForce.Size = new Size(58, 55);
            lblPitchUserForce.TabIndex = 15;
            lblPitchUserForce.Text = "U:";
            lblPitchUserForce.TextAlign = ContentAlignment.MiddleLeft;
            // 
            // lblPitchForce
            // 
            lblPitchForce.AutoSize = true;
            lblPitchForce.BackColor = Color.Transparent;
            lblPitchForce.Dock = DockStyle.Bottom;
            lblPitchForce.Font = new Font("Microsoft Sans Serif", 9F, FontStyle.Regular, GraphicsUnit.Point, 0);
            lblPitchForce.ForeColor = Color.WhiteSmoke;
            lblPitchForce.Location = new Point(13, 109);
            lblPitchForce.Margin = new Padding(4, 0, 4, 0);
            lblPitchForce.Name = "lblPitchForce";
            lblPitchForce.Padding = new Padding(11, 13, 11, 13);
            lblPitchForce.Size = new Size(58, 55);
            lblPitchForce.TabIndex = 14;
            lblPitchForce.Text = "F:";
            lblPitchForce.TextAlign = ContentAlignment.MiddleLeft;
            // 
            // lblPitchPosition
            // 
            lblPitchPosition.AutoSize = true;
            lblPitchPosition.BackColor = Color.Transparent;
            lblPitchPosition.Dock = DockStyle.Bottom;
            lblPitchPosition.Font = new Font("Microsoft Sans Serif", 9F, FontStyle.Regular, GraphicsUnit.Point, 0);
            lblPitchPosition.ForeColor = Color.WhiteSmoke;
            lblPitchPosition.Location = new Point(13, 55);
            lblPitchPosition.Margin = new Padding(4, 0, 4, 0);
            lblPitchPosition.Name = "lblPitchPosition";
            lblPitchPosition.Padding = new Padding(11, 13, 11, 13);
            lblPitchPosition.Size = new Size(58, 54);
            lblPitchPosition.TabIndex = 13;
            lblPitchPosition.Text = "P:";
            lblPitchPosition.TextAlign = ContentAlignment.MiddleLeft;
            // 
            // label9
            // 
            label9.AutoSize = true;
            label9.BackColor = Color.Transparent;
            pitchMonitorPanel.SetColumnSpan(label9, 3);
            label9.Dock = DockStyle.Bottom;
            label9.Font = new Font("Microsoft Sans Serif", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            label9.ForeColor = Color.WhiteSmoke;
            label9.Location = new Point(13, 0);
            label9.Margin = new Padding(4, 0, 4, 0);
            label9.Name = "label9";
            label9.Padding = new Padding(11, 13, 11, 13);
            label9.Size = new Size(431, 55);
            label9.TabIndex = 12;
            label9.Text = "Pitch:";
            label9.TextAlign = ContentAlignment.MiddleLeft;
            // 
            // lblPitchUserForceValue
            // 
            lblPitchUserForceValue.AutoSize = true;
            lblPitchUserForceValue.BackColor = Color.Transparent;
            lblPitchUserForceValue.Dock = DockStyle.Fill;
            lblPitchUserForceValue.Font = new Font("Microsoft Sans Serif", 9F, FontStyle.Regular, GraphicsUnit.Point, 0);
            lblPitchUserForceValue.ForeColor = Color.WhiteSmoke;
            lblPitchUserForceValue.Location = new Point(297, 164);
            lblPitchUserForceValue.Margin = new Padding(4, 0, 4, 0);
            lblPitchUserForceValue.MinimumSize = new Size(123, 0);
            lblPitchUserForceValue.Name = "lblPitchUserForceValue";
            lblPitchUserForceValue.Padding = new Padding(11, 13, 11, 13);
            lblPitchUserForceValue.Size = new Size(147, 56);
            lblPitchUserForceValue.TabIndex = 11;
            lblPitchUserForceValue.Text = "--.-- N";
            lblPitchUserForceValue.TextAlign = ContentAlignment.MiddleRight;
            // 
            // lblPitchForceValue
            // 
            lblPitchForceValue.AutoSize = true;
            lblPitchForceValue.BackColor = Color.Transparent;
            lblPitchForceValue.Dock = DockStyle.Fill;
            lblPitchForceValue.Font = new Font("Microsoft Sans Serif", 9F, FontStyle.Regular, GraphicsUnit.Point, 0);
            lblPitchForceValue.ForeColor = Color.WhiteSmoke;
            lblPitchForceValue.Location = new Point(297, 109);
            lblPitchForceValue.Margin = new Padding(4, 0, 4, 0);
            lblPitchForceValue.MinimumSize = new Size(123, 0);
            lblPitchForceValue.Name = "lblPitchForceValue";
            lblPitchForceValue.Padding = new Padding(11, 13, 11, 13);
            lblPitchForceValue.Size = new Size(147, 55);
            lblPitchForceValue.TabIndex = 9;
            lblPitchForceValue.Text = "--.-- N";
            lblPitchForceValue.TextAlign = ContentAlignment.MiddleRight;
            // 
            // lblPitchPosValue
            // 
            lblPitchPosValue.AutoSize = true;
            lblPitchPosValue.BackColor = Color.Transparent;
            lblPitchPosValue.Dock = DockStyle.Fill;
            lblPitchPosValue.Font = new Font("Microsoft Sans Serif", 9F, FontStyle.Regular, GraphicsUnit.Point, 0);
            lblPitchPosValue.ForeColor = Color.WhiteSmoke;
            lblPitchPosValue.Location = new Point(297, 55);
            lblPitchPosValue.Margin = new Padding(4, 0, 4, 0);
            lblPitchPosValue.MinimumSize = new Size(147, 0);
            lblPitchPosValue.Name = "lblPitchPosValue";
            lblPitchPosValue.Padding = new Padding(11, 13, 11, 13);
            lblPitchPosValue.Size = new Size(147, 54);
            lblPitchPosValue.TabIndex = 7;
            lblPitchPosValue.Text = "----.- mm";
            lblPitchPosValue.TextAlign = ContentAlignment.MiddleRight;
            // 
            // rollMonitorPanel
            // 
            rollMonitorPanel.ColumnCount = 3;
            rollMonitorPanel.ColumnStyles.Add(new ColumnStyle());
            rollMonitorPanel.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100F));
            rollMonitorPanel.ColumnStyles.Add(new ColumnStyle());
            rollMonitorPanel.Controls.Add(lblRollUserTorque, 0, 3);
            rollMonitorPanel.Controls.Add(lblRollTorque, 0, 2);
            rollMonitorPanel.Controls.Add(lblRollPosition, 0, 1);
            rollMonitorPanel.Controls.Add(lblRollMonitor, 0, 0);
            rollMonitorPanel.Controls.Add(lblRollUserTorqueValue, 2, 3);
            rollMonitorPanel.Controls.Add(lblRollTorqueValue, 2, 2);
            rollMonitorPanel.Controls.Add(lblRollPosValue, 2, 1);
            rollMonitorPanel.Dock = DockStyle.Fill;
            rollMonitorPanel.Location = new Point(0, 802);
            rollMonitorPanel.Margin = new Padding(0);
            rollMonitorPanel.Name = "rollMonitorPanel";
            rollMonitorPanel.Padding = new Padding(9, 0, 0, 0);
            rollMonitorPanel.RowCount = 4;
            rollMonitorPanel.RowStyles.Add(new RowStyle());
            rollMonitorPanel.RowStyles.Add(new RowStyle(SizeType.Percent, 33.33333F));
            rollMonitorPanel.RowStyles.Add(new RowStyle(SizeType.Percent, 33.3333359F));
            rollMonitorPanel.RowStyles.Add(new RowStyle(SizeType.Percent, 33.3333359F));
            rollMonitorPanel.Size = new Size(448, 224);
            rollMonitorPanel.TabIndex = 9;
            // 
            // lblRollUserTorque
            // 
            lblRollUserTorque.AutoSize = true;
            lblRollUserTorque.BackColor = Color.Transparent;
            lblRollUserTorque.Dock = DockStyle.Bottom;
            lblRollUserTorque.Font = new Font("Microsoft Sans Serif", 9F, FontStyle.Regular, GraphicsUnit.Point, 0);
            lblRollUserTorque.ForeColor = Color.WhiteSmoke;
            lblRollUserTorque.Location = new Point(13, 169);
            lblRollUserTorque.Margin = new Padding(4, 0, 4, 0);
            lblRollUserTorque.Name = "lblRollUserTorque";
            lblRollUserTorque.Padding = new Padding(11, 13, 11, 13);
            lblRollUserTorque.Size = new Size(58, 55);
            lblRollUserTorque.TabIndex = 15;
            lblRollUserTorque.Text = "U:";
            lblRollUserTorque.TextAlign = ContentAlignment.MiddleLeft;
            // 
            // lblRollTorque
            // 
            lblRollTorque.AutoSize = true;
            lblRollTorque.BackColor = Color.Transparent;
            lblRollTorque.Dock = DockStyle.Bottom;
            lblRollTorque.Font = new Font("Microsoft Sans Serif", 9F, FontStyle.Regular, GraphicsUnit.Point, 0);
            lblRollTorque.ForeColor = Color.WhiteSmoke;
            lblRollTorque.Location = new Point(13, 112);
            lblRollTorque.Margin = new Padding(4, 0, 4, 0);
            lblRollTorque.Name = "lblRollTorque";
            lblRollTorque.Padding = new Padding(11, 13, 11, 13);
            lblRollTorque.Size = new Size(58, 55);
            lblRollTorque.TabIndex = 14;
            lblRollTorque.Text = "F:";
            lblRollTorque.TextAlign = ContentAlignment.MiddleLeft;
            // 
            // lblRollPosition
            // 
            lblRollPosition.AutoSize = true;
            lblRollPosition.BackColor = Color.Transparent;
            lblRollPosition.Dock = DockStyle.Bottom;
            lblRollPosition.Font = new Font("Microsoft Sans Serif", 9F, FontStyle.Regular, GraphicsUnit.Point, 0);
            lblRollPosition.ForeColor = Color.WhiteSmoke;
            lblRollPosition.Location = new Point(13, 56);
            lblRollPosition.Margin = new Padding(4, 0, 4, 0);
            lblRollPosition.Name = "lblRollPosition";
            lblRollPosition.Padding = new Padding(11, 13, 11, 13);
            lblRollPosition.Size = new Size(58, 55);
            lblRollPosition.TabIndex = 13;
            lblRollPosition.Text = "P:";
            lblRollPosition.TextAlign = ContentAlignment.MiddleLeft;
            // 
            // lblRollMonitor
            // 
            lblRollMonitor.AutoSize = true;
            lblRollMonitor.BackColor = Color.Transparent;
            rollMonitorPanel.SetColumnSpan(lblRollMonitor, 3);
            lblRollMonitor.Dock = DockStyle.Bottom;
            lblRollMonitor.Font = new Font("Microsoft Sans Serif", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            lblRollMonitor.ForeColor = Color.WhiteSmoke;
            lblRollMonitor.Location = new Point(13, 0);
            lblRollMonitor.Margin = new Padding(4, 0, 4, 0);
            lblRollMonitor.Name = "lblRollMonitor";
            lblRollMonitor.Padding = new Padding(11, 13, 11, 13);
            lblRollMonitor.Size = new Size(431, 55);
            lblRollMonitor.TabIndex = 12;
            lblRollMonitor.Text = "Roll:";
            lblRollMonitor.TextAlign = ContentAlignment.MiddleLeft;
            // 
            // lblRollUserTorqueValue
            // 
            lblRollUserTorqueValue.AutoSize = true;
            lblRollUserTorqueValue.BackColor = Color.Transparent;
            lblRollUserTorqueValue.Dock = DockStyle.Fill;
            lblRollUserTorqueValue.Font = new Font("Microsoft Sans Serif", 9F, FontStyle.Regular, GraphicsUnit.Point, 0);
            lblRollUserTorqueValue.ForeColor = Color.WhiteSmoke;
            lblRollUserTorqueValue.Location = new Point(297, 167);
            lblRollUserTorqueValue.Margin = new Padding(4, 0, 4, 0);
            lblRollUserTorqueValue.MinimumSize = new Size(123, 0);
            lblRollUserTorqueValue.Name = "lblRollUserTorqueValue";
            lblRollUserTorqueValue.Padding = new Padding(11, 13, 11, 13);
            lblRollUserTorqueValue.Size = new Size(147, 57);
            lblRollUserTorqueValue.TabIndex = 11;
            lblRollUserTorqueValue.Text = "--.-- Nm";
            lblRollUserTorqueValue.TextAlign = ContentAlignment.MiddleRight;
            // 
            // lblRollTorqueValue
            // 
            lblRollTorqueValue.AutoSize = true;
            lblRollTorqueValue.BackColor = Color.Transparent;
            lblRollTorqueValue.Dock = DockStyle.Fill;
            lblRollTorqueValue.Font = new Font("Microsoft Sans Serif", 9F, FontStyle.Regular, GraphicsUnit.Point, 0);
            lblRollTorqueValue.ForeColor = Color.WhiteSmoke;
            lblRollTorqueValue.Location = new Point(297, 111);
            lblRollTorqueValue.Margin = new Padding(4, 0, 4, 0);
            lblRollTorqueValue.MinimumSize = new Size(123, 0);
            lblRollTorqueValue.Name = "lblRollTorqueValue";
            lblRollTorqueValue.Padding = new Padding(11, 13, 11, 13);
            lblRollTorqueValue.Size = new Size(147, 56);
            lblRollTorqueValue.TabIndex = 9;
            lblRollTorqueValue.Text = "--.-- Nm";
            lblRollTorqueValue.TextAlign = ContentAlignment.MiddleRight;
            // 
            // lblRollPosValue
            // 
            lblRollPosValue.AutoSize = true;
            lblRollPosValue.BackColor = Color.Transparent;
            lblRollPosValue.Dock = DockStyle.Fill;
            lblRollPosValue.Font = new Font("Microsoft Sans Serif", 9F, FontStyle.Regular, GraphicsUnit.Point, 0);
            lblRollPosValue.ForeColor = Color.WhiteSmoke;
            lblRollPosValue.Location = new Point(297, 55);
            lblRollPosValue.Margin = new Padding(4, 0, 4, 0);
            lblRollPosValue.MinimumSize = new Size(147, 0);
            lblRollPosValue.Name = "lblRollPosValue";
            lblRollPosValue.Padding = new Padding(11, 13, 11, 13);
            lblRollPosValue.Size = new Size(147, 56);
            lblRollPosValue.TabIndex = 7;
            lblRollPosValue.Text = "---.- deg";
            lblRollPosValue.TextAlign = ContentAlignment.MiddleRight;
            // 
            // lblStatus
            // 
            lblStatus.AutoSize = true;
            lblStatus.BackColor = Color.Transparent;
            lblStatus.Dock = DockStyle.Bottom;
            lblStatus.Font = new Font("Microsoft Sans Serif", 12F, FontStyle.Bold, GraphicsUnit.Point, 0);
            lblStatus.ForeColor = Color.WhiteSmoke;
            lblStatus.Location = new Point(4, 1026);
            lblStatus.Margin = new Padding(4, 0, 4, 0);
            lblStatus.Name = "lblStatus";
            lblStatus.Padding = new Padding(11, 13, 11, 13);
            lblStatus.Size = new Size(440, 63);
            lblStatus.TabIndex = 8;
            lblStatus.Text = "Status: Disconnected";
            lblStatus.TextAlign = ContentAlignment.MiddleLeft;
            // 
            // lblMonitor
            // 
            lblMonitor.AutoSize = true;
            lblMonitor.BackColor = Color.Transparent;
            lblMonitor.Dock = DockStyle.Bottom;
            lblMonitor.Font = new Font("Microsoft Sans Serif", 12F, FontStyle.Bold, GraphicsUnit.Point, 0);
            lblMonitor.ForeColor = Color.WhiteSmoke;
            lblMonitor.Location = new Point(4, 519);
            lblMonitor.Margin = new Padding(4, 0, 4, 0);
            lblMonitor.Name = "lblMonitor";
            lblMonitor.Padding = new Padding(11, 13, 11, 13);
            lblMonitor.Size = new Size(440, 63);
            lblMonitor.TabIndex = 5;
            lblMonitor.Text = "Yoke Monitor";
            lblMonitor.TextAlign = ContentAlignment.MiddleLeft;
            // 
            // btnHome
            // 
            btnHome.AutoSize = true;
            btnHome.BackColor = Color.DodgerBlue;
            btnHome.Dock = DockStyle.Fill;
            btnHome.FlatAppearance.BorderSize = 0;
            btnHome.FlatAppearance.MouseDownBackColor = Color.DeepSkyBlue;
            btnHome.FlatStyle = FlatStyle.Flat;
            btnHome.Font = new Font("Microsoft Sans Serif", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            btnHome.ForeColor = Color.WhiteSmoke;
            btnHome.Location = new Point(17, 76);
            btnHome.Margin = new Padding(17, 13, 17, 13);
            btnHome.Name = "btnHome";
            btnHome.Padding = new Padding(11, 13, 11, 13);
            btnHome.Size = new Size(414, 126);
            btnHome.TabIndex = 4;
            btnHome.Text = "Home";
            btnHome.TextAlign = ContentAlignment.MiddleLeft;
            btnHome.UseVisualStyleBackColor = false;
            btnHome.Click += btnHome_Click;
            // 
            // btnYokeData
            // 
            btnYokeData.AutoSize = true;
            btnYokeData.BackColor = Color.DodgerBlue;
            btnYokeData.Dock = DockStyle.Fill;
            btnYokeData.FlatAppearance.BorderSize = 0;
            btnYokeData.FlatAppearance.MouseDownBackColor = Color.DeepSkyBlue;
            btnYokeData.FlatStyle = FlatStyle.Flat;
            btnYokeData.Font = new Font("Microsoft Sans Serif", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            btnYokeData.ForeColor = Color.WhiteSmoke;
            btnYokeData.Location = new Point(17, 380);
            btnYokeData.Margin = new Padding(17, 13, 17, 13);
            btnYokeData.Name = "btnYokeData";
            btnYokeData.Padding = new Padding(11, 13, 11, 13);
            btnYokeData.Size = new Size(414, 126);
            btnYokeData.TabIndex = 3;
            btnYokeData.Text = "Yoke Data";
            btnYokeData.TextAlign = ContentAlignment.MiddleLeft;
            btnYokeData.UseVisualStyleBackColor = false;
            btnYokeData.Click += btnYokeData_Click;
            // 
            // lblMenu
            // 
            lblMenu.AutoSize = true;
            lblMenu.BackColor = Color.Transparent;
            lblMenu.Dock = DockStyle.Fill;
            lblMenu.Font = new Font("Microsoft Sans Serif", 12F, FontStyle.Bold, GraphicsUnit.Point, 0);
            lblMenu.ForeColor = Color.WhiteSmoke;
            lblMenu.Location = new Point(4, 0);
            lblMenu.Margin = new Padding(4, 0, 4, 0);
            lblMenu.Name = "lblMenu";
            lblMenu.Padding = new Padding(11, 13, 11, 13);
            lblMenu.Size = new Size(440, 63);
            lblMenu.TabIndex = 0;
            lblMenu.Text = "Menu";
            lblMenu.TextAlign = ContentAlignment.MiddleLeft;
            // 
            // btnProfiles
            // 
            btnProfiles.AutoSize = true;
            btnProfiles.BackColor = Color.DodgerBlue;
            btnProfiles.Dock = DockStyle.Fill;
            btnProfiles.FlatAppearance.BorderSize = 0;
            btnProfiles.FlatAppearance.MouseDownBackColor = Color.DeepSkyBlue;
            btnProfiles.FlatStyle = FlatStyle.Flat;
            btnProfiles.Font = new Font("Microsoft Sans Serif", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            btnProfiles.ForeColor = Color.WhiteSmoke;
            btnProfiles.Location = new Point(17, 228);
            btnProfiles.Margin = new Padding(17, 13, 17, 13);
            btnProfiles.Name = "btnProfiles";
            btnProfiles.Padding = new Padding(11, 13, 11, 13);
            btnProfiles.Size = new Size(414, 126);
            btnProfiles.TabIndex = 1;
            btnProfiles.Text = "Profiles";
            btnProfiles.TextAlign = ContentAlignment.MiddleLeft;
            btnProfiles.UseVisualStyleBackColor = false;
            btnProfiles.Click += btnProfiles_Click;
            // 
            // flowLayoutPanel1
            // 
            flowLayoutPanel1.AutoSize = true;
            flowLayoutPanel1.Controls.Add(btnConnect);
            flowLayoutPanel1.Controls.Add(btnFfbOn);
            flowLayoutPanel1.Dock = DockStyle.Fill;
            flowLayoutPanel1.Location = new Point(0, 1089);
            flowLayoutPanel1.Margin = new Padding(0);
            flowLayoutPanel1.Name = "flowLayoutPanel1";
            flowLayoutPanel1.Size = new Size(448, 111);
            flowLayoutPanel1.TabIndex = 0;
            // 
            // btnConnect
            // 
            btnConnect.AutoSize = true;
            btnConnect.AutoSizeMode = AutoSizeMode.GrowAndShrink;
            btnConnect.BackColor = Color.DodgerBlue;
            btnConnect.FlatAppearance.BorderSize = 0;
            btnConnect.FlatAppearance.MouseDownBackColor = Color.DeepSkyBlue;
            btnConnect.FlatStyle = FlatStyle.Flat;
            btnConnect.Font = new Font("Microsoft Sans Serif", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            btnConnect.ForeColor = Color.WhiteSmoke;
            btnConnect.Location = new Point(17, 19);
            btnConnect.Margin = new Padding(17, 19, 17, 19);
            btnConnect.MinimumSize = new Size(206, 0);
            btnConnect.Name = "btnConnect";
            btnConnect.Padding = new Padding(11, 13, 11, 13);
            btnConnect.Size = new Size(206, 73);
            btnConnect.TabIndex = 3;
            btnConnect.Text = "Connect";
            btnConnect.UseVisualStyleBackColor = false;
            btnConnect.Click += btnConnect_Click;
            // 
            // btnFfbOn
            // 
            btnFfbOn.AutoSize = true;
            btnFfbOn.AutoSizeMode = AutoSizeMode.GrowAndShrink;
            btnFfbOn.BackColor = Color.DodgerBlue;
            btnFfbOn.Dock = DockStyle.Fill;
            btnFfbOn.Enabled = false;
            btnFfbOn.FlatAppearance.BorderSize = 0;
            btnFfbOn.FlatAppearance.MouseDownBackColor = Color.DeepSkyBlue;
            btnFfbOn.FlatStyle = FlatStyle.Flat;
            btnFfbOn.Font = new Font("Microsoft Sans Serif", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            btnFfbOn.ForeColor = Color.WhiteSmoke;
            btnFfbOn.Location = new Point(257, 19);
            btnFfbOn.Margin = new Padding(17, 19, 17, 19);
            btnFfbOn.Name = "btnFfbOn";
            btnFfbOn.Padding = new Padding(11, 13, 11, 13);
            btnFfbOn.Size = new Size(168, 73);
            btnFfbOn.TabIndex = 4;
            btnFfbOn.Text = "FFB ON";
            btnFfbOn.UseVisualStyleBackColor = false;
            // 
            // tablessControlContent
            // 
            tablessControlContent.Controls.Add(homePage);
            tablessControlContent.Controls.Add(profilesPage);
            tablessControlContent.Controls.Add(yokeDataPage);
            tablessControlContent.Dock = DockStyle.Fill;
            tablessControlContent.Location = new Point(448, 0);
            tablessControlContent.Margin = new Padding(0);
            tablessControlContent.Name = "tablessControlContent";
            tablessControlContent.SelectedIndex = 0;
            tablessControlContent.Size = new Size(1199, 1129);
            tablessControlContent.TabIndex = 1;
            // 
            // homePage
            // 
            homePage.BackColor = Color.Gray;
            homePage.Controls.Add(homeTableLayoutPanel);
            homePage.Location = new Point(8, 46);
            homePage.Margin = new Padding(4, 4, 4, 4);
            homePage.Name = "homePage";
            homePage.Padding = new Padding(4, 4, 4, 4);
            homePage.Size = new Size(1183, 1075);
            homePage.TabIndex = 0;
            homePage.Text = "Home";
            // 
            // homeTableLayoutPanel
            // 
            homeTableLayoutPanel.ColumnCount = 3;
            homeTableLayoutPanel.ColumnStyles.Add(new ColumnStyle());
            homeTableLayoutPanel.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100F));
            homeTableLayoutPanel.ColumnStyles.Add(new ColumnStyle());
            homeTableLayoutPanel.Controls.Add(lblCurrentProfile, 0, 1);
            homeTableLayoutPanel.Controls.Add(btnConnectSim, 2, 0);
            homeTableLayoutPanel.Controls.Add(lblConnectSimStatus, 0, 0);
            homeTableLayoutPanel.Controls.Add(cboProfile, 1, 1);
            homeTableLayoutPanel.Controls.Add(cbProfileAutoSelect, 2, 1);
            homeTableLayoutPanel.Dock = DockStyle.Fill;
            homeTableLayoutPanel.Location = new Point(4, 4);
            homeTableLayoutPanel.Margin = new Padding(4, 2, 4, 2);
            homeTableLayoutPanel.Name = "homeTableLayoutPanel";
            homeTableLayoutPanel.RowCount = 3;
            homeTableLayoutPanel.RowStyles.Add(new RowStyle());
            homeTableLayoutPanel.RowStyles.Add(new RowStyle());
            homeTableLayoutPanel.RowStyles.Add(new RowStyle(SizeType.Absolute, 659F));
            homeTableLayoutPanel.Size = new Size(1175, 1067);
            homeTableLayoutPanel.TabIndex = 0;
            // 
            // lblCurrentProfile
            // 
            lblCurrentProfile.AutoSize = true;
            lblCurrentProfile.Dock = DockStyle.Fill;
            lblCurrentProfile.Font = new Font("Microsoft Sans Serif", 12F, FontStyle.Bold);
            lblCurrentProfile.ForeColor = Color.WhiteSmoke;
            lblCurrentProfile.Location = new Point(4, 152);
            lblCurrentProfile.Margin = new Padding(4, 0, 4, 0);
            lblCurrentProfile.MinimumSize = new Size(0, 73);
            lblCurrentProfile.Name = "lblCurrentProfile";
            lblCurrentProfile.Padding = new Padding(11, 13, 11, 13);
            lblCurrentProfile.Size = new Size(270, 73);
            lblCurrentProfile.TabIndex = 6;
            lblCurrentProfile.Text = "Current Profile:";
            lblCurrentProfile.TextAlign = ContentAlignment.MiddleLeft;
            // 
            // btnConnectSim
            // 
            btnConnectSim.AutoSize = true;
            btnConnectSim.BackColor = Color.DodgerBlue;
            btnConnectSim.Dock = DockStyle.Top;
            btnConnectSim.FlatAppearance.BorderSize = 0;
            btnConnectSim.FlatAppearance.MouseDownBackColor = Color.DeepSkyBlue;
            btnConnectSim.FlatStyle = FlatStyle.Flat;
            btnConnectSim.Font = new Font("Microsoft Sans Serif", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            btnConnectSim.ForeColor = Color.WhiteSmoke;
            btnConnectSim.Location = new Point(848, 13);
            btnConnectSim.Margin = new Padding(17, 13, 17, 13);
            btnConnectSim.MinimumSize = new Size(206, 0);
            btnConnectSim.Name = "btnConnectSim";
            btnConnectSim.Padding = new Padding(11, 13, 11, 13);
            btnConnectSim.Size = new Size(310, 126);
            btnConnectSim.TabIndex = 5;
            btnConnectSim.Text = "Connect";
            btnConnectSim.UseVisualStyleBackColor = false;
            // 
            // lblConnectSimStatus
            // 
            lblConnectSimStatus.AutoSize = true;
            homeTableLayoutPanel.SetColumnSpan(lblConnectSimStatus, 2);
            lblConnectSimStatus.Dock = DockStyle.Fill;
            lblConnectSimStatus.Font = new Font("Microsoft Sans Serif", 12F, FontStyle.Bold);
            lblConnectSimStatus.ForeColor = Color.WhiteSmoke;
            lblConnectSimStatus.Location = new Point(4, 0);
            lblConnectSimStatus.Margin = new Padding(4, 0, 4, 0);
            lblConnectSimStatus.MinimumSize = new Size(0, 73);
            lblConnectSimStatus.Name = "lblConnectSimStatus";
            lblConnectSimStatus.Padding = new Padding(11, 13, 11, 13);
            lblConnectSimStatus.Size = new Size(823, 152);
            lblConnectSimStatus.TabIndex = 0;
            lblConnectSimStatus.Text = "Simulator Status: Disconnected";
            lblConnectSimStatus.TextAlign = ContentAlignment.MiddleLeft;
            // 
            // cboProfile
            // 
            cboProfile.Dock = DockStyle.Fill;
            cboProfile.FlatStyle = FlatStyle.Flat;
            cboProfile.FormattingEnabled = true;
            cboProfile.Location = new Point(295, 165);
            cboProfile.Margin = new Padding(17, 13, 17, 13);
            cboProfile.Name = "cboProfile";
            cboProfile.Size = new Size(519, 40);
            cboProfile.TabIndex = 7;
            // 
            // cbProfileAutoSelect
            // 
            cbProfileAutoSelect.AutoSize = true;
            cbProfileAutoSelect.Dock = DockStyle.Fill;
            cbProfileAutoSelect.Font = new Font("Microsoft Sans Serif", 9F);
            cbProfileAutoSelect.ForeColor = Color.WhiteSmoke;
            cbProfileAutoSelect.Location = new Point(848, 165);
            cbProfileAutoSelect.Margin = new Padding(17, 13, 17, 13);
            cbProfileAutoSelect.Name = "cbProfileAutoSelect";
            cbProfileAutoSelect.Size = new Size(310, 47);
            cbProfileAutoSelect.TabIndex = 8;
            cbProfileAutoSelect.Text = "Auto Select";
            cbProfileAutoSelect.UseVisualStyleBackColor = true;
            // 
            // profilesPage
            // 
            profilesPage.BackColor = Color.Gray;
            profilesPage.Controls.Add(tableLayoutPanel2);
            profilesPage.Location = new Point(8, 46);
            profilesPage.Margin = new Padding(4, 4, 4, 4);
            profilesPage.Name = "profilesPage";
            profilesPage.Padding = new Padding(4, 4, 4, 4);
            profilesPage.Size = new Size(1184, 1075);
            profilesPage.TabIndex = 1;
            profilesPage.Text = "Profiles";
            // 
            // tableLayoutPanel2
            // 
            tableLayoutPanel2.ColumnCount = 2;
            tableLayoutPanel2.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 83.2807541F));
            tableLayoutPanel2.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 16.7192421F));
            tableLayoutPanel2.Controls.Add(listBox1, 0, 0);
            tableLayoutPanel2.Dock = DockStyle.Fill;
            tableLayoutPanel2.Location = new Point(4, 4);
            tableLayoutPanel2.Margin = new Padding(6, 6, 6, 6);
            tableLayoutPanel2.Name = "tableLayoutPanel2";
            tableLayoutPanel2.RowCount = 2;
            tableLayoutPanel2.RowStyles.Add(new RowStyle(SizeType.Percent, 87.3239441F));
            tableLayoutPanel2.RowStyles.Add(new RowStyle(SizeType.Percent, 12.6760559F));
            tableLayoutPanel2.Size = new Size(1176, 1067);
            tableLayoutPanel2.TabIndex = 0;
            // 
            // listBox1
            // 
            listBox1.FormattingEnabled = true;
            listBox1.Location = new Point(6, 6);
            listBox1.Margin = new Padding(6, 6, 6, 6);
            listBox1.Name = "listBox1";
            listBox1.Size = new Size(966, 900);
            listBox1.TabIndex = 0;
            // 
            // yokeDataPage
            // 
            yokeDataPage.BackColor = Color.Gray;
            yokeDataPage.Location = new Point(8, 46);
            yokeDataPage.Margin = new Padding(4, 4, 4, 4);
            yokeDataPage.Name = "yokeDataPage";
            yokeDataPage.Padding = new Padding(4, 4, 4, 4);
            yokeDataPage.Size = new Size(1184, 1075);
            yokeDataPage.TabIndex = 2;
            yokeDataPage.Text = "Yoke Data";
            // 
            // BottomToolStripPanel
            // 
            BottomToolStripPanel.Location = new Point(0, 0);
            BottomToolStripPanel.Name = "BottomToolStripPanel";
            BottomToolStripPanel.Orientation = Orientation.Horizontal;
            BottomToolStripPanel.RowMargin = new Padding(3, 0, 0, 0);
            BottomToolStripPanel.Size = new Size(0, 0);
            // 
            // TopToolStripPanel
            // 
            TopToolStripPanel.Location = new Point(0, 0);
            TopToolStripPanel.Name = "TopToolStripPanel";
            TopToolStripPanel.Orientation = Orientation.Horizontal;
            TopToolStripPanel.Padding = new Padding(0, 0, 25, 25);
            TopToolStripPanel.RowMargin = new Padding(3, 0, 0, 0);
            TopToolStripPanel.Size = new Size(0, 0);
            // 
            // RightToolStripPanel
            // 
            RightToolStripPanel.Location = new Point(0, 0);
            RightToolStripPanel.Name = "RightToolStripPanel";
            RightToolStripPanel.Orientation = Orientation.Horizontal;
            RightToolStripPanel.Padding = new Padding(25, 0, 0, 0);
            RightToolStripPanel.RowMargin = new Padding(3, 0, 0, 0);
            RightToolStripPanel.Size = new Size(0, 0);
            // 
            // LeftToolStripPanel
            // 
            LeftToolStripPanel.Location = new Point(0, 0);
            LeftToolStripPanel.Name = "LeftToolStripPanel";
            LeftToolStripPanel.Orientation = Orientation.Horizontal;
            LeftToolStripPanel.RowMargin = new Padding(3, 0, 0, 0);
            LeftToolStripPanel.Size = new Size(0, 0);
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(13F, 32F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1647, 1129);
            Controls.Add(mainTableLayoutPanel);
            Margin = new Padding(4, 4, 4, 4);
            Name = "Form1";
            Text = "Force Feedback Yoke Desktop App";
            FormClosed += Form1_FormClosed;
            mainTableLayoutPanel.ResumeLayout(false);
            mainTableLayoutPanel.PerformLayout();
            menuTableLayoutPanel.ResumeLayout(false);
            menuTableLayoutPanel.PerformLayout();
            pitchMonitorPanel.ResumeLayout(false);
            pitchMonitorPanel.PerformLayout();
            rollMonitorPanel.ResumeLayout(false);
            rollMonitorPanel.PerformLayout();
            flowLayoutPanel1.ResumeLayout(false);
            flowLayoutPanel1.PerformLayout();
            tablessControlContent.ResumeLayout(false);
            homePage.ResumeLayout(false);
            homeTableLayoutPanel.ResumeLayout(false);
            homeTableLayoutPanel.PerformLayout();
            profilesPage.ResumeLayout(false);
            tableLayoutPanel2.ResumeLayout(false);
            ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel mainTableLayoutPanel;
        private System.Windows.Forms.TableLayoutPanel menuTableLayoutPanel;
        private System.Windows.Forms.Label lblMenu;
        private System.Windows.Forms.Button btnYokeData;
        private System.Windows.Forms.Button btnProfiles;
        private System.Windows.Forms.Button btnHome;
        private Controls.TablessControl tablessControlContent;
        private System.Windows.Forms.TabPage homePage;
        private System.Windows.Forms.TabPage yokeDataPage;
        private System.Windows.Forms.Label lblMonitor;
        private Label lblStatus;
        private TableLayoutPanel rollMonitorPanel;
        private Label lblRollUserTorqueValue;
        private Force_Feedback_Yoke_Desktop_App.TravelIndicator tiRollUserTorque;
        private Label lblRollTorqueValue;
        private Force_Feedback_Yoke_Desktop_App.TravelIndicator tiRollTorque;
        private Label lblRollPosValue;
        private Force_Feedback_Yoke_Desktop_App.TravelIndicator tiRollPosition;
        private Label lblRollUserTorque;
        private Label lblRollTorque;
        private Label lblRollPosition;
        private Label lblRollMonitor;
        private TableLayoutPanel pitchMonitorPanel;
        private Label lblPitchUserForce;
        private Label lblPitchForce;
        private Label lblPitchPosition;
        private Label label9;
        private Label lblPitchUserForceValue;
        private Force_Feedback_Yoke_Desktop_App.TravelIndicator tiPitchUserForce;
        private Label lblPitchForceValue;
        private Force_Feedback_Yoke_Desktop_App.TravelIndicator tiPitchForce;
        private Label lblPitchPosValue;
        private Force_Feedback_Yoke_Desktop_App.TravelIndicator tiPitchPosition;
        private FlowLayoutPanel flowLayoutPanel1;
        private Button btnConnect;
        private Button btnFfbOn;
        private TableLayoutPanel homeTableLayoutPanel;
        private Label lblConnectSimStatus;
        private Button btnConnectSim;
        private Label lblCurrentProfile;
        private ComboBox cboProfile;
        private CheckBox cbProfileAutoSelect;
        private TabPage profilesPage;
        private TableLayoutPanel tableLayoutPanel2;
        private ToolStripPanel BottomToolStripPanel;
        private ToolStripPanel TopToolStripPanel;
        private ToolStripPanel RightToolStripPanel;
        private ToolStripPanel LeftToolStripPanel;
        private ListBox listBox1;
    }
}

