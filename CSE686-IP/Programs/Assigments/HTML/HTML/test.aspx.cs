﻿using System;
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
                LoadFilesAndFolds(lblCurPath.Text);
            }
        }

        /// <summary>
        /// Load the files and directories name under current directory
        /// </summary>
        private void LoadFilesAndFolds(string path)
        {
            try
            {
                StringBuilder sb = new StringBuilder();

                sb.Append("<table width='100%' border='0' align='left'"
                    + " cellpadding='5' cellspacing='0' class='map' style='border: 0px solid #fff;'>");
                //AppendTableHead(sb);

                sb.Append("<tbody>");
                AppendParentFoldInfo(path, sb);
                AppendFoldsInfo(path, sb);
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

        private void AppendParentFoldInfo(string path, StringBuilder sb)
        {
            string fold = Path.GetFullPath(path + "/..");
            string format = string.Format(GetTableRowFormat()
                , "<td class='fileName'>{3}[ {0} ]</td>"
                + "<td class='fileType'>{1}</td>"
                + "<td class='lastModified'>{2}</td>");
            string name = Path.GetFileName(fold);
            string type = "Directory";
            string lastModified = Directory.GetLastWriteTime(fold).ToString("MM/dd/yyyy hh:mm:ss"); ;

            sb.Append(string.Format(format, name, type, lastModified, "../"));
        }

        private void AppendFoldsInfo(string path, StringBuilder sb)
        {
            string[] folds = Directory.GetDirectories(path);
            string format = string.Format(GetTableRowFormat()
                , "<td>{0}</td><td>{1}</td><td>{2}</td>");
            string name = string.Empty;
            string type = "Directory";
            string lastModified = string.Empty;

            foreach (string fold in folds)
            {
                name = Path.GetFileName(fold);
                lastModified = Directory.GetLastWriteTime(fold).ToString("MM/dd/yyyy hh:mm:ss");
                sb.Append(string.Format(format, name, type, lastModified));
            }
        }

        private void AppendFilesInfo(string path, StringBuilder sb)
        {
            string[] files = Directory.GetFiles(path);
            string format = string.Format(GetTableRowFormat()
                , "<td>{0}</td><td>{1}</td><td>{2}</td>");
            string name = string.Empty;
            string type = string.Empty;
            string lastModified = string.Empty;

            foreach (string file in files)
            {
                name = Path.GetFileName(file);
                type = Path.GetExtension(file);
                lastModified = Directory.GetLastWriteTime(file).ToString("MM/dd/yyyy hh:mm:ss");
                sb.Append(string.Format(format, name, type, lastModified));
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

        private void ShowError(Exception ex)
        {
            lblCurPath.Text = ex.Message;
        }
    }
}