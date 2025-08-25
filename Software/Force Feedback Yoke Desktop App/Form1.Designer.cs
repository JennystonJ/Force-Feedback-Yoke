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
            tiPitchUserForce = new MSFSForceFeedbackController.TravelIndicator();
            lblPitchForceValue = new Label();
            tiPitchForce = new MSFSForceFeedbackController.TravelIndicator();
            lblPitchPosValue = new Label();
            tiPitchPosition = new MSFSForceFeedbackController.TravelIndicator();
            rollMonitorPanel = new TableLayoutPanel();
            lblRollUserTorque = new Label();
            lblRollTorque = new Label();
            lblRollPosition = new Label();
            lblRollMonitor = new Label();
            lblRollUserForceValue = new Label();
            tiRollUserTorque = new MSFSForceFeedbackController.TravelIndicator();
            lblRollTorqueValue = new Label();
            tiRollTorque = new MSFSForceFeedbackController.TravelIndicator();
            lblRollPosValue = new Label();
            tiRollPosition = new MSFSForceFeedbackController.TravelIndicator();
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
            profilesPage = new TabPage();
            yokeDataPage = new TabPage();
            mainTableLayoutPanel.SuspendLayout();
            menuTableLayoutPanel.SuspendLayout();
            pitchMonitorPanel.SuspendLayout();
            rollMonitorPanel.SuspendLayout();
            flowLayoutPanel1.SuspendLayout();
            tablessControlContent.SuspendLayout();
            SuspendLayout();
            // 
            // mainTableLayoutPanel
            // 
            mainTableLayoutPanel.BackColor = Color.Gray;
            mainTableLayoutPanel.ColumnCount = 2;
            mainTableLayoutPanel.ColumnStyles.Add(new ColumnStyle(SizeType.Absolute, 447F));
            mainTableLayoutPanel.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100F));
            mainTableLayoutPanel.Controls.Add(menuTableLayoutPanel, 0, 0);
            mainTableLayoutPanel.Controls.Add(tablessControlContent, 1, 0);
            mainTableLayoutPanel.Dock = DockStyle.Fill;
            mainTableLayoutPanel.Location = new Point(0, 0);
            mainTableLayoutPanel.Margin = new Padding(3, 4, 3, 4);
            mainTableLayoutPanel.Name = "mainTableLayoutPanel";
            mainTableLayoutPanel.RowCount = 1;
            mainTableLayoutPanel.RowStyles.Add(new RowStyle(SizeType.Percent, 100F));
            mainTableLayoutPanel.Size = new Size(1648, 1080);
            mainTableLayoutPanel.TabIndex = 0;
            // 
            // menuTableLayoutPanel
            // 
            menuTableLayoutPanel.AutoSize = true;
            menuTableLayoutPanel.AutoSizeMode = AutoSizeMode.GrowAndShrink;
            menuTableLayoutPanel.BackColor = Color.DimGray;
            menuTableLayoutPanel.ColumnCount = 1;
            menuTableLayoutPanel.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100F));
            menuTableLayoutPanel.Controls.Add(pitchMonitorPanel, 0, 6);
            menuTableLayoutPanel.Controls.Add(rollMonitorPanel, 0, 5);
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
            menuTableLayoutPanel.Size = new Size(447, 1080);
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
            pitchMonitorPanel.Controls.Add(tiPitchUserForce, 1, 3);
            pitchMonitorPanel.Controls.Add(lblPitchForceValue, 2, 2);
            pitchMonitorPanel.Controls.Add(tiPitchForce, 1, 2);
            pitchMonitorPanel.Controls.Add(lblPitchPosValue, 2, 1);
            pitchMonitorPanel.Controls.Add(tiPitchPosition, 1, 1);
            pitchMonitorPanel.Dock = DockStyle.Fill;
            pitchMonitorPanel.Location = new Point(0, 686);
            pitchMonitorPanel.Margin = new Padding(0);
            pitchMonitorPanel.Name = "pitchMonitorPanel";
            pitchMonitorPanel.Padding = new Padding(10, 0, 0, 0);
            pitchMonitorPanel.RowCount = 4;
            pitchMonitorPanel.RowStyles.Add(new RowStyle());
            pitchMonitorPanel.RowStyles.Add(new RowStyle(SizeType.Percent, 33.33333F));
            pitchMonitorPanel.RowStyles.Add(new RowStyle(SizeType.Percent, 33.3333359F));
            pitchMonitorPanel.RowStyles.Add(new RowStyle(SizeType.Percent, 33.3333359F));
            pitchMonitorPanel.RowStyles.Add(new RowStyle(SizeType.Absolute, 20F));
            pitchMonitorPanel.Size = new Size(447, 226);
            pitchMonitorPanel.TabIndex = 10;
            // 
            // lblPitchUserForce
            // 
            lblPitchUserForce.AutoSize = true;
            lblPitchUserForce.BackColor = Color.Transparent;
            lblPitchUserForce.Dock = DockStyle.Bottom;
            lblPitchUserForce.Font = new Font("Microsoft Sans Serif", 9F, FontStyle.Regular, GraphicsUnit.Point, 0);
            lblPitchUserForce.ForeColor = Color.WhiteSmoke;
            lblPitchUserForce.Location = new Point(13, 171);
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
            lblPitchForce.Location = new Point(13, 113);
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
            lblPitchPosition.Location = new Point(13, 56);
            lblPitchPosition.Name = "lblPitchPosition";
            lblPitchPosition.Padding = new Padding(11, 13, 11, 13);
            lblPitchPosition.Size = new Size(58, 55);
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
            lblPitchUserForceValue.Location = new Point(321, 168);
            lblPitchUserForceValue.MinimumSize = new Size(123, 0);
            lblPitchUserForceValue.Name = "lblPitchUserForceValue";
            lblPitchUserForceValue.Padding = new Padding(11, 13, 11, 13);
            lblPitchUserForceValue.Size = new Size(123, 58);
            lblPitchUserForceValue.TabIndex = 11;
            lblPitchUserForceValue.Text = "--.-- N";
            lblPitchUserForceValue.TextAlign = ContentAlignment.MiddleRight;
            // 
            // tiPitchUserForce
            // 
            tiPitchUserForce.BackColor = Color.Gray;
            tiPitchUserForce.CenterLineColor = Color.FromArgb(203, 0, 215);
            tiPitchUserForce.Dock = DockStyle.Fill;
            tiPitchUserForce.ForeColor = Color.FromArgb(203, 0, 215);
            tiPitchUserForce.Location = new Point(84, 188);
            tiPitchUserForce.Margin = new Padding(10, 20, 10, 20);
            tiPitchUserForce.Maximum = 100;
            tiPitchUserForce.MaximumSize = new Size(0, 17);
            tiPitchUserForce.Minimum = -100;
            tiPitchUserForce.Name = "tiPitchUserForce";
            tiPitchUserForce.Size = new Size(224, 17);
            tiPitchUserForce.TabIndex = 10;
            tiPitchUserForce.Type = MSFSForceFeedbackController.TravelIndicator.TravelIndicatorType.Centered;
            tiPitchUserForce.Value = 0;
            // 
            // lblPitchForceValue
            // 
            lblPitchForceValue.AutoSize = true;
            lblPitchForceValue.BackColor = Color.Transparent;
            lblPitchForceValue.Dock = DockStyle.Fill;
            lblPitchForceValue.Font = new Font("Microsoft Sans Serif", 9F, FontStyle.Regular, GraphicsUnit.Point, 0);
            lblPitchForceValue.ForeColor = Color.WhiteSmoke;
            lblPitchForceValue.Location = new Point(321, 111);
            lblPitchForceValue.MinimumSize = new Size(123, 0);
            lblPitchForceValue.Name = "lblPitchForceValue";
            lblPitchForceValue.Padding = new Padding(11, 13, 11, 13);
            lblPitchForceValue.Size = new Size(123, 57);
            lblPitchForceValue.TabIndex = 9;
            lblPitchForceValue.Text = "--.-- N";
            lblPitchForceValue.TextAlign = ContentAlignment.MiddleRight;
            // 
            // tiPitchForce
            // 
            tiPitchForce.BackColor = Color.Gray;
            tiPitchForce.CenterLineColor = Color.FromArgb(215, 95, 0);
            tiPitchForce.Dock = DockStyle.Fill;
            tiPitchForce.ForeColor = Color.FromArgb(215, 95, 0);
            tiPitchForce.Location = new Point(84, 131);
            tiPitchForce.Margin = new Padding(10, 20, 10, 20);
            tiPitchForce.Maximum = 100;
            tiPitchForce.MaximumSize = new Size(0, 17);
            tiPitchForce.Minimum = -100;
            tiPitchForce.Name = "tiPitchForce";
            tiPitchForce.Size = new Size(224, 17);
            tiPitchForce.TabIndex = 8;
            tiPitchForce.Type = MSFSForceFeedbackController.TravelIndicator.TravelIndicatorType.Centered;
            tiPitchForce.Value = 0;
            // 
            // lblPitchPosValue
            // 
            lblPitchPosValue.AutoSize = true;
            lblPitchPosValue.BackColor = Color.Transparent;
            lblPitchPosValue.Dock = DockStyle.Fill;
            lblPitchPosValue.Font = new Font("Microsoft Sans Serif", 9F, FontStyle.Regular, GraphicsUnit.Point, 0);
            lblPitchPosValue.ForeColor = Color.WhiteSmoke;
            lblPitchPosValue.Location = new Point(321, 55);
            lblPitchPosValue.MinimumSize = new Size(123, 0);
            lblPitchPosValue.Name = "lblPitchPosValue";
            lblPitchPosValue.Padding = new Padding(11, 13, 11, 13);
            lblPitchPosValue.Size = new Size(123, 56);
            lblPitchPosValue.TabIndex = 7;
            lblPitchPosValue.Text = "---.- mm";
            lblPitchPosValue.TextAlign = ContentAlignment.MiddleRight;
            // 
            // tiPitchPosition
            // 
            tiPitchPosition.BackColor = Color.Gray;
            tiPitchPosition.CenterLineColor = Color.FromArgb(12, 215, 0);
            tiPitchPosition.Dock = DockStyle.Fill;
            tiPitchPosition.ForeColor = Color.FromArgb(12, 215, 0);
            tiPitchPosition.Location = new Point(84, 75);
            tiPitchPosition.Margin = new Padding(10, 20, 10, 20);
            tiPitchPosition.Maximum = 100;
            tiPitchPosition.MaximumSize = new Size(0, 17);
            tiPitchPosition.Minimum = -100;
            tiPitchPosition.Name = "tiPitchPosition";
            tiPitchPosition.Size = new Size(224, 16);
            tiPitchPosition.TabIndex = 0;
            tiPitchPosition.Type = MSFSForceFeedbackController.TravelIndicator.TravelIndicatorType.Centered;
            tiPitchPosition.Value = 0;
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
            rollMonitorPanel.Controls.Add(lblRollUserForceValue, 2, 3);
            rollMonitorPanel.Controls.Add(tiRollUserTorque, 1, 3);
            rollMonitorPanel.Controls.Add(lblRollTorqueValue, 2, 2);
            rollMonitorPanel.Controls.Add(tiRollTorque, 1, 2);
            rollMonitorPanel.Controls.Add(lblRollPosValue, 2, 1);
            rollMonitorPanel.Controls.Add(tiRollPosition, 1, 1);
            rollMonitorPanel.Dock = DockStyle.Fill;
            rollMonitorPanel.Location = new Point(0, 462);
            rollMonitorPanel.Margin = new Padding(0);
            rollMonitorPanel.Name = "rollMonitorPanel";
            rollMonitorPanel.Padding = new Padding(10, 0, 0, 0);
            rollMonitorPanel.RowCount = 4;
            rollMonitorPanel.RowStyles.Add(new RowStyle());
            rollMonitorPanel.RowStyles.Add(new RowStyle(SizeType.Percent, 33.33333F));
            rollMonitorPanel.RowStyles.Add(new RowStyle(SizeType.Percent, 33.3333359F));
            rollMonitorPanel.RowStyles.Add(new RowStyle(SizeType.Percent, 33.3333359F));
            rollMonitorPanel.Size = new Size(447, 224);
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
            lblRollMonitor.Name = "lblRollMonitor";
            lblRollMonitor.Padding = new Padding(11, 13, 11, 13);
            lblRollMonitor.Size = new Size(431, 55);
            lblRollMonitor.TabIndex = 12;
            lblRollMonitor.Text = "Roll:";
            lblRollMonitor.TextAlign = ContentAlignment.MiddleLeft;
            // 
            // lblRollUserForceValue
            // 
            lblRollUserForceValue.AutoSize = true;
            lblRollUserForceValue.BackColor = Color.Transparent;
            lblRollUserForceValue.Dock = DockStyle.Fill;
            lblRollUserForceValue.Font = new Font("Microsoft Sans Serif", 9F, FontStyle.Regular, GraphicsUnit.Point, 0);
            lblRollUserForceValue.ForeColor = Color.WhiteSmoke;
            lblRollUserForceValue.Location = new Point(321, 167);
            lblRollUserForceValue.MinimumSize = new Size(123, 0);
            lblRollUserForceValue.Name = "lblRollUserForceValue";
            lblRollUserForceValue.Padding = new Padding(11, 13, 11, 13);
            lblRollUserForceValue.Size = new Size(123, 57);
            lblRollUserForceValue.TabIndex = 11;
            lblRollUserForceValue.Text = "--.-- Nm";
            lblRollUserForceValue.TextAlign = ContentAlignment.MiddleRight;
            // 
            // tiRollUserTorque
            // 
            tiRollUserTorque.BackColor = Color.Gray;
            tiRollUserTorque.CenterLineColor = Color.FromArgb(203, 0, 215);
            tiRollUserTorque.Dock = DockStyle.Fill;
            tiRollUserTorque.ForeColor = Color.FromArgb(203, 0, 215);
            tiRollUserTorque.Location = new Point(84, 187);
            tiRollUserTorque.Margin = new Padding(10, 20, 10, 20);
            tiRollUserTorque.Maximum = 100;
            tiRollUserTorque.MaximumSize = new Size(0, 17);
            tiRollUserTorque.Minimum = -100;
            tiRollUserTorque.Name = "tiRollUserTorque";
            tiRollUserTorque.Size = new Size(224, 17);
            tiRollUserTorque.TabIndex = 50;
            tiRollUserTorque.Type = MSFSForceFeedbackController.TravelIndicator.TravelIndicatorType.Centered;
            tiRollUserTorque.Value = 0;
            // 
            // lblRollTorqueValue
            // 
            lblRollTorqueValue.AutoSize = true;
            lblRollTorqueValue.BackColor = Color.Transparent;
            lblRollTorqueValue.Dock = DockStyle.Fill;
            lblRollTorqueValue.Font = new Font("Microsoft Sans Serif", 9F, FontStyle.Regular, GraphicsUnit.Point, 0);
            lblRollTorqueValue.ForeColor = Color.WhiteSmoke;
            lblRollTorqueValue.Location = new Point(321, 111);
            lblRollTorqueValue.MinimumSize = new Size(123, 0);
            lblRollTorqueValue.Name = "lblRollTorqueValue";
            lblRollTorqueValue.Padding = new Padding(11, 13, 11, 13);
            lblRollTorqueValue.Size = new Size(123, 56);
            lblRollTorqueValue.TabIndex = 9;
            lblRollTorqueValue.Text = "--.-- Nm";
            lblRollTorqueValue.TextAlign = ContentAlignment.MiddleRight;
            // 
            // tiRollTorque
            // 
            tiRollTorque.BackColor = Color.Gray;
            tiRollTorque.CenterLineColor = Color.FromArgb(215, 95, 0);
            tiRollTorque.Dock = DockStyle.Fill;
            tiRollTorque.ForeColor = Color.FromArgb(215, 95, 0);
            tiRollTorque.Location = new Point(84, 131);
            tiRollTorque.Margin = new Padding(10, 20, 10, 20);
            tiRollTorque.Maximum = 100;
            tiRollTorque.MaximumSize = new Size(0, 17);
            tiRollTorque.Minimum = -100;
            tiRollTorque.Name = "tiRollTorque";
            tiRollTorque.Size = new Size(224, 16);
            tiRollTorque.TabIndex = 8;
            tiRollTorque.Type = MSFSForceFeedbackController.TravelIndicator.TravelIndicatorType.Centered;
            tiRollTorque.Value = 0;
            // 
            // lblRollPosValue
            // 
            lblRollPosValue.AutoSize = true;
            lblRollPosValue.BackColor = Color.Transparent;
            lblRollPosValue.Dock = DockStyle.Fill;
            lblRollPosValue.Font = new Font("Microsoft Sans Serif", 9F, FontStyle.Regular, GraphicsUnit.Point, 0);
            lblRollPosValue.ForeColor = Color.WhiteSmoke;
            lblRollPosValue.Location = new Point(321, 55);
            lblRollPosValue.MinimumSize = new Size(123, 0);
            lblRollPosValue.Name = "lblRollPosValue";
            lblRollPosValue.Padding = new Padding(11, 13, 11, 13);
            lblRollPosValue.Size = new Size(123, 56);
            lblRollPosValue.TabIndex = 7;
            lblRollPosValue.Text = "---.- deg";
            lblRollPosValue.TextAlign = ContentAlignment.MiddleRight;
            // 
            // tiRollPosition
            // 
            tiRollPosition.BackColor = Color.Gray;
            tiRollPosition.CenterLineColor = Color.FromArgb(12, 215, 0);
            tiRollPosition.Dock = DockStyle.Fill;
            tiRollPosition.ForeColor = Color.FromArgb(12, 215, 0);
            tiRollPosition.Location = new Point(84, 75);
            tiRollPosition.Margin = new Padding(10, 20, 10, 20);
            tiRollPosition.Maximum = 100;
            tiRollPosition.MaximumSize = new Size(0, 17);
            tiRollPosition.Minimum = -100;
            tiRollPosition.Name = "tiRollPosition";
            tiRollPosition.Size = new Size(224, 16);
            tiRollPosition.TabIndex = 0;
            tiRollPosition.Type = MSFSForceFeedbackController.TravelIndicator.TravelIndicatorType.Centered;
            tiRollPosition.Value = 0;
            // 
            // lblStatus
            // 
            lblStatus.AutoSize = true;
            lblStatus.BackColor = Color.Transparent;
            lblStatus.Dock = DockStyle.Bottom;
            lblStatus.Font = new Font("Microsoft Sans Serif", 12F, FontStyle.Bold, GraphicsUnit.Point, 0);
            lblStatus.ForeColor = Color.WhiteSmoke;
            lblStatus.Location = new Point(3, 912);
            lblStatus.Name = "lblStatus";
            lblStatus.Padding = new Padding(11, 13, 11, 13);
            lblStatus.Size = new Size(441, 63);
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
            lblMonitor.Location = new Point(3, 399);
            lblMonitor.Name = "lblMonitor";
            lblMonitor.Padding = new Padding(11, 13, 11, 13);
            lblMonitor.Size = new Size(441, 63);
            lblMonitor.TabIndex = 5;
            lblMonitor.Text = "Monitor";
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
            btnHome.Location = new Point(16, 76);
            btnHome.Margin = new Padding(16, 13, 16, 13);
            btnHome.Name = "btnHome";
            btnHome.Padding = new Padding(11, 13, 11, 13);
            btnHome.Size = new Size(415, 86);
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
            btnYokeData.Location = new Point(16, 300);
            btnYokeData.Margin = new Padding(16, 13, 16, 13);
            btnYokeData.Name = "btnYokeData";
            btnYokeData.Padding = new Padding(11, 13, 11, 13);
            btnYokeData.Size = new Size(415, 86);
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
            lblMenu.Location = new Point(3, 0);
            lblMenu.Name = "lblMenu";
            lblMenu.Padding = new Padding(11, 13, 11, 13);
            lblMenu.Size = new Size(441, 63);
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
            btnProfiles.Location = new Point(16, 188);
            btnProfiles.Margin = new Padding(16, 13, 16, 13);
            btnProfiles.Name = "btnProfiles";
            btnProfiles.Padding = new Padding(11, 13, 11, 13);
            btnProfiles.Size = new Size(415, 86);
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
            flowLayoutPanel1.Location = new Point(0, 975);
            flowLayoutPanel1.Margin = new Padding(0);
            flowLayoutPanel1.Name = "flowLayoutPanel1";
            flowLayoutPanel1.Size = new Size(447, 111);
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
            btnConnect.Location = new Point(16, 19);
            btnConnect.Margin = new Padding(16, 19, 16, 19);
            btnConnect.MinimumSize = new Size(207, 0);
            btnConnect.Name = "btnConnect";
            btnConnect.Padding = new Padding(11, 13, 11, 13);
            btnConnect.Size = new Size(207, 73);
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
            btnFfbOn.Margin = new Padding(16, 19, 16, 19);
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
            tablessControlContent.Location = new Point(447, 0);
            tablessControlContent.Margin = new Padding(0);
            tablessControlContent.Name = "tablessControlContent";
            tablessControlContent.SelectedIndex = 0;
            tablessControlContent.Size = new Size(1201, 1080);
            tablessControlContent.TabIndex = 1;
            // 
            // homePage
            // 
            homePage.BackColor = Color.Gray;
            homePage.Location = new Point(8, 46);
            homePage.Margin = new Padding(3, 4, 3, 4);
            homePage.Name = "homePage";
            homePage.Padding = new Padding(3, 4, 3, 4);
            homePage.Size = new Size(1185, 1026);
            homePage.TabIndex = 0;
            homePage.Text = "Home";
            // 
            // profilesPage
            // 
            profilesPage.BackColor = Color.Gray;
            profilesPage.Location = new Point(8, 46);
            profilesPage.Margin = new Padding(3, 4, 3, 4);
            profilesPage.Name = "profilesPage";
            profilesPage.Padding = new Padding(3, 4, 3, 4);
            profilesPage.Size = new Size(1185, 1026);
            profilesPage.TabIndex = 1;
            profilesPage.Text = "Profiles";
            // 
            // yokeDataPage
            // 
            yokeDataPage.BackColor = Color.Gray;
            yokeDataPage.Location = new Point(8, 46);
            yokeDataPage.Margin = new Padding(3, 4, 3, 4);
            yokeDataPage.Name = "yokeDataPage";
            yokeDataPage.Padding = new Padding(3, 4, 3, 4);
            yokeDataPage.Size = new Size(1185, 1026);
            yokeDataPage.TabIndex = 2;
            yokeDataPage.Text = "Yoke Data";
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(13F, 32F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1648, 1080);
            Controls.Add(mainTableLayoutPanel);
            Margin = new Padding(3, 4, 3, 4);
            Name = "Form1";
            Text = "Force Feedback Yoke Desktop App";
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
        private System.Windows.Forms.TabPage profilesPage;
        private System.Windows.Forms.TabPage yokeDataPage;
        private System.Windows.Forms.Label lblMonitor;
        private Label lblStatus;
        private TableLayoutPanel rollMonitorPanel;
        private Label lblRollUserForceValue;
        private MSFSForceFeedbackController.TravelIndicator tiRollUserTorque;
        private Label lblRollTorqueValue;
        private MSFSForceFeedbackController.TravelIndicator tiRollTorque;
        private Label lblRollPosValue;
        private MSFSForceFeedbackController.TravelIndicator tiRollPosition;
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
        private MSFSForceFeedbackController.TravelIndicator tiPitchUserForce;
        private Label lblPitchForceValue;
        private MSFSForceFeedbackController.TravelIndicator tiPitchForce;
        private Label lblPitchPosValue;
        private MSFSForceFeedbackController.TravelIndicator tiPitchPosition;
        private FlowLayoutPanel flowLayoutPanel1;
        private Button btnConnect;
        private Button btnFfbOn;
    }
}

