using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Xml.Linq;

namespace FinalProject.Models
{

    public class BugReport
    {
        public int Number { get; set; }
        public string ReportedBy { get; set; }
        public string OwnedBy { get; set; }
        public string Component { get; set; }
        public string Keywords { get; set; }
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
                r.Number =Convert.ToInt32(elem.Element("Number").Value);
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