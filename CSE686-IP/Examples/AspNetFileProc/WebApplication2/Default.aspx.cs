///////////////////////////////////////////////////////////////
// Default.aspx.cs - Show file contents                      //
//                                                           //
// Jim Fawcett, CSE686 - Internet Programming, Summer 2009   //
///////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace WebApplication2
{
    public partial class _Default : System.Web.UI.Page
    {
        private void FillListBox()
        {
            string[] dirs = Directory.GetDirectories(TextBox1.Text);
            ListBox1.Items.Clear();
            ListBox1.Items.Add("<> ..");
            foreach (string dir in dirs)
            {
                string name = "<> " + Path.GetFileName(dir);
                ListBox1.Items.Add(name);
            }
            string[] files = Directory.GetFiles(TextBox1.Text);
            foreach (string file in files)
            {
                string name = Path.GetFileName(file);
                ListBox1.Items.Add(name);
            }
        }
        protected void Page_Load(object sender, EventArgs e)
        {
            if (Session.IsNewSession)
                Session["currentPath"] = Server.MapPath(".");
            TextBox1.Text = Session["currentPath"] as string;
            Directory.SetCurrentDirectory(TextBox1.Text);
            FillListBox();
        }
        protected void ListBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            bool IsDir = false;
            string name = Request.Form[ListBox1.UniqueID];
            string temp;
            if (name[0] == '<')
            {
                int pos = name.LastIndexOf('>') + 2;
                temp = name.Substring(pos);
                IsDir = true;
            }
            else
                temp = name;
            if (IsDir)
            {
                string debug = Directory.GetCurrentDirectory();
                string path = Path.GetFullPath(temp);
                Directory.SetCurrentDirectory(path);
                Session["currentPath"] = path;
                TextBox1.Text = path;
                FillListBox();
                TextBox2.Text = "";
            }
            else
            {
                StreamReader sr = new StreamReader(temp);
                TextBox2.Text = sr.ReadToEnd();
            }
        }
    }
}
