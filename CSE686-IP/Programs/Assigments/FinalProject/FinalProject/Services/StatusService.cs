using System;
using System.Web;
using System.Linq;
using System.Xml.Linq;
using System.Collections.Generic;

using FinalProject.Models;
using FinalProject.Helper;


namespace FinalProject.Services
{
    public class StatusReportService
    {
        //revise this class to be singleton
        public IList<StatusReport> GetStatusReports()
        {
            IList<StatusReport> reports = new List<StatusReport>();

            XDocument doc = XDocument.Load(Constant.STATUS_XML_PATH);
            var result = from Status in doc.Elements("StatusReports").Elements("StatusReport") select Status;

            foreach (var elem in result)
            {
                StatusReport r = new StatusReport();
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

        public StatusReport GetStatusReportByID(int id)
        {
            StatusReport br = new StatusReport();
            if (id <= 0) return br;

            try
            {
                XDocument doc = XDocument.Load(Constant.STATUS_XML_PATH);
                var elem = doc.Elements("StatusReports")
                                 .Elements("StatusReport")
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

        public bool InsertStatusReport(StatusReport br)
        {
            br.Number = (new Random()).Next(1000, 10000);
            XElement elem = new XElement("StatusReport"
                , new XElement("Number", br.Number)
                , new XElement("ReportedBy", br.ReportedBy ?? string.Empty)
                , new XElement("OwnedBy", br.OwnedBy ?? string.Empty)
                , new XElement("Component", br.Component ?? string.Empty)
                , new XElement("Keywords", br.Keywords ?? string.Empty)
                , new XElement("ReportedTime", DateTime.Now.ToString(Constant.DATETIME_FORMAT))
                , new XElement("Description", br.Description ?? string.Empty)
                , new XElement("Comments", string.Empty)
                );

            XDocument doc = XDocument.Load(Constant.STATUS_XML_PATH);
            doc.Element("StatusReports").Add(elem);
            doc.Save(Constant.STATUS_XML_PATH);
            return true;
        }

        public bool UpdateStatusReport(StatusReport br)
        {
            XDocument doc = XDocument.Load(Constant.STATUS_XML_PATH);
            var elem = doc.Elements("StatusReports")
                             .Elements("StatusReport")
                             .First(M => Convert.ToInt32(M.Element("Number").Value) == br.Number);
            if (elem != null)
            {
                elem.Element("ReportedBy").Value = br.ReportedBy ?? string.Empty;
                elem.Element("OwnedBy").Value = br.OwnedBy ?? string.Empty;
                elem.Element("Keywords").Value = br.Keywords ?? string.Empty;
                elem.Element("Component").Value = br.Component ?? string.Empty;
                elem.Element("Description").Value = br.Description ?? string.Empty;
            }
            doc.Save(Constant.STATUS_XML_PATH);

            return true;
        }

        public bool DeleteStatusReport(int id)
        {
            StatusReport br = new StatusReport();
            if (id <= 0) return false;

            try
            {
                XDocument doc = XDocument.Load(Constant.STATUS_XML_PATH);
                var elem = doc.Elements("StatusReports")
                                 .Elements("StatusReport")
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

                doc.Save(Constant.STATUS_XML_PATH);
            }
            catch
            {
                return false;
            }

            return true;
        }
    }
}