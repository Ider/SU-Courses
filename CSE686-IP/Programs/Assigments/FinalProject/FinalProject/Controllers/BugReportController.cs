using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using FinalProject.Models;
using FinalProject.Helper;

namespace FinalProject.Controllers
{
    public class BugReportController : Controller
    {

        static BugReportService brService = new BugReportService();
        //
        // GET: /Bug/

        public ActionResult Index(BugListModel buglist)
        {
            ViewData["Path"] = Constant.BUG_XML_PATH;
            bool succed = buglist.GetBugList(Constant.BUG_XML_PATH);
            ViewData["Message"] = "Bug Report List";
            return View(buglist);
        }

        //
        // GET: /Bug/Details/5

        public ActionResult Details(int id)
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

        public ActionResult Edit(int? id)
        {
            BugReport br = brService.GetBugReportByID(id ?? -1);
            return View(br);
        }

        //
        // POST: /Bug/Edit/5

        [HttpPost]
        public ActionResult Edit(int? id, BugReport model)
        {
            int temp = Request.Form.Count;
            model.Number = id ?? 0;
            try
            {
                if (id == null)
                    brService.InsertBugReport(model);
                else
                    brService.UpdateBugReport(model);
                return RedirectToAction("Index");
            }
            catch(Exception ex)
            {
                return View(model);
            }
        }

        //
        // GET: /Bug/Delete/5

        [HttpPost]
        public ActionResult DeleteBugReport(int id)
        {
            string message = string.Format("Bug Report #{0} has been deleted.", id);
            try
            {
                brService.DeleteBugReport(id);
            }
            catch (Exception ex)
            {
                id = 0;
                message = ex.Message;
            }
            return Json(new { ID = id, Message = message });
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
