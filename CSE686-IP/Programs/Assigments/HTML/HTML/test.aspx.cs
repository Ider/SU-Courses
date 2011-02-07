using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Text;
using System.IO;

namespace HTML
{
    public partial class test : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                if (Session.IsNewSession)
                    Session["currentPath"] = Server.MapPath(".");
                lblCurPath.Text = Session["currentPath"] as string;
                LoadFilesAndFolders(lblCurPath.Text);
            }
        }

        /// <summary>
        /// Load the files and directories name under current directory
        /// </summary>
        private void LoadFilesAndFolders(string path)
        {
            try
            {
                StringBuilder sb = new StringBuilder();

                sb.Append("<table width='100%' border='0' align='left'"
                    + " cellpadding='5' cellspacing='0' class='map' style='border: 0px solid #fff;'>");
                //AppendTableHead(sb);

                sb.Append("<tbody>");
                AppendParentFolderInfo(path, sb);
                AppendFoldersInfo(path, sb);
                AppendFilesInfo(path, sb);

                sb.Append("</tbody></table>");
                litList.Text = sb.ToString();
            }
            catch (Exception ex)
            {
                ShowError(ex);
                return;
            }
        }

        #region Append HTML elements to String Builder

        private void AppendTableHead(StringBuilder sb)
        {
            string tr = string.Format("<tr><td>{0}</td><td>{1}</td><td>{2}</td></tr>"
                , "Name", "Type", "Last Modified");
            sb.Append(string.Format("<thead>{0}</thead>", tr));
        }

        private void AppendParentFolderInfo(string path, StringBuilder sb)
        {
            string folder = Path.GetFullPath(path + "/..");
            string format = string.Format(GetTableRowFormat()
                , "<td class='fileName'>{0}</td>"
                + "<td class='fileType'>{1}</td>"
                + "<td class='lastModified'>{2}</td>");

            string link = GetFormatedLink(Path.GetFileName(folder));
            string type = "Directory";
            string lastModified = Directory.GetLastWriteTime(folder).ToString("MM/dd/yyyy hh:mm:ss"); ;

            sb.Append(string.Format(format, link, type, lastModified));
        }

        private void AppendFoldersInfo(string path, StringBuilder sb)
        {
            string[] folders = Directory.GetDirectories(path);
            string format = string.Format(GetTableRowFormat()
                , "<td>{0}</td><td>{1}</td><td>{2}</td>");
            string link = string.Empty;
            string type = "Directory";
            string lastModified = string.Empty;

            foreach (string folder in folders)
            {
                link = GetFormatedLink(Path.GetFileName(folder), true);
                lastModified = Directory.GetLastWriteTime(folder).ToString("MM/dd/yyyy hh:mm:ss");
                sb.Append(string.Format(format, link, type, lastModified));
            }
        }

        private void AppendFilesInfo(string path, StringBuilder sb)
        {
            string[] files = Directory.GetFiles(path);
            string format = string.Format(GetTableRowFormat()
                , "<td>{0}</td><td>{1}</td><td>{2}</td>");
            string link = string.Empty;
            string type = string.Empty;
            string lastModified = string.Empty;

            foreach (string file in files)
            {
                link = GetFormatedLink(Path.GetFileName(file), false);
                type = Path.GetExtension(file);
                lastModified = Directory.GetLastWriteTime(file).ToString("MM/dd/yyyy hh:mm:ss");
                sb.Append(string.Format(format, link, type, lastModified));
            }
        }

        #endregion

        private string GetTableRowFormat()
        {
            string mouseEvents = "onmouseover=\"currentcolor=this.style.backgroundColor;"
                + "this.style.backgroundColor='#f47321';\""
                + "onmouseout='this.style.backgroundColor=currentcolor'";
            string trFormat = string.Format("<tr {0}>{{0}}</tr>", mouseEvents);

            return trFormat;
        }

        private string GetFormatedLink(string name, bool isFolder)
        {
            string format = "<a href='#{0}' ftype='{1}' {2}>{0}</a>"; //{0}name, {1}for iconizer, {2}event
            string fileType = isFolder ? "folder" : name.ToLower();

            return string.Format(format, name, fileType, "");
        }

        /// <summary>
        /// Get formated <a> elemnt for parent folder
        /// </summary>
        /// <param name="name">parent folder name</param>
        /// <returns>formated </returns>
        private string GetFormatedLink(string name)
        {
            string format = "<a href='#{0}' ftype='folder' {1} title='{0}'>..</a>"; //{0}name, {1}event
            return string.Format(format, name, "");
        }

        private void ShowError(Exception ex)
        {
            lblCurPath.Text = ex.Message;
        }
    }
}