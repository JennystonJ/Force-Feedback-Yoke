namespace Force_Feedback_Yoke_Desktop_App
{
    partial class SaveAsDialog
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
            tableLayoutPanel2 = new TableLayoutPanel();
            btnCancel = new Button();
            btnSave = new Button();
            lblInput = new Label();
            txtName = new TextBox();
            lblPrompt = new Label();
            mainTableLayoutPanel.SuspendLayout();
            tableLayoutPanel2.SuspendLayout();
            SuspendLayout();
            // 
            // mainTableLayoutPanel
            // 
            mainTableLayoutPanel.AutoSize = true;
            mainTableLayoutPanel.ColumnCount = 2;
            mainTableLayoutPanel.ColumnStyles.Add(new ColumnStyle());
            mainTableLayoutPanel.ColumnStyles.Add(new ColumnStyle());
            mainTableLayoutPanel.Controls.Add(tableLayoutPanel2, 1, 2);
            mainTableLayoutPanel.Controls.Add(lblInput, 0, 1);
            mainTableLayoutPanel.Controls.Add(txtName, 1, 1);
            mainTableLayoutPanel.Controls.Add(lblPrompt, 0, 0);
            mainTableLayoutPanel.Dock = DockStyle.Fill;
            mainTableLayoutPanel.Location = new Point(0, 0);
            mainTableLayoutPanel.Margin = new Padding(11, 13, 11, 13);
            mainTableLayoutPanel.Name = "mainTableLayoutPanel";
            mainTableLayoutPanel.RowCount = 3;
            mainTableLayoutPanel.RowStyles.Add(new RowStyle(SizeType.Percent, 100F));
            mainTableLayoutPanel.RowStyles.Add(new RowStyle());
            mainTableLayoutPanel.RowStyles.Add(new RowStyle());
            mainTableLayoutPanel.Size = new Size(745, 275);
            mainTableLayoutPanel.TabIndex = 0;
            // 
            // tableLayoutPanel2
            // 
            tableLayoutPanel2.AutoSize = true;
            tableLayoutPanel2.ColumnCount = 2;
            tableLayoutPanel2.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 50F));
            tableLayoutPanel2.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 50F));
            tableLayoutPanel2.Controls.Add(btnCancel, 0, 0);
            tableLayoutPanel2.Controls.Add(btnSave, 1, 0);
            tableLayoutPanel2.Dock = DockStyle.Fill;
            tableLayoutPanel2.Location = new Point(95, 190);
            tableLayoutPanel2.Margin = new Padding(0);
            tableLayoutPanel2.Name = "tableLayoutPanel2";
            tableLayoutPanel2.RowCount = 1;
            tableLayoutPanel2.RowStyles.Add(new RowStyle(SizeType.Percent, 50F));
            tableLayoutPanel2.Size = new Size(654, 85);
            tableLayoutPanel2.TabIndex = 0;
            // 
            // btnCancel
            // 
            btnCancel.AutoSize = true;
            btnCancel.AutoSizeMode = AutoSizeMode.GrowAndShrink;
            btnCancel.BackColor = Color.DodgerBlue;
            btnCancel.Dock = DockStyle.Fill;
            btnCancel.FlatAppearance.BorderSize = 0;
            btnCancel.FlatAppearance.MouseDownBackColor = Color.DeepSkyBlue;
            btnCancel.FlatStyle = FlatStyle.Flat;
            btnCancel.Font = new Font("Microsoft Sans Serif", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            btnCancel.ForeColor = Color.WhiteSmoke;
            btnCancel.Location = new Point(17, 19);
            btnCancel.Margin = new Padding(17, 19, 17, 19);
            btnCancel.MaximumSize = new Size(0, 90);
            btnCancel.Name = "btnCancel";
            btnCancel.Size = new Size(293, 47);
            btnCancel.TabIndex = 7;
            btnCancel.Text = "Cancel";
            btnCancel.UseVisualStyleBackColor = false;
            btnCancel.Click += btnCancel_Click;
            // 
            // btnSave
            // 
            btnSave.AutoSize = true;
            btnSave.AutoSizeMode = AutoSizeMode.GrowAndShrink;
            btnSave.BackColor = Color.DodgerBlue;
            btnSave.Dock = DockStyle.Fill;
            btnSave.Enabled = false;
            btnSave.FlatAppearance.BorderSize = 0;
            btnSave.FlatAppearance.MouseDownBackColor = Color.DeepSkyBlue;
            btnSave.FlatStyle = FlatStyle.Flat;
            btnSave.Font = new Font("Microsoft Sans Serif", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            btnSave.ForeColor = Color.WhiteSmoke;
            btnSave.Location = new Point(344, 19);
            btnSave.Margin = new Padding(17, 19, 17, 19);
            btnSave.MaximumSize = new Size(0, 90);
            btnSave.Name = "btnSave";
            btnSave.Size = new Size(293, 47);
            btnSave.TabIndex = 6;
            btnSave.Text = "Save";
            btnSave.UseVisualStyleBackColor = false;
            btnSave.Click += btnSave_Click;
            // 
            // lblInput
            // 
            lblInput.AutoSize = true;
            lblInput.Dock = DockStyle.Fill;
            lblInput.ForeColor = Color.WhiteSmoke;
            lblInput.Location = new Point(6, 139);
            lblInput.Margin = new Padding(6, 0, 6, 0);
            lblInput.Name = "lblInput";
            lblInput.Size = new Size(83, 51);
            lblInput.TabIndex = 1;
            lblInput.Text = "Name:";
            lblInput.TextAlign = ContentAlignment.MiddleLeft;
            // 
            // txtName
            // 
            txtName.BorderStyle = BorderStyle.FixedSingle;
            txtName.Dock = DockStyle.Fill;
            txtName.Location = new Point(112, 145);
            txtName.Margin = new Padding(17, 6, 17, 6);
            txtName.Name = "txtName";
            txtName.Size = new Size(620, 39);
            txtName.TabIndex = 2;
            txtName.TextChanged += txtName_TextChanged;
            // 
            // lblPrompt
            // 
            lblPrompt.Anchor = AnchorStyles.Left;
            lblPrompt.AutoSize = true;
            mainTableLayoutPanel.SetColumnSpan(lblPrompt, 2);
            lblPrompt.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            lblPrompt.ForeColor = Color.WhiteSmoke;
            lblPrompt.Location = new Point(6, 53);
            lblPrompt.Margin = new Padding(6, 0, 6, 0);
            lblPrompt.Name = "lblPrompt";
            lblPrompt.Size = new Size(254, 32);
            lblPrompt.TabIndex = 3;
            lblPrompt.Text = "Enter a profile name:";
            lblPrompt.TextAlign = ContentAlignment.MiddleLeft;
            // 
            // SaveAsDialog
            // 
            AcceptButton = btnSave;
            AutoScaleDimensions = new SizeF(13F, 32F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = Color.Gray;
            CancelButton = btnCancel;
            ClientSize = new Size(745, 275);
            Controls.Add(mainTableLayoutPanel);
            Margin = new Padding(6, 6, 6, 6);
            MaximizeBox = false;
            MinimizeBox = false;
            Name = "SaveAsDialog";
            Text = "Save As...";
            mainTableLayoutPanel.ResumeLayout(false);
            mainTableLayoutPanel.PerformLayout();
            tableLayoutPanel2.ResumeLayout(false);
            tableLayoutPanel2.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private TableLayoutPanel mainTableLayoutPanel;
        private TableLayoutPanel tableLayoutPanel2;
        private Label lblInput;
        private TextBox txtName;
        private Label lblPrompt;
        private Button btnCancel;
        private Button btnSave;
    }
}