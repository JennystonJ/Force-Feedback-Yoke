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
            rangeFlowLayoutPanel.Name = "rangeFlowLayoutPanel";
            rangeFlowLayoutPanel.Size = new Size(283, 27);
            rangeFlowLayoutPanel.TabIndex = 11;
            // 
            // nudMinRange
            // 
            nudMinRange.BackColor = Color.DimGray;
            nudMinRange.Dock = DockStyle.Fill;
            nudMinRange.ForeColor = Color.WhiteSmoke;
            nudMinRange.Location = new Point(3, 3);
            nudMinRange.Minimum = new decimal(new int[] { 100, 0, 0, int.MinValue });
            nudMinRange.Name = "nudMinRange";
            nudMinRange.Size = new Size(86, 23);
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
            lblMinRangeUnit.Location = new Point(94, 0);
            lblMinRangeUnit.Margin = new Padding(2, 0, 2, 0);
            lblMinRangeUnit.Name = "lblMinRangeUnit";
            lblMinRangeUnit.Padding = new Padding(6);
            lblMinRangeUnit.Size = new Size(52, 27);
            lblMinRangeUnit.TabIndex = 10;
            lblMinRangeUnit.Text = "unit to";
            lblMinRangeUnit.TextAlign = ContentAlignment.MiddleRight;
            // 
            // nudMaxRange
            // 
            nudMaxRange.BackColor = Color.DimGray;
            nudMaxRange.Dock = DockStyle.Fill;
            nudMaxRange.ForeColor = Color.WhiteSmoke;
            nudMaxRange.Location = new Point(151, 3);
            nudMaxRange.Minimum = new decimal(new int[] { 100, 0, 0, int.MinValue });
            nudMaxRange.Name = "nudMaxRange";
            nudMaxRange.Size = new Size(86, 23);
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
            lblMaxRangeUnit.Location = new Point(242, 0);
            lblMaxRangeUnit.Margin = new Padding(2, 0, 2, 0);
            lblMaxRangeUnit.Name = "lblMaxRangeUnit";
            lblMaxRangeUnit.Padding = new Padding(6);
            lblMaxRangeUnit.Size = new Size(39, 27);
            lblMaxRangeUnit.TabIndex = 12;
            lblMaxRangeUnit.Text = "unit";
            lblMaxRangeUnit.TextAlign = ContentAlignment.MiddleRight;
            // 
            // RangeSelector
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            AutoSize = true;
            AutoSizeMode = AutoSizeMode.GrowAndShrink;
            Controls.Add(rangeFlowLayoutPanel);
            Name = "RangeSelector";
            Size = new Size(283, 27);
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
