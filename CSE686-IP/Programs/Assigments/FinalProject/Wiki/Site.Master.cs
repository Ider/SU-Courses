using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Configuration;

namespace Wiki
{
    public partial class SiteMaster : System.Web.UI.MasterPage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
                string mvcWebsite = ConfigurationManager.AppSettings["MvcSiteAddress"];
                NavigationMenu.Items.Add(new MenuItem("MVC") { NavigateUrl = mvcWebsite });
        }
    }
}
