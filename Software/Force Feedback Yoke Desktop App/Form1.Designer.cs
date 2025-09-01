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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            mainTableLayoutPanel = new TableLayoutPanel();
            menuTableLayoutPanel = new TableLayoutPanel();
            pitchMonitorPanel = new TableLayoutPanel();
            tiPitchUserForce = new TravelIndicator();
            tiPitchForce = new TravelIndicator();
            lblPitchUserForce = new Label();
            lblPitchForce = new Label();
            lblPitchPosition = new Label();
            lblPitchMonitor = new Label();
            lblPitchUserForceValue = new Label();
            lblPitchForceValue = new Label();
            lblPitchPosValue = new Label();
            tiPitchPosition = new TravelIndicator();
            rollMonitorPanel = new TableLayoutPanel();
            tiRollUserTorque = new TravelIndicator();
            tiRollTorque = new TravelIndicator();
            tiRollPosition = new TravelIndicator();
            lblRollUserTorque = new Label();
            lblRollTorque = new Label();
            lblRollPosition = new Label();
            lblRollMonitor = new Label();
            lblRollUserTorqueValue = new Label();
            lblRollTorqueValue = new Label();
            lblRollPosValue = new Label();
            lblMonitor = new Label();
            btnHome = new Button();
            btnYokeData = new Button();
            lblMenu = new Label();
            btnProfiles = new Button();
            tableLayoutPanel1 = new TableLayoutPanel();
            lblStatus = new Label();
            connectFlowLayoutPanel = new FlowLayoutPanel();
            btnConnect = new Button();
            btnFfbOn = new Button();
            tablessControlContent = new TablessControl();
            homePage = new TabPage();
            homeTableLayoutPanel = new TableLayoutPanel();
            btnConnectSim = new Button();
            lblConnectSimStatus = new Label();
            profilesPage = new TabPage();
            profilesTableLayoutPanel = new TableLayoutPanel();
            profileEditorTablessControl = new TablessControl();
            pitchProfileTabPage = new TabPage();
            pitchSettingsTable = new SettingsTable();
            rollProfileTabPage = new TabPage();
            rollSettingsTable = new SettingsTable();
            currentProfileTableLayoutPanel = new TableLayoutPanel();
            cbProfileAutoSelect = new CheckBox();
            lblCurrentProfile = new Label();
            cboProfile = new ComboBox();
            saveTableLayoutPanel = new TableLayoutPanel();
            btnSaveAs = new Button();
            btnSaveProfile = new Button();
            flowLayoutPanel2 = new FlowLayoutPanel();
            btnPitchProfile = new Button();
            btnRollProfile = new Button();
            yokeDataPage = new TabPage();
            BottomToolStripPanel = new ToolStripPanel();
            TopToolStripPanel = new ToolStripPanel();
            RightToolStripPanel = new ToolStripPanel();
            LeftToolStripPanel = new ToolStripPanel();
            mainTableLayoutPanel.SuspendLayout();
            menuTableLayoutPanel.SuspendLayout();
            pitchMonitorPanel.SuspendLayout();
            rollMonitorPanel.SuspendLayout();
            tableLayoutPanel1.SuspendLayout();
            connectFlowLayoutPanel.SuspendLayout();
            tablessControlContent.SuspendLayout();
            homePage.SuspendLayout();
            homeTableLayoutPanel.SuspendLayout();
            profilesPage.SuspendLayout();
            profilesTableLayoutPanel.SuspendLayout();
            profileEditorTablessControl.SuspendLayout();
            pitchProfileTabPage.SuspendLayout();
            rollProfileTabPage.SuspendLayout();
            currentProfileTableLayoutPanel.SuspendLayout();
            saveTableLayoutPanel.SuspendLayout();
            flowLayoutPanel2.SuspendLayout();
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
            mainTableLayoutPanel.Size = new Size(1657, 1267);
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
            menuTableLayoutPanel.Controls.Add(lblMonitor, 0, 4);
            menuTableLayoutPanel.Controls.Add(btnHome, 0, 1);
            menuTableLayoutPanel.Controls.Add(btnYokeData, 0, 3);
            menuTableLayoutPanel.Controls.Add(lblMenu, 0, 0);
            menuTableLayoutPanel.Controls.Add(btnProfiles, 0, 2);
            menuTableLayoutPanel.Controls.Add(tableLayoutPanel1, 0, 8);
            menuTableLayoutPanel.Dock = DockStyle.Fill;
            menuTableLayoutPanel.Location = new Point(0, 0);
            menuTableLayoutPanel.Margin = new Padding(0);
            menuTableLayoutPanel.Name = "menuTableLayoutPanel";
            menuTableLayoutPanel.RowCount = 8;
            menuTableLayoutPanel.RowStyles.Add(new RowStyle());
            menuTableLayoutPanel.RowStyles.Add(new RowStyle());
            menuTableLayoutPanel.RowStyles.Add(new RowStyle());
            menuTableLayoutPanel.RowStyles.Add(new RowStyle());
            menuTableLayoutPanel.RowStyles.Add(new RowStyle());
            menuTableLayoutPanel.RowStyles.Add(new RowStyle());
            menuTableLayoutPanel.RowStyles.Add(new RowStyle());
            menuTableLayoutPanel.RowStyles.Add(new RowStyle());
            menuTableLayoutPanel.RowStyles.Add(new RowStyle(SizeType.Absolute, 43F));
            menuTableLayoutPanel.Size = new Size(448, 1267);
            menuTableLayoutPanel.TabIndex = 0;
            // 
            // pitchMonitorPanel
            // 
            pitchMonitorPanel.AutoSize = true;
            pitchMonitorPanel.ColumnCount = 3;
            pitchMonitorPanel.ColumnStyles.Add(new ColumnStyle());
            pitchMonitorPanel.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100F));
            pitchMonitorPanel.ColumnStyles.Add(new ColumnStyle());
            pitchMonitorPanel.Controls.Add(tiPitchUserForce, 1, 3);
            pitchMonitorPanel.Controls.Add(tiPitchForce, 1, 2);
            pitchMonitorPanel.Controls.Add(lblPitchUserForce, 0, 3);
            pitchMonitorPanel.Controls.Add(lblPitchForce, 0, 2);
            pitchMonitorPanel.Controls.Add(lblPitchPosition, 0, 1);
            pitchMonitorPanel.Controls.Add(lblPitchMonitor, 0, 0);
            pitchMonitorPanel.Controls.Add(lblPitchUserForceValue, 2, 3);
            pitchMonitorPanel.Controls.Add(lblPitchForceValue, 2, 2);
            pitchMonitorPanel.Controls.Add(lblPitchPosValue, 2, 1);
            pitchMonitorPanel.Controls.Add(tiPitchPosition, 1, 1);
            pitchMonitorPanel.Dock = DockStyle.Fill;
            pitchMonitorPanel.Location = new Point(0, 582);
            pitchMonitorPanel.Margin = new Padding(0);
            pitchMonitorPanel.Name = "pitchMonitorPanel";
            pitchMonitorPanel.Padding = new Padding(9, 0, 0, 0);
            pitchMonitorPanel.RowCount = 4;
            pitchMonitorPanel.RowStyles.Add(new RowStyle());
            pitchMonitorPanel.RowStyles.Add(new RowStyle());
            pitchMonitorPanel.RowStyles.Add(new RowStyle());
            pitchMonitorPanel.RowStyles.Add(new RowStyle());
            pitchMonitorPanel.Size = new Size(448, 220);
            pitchMonitorPanel.TabIndex = 10;
            // 
            // tiPitchUserForce
            // 
            tiPitchUserForce.AutoSize = true;
            tiPitchUserForce.BackColor = Color.Gray;
            tiPitchUserForce.CenterLineColor = Color.FromArgb(31, 255, 30);
            tiPitchUserForce.Dock = DockStyle.Fill;
            tiPitchUserForce.ForeColor = Color.FromArgb(31, 255, 30);
            tiPitchUserForce.Location = new Point(81, 184);
            tiPitchUserForce.Margin = new Padding(6, 19, 6, 19);
            tiPitchUserForce.Maximum = 100;
            tiPitchUserForce.MaximumSize = new Size(0, 32);
            tiPitchUserForce.Minimum = -100;
            tiPitchUserForce.Name = "tiPitchUserForce";
            tiPitchUserForce.Size = new Size(206, 17);
            tiPitchUserForce.TabIndex = 18;
            tiPitchUserForce.Type = TravelIndicator.TravelIndicatorType.Centered;
            tiPitchUserForce.Value = 0;
            // 
            // tiPitchForce
            // 
            tiPitchForce.AutoSize = true;
            tiPitchForce.BackColor = Color.Gray;
            tiPitchForce.CenterLineColor = Color.FromArgb(255, 141, 30);
            tiPitchForce.Dock = DockStyle.Fill;
            tiPitchForce.ForeColor = Color.FromArgb(255, 141, 30);
            tiPitchForce.Location = new Point(81, 129);
            tiPitchForce.Margin = new Padding(6, 19, 6, 19);
            tiPitchForce.Maximum = 100;
            tiPitchForce.Minimum = -100;
            tiPitchForce.Name = "tiPitchForce";
            tiPitchForce.Size = new Size(206, 17);
            tiPitchForce.TabIndex = 17;
            tiPitchForce.Type = TravelIndicator.TravelIndicatorType.Centered;
            tiPitchForce.Value = 0;
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
            lblPitchForce.Location = new Point(13, 110);
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
            lblPitchPosition.Size = new Size(58, 55);
            lblPitchPosition.TabIndex = 13;
            lblPitchPosition.Text = "P:";
            lblPitchPosition.TextAlign = ContentAlignment.MiddleLeft;
            // 
            // lblPitchMonitor
            // 
            lblPitchMonitor.AutoSize = true;
            lblPitchMonitor.BackColor = Color.Transparent;
            pitchMonitorPanel.SetColumnSpan(lblPitchMonitor, 3);
            lblPitchMonitor.Dock = DockStyle.Bottom;
            lblPitchMonitor.Font = new Font("Microsoft Sans Serif", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            lblPitchMonitor.ForeColor = Color.WhiteSmoke;
            lblPitchMonitor.Location = new Point(13, 0);
            lblPitchMonitor.Margin = new Padding(4, 0, 4, 0);
            lblPitchMonitor.Name = "lblPitchMonitor";
            lblPitchMonitor.Padding = new Padding(11, 13, 11, 13);
            lblPitchMonitor.Size = new Size(431, 55);
            lblPitchMonitor.TabIndex = 12;
            lblPitchMonitor.Text = "Pitch:";
            lblPitchMonitor.TextAlign = ContentAlignment.MiddleLeft;
            // 
            // lblPitchUserForceValue
            // 
            lblPitchUserForceValue.AutoSize = true;
            lblPitchUserForceValue.BackColor = Color.Transparent;
            lblPitchUserForceValue.Dock = DockStyle.Fill;
            lblPitchUserForceValue.Font = new Font("Microsoft Sans Serif", 9F, FontStyle.Regular, GraphicsUnit.Point, 0);
            lblPitchUserForceValue.ForeColor = Color.WhiteSmoke;
            lblPitchUserForceValue.Location = new Point(297, 165);
            lblPitchUserForceValue.Margin = new Padding(4, 0, 4, 0);
            lblPitchUserForceValue.MinimumSize = new Size(123, 0);
            lblPitchUserForceValue.Name = "lblPitchUserForceValue";
            lblPitchUserForceValue.Padding = new Padding(11, 13, 11, 13);
            lblPitchUserForceValue.Size = new Size(147, 55);
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
            lblPitchForceValue.Location = new Point(297, 110);
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
            lblPitchPosValue.Size = new Size(147, 55);
            lblPitchPosValue.TabIndex = 7;
            lblPitchPosValue.Text = "----.- mm";
            lblPitchPosValue.TextAlign = ContentAlignment.MiddleRight;
            // 
            // tiPitchPosition
            // 
            tiPitchPosition.AutoSize = true;
            tiPitchPosition.BackColor = Color.Gray;
            tiPitchPosition.CenterLineColor = Color.FromArgb(254, 30, 255);
            tiPitchPosition.Dock = DockStyle.Fill;
            tiPitchPosition.ForeColor = Color.FromArgb(254, 30, 255);
            tiPitchPosition.Location = new Point(81, 74);
            tiPitchPosition.Margin = new Padding(6, 19, 6, 19);
            tiPitchPosition.Maximum = 100;
            tiPitchPosition.Minimum = -100;
            tiPitchPosition.Name = "tiPitchPosition";
            tiPitchPosition.Size = new Size(206, 17);
            tiPitchPosition.TabIndex = 16;
            tiPitchPosition.Type = TravelIndicator.TravelIndicatorType.Centered;
            tiPitchPosition.Value = 0;
            // 
            // rollMonitorPanel
            // 
            rollMonitorPanel.ColumnCount = 3;
            rollMonitorPanel.ColumnStyles.Add(new ColumnStyle());
            rollMonitorPanel.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100F));
            rollMonitorPanel.ColumnStyles.Add(new ColumnStyle());
            rollMonitorPanel.Controls.Add(tiRollUserTorque, 1, 3);
            rollMonitorPanel.Controls.Add(tiRollTorque, 1, 2);
            rollMonitorPanel.Controls.Add(tiRollPosition, 1, 1);
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
            rollMonitorPanel.RowStyles.Add(new RowStyle());
            rollMonitorPanel.RowStyles.Add(new RowStyle());
            rollMonitorPanel.RowStyles.Add(new RowStyle());
            rollMonitorPanel.Size = new Size(448, 224);
            rollMonitorPanel.TabIndex = 9;
            // 
            // tiRollUserTorque
            // 
            tiRollUserTorque.AutoSize = true;
            tiRollUserTorque.BackColor = Color.Gray;
            tiRollUserTorque.CenterLineColor = Color.FromArgb(31, 255, 30);
            tiRollUserTorque.Dock = DockStyle.Fill;
            tiRollUserTorque.ForeColor = Color.FromArgb(31, 255, 30);
            tiRollUserTorque.Location = new Point(81, 184);
            tiRollUserTorque.Margin = new Padding(6, 19, 6, 19);
            tiRollUserTorque.Maximum = 100;
            tiRollUserTorque.Minimum = -100;
            tiRollUserTorque.Name = "tiRollUserTorque";
            tiRollUserTorque.Size = new Size(206, 21);
            tiRollUserTorque.TabIndex = 19;
            tiRollUserTorque.Type = TravelIndicator.TravelIndicatorType.Centered;
            tiRollUserTorque.Value = 0;
            // 
            // tiRollTorque
            // 
            tiRollTorque.AutoSize = true;
            tiRollTorque.BackColor = Color.Gray;
            tiRollTorque.CenterLineColor = Color.FromArgb(255, 141, 30);
            tiRollTorque.Dock = DockStyle.Fill;
            tiRollTorque.ForeColor = Color.FromArgb(255, 141, 30);
            tiRollTorque.Location = new Point(81, 129);
            tiRollTorque.Margin = new Padding(6, 19, 6, 19);
            tiRollTorque.Maximum = 100;
            tiRollTorque.Minimum = -100;
            tiRollTorque.Name = "tiRollTorque";
            tiRollTorque.Size = new Size(206, 17);
            tiRollTorque.TabIndex = 18;
            tiRollTorque.Type = TravelIndicator.TravelIndicatorType.Centered;
            tiRollTorque.Value = 0;
            // 
            // tiRollPosition
            // 
            tiRollPosition.AutoSize = true;
            tiRollPosition.BackColor = Color.Gray;
            tiRollPosition.CenterLineColor = Color.FromArgb(254, 30, 255);
            tiRollPosition.Dock = DockStyle.Fill;
            tiRollPosition.ForeColor = Color.FromArgb(254, 30, 255);
            tiRollPosition.Location = new Point(81, 74);
            tiRollPosition.Margin = new Padding(6, 19, 6, 19);
            tiRollPosition.Maximum = 100;
            tiRollPosition.Minimum = -100;
            tiRollPosition.Name = "tiRollPosition";
            tiRollPosition.Size = new Size(206, 17);
            tiRollPosition.TabIndex = 17;
            tiRollPosition.Type = TravelIndicator.TravelIndicatorType.Centered;
            tiRollPosition.Value = 0;
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
            lblRollTorque.Location = new Point(13, 110);
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
            lblRollPosition.Location = new Point(13, 55);
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
            lblRollUserTorqueValue.Location = new Point(297, 165);
            lblRollUserTorqueValue.Margin = new Padding(4, 0, 4, 0);
            lblRollUserTorqueValue.MinimumSize = new Size(123, 0);
            lblRollUserTorqueValue.Name = "lblRollUserTorqueValue";
            lblRollUserTorqueValue.Padding = new Padding(11, 13, 11, 13);
            lblRollUserTorqueValue.Size = new Size(147, 59);
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
            lblRollTorqueValue.Location = new Point(297, 110);
            lblRollTorqueValue.Margin = new Padding(4, 0, 4, 0);
            lblRollTorqueValue.MinimumSize = new Size(123, 0);
            lblRollTorqueValue.Name = "lblRollTorqueValue";
            lblRollTorqueValue.Padding = new Padding(11, 13, 11, 13);
            lblRollTorqueValue.Size = new Size(147, 55);
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
            lblRollPosValue.Size = new Size(147, 55);
            lblRollPosValue.TabIndex = 7;
            lblRollPosValue.Text = "---.- deg";
            lblRollPosValue.TextAlign = ContentAlignment.MiddleRight;
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
            // tableLayoutPanel1
            // 
            tableLayoutPanel1.ColumnCount = 1;
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100F));
            tableLayoutPanel1.Controls.Add(lblStatus, 0, 0);
            tableLayoutPanel1.Controls.Add(connectFlowLayoutPanel, 0, 1);
            tableLayoutPanel1.Dock = DockStyle.Fill;
            tableLayoutPanel1.Location = new Point(0, 1026);
            tableLayoutPanel1.Margin = new Padding(0);
            tableLayoutPanel1.Name = "tableLayoutPanel1";
            tableLayoutPanel1.RowCount = 2;
            tableLayoutPanel1.RowStyles.Add(new RowStyle());
            tableLayoutPanel1.RowStyles.Add(new RowStyle());
            tableLayoutPanel1.Size = new Size(448, 241);
            tableLayoutPanel1.TabIndex = 11;
            // 
            // lblStatus
            // 
            lblStatus.AutoSize = true;
            lblStatus.BackColor = Color.Transparent;
            lblStatus.Dock = DockStyle.Bottom;
            lblStatus.Font = new Font("Microsoft Sans Serif", 12F, FontStyle.Bold, GraphicsUnit.Point, 0);
            lblStatus.ForeColor = Color.WhiteSmoke;
            lblStatus.Location = new Point(4, 0);
            lblStatus.Margin = new Padding(4, 0, 4, 0);
            lblStatus.Name = "lblStatus";
            lblStatus.Padding = new Padding(11, 13, 11, 13);
            lblStatus.Size = new Size(440, 63);
            lblStatus.TabIndex = 9;
            lblStatus.Text = "Status: Disconnected";
            lblStatus.TextAlign = ContentAlignment.MiddleLeft;
            // 
            // connectFlowLayoutPanel
            // 
            connectFlowLayoutPanel.AutoSize = true;
            connectFlowLayoutPanel.Controls.Add(btnConnect);
            connectFlowLayoutPanel.Controls.Add(btnFfbOn);
            connectFlowLayoutPanel.Dock = DockStyle.Fill;
            connectFlowLayoutPanel.Location = new Point(0, 63);
            connectFlowLayoutPanel.Margin = new Padding(0);
            connectFlowLayoutPanel.Name = "connectFlowLayoutPanel";
            connectFlowLayoutPanel.Size = new Size(448, 178);
            connectFlowLayoutPanel.TabIndex = 0;
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
            btnConnect.MinimumSize = new Size(204, 0);
            btnConnect.Name = "btnConnect";
            btnConnect.Padding = new Padding(6, 13, 6, 13);
            btnConnect.Size = new Size(204, 73);
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
            btnFfbOn.Location = new Point(255, 19);
            btnFfbOn.Margin = new Padding(17, 19, 17, 19);
            btnFfbOn.MinimumSize = new Size(171, 0);
            btnFfbOn.Name = "btnFfbOn";
            btnFfbOn.Padding = new Padding(6, 13, 6, 13);
            btnFfbOn.Size = new Size(171, 73);
            btnFfbOn.TabIndex = 4;
            btnFfbOn.Text = "FFB ON";
            btnFfbOn.UseVisualStyleBackColor = false;
            btnFfbOn.Click += btnFfbOn_Click;
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
            tablessControlContent.Size = new Size(1209, 1267);
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
            homePage.Size = new Size(1193, 1213);
            homePage.TabIndex = 0;
            homePage.Text = "Home";
            // 
            // homeTableLayoutPanel
            // 
            homeTableLayoutPanel.ColumnCount = 3;
            homeTableLayoutPanel.ColumnStyles.Add(new ColumnStyle());
            homeTableLayoutPanel.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100F));
            homeTableLayoutPanel.ColumnStyles.Add(new ColumnStyle());
            homeTableLayoutPanel.Controls.Add(btnConnectSim, 2, 0);
            homeTableLayoutPanel.Controls.Add(lblConnectSimStatus, 0, 0);
            homeTableLayoutPanel.Dock = DockStyle.Fill;
            homeTableLayoutPanel.Location = new Point(4, 4);
            homeTableLayoutPanel.Margin = new Padding(4, 2, 4, 2);
            homeTableLayoutPanel.Name = "homeTableLayoutPanel";
            homeTableLayoutPanel.RowCount = 3;
            homeTableLayoutPanel.RowStyles.Add(new RowStyle());
            homeTableLayoutPanel.RowStyles.Add(new RowStyle());
            homeTableLayoutPanel.RowStyles.Add(new RowStyle(SizeType.Absolute, 659F));
            homeTableLayoutPanel.Size = new Size(1185, 1205);
            homeTableLayoutPanel.TabIndex = 0;
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
            btnConnectSim.Location = new Point(858, 13);
            btnConnectSim.Margin = new Padding(17, 13, 17, 13);
            btnConnectSim.MinimumSize = new Size(206, 0);
            btnConnectSim.Name = "btnConnectSim";
            btnConnectSim.Padding = new Padding(11, 13, 11, 13);
            btnConnectSim.Size = new Size(310, 126);
            btnConnectSim.TabIndex = 5;
            btnConnectSim.Text = "Connect";
            btnConnectSim.UseVisualStyleBackColor = false;
            btnConnectSim.Click += btnConnectSim_Click;
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
            lblConnectSimStatus.Size = new Size(833, 152);
            lblConnectSimStatus.TabIndex = 0;
            lblConnectSimStatus.Text = "Simulator Status: Disconnected";
            lblConnectSimStatus.TextAlign = ContentAlignment.MiddleLeft;
            // 
            // profilesPage
            // 
            profilesPage.BackColor = Color.Gray;
            profilesPage.Controls.Add(profilesTableLayoutPanel);
            profilesPage.Location = new Point(8, 46);
            profilesPage.Margin = new Padding(4, 4, 4, 4);
            profilesPage.Name = "profilesPage";
            profilesPage.Padding = new Padding(4, 4, 4, 4);
            profilesPage.Size = new Size(1193, 1213);
            profilesPage.TabIndex = 1;
            profilesPage.Text = "Profiles";
            // 
            // profilesTableLayoutPanel
            // 
            profilesTableLayoutPanel.ColumnCount = 1;
            profilesTableLayoutPanel.ColumnStyles.Add(new ColumnStyle());
            profilesTableLayoutPanel.Controls.Add(profileEditorTablessControl, 0, 2);
            profilesTableLayoutPanel.Controls.Add(currentProfileTableLayoutPanel, 0, 0);
            profilesTableLayoutPanel.Controls.Add(saveTableLayoutPanel, 0, 3);
            profilesTableLayoutPanel.Controls.Add(flowLayoutPanel2, 0, 1);
            profilesTableLayoutPanel.Dock = DockStyle.Fill;
            profilesTableLayoutPanel.Location = new Point(4, 4);
            profilesTableLayoutPanel.Margin = new Padding(6, 6, 6, 6);
            profilesTableLayoutPanel.Name = "profilesTableLayoutPanel";
            profilesTableLayoutPanel.RowCount = 4;
            profilesTableLayoutPanel.RowStyles.Add(new RowStyle());
            profilesTableLayoutPanel.RowStyles.Add(new RowStyle());
            profilesTableLayoutPanel.RowStyles.Add(new RowStyle());
            profilesTableLayoutPanel.RowStyles.Add(new RowStyle());
            profilesTableLayoutPanel.Size = new Size(1185, 1205);
            profilesTableLayoutPanel.TabIndex = 0;
            // 
            // profileEditorTablessControl
            // 
            profileEditorTablessControl.Controls.Add(pitchProfileTabPage);
            profileEditorTablessControl.Controls.Add(rollProfileTabPage);
            profileEditorTablessControl.Dock = DockStyle.Fill;
            profileEditorTablessControl.Location = new Point(0, 206);
            profileEditorTablessControl.Margin = new Padding(0);
            profileEditorTablessControl.Name = "profileEditorTablessControl";
            profileEditorTablessControl.SelectedIndex = 0;
            profileEditorTablessControl.Size = new Size(1200, 834);
            profileEditorTablessControl.TabIndex = 2;
            // 
            // pitchProfileTabPage
            // 
            pitchProfileTabPage.AutoScroll = true;
            pitchProfileTabPage.BackColor = Color.Gray;
            pitchProfileTabPage.Controls.Add(pitchSettingsTable);
            pitchProfileTabPage.Location = new Point(8, 46);
            pitchProfileTabPage.Margin = new Padding(4, 4, 4, 4);
            pitchProfileTabPage.Name = "pitchProfileTabPage";
            pitchProfileTabPage.Padding = new Padding(4, 4, 4, 4);
            pitchProfileTabPage.Size = new Size(1184, 780);
            pitchProfileTabPage.TabIndex = 0;
            pitchProfileTabPage.Text = "Pitch";
            // 
            // pitchSettingsTable
            // 
            pitchSettingsTable.AutoScroll = true;
            pitchSettingsTable.Dock = DockStyle.Fill;
            pitchSettingsTable.Location = new Point(4, 4);
            pitchSettingsTable.Margin = new Padding(11, 13, 11, 13);
            pitchSettingsTable.Name = "pitchSettingsTable";
            pitchSettingsTable.Size = new Size(1176, 772);
            pitchSettingsTable.TabIndex = 1;
            pitchSettingsTable.ValueChanged += pitchSettingsTable_ValueChanged;
            // 
            // rollProfileTabPage
            // 
            rollProfileTabPage.AutoScroll = true;
            rollProfileTabPage.BackColor = Color.Gray;
            rollProfileTabPage.Controls.Add(rollSettingsTable);
            rollProfileTabPage.Location = new Point(8, 46);
            rollProfileTabPage.Margin = new Padding(4, 4, 4, 4);
            rollProfileTabPage.Name = "rollProfileTabPage";
            rollProfileTabPage.Padding = new Padding(4, 4, 4, 4);
            rollProfileTabPage.Size = new Size(1184, 780);
            rollProfileTabPage.TabIndex = 1;
            rollProfileTabPage.Text = "Roll";
            // 
            // rollSettingsTable
            // 
            rollSettingsTable.AutoScroll = true;
            rollSettingsTable.Dock = DockStyle.Fill;
            rollSettingsTable.Location = new Point(4, 4);
            rollSettingsTable.Margin = new Padding(11, 13, 11, 13);
            rollSettingsTable.Name = "rollSettingsTable";
            rollSettingsTable.Size = new Size(1176, 772);
            rollSettingsTable.TabIndex = 2;
            rollSettingsTable.ValueChanged += rollSettingsTable_ValueChanged;
            // 
            // currentProfileTableLayoutPanel
            // 
            currentProfileTableLayoutPanel.ColumnCount = 3;
            currentProfileTableLayoutPanel.ColumnStyles.Add(new ColumnStyle());
            currentProfileTableLayoutPanel.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100F));
            currentProfileTableLayoutPanel.ColumnStyles.Add(new ColumnStyle());
            currentProfileTableLayoutPanel.Controls.Add(cbProfileAutoSelect, 2, 0);
            currentProfileTableLayoutPanel.Controls.Add(lblCurrentProfile, 0, 0);
            currentProfileTableLayoutPanel.Controls.Add(cboProfile, 1, 0);
            currentProfileTableLayoutPanel.Location = new Point(0, 0);
            currentProfileTableLayoutPanel.Margin = new Padding(0);
            currentProfileTableLayoutPanel.Name = "currentProfileTableLayoutPanel";
            currentProfileTableLayoutPanel.RowCount = 1;
            currentProfileTableLayoutPanel.RowStyles.Add(new RowStyle(SizeType.Percent, 100F));
            currentProfileTableLayoutPanel.Size = new Size(1161, 83);
            currentProfileTableLayoutPanel.TabIndex = 0;
            // 
            // cbProfileAutoSelect
            // 
            cbProfileAutoSelect.AutoSize = true;
            cbProfileAutoSelect.Dock = DockStyle.Fill;
            cbProfileAutoSelect.Font = new Font("Microsoft Sans Serif", 9F);
            cbProfileAutoSelect.ForeColor = Color.WhiteSmoke;
            cbProfileAutoSelect.Location = new Point(977, 13);
            cbProfileAutoSelect.Margin = new Padding(17, 13, 17, 13);
            cbProfileAutoSelect.Name = "cbProfileAutoSelect";
            cbProfileAutoSelect.Size = new Size(167, 57);
            cbProfileAutoSelect.TabIndex = 11;
            cbProfileAutoSelect.Text = "Auto Select";
            cbProfileAutoSelect.UseVisualStyleBackColor = true;
            // 
            // lblCurrentProfile
            // 
            lblCurrentProfile.AutoSize = true;
            lblCurrentProfile.Dock = DockStyle.Fill;
            lblCurrentProfile.Font = new Font("Microsoft Sans Serif", 12F, FontStyle.Bold);
            lblCurrentProfile.ForeColor = Color.WhiteSmoke;
            lblCurrentProfile.Location = new Point(4, 0);
            lblCurrentProfile.Margin = new Padding(4, 0, 4, 0);
            lblCurrentProfile.Name = "lblCurrentProfile";
            lblCurrentProfile.Padding = new Padding(11, 13, 11, 13);
            lblCurrentProfile.Size = new Size(270, 83);
            lblCurrentProfile.TabIndex = 9;
            lblCurrentProfile.Text = "Current Profile:";
            lblCurrentProfile.TextAlign = ContentAlignment.MiddleLeft;
            // 
            // cboProfile
            // 
            cboProfile.AutoCompleteMode = AutoCompleteMode.SuggestAppend;
            cboProfile.AutoCompleteSource = AutoCompleteSource.ListItems;
            cboProfile.Dock = DockStyle.Fill;
            cboProfile.FlatStyle = FlatStyle.Flat;
            cboProfile.Location = new Point(295, 13);
            cboProfile.Margin = new Padding(17, 13, 17, 13);
            cboProfile.Name = "cboProfile";
            cboProfile.Size = new Size(648, 40);
            cboProfile.TabIndex = 10;
            // 
            // saveTableLayoutPanel
            // 
            saveTableLayoutPanel.AutoSize = true;
            saveTableLayoutPanel.ColumnCount = 3;
            saveTableLayoutPanel.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100F));
            saveTableLayoutPanel.ColumnStyles.Add(new ColumnStyle());
            saveTableLayoutPanel.ColumnStyles.Add(new ColumnStyle());
            saveTableLayoutPanel.Controls.Add(btnSaveAs, 2, 0);
            saveTableLayoutPanel.Controls.Add(btnSaveProfile, 1, 0);
            saveTableLayoutPanel.Dock = DockStyle.Bottom;
            saveTableLayoutPanel.Location = new Point(6, 1088);
            saveTableLayoutPanel.Margin = new Padding(6, 6, 6, 6);
            saveTableLayoutPanel.Name = "saveTableLayoutPanel";
            saveTableLayoutPanel.RowCount = 1;
            saveTableLayoutPanel.RowStyles.Add(new RowStyle());
            saveTableLayoutPanel.Size = new Size(1188, 111);
            saveTableLayoutPanel.TabIndex = 1;
            // 
            // btnSaveAs
            // 
            btnSaveAs.AutoSize = true;
            btnSaveAs.AutoSizeMode = AutoSizeMode.GrowAndShrink;
            btnSaveAs.BackColor = Color.DodgerBlue;
            btnSaveAs.Dock = DockStyle.Fill;
            btnSaveAs.FlatAppearance.BorderSize = 0;
            btnSaveAs.FlatAppearance.MouseDownBackColor = Color.DeepSkyBlue;
            btnSaveAs.FlatStyle = FlatStyle.Flat;
            btnSaveAs.Font = new Font("Microsoft Sans Serif", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            btnSaveAs.ForeColor = Color.WhiteSmoke;
            btnSaveAs.Location = new Point(977, 19);
            btnSaveAs.Margin = new Padding(17, 19, 17, 19);
            btnSaveAs.MaximumSize = new Size(0, 90);
            btnSaveAs.Name = "btnSaveAs";
            btnSaveAs.Padding = new Padding(11, 13, 11, 13);
            btnSaveAs.Size = new Size(194, 73);
            btnSaveAs.TabIndex = 6;
            btnSaveAs.Text = "Save As...";
            btnSaveAs.UseVisualStyleBackColor = false;
            btnSaveAs.Click += btnSaveAs_Click;
            // 
            // btnSaveProfile
            // 
            btnSaveProfile.AutoSize = true;
            btnSaveProfile.AutoSizeMode = AutoSizeMode.GrowAndShrink;
            btnSaveProfile.BackColor = Color.DodgerBlue;
            btnSaveProfile.Dock = DockStyle.Fill;
            btnSaveProfile.FlatAppearance.BorderSize = 0;
            btnSaveProfile.FlatAppearance.MouseDownBackColor = Color.DeepSkyBlue;
            btnSaveProfile.FlatStyle = FlatStyle.Flat;
            btnSaveProfile.Font = new Font("Microsoft Sans Serif", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            btnSaveProfile.ForeColor = Color.WhiteSmoke;
            btnSaveProfile.Location = new Point(823, 19);
            btnSaveProfile.Margin = new Padding(17, 19, 17, 19);
            btnSaveProfile.MaximumSize = new Size(0, 90);
            btnSaveProfile.Name = "btnSaveProfile";
            btnSaveProfile.Padding = new Padding(11, 13, 11, 13);
            btnSaveProfile.Size = new Size(120, 73);
            btnSaveProfile.TabIndex = 5;
            btnSaveProfile.Text = "Save";
            btnSaveProfile.UseVisualStyleBackColor = false;
            btnSaveProfile.Click += btnSaveProfile_Click;
            // 
            // flowLayoutPanel2
            // 
            flowLayoutPanel2.AutoSize = true;
            flowLayoutPanel2.Controls.Add(btnPitchProfile);
            flowLayoutPanel2.Controls.Add(btnRollProfile);
            flowLayoutPanel2.Dock = DockStyle.Fill;
            flowLayoutPanel2.Location = new Point(6, 89);
            flowLayoutPanel2.Margin = new Padding(6, 6, 6, 6);
            flowLayoutPanel2.Name = "flowLayoutPanel2";
            flowLayoutPanel2.Size = new Size(1188, 111);
            flowLayoutPanel2.TabIndex = 3;
            // 
            // btnPitchProfile
            // 
            btnPitchProfile.AutoSize = true;
            btnPitchProfile.AutoSizeMode = AutoSizeMode.GrowAndShrink;
            btnPitchProfile.BackColor = Color.DodgerBlue;
            btnPitchProfile.Dock = DockStyle.Fill;
            btnPitchProfile.FlatAppearance.BorderSize = 0;
            btnPitchProfile.FlatAppearance.MouseDownBackColor = Color.DeepSkyBlue;
            btnPitchProfile.FlatStyle = FlatStyle.Flat;
            btnPitchProfile.Font = new Font("Microsoft Sans Serif", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            btnPitchProfile.ForeColor = Color.WhiteSmoke;
            btnPitchProfile.Location = new Point(17, 19);
            btnPitchProfile.Margin = new Padding(17, 19, 17, 19);
            btnPitchProfile.Name = "btnPitchProfile";
            btnPitchProfile.Padding = new Padding(11, 13, 11, 13);
            btnPitchProfile.Size = new Size(120, 73);
            btnPitchProfile.TabIndex = 6;
            btnPitchProfile.Text = "Pitch";
            btnPitchProfile.UseVisualStyleBackColor = false;
            btnPitchProfile.Click += btnPitchProfile_Click;
            // 
            // btnRollProfile
            // 
            btnRollProfile.AutoSize = true;
            btnRollProfile.AutoSizeMode = AutoSizeMode.GrowAndShrink;
            btnRollProfile.BackColor = Color.DodgerBlue;
            btnRollProfile.Dock = DockStyle.Fill;
            btnRollProfile.FlatAppearance.BorderSize = 0;
            btnRollProfile.FlatAppearance.MouseDownBackColor = Color.DeepSkyBlue;
            btnRollProfile.FlatStyle = FlatStyle.Flat;
            btnRollProfile.Font = new Font("Microsoft Sans Serif", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            btnRollProfile.ForeColor = Color.WhiteSmoke;
            btnRollProfile.Location = new Point(171, 19);
            btnRollProfile.Margin = new Padding(17, 19, 17, 19);
            btnRollProfile.Name = "btnRollProfile";
            btnRollProfile.Padding = new Padding(11, 13, 11, 13);
            btnRollProfile.Size = new Size(103, 73);
            btnRollProfile.TabIndex = 7;
            btnRollProfile.Text = "Roll";
            btnRollProfile.UseVisualStyleBackColor = false;
            btnRollProfile.Click += btnRollProfile_Click;
            // 
            // yokeDataPage
            // 
            yokeDataPage.BackColor = Color.Gray;
            yokeDataPage.Location = new Point(8, 46);
            yokeDataPage.Margin = new Padding(4, 4, 4, 4);
            yokeDataPage.Name = "yokeDataPage";
            yokeDataPage.Padding = new Padding(4, 4, 4, 4);
            yokeDataPage.Size = new Size(1193, 1213);
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
            ClientSize = new Size(1657, 1267);
            Controls.Add(mainTableLayoutPanel);
            Margin = new Padding(4, 4, 4, 4);
            Name = "Form1";
            Text = "Force Feedback Yoke Desktop App";
            FormClosed += Form1_FormClosed;
            Load += Form1_Load;
            mainTableLayoutPanel.ResumeLayout(false);
            mainTableLayoutPanel.PerformLayout();
            menuTableLayoutPanel.ResumeLayout(false);
            menuTableLayoutPanel.PerformLayout();
            pitchMonitorPanel.ResumeLayout(false);
            pitchMonitorPanel.PerformLayout();
            rollMonitorPanel.ResumeLayout(false);
            rollMonitorPanel.PerformLayout();
            tableLayoutPanel1.ResumeLayout(false);
            tableLayoutPanel1.PerformLayout();
            connectFlowLayoutPanel.ResumeLayout(false);
            connectFlowLayoutPanel.PerformLayout();
            tablessControlContent.ResumeLayout(false);
            homePage.ResumeLayout(false);
            homeTableLayoutPanel.ResumeLayout(false);
            homeTableLayoutPanel.PerformLayout();
            profilesPage.ResumeLayout(false);
            profilesTableLayoutPanel.ResumeLayout(false);
            profilesTableLayoutPanel.PerformLayout();
            profileEditorTablessControl.ResumeLayout(false);
            pitchProfileTabPage.ResumeLayout(false);
            rollProfileTabPage.ResumeLayout(false);
            currentProfileTableLayoutPanel.ResumeLayout(false);
            currentProfileTableLayoutPanel.PerformLayout();
            saveTableLayoutPanel.ResumeLayout(false);
            saveTableLayoutPanel.PerformLayout();
            flowLayoutPanel2.ResumeLayout(false);
            flowLayoutPanel2.PerformLayout();
            ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel mainTableLayoutPanel;
        private System.Windows.Forms.TableLayoutPanel menuTableLayoutPanel;
        private System.Windows.Forms.Label lblMenu;
        private System.Windows.Forms.Button btnYokeData;
        private System.Windows.Forms.Button btnProfiles;
        private System.Windows.Forms.Button btnHome;
        private TablessControl tablessControlContent;
        private System.Windows.Forms.TabPage homePage;
        private System.Windows.Forms.TabPage yokeDataPage;
        private System.Windows.Forms.Label lblMonitor;
        private TableLayoutPanel rollMonitorPanel;
        private Label lblRollUserTorqueValue;
        private Label lblRollTorqueValue;
        private Label lblRollPosValue;
        private Label lblRollUserTorque;
        private Label lblRollTorque;
        private Label lblRollPosition;
        private Label lblRollMonitor;
        private TableLayoutPanel pitchMonitorPanel;
        private Label lblPitchUserForce;
        private Label lblPitchForce;
        private Label lblPitchPosition;
        private Label lblPitchMonitor;
        private Label lblPitchUserForceValue;
        private Label lblPitchForceValue;
        private Label lblPitchPosValue;
        private FlowLayoutPanel connectFlowLayoutPanel;
        private Button btnConnect;
        private Button btnFfbOn;
        private TableLayoutPanel homeTableLayoutPanel;
        private Label lblConnectSimStatus;
        private Button btnConnectSim;
        private TabPage profilesPage;
        private TableLayoutPanel profilesTableLayoutPanel;
        private ToolStripPanel BottomToolStripPanel;
        private ToolStripPanel TopToolStripPanel;
        private ToolStripPanel RightToolStripPanel;
        private ToolStripPanel LeftToolStripPanel;
        private TableLayoutPanel currentProfileTableLayoutPanel;
        private CheckBox cbProfileAutoSelect;
        private Label lblCurrentProfile;
        private ComboBox cboProfile;
        private TablessControl profileEditorTablessControl;
        private TabPage pitchProfileTabPage;
        private TableLayoutPanel saveTableLayoutPanel;
        private Button btnSaveAs;
        private Button btnSaveProfile;
        private FlowLayoutPanel flowLayoutPanel2;
        private Button btnPitchProfile;
        private Button btnRollProfile;
        private TravelIndicator tiPitchPosition;
        private TravelIndicator tiPitchUserForce;
        private TravelIndicator tiPitchForce;
        private TravelIndicator tiRollUserTorque;
        private TravelIndicator tiRollTorque;
        private TravelIndicator tiRollPosition;
        private TableLayoutPanel tableLayoutPanel1;
        private Label lblStatus;
        private TableLayoutPanel pitchProfileTableLayoutPanel;
        private Label lblPitchRange;
        private NumericSlider numericSlider1;
        private SettingsTable pitchSettingsTable;
        private TabPage rollProfileTabPage;
        private SettingsTable rollSettingsTable;
    }
}

