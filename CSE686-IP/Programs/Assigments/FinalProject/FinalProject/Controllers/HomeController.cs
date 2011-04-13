using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using FinalProject.Helper;
using System.IO;

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

        [HttpPost]
        public void Upload()
        {
            foreach (string inputTagName in Request.Files)
            {
                HttpPostedFileBase file = Request.Files[inputTagName];
                if (file.ContentLength > 0)
                {
                    string path = HttpContext.Server.MapPath("../Uploads");
                    string filePath = Path.Combine(path, Path.GetFileName(file.FileName));
                    file.SaveAs(filePath);
                }
            }

            RedirectToAction("Index");
        }
    }
}
