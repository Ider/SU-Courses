using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using FinalProject.Models;

namespace FinalProject.Controllers
{
    public class BugReportController : Controller
    {
        //
        // GET: /Bug/

        public ActionResult Index(BugListModel buglist)
        {
            ViewData["Path"] = Server.MapPath(Constant.BUG_XML_PATH);
            bool succed = buglist.GetBugList(Server.MapPath(Constant.BUG_XML_PATH));
            ViewData["Message"] = "Bug Report List";
            return View(buglist);
        }

        //
        // GET: /Bug/Details/5

        public ActionResult Details(int? id)
        {
            return View();
        }

        //
        // GET: /Bug/Create

        public ActionResult Create()
        {
            return View();
        }

        //
        // POST: /Bug/Create

        [HttpPost]
        public ActionResult Create(FormCollection collection)
        {
            try
            {
                // TODO: Add insert logic here

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }

        //
        // GET: /Bug/Edit/5

        public ActionResult Edit(int id)
        {
            return View();
        }

        //
        // POST: /Bug/Edit/5

        [HttpPost]
        public ActionResult Edit(int id, FormCollection collection)
        {
            try
            {
                // TODO: Add update logic here

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }

        //
        // GET: /Bug/Delete/5

        public ActionResult Delete(int id)
        {
            return View();
        }

        //
        // POST: /Bug/Delete/5

        [HttpPost]
        public ActionResult Delete(int id, FormCollection collection)
        {
            try
            {
                // TODO: Add delete logic here

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }
    }
}
