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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(TestDialog));
            TablessButtonGroup tablessButtonGroup2 = new TablessButtonGroup();
            mainTableLayoutPanel = new TableLayoutPanel();
            flpTabs = new FlowLayoutPanel();
            btnAircraft = new TablessButton();
            btnWeather = new TablessButton();
            weatherTabPage = new TabPage();
            weatherSettingsTable = new SettingsTable();
            aircraftTabPage = new TabPage();
            aircraftSettingsTable = new SettingsTable();
            mainTablessControl = new TablessControl();
            flpTest = new FlowLayoutPanel();
            btnTest = new Button();
            mainTableLayoutPanel.SuspendLayout();
            flpTabs.SuspendLayout();
            weatherTabPage.SuspendLayout();
            aircraftTabPage.SuspendLayout();
            mainTablessControl.SuspendLayout();
            flpTest.SuspendLayout();
            SuspendLayout();
            // 
            // mainTableLayoutPanel
            // 
            mainTableLayoutPanel.ColumnCount = 1;
            mainTableLayoutPanel.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100F));
            mainTableLayoutPanel.Controls.Add(mainTablessControl, 0, 1);
            mainTableLayoutPanel.Controls.Add(flpTabs, 0, 0);
            mainTableLayoutPanel.Controls.Add(flpTest, 0, 2);
            mainTableLayoutPanel.Dock = DockStyle.Fill;
            mainTableLayoutPanel.Location = new Point(0, 0);
            mainTableLayoutPanel.Margin = new Padding(2, 1, 2, 1);
            mainTableLayoutPanel.Name = "mainTableLayoutPanel";
            mainTableLayoutPanel.RowCount = 3;
            mainTableLayoutPanel.RowStyles.Add(new RowStyle());
            mainTableLayoutPanel.RowStyles.Add(new RowStyle());
            mainTableLayoutPanel.RowStyles.Add(new RowStyle());
            mainTableLayoutPanel.Size = new Size(583, 391);
            mainTableLayoutPanel.TabIndex = 0;
            // 
            // flpTabs
            // 
            flpTabs.AutoSize = true;
            flpTabs.AutoSizeMode = AutoSizeMode.GrowAndShrink;
            flpTabs.Controls.Add(btnAircraft);
            flpTabs.Controls.Add(btnWeather);
            flpTabs.Dock = DockStyle.Fill;
            flpTabs.Location = new Point(0, 0);
            flpTabs.Margin = new Padding(0);
            flpTabs.Name = "flpTabs";
            flpTabs.Size = new Size(583, 60);
            flpTabs.TabIndex = 1;
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
            btnAircraft.Location = new Point(9, 9);
            btnAircraft.Margin = new Padding(9);
            btnAircraft.Name = "btnAircraft";
            btnAircraft.Padding = new Padding(6);
            btnAircraft.Selected = false;
            btnAircraft.SelectedBackColor = Color.DeepSkyBlue;
            btnAircraft.SelectedForeColor = Color.WhiteSmoke;
            btnAircraft.Size = new Size(82, 42);
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
            btnWeather.Location = new Point(109, 9);
            btnWeather.Margin = new Padding(9);
            btnWeather.Name = "btnWeather";
            btnWeather.Padding = new Padding(6);
            btnWeather.Selected = false;
            btnWeather.SelectedBackColor = Color.DeepSkyBlue;
            btnWeather.SelectedForeColor = Color.WhiteSmoke;
            btnWeather.Size = new Size(92, 42);
            btnWeather.TabIndex = 10;
            btnWeather.Text = "Weather";
            btnWeather.UseVisualStyleBackColor = false;
            // 
            // weatherTabPage
            // 
            weatherTabPage.BackColor = Color.Gray;
            weatherTabPage.Controls.Add(weatherSettingsTable);
            weatherTabPage.Location = new Point(4, 24);
            weatherTabPage.Margin = new Padding(2, 1, 2, 1);
            weatherTabPage.Name = "weatherTabPage";
            weatherTabPage.Padding = new Padding(2, 1, 2, 1);
            weatherTabPage.Size = new Size(571, 240);
            weatherTabPage.TabIndex = 1;
            weatherTabPage.Text = "Weather";
            // 
            // weatherSettingsTable
            // 
            weatherSettingsTable.Dock = DockStyle.Fill;
            weatherSettingsTable.ForeColor = Color.WhiteSmoke;
            weatherSettingsTable.Location = new Point(2, 1);
            weatherSettingsTable.Name = "weatherSettingsTable";
            weatherSettingsTable.Size = new Size(567, 238);
            weatherSettingsTable.TabIndex = 0;
            // 
            // aircraftTabPage
            // 
            aircraftTabPage.BackColor = Color.Gray;
            aircraftTabPage.Controls.Add(aircraftSettingsTable);
            aircraftTabPage.Location = new Point(4, 24);
            aircraftTabPage.Margin = new Padding(2, 1, 2, 1);
            aircraftTabPage.Name = "aircraftTabPage";
            aircraftTabPage.Padding = new Padding(2, 1, 2, 1);
            aircraftTabPage.Size = new Size(571, 240);
            aircraftTabPage.TabIndex = 0;
            aircraftTabPage.Text = "Aircraft";
            // 
            // aircraftSettingsTable
            // 
            aircraftSettingsTable.Dock = DockStyle.Fill;
            aircraftSettingsTable.ForeColor = Color.WhiteSmoke;
            aircraftSettingsTable.Location = new Point(2, 1);
            aircraftSettingsTable.Name = "aircraftSettingsTable";
            aircraftSettingsTable.Size = new Size(567, 238);
            aircraftSettingsTable.TabIndex = 0;
            // 
            // mainTablessControl
            // 
            mainTablessControl.Controls.Add(aircraftTabPage);
            mainTablessControl.Controls.Add(weatherTabPage);
            mainTablessControl.Dock = DockStyle.Fill;
            mainTablessControl.Location = new Point(2, 61);
            mainTablessControl.Margin = new Padding(2, 1, 2, 1);
            mainTablessControl.Name = "mainTablessControl";
            mainTablessControl.SelectedIndex = 0;
            mainTablessControl.Size = new Size(579, 268);
            mainTablessControl.TabIndex = 0;
            tablessButtonGroup2.SelectedIndex = 0;
            mainTablessControl.TablessButtonGroup = tablessButtonGroup2;
            mainTablessControl.Selected += mainTablessControl_Selected;
            // 
            // flpTest
            // 
            flpTest.AutoSize = true;
            flpTest.BackColor = Color.DimGray;
            flpTest.Controls.Add(btnTest);
            flpTest.Dock = DockStyle.Fill;
            flpTest.FlowDirection = FlowDirection.RightToLeft;
            flpTest.Location = new Point(0, 330);
            flpTest.Margin = new Padding(0);
            flpTest.Name = "flpTest";
            flpTest.Size = new Size(583, 61);
            flpTest.TabIndex = 2;
            // 
            // btnTest
            // 
            btnTest.AutoSize = true;
            btnTest.AutoSizeMode = AutoSizeMode.GrowAndShrink;
            btnTest.BackColor = Color.DodgerBlue;
            btnTest.FlatAppearance.BorderSize = 0;
            btnTest.FlatAppearance.MouseDownBackColor = Color.DeepSkyBlue;
            btnTest.FlatStyle = FlatStyle.Flat;
            btnTest.Font = new Font("Microsoft Sans Serif", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            btnTest.ForeColor = Color.WhiteSmoke;
            btnTest.Location = new Point(464, 9);
            btnTest.Margin = new Padding(9);
            btnTest.MinimumSize = new Size(110, 0);
            btnTest.Name = "btnTest";
            btnTest.Padding = new Padding(3, 6, 3, 6);
            btnTest.Size = new Size(110, 42);
            btnTest.TabIndex = 4;
            btnTest.Text = "Test";
            btnTest.UseVisualStyleBackColor = false;
            // 
            // TestDialog
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = Color.Gray;
            ClientSize = new Size(583, 391);
            Controls.Add(mainTableLayoutPanel);
            Margin = new Padding(2, 1, 2, 1);
            Name = "TestDialog";
            Text = "Test";
            Load += TestDialog_Load;
            mainTableLayoutPanel.ResumeLayout(false);
            mainTableLayoutPanel.PerformLayout();
            flpTabs.ResumeLayout(false);
            flpTabs.PerformLayout();
            weatherTabPage.ResumeLayout(false);
            aircraftTabPage.ResumeLayout(false);
            mainTablessControl.ResumeLayout(false);
            flpTest.ResumeLayout(false);
            flpTest.PerformLayout();
            ResumeLayout(false);
        }

        #endregion

        private TableLayoutPanel mainTableLayoutPanel;
        private FlowLayoutPanel flpTabs;
        private TablessButton btnAircraft;
        private TablessButton btnWeather;
        private TablessControl mainTablessControl;
        private TabPage aircraftTabPage;
        private SettingsTable aircraftSettingsTable;
        private TabPage weatherTabPage;
        private SettingsTable weatherSettingsTable;
        private FlowLayoutPanel flpTest;
        private Button btnTest;
    }
}