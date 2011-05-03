using System.Collections.Generic;
using System.Web;
using System;
using System.Configuration;

using FinalProject.Models;

namespace FinalProject.Helper
{
    public abstract class Constant
    {
        public static string BUG_XML_PATH
        {
            get
            {
                return HttpContext.Current.Server.MapPath("~\\App_Data\\BugReports.xml");
            }
        }

        public static string DATETIME_FORMAT
        {
            get
            {
                return "MM/dd/yyyy HH:mm:ss";
            }
        }

        public static string WIKI_WEBSITE
        {
            get { return ConfigurationManager.AppSettings["WikiSiteAddress"]; }
        }
        //public static readonly string FINALDB_CONNECTIONSTRING = System.Web.Configuration.WebConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString;
    }

    public abstract class EnumHelper
    {
        public static IDictionary<int, string> GetStatus()
        {
            IDictionary<int, string> enums = new Dictionary<int, string>();
            foreach (int key in Enum.GetValues(typeof(WorkStatus)))
            {
                enums.Add(new KeyValuePair<int, string>(key, ((WorkStatus)key).ToString()));
            }

            return enums;
        }
    }
}