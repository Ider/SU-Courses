using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using FinalProject.Models;

namespace FinalProject.Controllers
{
    public class RequirementController : Controller
    {
        //
        // GET: /Requirement/

        public ActionResult Index()
        {
            IPFinalDBDataContext finalDB = new IPFinalDBDataContext();
            var data = (from sr in finalDB.Software_Requirements
                        select sr).ToList(); ;
            return View(data);
        }

        //
        // GET: /Requirement/Details/5

        public ActionResult Details(int id)
        {
            IPFinalDBDataContext finalDB = new IPFinalDBDataContext();
            var data = (from sr in finalDB.Software_Requirements
                       where sr.id == id
                       select sr).Single();
            return View(data);
        }

        //
        // GET: /Requirement/Create

        public ActionResult Create()
        {
            return View();
        }

        //
        // POST: /Requirement/Create

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
        // GET: /Requirement/Edit/5

        public ActionResult Edit(int id)
        {
            return View();
        }

        //
        // POST: /Requirement/Edit/5

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
        // GET: /Requirement/Delete/5

        public ActionResult Delete(int id)
        {
            return View();
        }

        //
        // POST: /Requirement/Delete/5

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
