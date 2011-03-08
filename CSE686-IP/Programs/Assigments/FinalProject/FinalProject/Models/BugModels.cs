using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Xml.Linq;
using FinalProject.Helper;


namespace FinalProject.Models
{

    public class BugReportService
    {
        //revise this class to be singleton

        public BugReport GetBugReportByID(int id)
        {
            BugReport br = new BugReport();
            if (id < 0) return br;

            try
            {
                XDocument doc = XDocument.Load(Constant.BUG_XML_PATH);
                var elem = doc.Elements("BugReports")
                                 .Elements("BugReport")
                                 .First(M => Convert.ToInt32(M.Element("Number").Value) == id);
                if (elem != null)
                {
                    br.Number = Convert.ToInt32(elem.Element("Number").Value);
                    br.ReportedBy = elem.Element("ReportedBy").Value;
                    br.OwnedBy = elem.Element("OwnedBy").Value;
                    br.Keywords = elem.Element("Keywords").Value;
                    br.Component = elem.Element("Component").Value;
                    br.ReportedTime = Convert.ToDateTime(elem.Element("ReportedTime").Value);
                    br.Description = elem.Element("Description").Value;

                }
            }
            catch
            {
                return null;
            }

            return br;
        }

        public bool UpdateBugReport(BugReport br)
        {

            return false;
        }

        public bool InsertBugReport(BugReport br)
        {
            br.Number = (new Random()).Next(1000, 10000);
            XElement elem = new XElement("BugReport"
                , new XElement("Number", br.Number)
                , new XElement("ReportedBy", br.ReportedBy ?? string.Empty)
                , new XElement("OwnedBy", br.OwnedBy ?? string.Empty)
                , new XElement("Component", br.Component ?? string.Empty)
                , new XElement("Keywords", br.Keywords ?? string.Empty)
                , new XElement("ReportedTime", DateTime.Now.ToString(Constant.DATETIME_FORMAT))
                , new XElement("Description", br.Description ?? string.Empty)
                , new XElement("Comments", string.Empty)
                );

            XDocument doc = XDocument.Load(Constant.BUG_XML_PATH);
            doc.Element("BugReports").Add(elem);
            doc.Save(Constant.BUG_XML_PATH);
            return false;
        }
    }

    public class BugReport
    {
        public int Number { get; set; }
        public string ReportedBy { get; set; }
        public string OwnedBy { get; set; }
        public string Component { get; set; }
        public string Keywords { get; set; }
        public DateTime ReportedTime { get; set; }
        public string Description { get; set; }
        public IList<Comment> Comments { get; set; }
    }

    public class Comment
    {
        public string CommentedBy { get; set; }
        public DateTime Dtaetime { get; set; }
        public string Content { get; set; }
    }

    public class BugListModel
    {
        public IList<BugReport> Reports { get; set; }

        public BugListModel()
        {
            Reports = new List<BugReport>();
        }

        public bool GetBugList(string path)
        {
            XDocument doc = XDocument.Load(path);
            var result = from bug in doc.Elements("BugReports").Elements("BugReport") select bug;

            foreach (var elem in result)
            {
                BugReport r = new BugReport();
                r.Number = Convert.ToInt32(elem.Element("Number").Value);
                r.ReportedBy = elem.Element("ReportedBy").Value;
                r.OwnedBy = elem.Element("OwnedBy").Value;
                r.Keywords = elem.Element("Keywords").Value;
                r.Component = elem.Element("Component").Value;
                r.Description = elem.Element("Description").Value;
                Reports.Add(r);
            }

            return true;
        }
    }
}