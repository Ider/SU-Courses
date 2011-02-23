using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace MVCTester.Controllers
{
    [HandleError]
    public class HomeController : Controller
    {
        public ActionResult Index()
        {
            ViewData["Message"] = "Welcome to ASP.NET MVC!";

            return View();
        }

        public ActionResult About()
        {
            ViewData["Message"] = "Here is about page!";
            return View();
        }

        public ActionResult Main()
        {
            ViewData["Message"] = "Here is main page!";
            return View();
        }
    }
}
