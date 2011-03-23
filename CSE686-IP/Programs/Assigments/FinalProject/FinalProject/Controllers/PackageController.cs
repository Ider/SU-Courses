using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using FinalProject.Models;

namespace FinalProject.Controllers
{
    public class PackageController : Controller
    {
        FinalDBEntities finalDB = new FinalDBEntities();

        //
        // GET: /Package/

        public ActionResult Index()
        {
            var data = from package in finalDB.Work_Package.Include("Package_Software")
                       orderby package.task_id, package.workorder
                       select package;
            //select new Work_Package()
            //{
            //    id = package.id,
            //    name = package.name,
            //    task_id = package.task_id,
            //    status = package.status,
            //    workorder = package.workorder,
            //    Package_Software = package.Package_Software
            //};
            return View(data);
        }

        public ActionResult Details(int id)
        {
            var data = (from package in finalDB.Work_Package.Include("Package_Software.Software_Requirement")
                       where package.id == id
                       select package).First();
                         
                       
                                                                    
            return View(data);
        }

    }
}
