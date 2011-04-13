using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;


using System.ServiceModel.Activation;


using WCFService.Models;
using WCFService.Services;

namespace WCFService
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "FinalService" in code, svc and config file together.
    
    
    [AspNetCompatibilityRequirements(RequirementsMode = AspNetCompatibilityRequirementsMode.Allowed)]
    public class FinalWCFService : IFinalWCFService
    {
        private static BugReportService brService = new BugReportService();



        public string DoWork()
        {
            string temp = System.Web.HttpContext.Current.Server.MapPath(".");

            return "WCF service works.";
        }

        public IList<BugReport> GetBugReports()
        {
            return brService.GetBugReports();
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
