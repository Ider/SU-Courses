using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.IO;

namespace Wiki
{
    public partial class _Default : System.Web.UI.Page
    {

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                ToggleVisiblity(true);
                GetWikiContent();
            }
        }

        private string HTMLEncode(string text)
        {
            return Server.HtmlEncode(text).Replace("\n", "<br>").Replace(" ", "&nbsp;");
        }

        private void GetWikiContent()
        {
            string FILE_NAME = Server.MapPath("App_Data\\WikiContent.txt");
            using (StreamReader sr = File.OpenText(FILE_NAME))
            {
                txtWiki.Text = sr.ReadToEnd();
                lblWiki.Text = HTMLEncode(txtWiki.Text);
                sr.Close();
            }
        }

        private void WriteWikiContent()
        {
            string FILE_NAME = Server.MapPath("App_Data\\WikiContent.txt");

            using (StreamWriter sw = File.CreateText(FILE_NAME))
            {
                sw.Write(txtWiki.Text);
                sw.Close();

            }
        }

        protected void btnSumbit_Click(object sender, EventArgs e)
        {
            if (lblWiki.Visible)
            {
                ToggleVisiblity(false);
            }
            else
            {
                lblWiki.Text = HTMLEncode(txtWiki.Text);
                WriteWikiContent();
                ToggleVisiblity(true);
            }
        }

        private void ToggleVisiblity(bool visible)
        {
            lblWiki.Visible = visible;
            txtWiki.Visible = !visible;
            btnSumbit.Text = visible ? "Edit" : "Save";
            btnCancel.Visible = !visible;
        }

        protected void btnCancel_Click(object sender, EventArgs e)
        {
            ToggleVisiblity(true);
        }
    }
}
