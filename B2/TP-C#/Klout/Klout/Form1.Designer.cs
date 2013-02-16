namespace Klout
{
    partial class Klout
    {
        /// <summary>
        /// Variable nécessaire au concepteur.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Nettoyage des ressources utilisées.
        /// </summary>
        /// <param name="disposing">true si les ressources managées doivent être supprimées ; sinon, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Code généré par le Concepteur Windows Form

        /// <summary>
        /// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
        /// le contenu de cette méthode avec l'éditeur de code.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Klout));
            this.search_tb = new System.Windows.Forms.TextBox();
            this.user_lb = new System.Windows.Forms.Label();
            this.search_bt = new System.Windows.Forms.Button();
            this.cloud_pb = new System.Windows.Forms.PictureBox();
            this.flowLayoutPanel = new System.Windows.Forms.FlowLayoutPanel();
            this.info_label = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.cloud_pb)).BeginInit();
            this.flowLayoutPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // search_tb
            // 
            this.search_tb.Location = new System.Drawing.Point(64, 113);
            this.search_tb.Name = "search_tb";
            this.search_tb.Size = new System.Drawing.Size(202, 22);
            this.search_tb.TabIndex = 0;
            this.search_tb.Text = "juliendollon";
            // 
            // user_lb
            // 
            this.user_lb.AutoSize = true;
            this.user_lb.Location = new System.Drawing.Point(12, 113);
            this.user_lb.Name = "user_lb";
            this.user_lb.Size = new System.Drawing.Size(46, 17);
            this.user_lb.TabIndex = 1;
            this.user_lb.Text = "User: ";
            // 
            // search_bt
            // 
            this.search_bt.Location = new System.Drawing.Point(272, 113);
            this.search_bt.Name = "search_bt";
            this.search_bt.Size = new System.Drawing.Size(75, 23);
            this.search_bt.TabIndex = 2;
            this.search_bt.Text = "Search !";
            this.search_bt.UseVisualStyleBackColor = true;
            this.search_bt.Click += new System.EventHandler(this.search_bt_Click);
            // 
            // cloud_pb
            // 
            this.cloud_pb.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.cloud_pb.Image = ((System.Drawing.Image)(resources.GetObject("cloud_pb.Image")));
            this.cloud_pb.Location = new System.Drawing.Point(1, 26);
            this.cloud_pb.Name = "cloud_pb";
            this.cloud_pb.Size = new System.Drawing.Size(357, 62);
            this.cloud_pb.TabIndex = 3;
            this.cloud_pb.TabStop = false;
            // 
            // flowLayoutPanel
            // 
            this.flowLayoutPanel.AutoScroll = true;
            this.flowLayoutPanel.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.flowLayoutPanel.Controls.Add(this.info_label);
            this.flowLayoutPanel.Location = new System.Drawing.Point(13, 145);
            this.flowLayoutPanel.Name = "flowLayoutPanel";
            this.flowLayoutPanel.Size = new System.Drawing.Size(334, 328);
            this.flowLayoutPanel.TabIndex = 4;
            // 
            // info_label
            // 
            this.info_label.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.info_label.AutoSize = true;
            this.info_label.Location = new System.Drawing.Point(3, 0);
            this.info_label.Name = "info_label";
            this.info_label.Size = new System.Drawing.Size(125, 17);
            this.info_label.TabIndex = 0;
            this.info_label.Text = "Enter an user first.";
            // 
            // Klout
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(359, 485);
            this.Controls.Add(this.flowLayoutPanel);
            this.Controls.Add(this.cloud_pb);
            this.Controls.Add(this.search_bt);
            this.Controls.Add(this.user_lb);
            this.Controls.Add(this.search_tb);
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(377, 530);
            this.MinimumSize = new System.Drawing.Size(377, 530);
            this.Name = "Klout";
            this.Text = "Klout";
            ((System.ComponentModel.ISupportInitialize)(this.cloud_pb)).EndInit();
            this.flowLayoutPanel.ResumeLayout(false);
            this.flowLayoutPanel.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox search_tb;
        private System.Windows.Forms.Label user_lb;
        private System.Windows.Forms.Button search_bt;
        private System.Windows.Forms.PictureBox cloud_pb;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel;
        private System.Windows.Forms.Label info_label;
    }
}

