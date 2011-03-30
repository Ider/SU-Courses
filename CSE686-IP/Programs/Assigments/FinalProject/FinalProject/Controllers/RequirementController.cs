using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using FinalProject.Models;
using FinalProject.Services;

namespace FinalProject.Controllers
{
    public class RequirementController : Controller
    {
        static RequirementService rs = new RequirementService();
        //
        // GET: /Requirement/

        public ActionResult Index()
        {
            var data = rs.GetRequirements();
            return View(data);
        }

        //
        // GET: /Requirement/Details/5

        public ActionResult Details(int id)
        {
            var data = rs.GetRequirementByID(id);
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

        public ActionResult Edit(int? id)
        {
            var data = rs.GetRequirementByID(id ?? -1);
            return View(data);
        }

        //
        // POST: /Requirement/Edit/5

        [HttpPost]
        public ActionResult Edit(int? id, Software_Requirement model)
        {
            model.id = id ?? -1;
            try
            {
                if (id == null)
                {
                    rs.InsertRequirement(model);
                    return RedirectToAction("Index");
                }
                else
                {
                    rs.UpdateRequirement(model);
                    return RedirectToAction("Details",new {id = model.id});
                }

            }
            catch
            {
                return View(model);
            }
        }

        //
        // GET: /Requirement/Delete/5

        public ActionResult Delete(int id)
        {
            rs.DeleteRequirement(id);
            return RedirectToAction("Index");
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
