using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

//using FinalProject.Models;
using FinalProject.Helper;
using FinalProject.Services;
using FinalProject.Models;

namespace FinalProject.Controllers
{
   
    public class BugReportController : Controller
    {
        BugReportService brService = new BugReportService();
        //
        // GET: /Bug/

        public ActionResult Index()
        {
            IList<BugReport> reports = brService.GetBugReports();
            return View(reports.ToList());
        }

        //
        // GET: /Bug/Details/5s

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
        [Authorize(Roles = "Admin,Manager")]
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
            //int temp = Request.Form.Count;
            model.Number = id ?? 0;
            try
            {
                if (id == null)
                    brService.InsertBugReport(model);
                else
                    brService.UpdateBugReport(model);
                return RedirectToAction("Index");
            }
            catch//(Exception ex)
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


        public ActionResult Sort(string key, bool asc)
        {
            ViewData["OrderAsc"] = !asc;

            IList<BugReport> reports = brService.GetBugReports();
            IOrderedEnumerable<BugReport> sorted;

            switch (key)
            {
                case "Number":
                    sorted = asc ?
                        reports.OrderBy(m => m.Number)
                        : reports.OrderByDescending(m => m.Number);
                    break;
                case "ReportedBy":
                    sorted = asc ?
                        reports.OrderBy(m => m.ReportedBy)
                        : reports.OrderByDescending(m => m.ReportedBy);
                    break;
                case "ReportedTime":
                    sorted = asc ?
                        reports.OrderBy(m => m.ReportedTime)
                        : reports.OrderByDescending(m => m.ReportedTime);
                    break;
                case "OwnedBy":
                    sorted = asc ?
                        reports.OrderBy(m => m.OwnedBy)
                        : reports.OrderByDescending(m => m.OwnedBy);
                    break;
                default:
                    sorted = reports.OrderByDescending(m => m.ReportedTime);
                    break;
            }

            return View("Index", sorted.ToList());
        }
    }
}
