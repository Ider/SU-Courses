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
                ResetControls();
                LoadFilesAndFolders(Server.MapPath("."));
            }
        }

        #region Load HTML content

        /// <summary>
        /// Load the files and directories name under current directory
        /// </summary>
        private void LoadFilesAndFolders(string path)
        {
            lblCurPath.Text = path;
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
            string lastModified = Directory.GetLastWriteTime(folder).ToString(Constant.DATETIME_FORMAT); ;

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
                lastModified = Directory.GetLastWriteTime(folder).ToString(Constant.DATETIME_FORMAT);
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

        private void LoadFile(string path)
        {
            StreamReader sr = new StreamReader(path);
            SetContent(HTMLEncode(sr.ReadToEnd()));
        }

        private void LoadImage(string path)
        {
            string mapPath = Page.MapPath(".");
            //if image file is in current website, load it as image
            if (path.Contains(mapPath))
            {
                path = path.Substring(mapPath.Length);
                string img = string.Format("<img src='{0}' alt='image'/>", path.Replace('\\', '/'));
                SetContent(img);
            }
            else//load image as bytes
            {
                LoadFile(path);
            }

        }

        #endregion

        #region Get formated elements string

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
            string clientEvent = string.Format("onClick=\"submitClick('{0}','{1}');\""
                , name, isFolder.ToString());

            return string.Format(format, name, fileType, clientEvent);
        }

        /// <summary>
        /// Get formated <a> elemnt for parent folder
        /// </summary>
        /// <param name="name">parent folder name</param>
        /// <returns>formated </returns>
        private string GetFormatedLink(string name)
        {
            string format = "<a href='#{0}' ftype='folder' {1} title='{0}'>..</a>"; //{0}name, {1}event
            string clientEvent = "onClick=\"submitClick('..','True');\"";

            return string.Format(format, name, clientEvent);
        }

        #endregion

        #region Auxiliary functions

        private void ShowError(Exception ex)
        {
            lblCurPath.Text = ex.Message;
        }

        private void ResetControls()
        {
            hfFileName.Value = string.Empty;
            hfIsFolder.Value = string.Empty;
            litContent.Text = string.Empty;
            lblContent.Text = "Please select a file...";
        }

        private void SetContent(string content)
        {
            litContent.Text = content;
        }

        private bool IsImageFile(string name)
        {
            string[] imgType = { "jpg", "gif", "png", "jpeg", "svg", "eps", "ico" };
            string extension = Path.GetExtension(name).Trim('.').ToLower();
            List<string> s = new List<string>();

            foreach (string item in imgType)
                if (item == extension) return true;

            return false;
        }

        private string HTMLEncode(string text)
        {
            return Server.HtmlEncode(text).Replace("\n", "<br>").Replace(" ", "&nbsp;");
        }

        #endregion

        #region Button Event

        protected void btnSubmit_Click(object sender, EventArgs e)
        {
            string name = hfFileName.Value;
            bool isFolder = Convert.ToBoolean(hfIsFolder.Value);
            string path = Path.GetFullPath(lblCurPath.Text + "/" + name);

            ResetControls();

            try
            {
                if (isFolder)
                {
                    lblCurPath.Text = string.Empty;
                    LoadFilesAndFolders(path);
                }
                else
                {
                    lblContent.Text = name;
                    if (IsImageFile(name))
                        LoadImage(path);
                    else
                        LoadFile(path);
                }
            }
            catch (Exception ex)
            {
                ShowError(ex);
            }
        }

        #endregion
    }
}