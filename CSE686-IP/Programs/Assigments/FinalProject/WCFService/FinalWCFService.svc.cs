using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;


using WCFService.Models;
using WCFService.Services;

namespace WCFService
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "FinalService" in code, svc and config file together.
    public class FinalWCFService : IFinalWCFService
    {
        private static BugReportService brService = new BugReportService();

        public string DoWork()
        {
            return "WCF service works.";
        }

        public BugReport GetBugReportByID(int id)
        {
          return  brService.GetBugReportByID(id);
        }

        public bool InsertBugReport(BugReport br)
        {
            return brService.InsertBugReport(br);
        }

        public bool UpdateBugReport(BugReport br)
        {
            return brService.UpdateBugReport(br);
        }

        public bool DeleteBugReport(int id)
        {
            return brService.DeleteBugReport(id);
        }

    }
}
