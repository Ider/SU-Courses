using System;
using System.Web;
using System.Linq;
using System.Xml.Linq;
using System.Collections.Generic;

using FinalProject.Models;
using FinalProject.Helper;


namespace FinalProject.Services
{
    public class BugReportService
    {
        //revise this class to be singleton

        public IList<BugReport> GetBugReports()
        {
            IList<BugReport> reports = new List<BugReport>();

            XDocument doc = XDocument.Load(Constant.BUG_XML_PATH);
            var result = from bug in doc.Elements("BugReports").Elements("BugReport") select bug;

            foreach (var elem in result)
            {
                BugReport r = new BugReport();
                r.Number = Convert.ToInt32(elem.Element("Number").Value);
                r.ReportedBy = elem.Element("ReportedBy").Value;
                r.OwnedBy = elem.Element("OwnedBy").Value;
                r.Keywords = elem.Element("Keywords").Value;
                r.Component = elem.Element("Component").Value;
                r.ReportedTime = Convert.ToDateTime(elem.Element("ReportedTime").Value);
                r.Description = elem.Element("Description").Value;
                reports.Add(r);
            }


            return reports;
        }

        public BugReport GetBugReportByID(int id)
        {
            BugReport br = new BugReport();
            if (id <= 0) return br;

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
            catch (Exception ex)
            {
                throw ex;
            }

            return br;
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
            return true;
        }

        public bool UpdateBugReport(BugReport br)
        {
            XDocument doc = XDocument.Load(Constant.BUG_XML_PATH);
            var elem = doc.Elements("BugReports")
                             .Elements("BugReport")
                             .First(M => Convert.ToInt32(M.Element("Number").Value) == br.Number);
            if (elem != null)
            {
                elem.Element("ReportedBy").Value = br.ReportedBy ?? string.Empty;
                elem.Element("OwnedBy").Value = br.OwnedBy ?? string.Empty;
                elem.Element("Keywords").Value = br.Keywords ?? string.Empty;
                elem.Element("Component").Value = br.Component ?? string.Empty;
                elem.Element("Description").Value = br.Description ?? string.Empty;
            }
            doc.Save(Constant.BUG_XML_PATH);

            return true;
        }

        public bool DeleteBugReport(int id)
        {
            BugReport br = new BugReport();
            if (id <= 0) return false;

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

                    elem.Remove();
                }

                doc.Save(Constant.BUG_XML_PATH);
            }
            catch
            {
                return false;
            }

            return true;
        }
    }
}