using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;
using FinalProject.Models;

namespace FinalProject
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the interface name "IWCFService" in both code and config file together.
    [ServiceContract]
    public interface IWCFService
    {

        [OperationContract]
        string DoWork();

        [OperationContract]
        IList<BugReport> GetBugReports();

        [OperationContract]
        BugReport GetBugReportByID(int id);

        [OperationContract]
        bool InsertBugReport(BugReport br);

        [OperationContract]
        bool UpdateBugReport(BugReport br);

        [OperationContract]
        bool DeleteBugReport(int id);
    }
}
