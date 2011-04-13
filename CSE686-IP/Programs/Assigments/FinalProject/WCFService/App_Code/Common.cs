using System.Collections.Generic;
using System.Web;
using System;

namespace WCFService.Helper
{
    public abstract class Constant
    {
        public static readonly string BUG_XML_PATH = HttpContext.Current.Server.MapPath("~\\App_Data\\BugReports.xml");
        public const string DATETIME_FORMAT = "MM/dd/yyyy HH:mm:ss";
        //public static readonly string FINALDB_CONNECTIONSTRING = System.Web.Configuration.WebConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString;
    }
}