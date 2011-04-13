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
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the interface name "IFinalService" in both code and config file together.
    [ServiceContract]
    public interface IFinalWCFService
    {
        [OperationContract]
        string DoWork();

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
