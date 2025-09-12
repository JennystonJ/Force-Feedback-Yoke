namespace Force_Feedback_Yoke_Desktop_App
{
    partial class RangeSelector
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
            rangeFlowLayoutPanel = new FlowLayoutPanel();
            nudMinRange = new NumericUpDown();
            lblMinRangeUnit = new Label();
            nudMaxRange = new NumericUpDown();
            lblMaxRangeUnit = new Label();
            rangeFlowLayoutPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)nudMinRange).BeginInit();
            ((System.ComponentModel.ISupportInitialize)nudMaxRange).BeginInit();
            SuspendLayout();
            // 
            // rangeFlowLayoutPanel
            // 
            rangeFlowLayoutPanel.AutoSize = true;
            rangeFlowLayoutPanel.BackColor = Color.Gray;
            rangeFlowLayoutPanel.Controls.Add(nudMinRange);
            rangeFlowLayoutPanel.Controls.Add(lblMinRangeUnit);
            rangeFlowLayoutPanel.Controls.Add(nudMaxRange);
            rangeFlowLayoutPanel.Controls.Add(lblMaxRangeUnit);
            rangeFlowLayoutPanel.Dock = DockStyle.Fill;
            rangeFlowLayoutPanel.Location = new Point(0, 0);
            rangeFlowLayoutPanel.Margin = new Padding(6);
            rangeFlowLayoutPanel.Name = "rangeFlowLayoutPanel";
            rangeFlowLayoutPanel.Size = new Size(532, 55);
            rangeFlowLayoutPanel.TabIndex = 11;
            // 
            // nudMinRange
            // 
            nudMinRange.BackColor = Color.DimGray;
            nudMinRange.Dock = DockStyle.Fill;
            nudMinRange.ForeColor = Color.WhiteSmoke;
            nudMinRange.Location = new Point(6, 6);
            nudMinRange.Margin = new Padding(6);
            nudMinRange.Minimum = new decimal(new int[] { 100, 0, 0, int.MinValue });
            nudMinRange.Name = "nudMinRange";
            nudMinRange.Size = new Size(160, 39);
            nudMinRange.TabIndex = 9;
            nudMinRange.ValueChanged += nudMinRange_ValueChanged;
            // 
            // lblMinRangeUnit
            // 
            lblMinRangeUnit.AutoSize = true;
            lblMinRangeUnit.BackColor = Color.Transparent;
            lblMinRangeUnit.Dock = DockStyle.Fill;
            lblMinRangeUnit.Font = new Font("Microsoft Sans Serif", 9F, FontStyle.Regular, GraphicsUnit.Point, 0);
            lblMinRangeUnit.ForeColor = Color.WhiteSmoke;
            lblMinRangeUnit.Location = new Point(176, 0);
            lblMinRangeUnit.Margin = new Padding(4, 0, 4, 0);
            lblMinRangeUnit.Name = "lblMinRangeUnit";
            lblMinRangeUnit.Padding = new Padding(11, 13, 11, 13);
            lblMinRangeUnit.Size = new Size(99, 55);
            lblMinRangeUnit.TabIndex = 10;
            lblMinRangeUnit.Text = "unit to";
            lblMinRangeUnit.TextAlign = ContentAlignment.MiddleRight;
            // 
            // nudMaxRange
            // 
            nudMaxRange.BackColor = Color.DimGray;
            nudMaxRange.Dock = DockStyle.Fill;
            nudMaxRange.ForeColor = Color.WhiteSmoke;
            nudMaxRange.Location = new Point(285, 6);
            nudMaxRange.Margin = new Padding(6);
            nudMaxRange.Minimum = new decimal(new int[] { 100, 0, 0, int.MinValue });
            nudMaxRange.Name = "nudMaxRange";
            nudMaxRange.Size = new Size(160, 39);
            nudMaxRange.TabIndex = 11;
            nudMaxRange.ValueChanged += nudMaxRange_ValueChanged;
            // 
            // lblMaxRangeUnit
            // 
            lblMaxRangeUnit.AutoSize = true;
            lblMaxRangeUnit.BackColor = Color.Transparent;
            lblMaxRangeUnit.Dock = DockStyle.Fill;
            lblMaxRangeUnit.Font = new Font("Microsoft Sans Serif", 9F, FontStyle.Regular, GraphicsUnit.Point, 0);
            lblMaxRangeUnit.ForeColor = Color.WhiteSmoke;
            lblMaxRangeUnit.Location = new Point(455, 0);
            lblMaxRangeUnit.Margin = new Padding(4, 0, 4, 0);
            lblMaxRangeUnit.Name = "lblMaxRangeUnit";
            lblMaxRangeUnit.Padding = new Padding(11, 13, 11, 13);
            lblMaxRangeUnit.Size = new Size(73, 55);
            lblMaxRangeUnit.TabIndex = 12;
            lblMaxRangeUnit.Text = "unit";
            lblMaxRangeUnit.TextAlign = ContentAlignment.MiddleRight;
            // 
            // RangeSelector
            // 
            AutoScaleDimensions = new SizeF(13F, 32F);
            AutoScaleMode = AutoScaleMode.Font;
            AutoSize = true;
            AutoSizeMode = AutoSizeMode.GrowAndShrink;
            Controls.Add(rangeFlowLayoutPanel);
            Margin = new Padding(6);
            Name = "RangeSelector";
            Size = new Size(532, 55);
            rangeFlowLayoutPanel.ResumeLayout(false);
            rangeFlowLayoutPanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)nudMinRange).EndInit();
            ((System.ComponentModel.ISupportInitialize)nudMaxRange).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private FlowLayoutPanel rangeFlowLayoutPanel;
        private NumericUpDown nudMinRange;
        private Label lblMinRangeUnit;
        private NumericUpDown nudMaxRange;
        private Label lblMaxRangeUnit;
    }
}
