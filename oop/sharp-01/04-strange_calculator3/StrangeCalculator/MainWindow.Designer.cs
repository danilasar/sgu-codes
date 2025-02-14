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
            this.labelXk = new System.Windows.Forms.Label();
            this.textBoxXk = new System.Windows.Forms.TextBox();
            this.labelX0 = new System.Windows.Forms.Label();
            this.textBoxX0 = new System.Windows.Forms.TextBox();
            this.textBoxA = new System.Windows.Forms.TextBox();
            this.labelA = new System.Windows.Forms.Label();
            this.labelDx = new System.Windows.Forms.Label();
            this.textBoxDx = new System.Windows.Forms.TextBox();
            this.tabulationsView = new System.Windows.Forms.DataGridView();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.authorLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.statusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.tableLayoutPanel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.tabulationsView)).BeginInit();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tableLayoutPanel1.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.tableLayoutPanel1.ColumnCount = 3;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 36F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 200F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Controls.Add(this.labelXk, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.textBoxXk, 1, 1);
            this.tableLayoutPanel1.Controls.Add(this.labelX0, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.textBoxX0, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.textBoxA, 1, 3);
            this.tableLayoutPanel1.Controls.Add(this.labelA, 0, 3);
            this.tableLayoutPanel1.Controls.Add(this.labelDx, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.textBoxDx, 1, 2);
            this.tableLayoutPanel1.Controls.Add(this.tabulationsView, 2, 0);
            this.tableLayoutPanel1.Location = new System.Drawing.Point(12, 12);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 4;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(562, 249);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // labelXk
            // 
            this.labelXk.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.labelXk.AutoSize = true;
            this.labelXk.Location = new System.Drawing.Point(3, 86);
            this.labelXk.Name = "labelXk";
            this.labelXk.Size = new System.Drawing.Size(30, 13);
            this.labelXk.TabIndex = 10;
            this.labelXk.Text = "xk =";
            this.labelXk.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // textBoxXk
            // 
            this.textBoxXk.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxXk.Location = new System.Drawing.Point(39, 83);
            this.textBoxXk.Name = "textBoxXk";
            this.textBoxXk.Size = new System.Drawing.Size(194, 20);
            this.textBoxXk.TabIndex = 1;
            // 
            // labelX0
            // 
            this.labelX0.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.labelX0.AutoSize = true;
            this.labelX0.Location = new System.Drawing.Point(3, 24);
            this.labelX0.Name = "labelX0";
            this.labelX0.Size = new System.Drawing.Size(30, 13);
            this.labelX0.TabIndex = 3;
            this.labelX0.Text = "x0 =";
            this.labelX0.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // textBoxX0
            // 
            this.textBoxX0.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxX0.Location = new System.Drawing.Point(39, 21);
            this.textBoxX0.Name = "textBoxX0";
            this.textBoxX0.Size = new System.Drawing.Size(194, 20);
            this.textBoxX0.TabIndex = 0;
            // 
            // textBoxA
            // 
            this.textBoxA.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxA.Location = new System.Drawing.Point(39, 207);
            this.textBoxA.Name = "textBoxA";
            this.textBoxA.Size = new System.Drawing.Size(194, 20);
            this.textBoxA.TabIndex = 3;
            // 
            // labelA
            // 
            this.labelA.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.labelA.AutoSize = true;
            this.labelA.Location = new System.Drawing.Point(3, 211);
            this.labelA.Name = "labelA";
            this.labelA.Size = new System.Drawing.Size(30, 13);
            this.labelA.TabIndex = 6;
            this.labelA.Text = "A =";
            this.labelA.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // labelDx
            // 
            this.labelDx.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.labelDx.AutoSize = true;
            this.labelDx.Location = new System.Drawing.Point(3, 148);
            this.labelDx.Name = "labelDx";
            this.labelDx.Size = new System.Drawing.Size(30, 13);
            this.labelDx.TabIndex = 12;
            this.labelDx.Text = "Dx =";
            this.labelDx.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // textBoxDx
            // 
            this.textBoxDx.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxDx.Location = new System.Drawing.Point(39, 145);
            this.textBoxDx.Name = "textBoxDx";
            this.textBoxDx.Size = new System.Drawing.Size(194, 20);
            this.textBoxDx.TabIndex = 2;
            // 
            // tabulationsView
            // 
            this.tabulationsView.AllowUserToDeleteRows = false;
            this.tabulationsView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.tabulationsView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabulationsView.Location = new System.Drawing.Point(239, 3);
            this.tabulationsView.Name = "tabulationsView";
            this.tabulationsView.ReadOnly = true;
            this.tableLayoutPanel1.SetRowSpan(this.tabulationsView, 4);
            this.tabulationsView.Size = new System.Drawing.Size(320, 243);
            this.tabulationsView.TabIndex = 13;
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.authorLabel,
            this.statusLabel});
            this.statusStrip1.Location = new System.Drawing.Point(0, 265);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(584, 22);
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
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(584, 287);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.tableLayoutPanel1);
            this.MinimumSize = new System.Drawing.Size(294, 325);
            this.Name = "MainWindow";
            this.Text = "Странный калькулятор";
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.tabulationsView)).EndInit();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.TextBox textBoxA;
        private System.Windows.Forms.Label labelA;
        private System.Windows.Forms.TextBox textBoxX0;
        private System.Windows.Forms.Label labelX0;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel authorLabel;
        private System.Windows.Forms.ToolStripStatusLabel statusLabel;
        private System.Windows.Forms.Label labelXk;
        private System.Windows.Forms.TextBox textBoxXk;
        private System.Windows.Forms.Label labelDx;
        private System.Windows.Forms.TextBox textBoxDx;
        private System.Windows.Forms.DataGridView tabulationsView;
    }
}

