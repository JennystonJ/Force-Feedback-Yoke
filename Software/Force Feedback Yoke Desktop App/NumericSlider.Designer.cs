namespace Force_Feedback_Yoke_Desktop_App
{
    partial class NumericSlider
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            mainTableLayoutPanel = new TableLayoutPanel();
            tbSlider = new TrackBar();
            nudFlowLayoutPanel = new FlowLayoutPanel();
            nudValue = new NumericUpDown();
            lblUnit = new Label();
            mainTableLayoutPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)tbSlider).BeginInit();
            nudFlowLayoutPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)nudValue).BeginInit();
            SuspendLayout();
            // 
            // mainTableLayoutPanel
            // 
            mainTableLayoutPanel.AutoSize = true;
            mainTableLayoutPanel.ColumnCount = 2;
            mainTableLayoutPanel.ColumnStyles.Add(new ColumnStyle());
            mainTableLayoutPanel.ColumnStyles.Add(new ColumnStyle(SizeType.Absolute, 131F));
            mainTableLayoutPanel.ColumnStyles.Add(new ColumnStyle(SizeType.Absolute, 20F));
            mainTableLayoutPanel.Controls.Add(tbSlider, 0, 0);
            mainTableLayoutPanel.Controls.Add(nudFlowLayoutPanel, 1, 0);
            mainTableLayoutPanel.Dock = DockStyle.Fill;
            mainTableLayoutPanel.Location = new Point(0, 0);
            mainTableLayoutPanel.Margin = new Padding(2, 1, 2, 1);
            mainTableLayoutPanel.Name = "mainTableLayoutPanel";
            mainTableLayoutPanel.RowCount = 1;
            mainTableLayoutPanel.RowStyles.Add(new RowStyle());
            mainTableLayoutPanel.Size = new Size(412, 47);
            mainTableLayoutPanel.TabIndex = 8;
            // 
            // tbSlider
            // 
            tbSlider.Dock = DockStyle.Fill;
            tbSlider.Location = new Point(2, 1);
            tbSlider.Margin = new Padding(2, 1, 2, 1);
            tbSlider.Maximum = 100;
            tbSlider.Name = "tbSlider";
            tbSlider.Size = new Size(277, 45);
            tbSlider.TabIndex = 8;
            tbSlider.Scroll += tbSlider_Scroll;
            // 
            // nudFlowLayoutPanel
            // 
            nudFlowLayoutPanel.AutoSize = true;
            nudFlowLayoutPanel.Controls.Add(nudValue);
            nudFlowLayoutPanel.Controls.Add(lblUnit);
            nudFlowLayoutPanel.Dock = DockStyle.Fill;
            nudFlowLayoutPanel.Location = new Point(283, 1);
            nudFlowLayoutPanel.Margin = new Padding(2, 1, 2, 1);
            nudFlowLayoutPanel.Name = "nudFlowLayoutPanel";
            nudFlowLayoutPanel.Size = new Size(127, 45);
            nudFlowLayoutPanel.TabIndex = 9;
            // 
            // nudValue
            // 
            nudValue.BackColor = Color.DimGray;
            nudValue.BorderStyle = BorderStyle.None;
            nudValue.DecimalPlaces = 2;
            nudValue.ForeColor = Color.WhiteSmoke;
            nudValue.Location = new Point(2, 1);
            nudValue.Margin = new Padding(2, 1, 2, 1);
            nudValue.Name = "nudValue";
            nudValue.Size = new Size(73, 19);
            nudValue.TabIndex = 0;
            nudValue.ValueChanged += nudValue_ValueChanged;
            // 
            // lblUnit
            // 
            lblUnit.AutoSize = true;
            lblUnit.ForeColor = Color.WhiteSmoke;
            lblUnit.Location = new Point(79, 0);
            lblUnit.Margin = new Padding(2, 0, 2, 0);
            lblUnit.Name = "lblUnit";
            lblUnit.Size = new Size(17, 15);
            lblUnit.TabIndex = 1;
            lblUnit.Text = "%";
            // 
            // NumericSlider
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            AutoSize = true;
            AutoSizeMode = AutoSizeMode.GrowAndShrink;
            BackColor = Color.Gray;
            Controls.Add(mainTableLayoutPanel);
            Margin = new Padding(2, 1, 2, 1);
            Name = "NumericSlider";
            Size = new Size(412, 47);
            mainTableLayoutPanel.ResumeLayout(false);
            mainTableLayoutPanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)tbSlider).EndInit();
            nudFlowLayoutPanel.ResumeLayout(false);
            nudFlowLayoutPanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)nudValue).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion
        private TableLayoutPanel mainTableLayoutPanel;
        private TrackBar tbSlider;
        private FlowLayoutPanel nudFlowLayoutPanel;
        private NumericUpDown nudValue;
        private Label lblUnit;
    }
}
