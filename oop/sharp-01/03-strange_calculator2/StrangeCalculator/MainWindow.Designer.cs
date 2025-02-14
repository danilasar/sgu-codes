namespace StrangeCalculator
{
    partial class MainWindow
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.groupF = new System.Windows.Forms.GroupBox();
            this.flowLayoutPanel1 = new System.Windows.Forms.FlowLayoutPanel();
            this.radioSh = new System.Windows.Forms.RadioButton();
            this.radioSq = new System.Windows.Forms.RadioButton();
            this.radioE = new System.Windows.Forms.RadioButton();
            this.labelX = new System.Windows.Forms.Label();
            this.textBoxX = new System.Windows.Forms.TextBox();
            this.textBoxG = new System.Windows.Forms.TextBox();
            this.labelG = new System.Windows.Forms.Label();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.authorLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.statusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.textBoxB = new System.Windows.Forms.TextBox();
            this.labelB = new System.Windows.Forms.Label();
            this.tableLayoutPanel1.SuspendLayout();
            this.groupF.SuspendLayout();
            this.flowLayoutPanel1.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.tableLayoutPanel1.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 36F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Controls.Add(this.labelB, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.textBoxB, 1, 1);
            this.tableLayoutPanel1.Controls.Add(this.groupF, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.labelX, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.textBoxX, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.textBoxG, 1, 3);
            this.tableLayoutPanel1.Controls.Add(this.labelG, 0, 3);
            this.tableLayoutPanel1.Location = new System.Drawing.Point(12, 9);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 4;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 100F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(256, 256);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // groupF
            // 
            this.tableLayoutPanel1.SetColumnSpan(this.groupF, 2);
            this.groupF.Controls.Add(this.flowLayoutPanel1);
            this.groupF.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupF.Location = new System.Drawing.Point(3, 107);
            this.groupF.Name = "groupF";
            this.groupF.Size = new System.Drawing.Size(250, 94);
            this.groupF.TabIndex = 8;
            this.groupF.TabStop = false;
            this.groupF.Text = "f(x)";
            // 
            // flowLayoutPanel1
            // 
            this.flowLayoutPanel1.Controls.Add(this.radioSh);
            this.flowLayoutPanel1.Controls.Add(this.radioSq);
            this.flowLayoutPanel1.Controls.Add(this.radioE);
            this.flowLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.flowLayoutPanel1.FlowDirection = System.Windows.Forms.FlowDirection.TopDown;
            this.flowLayoutPanel1.Location = new System.Drawing.Point(3, 16);
            this.flowLayoutPanel1.Name = "flowLayoutPanel1";
            this.flowLayoutPanel1.Size = new System.Drawing.Size(244, 75);
            this.flowLayoutPanel1.TabIndex = 0;
            // 
            // radioSh
            // 
            this.radioSh.AutoSize = true;
            this.radioSh.Location = new System.Drawing.Point(3, 3);
            this.radioSh.Name = "radioSh";
            this.radioSh.Size = new System.Drawing.Size(47, 17);
            this.radioSh.TabIndex = 0;
            this.radioSh.TabStop = true;
            this.radioSh.Text = "sh(x)";
            this.radioSh.UseVisualStyleBackColor = true;
            // 
            // radioSq
            // 
            this.radioSq.AutoSize = true;
            this.radioSq.Location = new System.Drawing.Point(3, 26);
            this.radioSq.Name = "radioSq";
            this.radioSq.Size = new System.Drawing.Size(42, 17);
            this.radioSq.TabIndex = 1;
            this.radioSq.TabStop = true;
            this.radioSq.Text = "x^2";
            this.radioSq.UseVisualStyleBackColor = true;
            // 
            // radioE
            // 
            this.radioE.AutoSize = true;
            this.radioE.Location = new System.Drawing.Point(3, 49);
            this.radioE.Name = "radioE";
            this.radioE.Size = new System.Drawing.Size(42, 17);
            this.radioE.TabIndex = 2;
            this.radioE.TabStop = true;
            this.radioE.Text = "e^x";
            this.radioE.UseVisualStyleBackColor = true;
            // 
            // labelX
            // 
            this.labelX.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.labelX.AutoSize = true;
            this.labelX.Location = new System.Drawing.Point(3, 19);
            this.labelX.Name = "labelX";
            this.labelX.Size = new System.Drawing.Size(30, 13);
            this.labelX.TabIndex = 3;
            this.labelX.Text = "x =";
            this.labelX.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // textBoxX
            // 
            this.textBoxX.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxX.Location = new System.Drawing.Point(39, 16);
            this.textBoxX.Name = "textBoxX";
            this.textBoxX.Size = new System.Drawing.Size(214, 20);
            this.textBoxX.TabIndex = 0;
            // 
            // textBoxG
            // 
            this.textBoxG.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxG.Enabled = false;
            this.textBoxG.Location = new System.Drawing.Point(39, 220);
            this.textBoxG.Name = "textBoxG";
            this.textBoxG.Size = new System.Drawing.Size(214, 20);
            this.textBoxG.TabIndex = 7;
            // 
            // labelG
            // 
            this.labelG.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.labelG.AutoSize = true;
            this.labelG.Location = new System.Drawing.Point(3, 223);
            this.labelG.Name = "labelG";
            this.labelG.Size = new System.Drawing.Size(30, 13);
            this.labelG.TabIndex = 6;
            this.labelG.Text = "g =";
            this.labelG.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.authorLabel,
            this.statusLabel});
            this.statusStrip1.Location = new System.Drawing.Point(0, 264);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(278, 22);
            this.statusStrip1.TabIndex = 1;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // authorLabel
            // 
            this.authorLabel.Name = "authorLabel";
            this.authorLabel.Size = new System.Drawing.Size(90, 17);
            this.authorLabel.Text = "Григорьев Д. Е.";
            // 
            // statusLabel
            // 
            this.statusLabel.Name = "statusLabel";
            this.statusLabel.Size = new System.Drawing.Size(0, 17);
            // 
            // textBoxB
            // 
            this.textBoxB.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxB.Location = new System.Drawing.Point(39, 68);
            this.textBoxB.Name = "textBoxB";
            this.textBoxB.Size = new System.Drawing.Size(214, 20);
            this.textBoxB.TabIndex = 9;
            // 
            // labelB
            // 
            this.labelB.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.labelB.AutoSize = true;
            this.labelB.Location = new System.Drawing.Point(3, 71);
            this.labelB.Name = "labelB";
            this.labelB.Size = new System.Drawing.Size(30, 13);
            this.labelB.TabIndex = 10;
            this.labelB.Text = "b =";
            this.labelB.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(278, 286);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.tableLayoutPanel1);
            this.MinimumSize = new System.Drawing.Size(294, 325);
            this.Name = "MainWindow";
            this.Text = "Странный калькулятор";
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.groupF.ResumeLayout(false);
            this.flowLayoutPanel1.ResumeLayout(false);
            this.flowLayoutPanel1.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.TextBox textBoxG;
        private System.Windows.Forms.Label labelG;
        private System.Windows.Forms.TextBox textBoxX;
        private System.Windows.Forms.Label labelX;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel authorLabel;
        private System.Windows.Forms.ToolStripStatusLabel statusLabel;
        private System.Windows.Forms.GroupBox groupF;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1;
        private System.Windows.Forms.RadioButton radioSh;
        private System.Windows.Forms.RadioButton radioSq;
        private System.Windows.Forms.RadioButton radioE;
        private System.Windows.Forms.Label labelB;
        private System.Windows.Forms.TextBox textBoxB;
    }
}

