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

    public class StatusReportController : Controller
    {
        StatusReportService srService = new StatusReportService();
        //
        // GET: /Status/

        public ActionResult Index()
        {
            IList<StatusReport> reports = srService.GetStatusReports();
            return View(reports.ToList());
        }

        //
        // GET: /Status/Details/5s

        public ActionResult Details(int id)
        {
            StatusReport br = srService.GetStatusReportByID(id);

            return View(br);
        }

        //
        // GET: /Status/Create

        public ActionResult Create()
        {
            return View();
        }

        //
        // POST: /Status/Create

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
        // GET: /Status/Edit/5
        [Authorize(Roles = "Admin,Manager")]
        public ActionResult Edit(int? id)
        {
            StatusReport br = srService.GetStatusReportByID(id ?? -1);

            return View(br);
        }

        //
        // POST: /Status/Edit/5

        [HttpPost]
        public ActionResult Edit(int? id, StatusReport model)
        {
            //int temp = Request.Form.Count;
            model.Number = id ?? 0;
            try
            {
                if (id == null)
                    srService.InsertStatusReport(model);
                else
                    srService.UpdateStatusReport(model);
                return RedirectToAction("Index");
            }
            catch//(Exception ex)
            {
                return View(model);
            }
        }

        //
        // GET: /Status/Delete/5

        [HttpPost]
        public ActionResult DeleteStatusReport(int id)
        {
            string message = string.Format("Status Report #{0} has been deleted.", id);
            try
            {
                srService.DeleteStatusReport(id);
            }
            catch (Exception ex)
            {
                id = 0;
                message = ex.Message;
            }
            return Json(new { ID = id, Message = message });
        }

        //
        // POST: /Status/Delete/5

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

            IList<StatusReport> reports = srService.GetStatusReports();
            IOrderedEnumerable<StatusReport> sorted;

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
