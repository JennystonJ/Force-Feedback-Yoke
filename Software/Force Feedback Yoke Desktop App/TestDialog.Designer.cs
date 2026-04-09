namespace Force_Feedback_Yoke_Desktop_App
{
    partial class TestDialog
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
            TablessButtonGroup tablessButtonGroup1 = new TablessButtonGroup();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(TestDialog));
            mainTableLayoutPanel = new TableLayoutPanel();
            mainTablessControl = new TablessControl();
            aircraftTabPage = new TabPage();
            aircraftSettingsTable = new SettingsTable();
            weatherTabPage = new TabPage();
            weatherSettingsTable = new SettingsTable();
            flowLayoutPanel1 = new FlowLayoutPanel();
            btnAircraft = new TablessButton();
            btnWeather = new TablessButton();
            mainTableLayoutPanel.SuspendLayout();
            mainTablessControl.SuspendLayout();
            aircraftTabPage.SuspendLayout();
            weatherTabPage.SuspendLayout();
            flowLayoutPanel1.SuspendLayout();
            SuspendLayout();
            // 
            // mainTableLayoutPanel
            // 
            mainTableLayoutPanel.ColumnCount = 1;
            mainTableLayoutPanel.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100F));
            mainTableLayoutPanel.Controls.Add(mainTablessControl, 0, 1);
            mainTableLayoutPanel.Controls.Add(flowLayoutPanel1, 0, 0);
            mainTableLayoutPanel.Dock = DockStyle.Fill;
            mainTableLayoutPanel.Location = new Point(0, 0);
            mainTableLayoutPanel.Name = "mainTableLayoutPanel";
            mainTableLayoutPanel.RowCount = 2;
            mainTableLayoutPanel.RowStyles.Add(new RowStyle());
            mainTableLayoutPanel.RowStyles.Add(new RowStyle());
            mainTableLayoutPanel.Size = new Size(1083, 672);
            mainTableLayoutPanel.TabIndex = 0;
            // 
            // mainTablessControl
            // 
            mainTablessControl.Controls.Add(aircraftTabPage);
            mainTablessControl.Controls.Add(weatherTabPage);
            mainTablessControl.Dock = DockStyle.Fill;
            mainTablessControl.Location = new Point(3, 114);
            mainTablessControl.Name = "mainTablessControl";
            mainTablessControl.SelectedIndex = 0;
            mainTablessControl.Size = new Size(1077, 555);
            mainTablessControl.TabIndex = 0;
            tablessButtonGroup1.SelectedIndex = -1;
            mainTablessControl.TablessButtonGroup = tablessButtonGroup1;
            mainTablessControl.Selected += mainTablessControl_Selected;
            // 
            // aircraftTabPage
            // 
            aircraftTabPage.BackColor = Color.Gray;
            aircraftTabPage.Controls.Add(aircraftSettingsTable);
            aircraftTabPage.Location = new Point(8, 46);
            aircraftTabPage.Name = "aircraftTabPage";
            aircraftTabPage.Padding = new Padding(3);
            aircraftTabPage.Size = new Size(1061, 501);
            aircraftTabPage.TabIndex = 0;
            aircraftTabPage.Text = "Aircraft";
            // 
            // aircraftSettingsTable
            // 
            aircraftSettingsTable.Dock = DockStyle.Fill;
            aircraftSettingsTable.ForeColor = Color.WhiteSmoke;
            aircraftSettingsTable.Location = new Point(3, 3);
            aircraftSettingsTable.Margin = new Padding(6);
            aircraftSettingsTable.Name = "aircraftSettingsTable";
            aircraftSettingsTable.Size = new Size(1055, 495);
            aircraftSettingsTable.TabIndex = 0;
            // 
            // weatherTabPage
            // 
            weatherTabPage.BackColor = Color.Gray;
            weatherTabPage.Controls.Add(weatherSettingsTable);
            weatherTabPage.Location = new Point(8, 46);
            weatherTabPage.Name = "weatherTabPage";
            weatherTabPage.Padding = new Padding(3);
            weatherTabPage.Size = new Size(1061, 501);
            weatherTabPage.TabIndex = 1;
            weatherTabPage.Text = "Weather";
            // 
            // weatherSettingsTable
            // 
            weatherSettingsTable.Dock = DockStyle.Fill;
            weatherSettingsTable.ForeColor = Color.WhiteSmoke;
            weatherSettingsTable.Location = new Point(3, 3);
            weatherSettingsTable.Margin = new Padding(6);
            weatherSettingsTable.Name = "weatherSettingsTable";
            weatherSettingsTable.Size = new Size(1055, 495);
            weatherSettingsTable.TabIndex = 0;
            // 
            // flowLayoutPanel1
            // 
            flowLayoutPanel1.AutoSize = true;
            flowLayoutPanel1.AutoSizeMode = AutoSizeMode.GrowAndShrink;
            flowLayoutPanel1.Controls.Add(btnAircraft);
            flowLayoutPanel1.Controls.Add(btnWeather);
            flowLayoutPanel1.Dock = DockStyle.Fill;
            flowLayoutPanel1.Location = new Point(0, 0);
            flowLayoutPanel1.Margin = new Padding(0);
            flowLayoutPanel1.Name = "flowLayoutPanel1";
            flowLayoutPanel1.Size = new Size(1083, 111);
            flowLayoutPanel1.TabIndex = 1;
            // 
            // btnAircraft
            // 
            btnAircraft.AutoSize = true;
            btnAircraft.AutoSizeMode = AutoSizeMode.GrowAndShrink;
            btnAircraft.BackColor = Color.DodgerBlue;
            btnAircraft.Dock = DockStyle.Fill;
            btnAircraft.FlatAppearance.BorderSize = 0;
            btnAircraft.FlatStyle = FlatStyle.Flat;
            btnAircraft.Font = new Font("Microsoft Sans Serif", 12F);
            btnAircraft.ForeColor = Color.WhiteSmoke;
            btnAircraft.Location = new Point(17, 19);
            btnAircraft.Margin = new Padding(17, 19, 17, 19);
            btnAircraft.Name = "btnAircraft";
            btnAircraft.Padding = new Padding(11, 13, 11, 13);
            btnAircraft.Selected = false;
            btnAircraft.SelectedBackColor = Color.DeepSkyBlue;
            btnAircraft.SelectedForeColor = Color.WhiteSmoke;
            btnAircraft.Size = new Size(152, 73);
            btnAircraft.TabIndex = 9;
            btnAircraft.Text = "Aircraft";
            btnAircraft.UseVisualStyleBackColor = false;
            // 
            // btnWeather
            // 
            btnWeather.AutoSize = true;
            btnWeather.AutoSizeMode = AutoSizeMode.GrowAndShrink;
            btnWeather.BackColor = Color.DodgerBlue;
            btnWeather.Dock = DockStyle.Fill;
            btnWeather.FlatAppearance.BorderSize = 0;
            btnWeather.FlatStyle = FlatStyle.Flat;
            btnWeather.Font = new Font("Microsoft Sans Serif", 12F);
            btnWeather.ForeColor = Color.WhiteSmoke;
            btnWeather.Location = new Point(203, 19);
            btnWeather.Margin = new Padding(17, 19, 17, 19);
            btnWeather.Name = "btnWeather";
            btnWeather.Padding = new Padding(11, 13, 11, 13);
            btnWeather.Selected = false;
            btnWeather.SelectedBackColor = Color.DeepSkyBlue;
            btnWeather.SelectedForeColor = Color.WhiteSmoke;
            btnWeather.Size = new Size(170, 73);
            btnWeather.TabIndex = 10;
            btnWeather.Text = "Weather";
            btnWeather.UseVisualStyleBackColor = false;
            // 
            // TestDialog
            // 
            AutoScaleDimensions = new SizeF(13F, 32F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = Color.Gray;
            ClientSize = new Size(1083, 672);
            Controls.Add(mainTableLayoutPanel);
            Name = "TestDialog";
            Text = "Test";
            Load += TestDialog_Load;
            mainTableLayoutPanel.ResumeLayout(false);
            mainTableLayoutPanel.PerformLayout();
            mainTablessControl.ResumeLayout(false);
            aircraftTabPage.ResumeLayout(false);
            weatherTabPage.ResumeLayout(false);
            flowLayoutPanel1.ResumeLayout(false);
            flowLayoutPanel1.PerformLayout();
            ResumeLayout(false);
        }

        #endregion

        private TableLayoutPanel mainTableLayoutPanel;
        private TablessControl mainTablessControl;
        private TabPage aircraftTabPage;
        private TabPage weatherTabPage;
        private FlowLayoutPanel flowLayoutPanel1;
        private SettingsTable aircraftSettingsTable;
        private SettingsTable weatherSettingsTable;
        private TablessButton btnAircraft;
        private TablessButton btnWeather;
    }
}