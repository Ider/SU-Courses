using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Xml;
using System.Text;

namespace HTML
{
    public partial class master : System.Web.UI.MasterPage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                LoadLabSubMenu();
            }
        }

        public void SetRevisedTime(string fileName)
        {
            try
            {
                string path = Server.MapPath(".") + "\\" + fileName;
                DateTime dt = System.IO.Directory.GetLastWriteTime(path);
                lblRevised.Text = "Revised: " + dt.ToString(Constant.DATETIME_FORMAT);
            }
            catch (Exception ex)
            {
                lblRevised.Text = string.Empty;
            }
        }

        private void LoadLabSubMenu()
        {
            try
            {
                StringBuilder sb = new StringBuilder();
                string path = "http://www.ecs.syr.edu/faculty/fawcett/handouts/CSE686/assignments/";

                XmlDocument xmlDoc = new XmlDocument();
                xmlDoc.Load(Server.MapPath(Constant.LAB_XML_PATH));
                XmlNodeList requirements = xmlDoc.GetElementsByTagName("requirement");
                XmlNodeList pages = xmlDoc.GetElementsByTagName("page");


                sb.Append("<ul>");
                for (int index = 0; index < pages.Count; index++)
                {
                    try
                    {
                        string txt = string.Empty;
                        string url = string.Empty;
                        if (string.IsNullOrEmpty(pages[index]["url"].InnerText))
                        {
                            txt = requirements[index]["text"].InnerText;
                            url = path + requirements[index]["url"].InnerText;
                        }
                        else
                        {
                            txt = pages[index]["text"].InnerText;
                            url = pages[index]["url"].InnerText;
                        }

                        sb.Append(string.Format("<li><a href='{0}'>{1}</a></li>", url, txt));
                    }
                    catch (Exception ex)
                    {

                    }
                }
                sb.Append("</ul>");

                litLab.Text = sb.ToString();
            }
            catch (System.Exception ex)
            {

            }


        }
    }
}