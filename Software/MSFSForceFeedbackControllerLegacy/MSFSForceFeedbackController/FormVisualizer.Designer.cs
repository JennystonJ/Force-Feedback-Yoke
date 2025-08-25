namespace MSFSForceFeedbackController
{
    partial class FormVisualizer
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
            components = new System.ComponentModel.Container();
            lgForce = new LiveLineGraph(components);
            graphUpdateTimer = new System.Windows.Forms.Timer(components);
            SuspendLayout();
            // 
            // lgForce
            // 
            lgForce.Location = new Point(12, 12);
            lgForce.MaxXValue = new decimal(new int[] { 100, 0, 0, 0 });
            lgForce.MaxYValue = new decimal(new int[] { 1000, 0, 0, 0 });
            lgForce.MinXValue = new decimal(new int[] { 0, 0, 0, 0 });
            lgForce.MinYValue = new decimal(new int[] { 1000, 0, 0, int.MinValue });
            lgForce.Name = "lgForce";
            lgForce.Size = new Size(776, 426);
            lgForce.TabIndex = 0;
            lgForce.TickMarkInterval = new decimal(new int[] { 50, 0, 0, 0 });
            lgForce.Time = new decimal(new int[] { 0, 0, 0, 0 });
            // 
            // graphUpdateTimer
            // 
            graphUpdateTimer.Interval = 32;
            graphUpdateTimer.Tick += timerGraph_Tick;
            // 
            // FormVisualizer
            // 
            AutoScaleDimensions = new SizeF(13F, 32F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 450);
            Controls.Add(lgForce);
            Name = "FormVisualizer";
            Text = "Visualizer";
            Load += FormVisualizer_Load;
            ResumeLayout(false);
        }

        #endregion

        private LiveLineGraph lgForce;
        private System.Windows.Forms.Timer graphUpdateTimer;
    }
}