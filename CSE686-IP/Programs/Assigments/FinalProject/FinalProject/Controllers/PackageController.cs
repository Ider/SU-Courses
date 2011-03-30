using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using FinalProject.Models;
using System.Data.Linq;

namespace FinalProject.Controllers
{
    public class PackageController : Controller
    {

        //
        // GET: /Package/

        public ActionResult Index()
        {
            IPFinalDBDataContext finalDB = new IPFinalDBDataContext();
            var data = from p in finalDB.Package_Softwares
                       group p by p.wp_id into psg
                       select psg;

            var packs = (from p in finalDB.Work_Packages
                         select p).ToList();

            foreach (var pack in packs)
            {
                pack.RequirementCount = data.Count(p => p.Key == pack.id);
            }


            return View(packs);
        }

        public ActionResult Details(int id)
        {
            IPFinalDBDataContext finalDB = new IPFinalDBDataContext();

            DataLoadOptions ds = new DataLoadOptions();
            ds.LoadWith<Work_Package>(wp => wp.Package_Softwares);
            ds.LoadWith<Package_Software>(ps => ps.Software_Requirement);
            finalDB.LoadOptions = ds;

            var pack = (from p in finalDB.Work_Packages
                        where p.id == id
                        select p).Single();

            //var data = from sr in finalDB.Software_Requirements
            //           join ps in finalDB.Package_Softwares
            //           on sr.id equals ps.sr_id
            //           where ps.wp_id == id
            //           select sr;

            //foreach (var ps in data)
            //{
            //    pack.Package_Softwares.Add(new Package_Software()
            //    {
            //        Software_Requirement = ps,
            //        Work_Package = pack
            //    });
            //}
            

            return View(pack);
        }

        public ActionResult Edit(int? id)
        {
            if (id == null) return View(new Package_Software());

            IPFinalDBDataContext finalDB = new IPFinalDBDataContext();

            var pack = (from p in finalDB.Work_Packages
                        where p.id == id
                        select p).Single();
            return View();
        }

    }
}
