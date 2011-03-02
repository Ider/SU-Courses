using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using FinalProject;

namespace FinalProject.Controllers
{
    [HandleError]
    public class HomeController : Controller
    {
        public ActionResult Index()
        {
            ViewData["Message"] = DateTime.Now.ToString(Constant.DATETIME_FORMAT);

            return View();
        }

        public ActionResult About()
        {
            return View();
        }

        public ActionResult Layout()
        {
            return View();
        }
    }
}
