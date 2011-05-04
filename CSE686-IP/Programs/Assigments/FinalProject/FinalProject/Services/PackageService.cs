using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Xml.Linq;
using FinalProject.Helper;
using FinalProject.Models;
using System.Collections;

namespace FinalProject.Services
{
    public class PackageService
    {
        //revise this class to be singleton

        public IEnumerable<Work_Package> GetPackages()
        {
            IPFinalDBDataContext finalDB = new IPFinalDBDataContext();
            var list = (from wp in finalDB.Work_Packages
                        select wp).ToList();
            return list;
        }

        public Work_Package GetPackageByID(int id)
        {
            if (id <= 0) return new Work_Package() { createddate = DateTime.Now, id = -1 };

            try
            {
                IPFinalDBDataContext finalDB = new IPFinalDBDataContext();
                var requirement = (from wp in finalDB.Work_Packages
                                   where wp.id == id
                                   select wp).SingleOrDefault();
                return requirement;
            }
            catch
            {
                return null;
            }
        }

        public Work_Package InsertPackage(Work_Package wp)
        {
            wp.createddate = DateTime.Now;

            IPFinalDBDataContext finalDB = new IPFinalDBDataContext();
            var task = from w in finalDB.Work_Packages
                       where w.task_id == wp.task_id
                       select w.workorder;

            int maxOrder = 0;
            if (task != null && task.Count() > 0)
                maxOrder = task.Max<int>();
            wp.workorder = maxOrder + 5;
            finalDB.Work_Packages.InsertOnSubmit(wp);
            finalDB.SubmitChanges();

            return wp;
        }

        public Work_Package UpdatePackage(Work_Package wp)
        {
            IPFinalDBDataContext finalDB = new IPFinalDBDataContext();
            var package = (from d in finalDB.Work_Packages
                           where d.id == wp.id
                           select d).Single();

            package.description = wp.description;
            package.name = wp.name;
            package.status = wp.status;
            package.notes = wp.notes;
            finalDB.SubmitChanges();

            return package;
        }

        public Work_Package DeletePackage(int id)
        {

            IPFinalDBDataContext finalDB = new IPFinalDBDataContext();
            var requirement = (from wp in finalDB.Work_Packages
                               where wp.id == id
                               select wp).FirstOrDefault();
            finalDB.Work_Packages.DeleteOnSubmit(requirement);

            finalDB.SubmitChanges();
            return null;
        }


        public PackageRequirementsModel GetPackageRequirementsInfo(int id)
        {
            PackageRequirementsModel prm = new PackageRequirementsModel();
            IPFinalDBDataContext finalDB = new IPFinalDBDataContext();
            var req1 = from sr in finalDB.Software_Requirements
                       join ps in finalDB.Package_Softwares
                       on sr.id equals ps.sr_id
                       where ps.wp_id == id
                       select new Software_Requirement
                       {
                           id = sr.id,
                           title = sr.title
                       };
            if (req1 != null) prm.Selected = req1.ToList();

            var req2 = from sr in finalDB.Software_Requirements
                       join ps in finalDB.Package_Softwares
                       on sr.id equals ps.sr_id
                       where ps.wp_id == id
                       select new Software_Requirement
                       {
                           id = sr.id,
                           title = sr.title
                       };

            //Not Completed...
            return null;

        }

        public IList<SelectedPakcagesResult> SelectedPackages(int id)
        {

            IPFinalDBDataContext finalDB = new IPFinalDBDataContext();

            return finalDB.SelectedPakcages(id).ToList<SelectedPakcagesResult>();
        }


        public bool UpdateRequirements(int id, List<Package_Software> reqs)
        {
           // try
            //{
                IPFinalDBDataContext finalDB = new IPFinalDBDataContext();
                finalDB.DeletePackageSoftware(id);

                foreach (Package_Software item in reqs)
                {
                    finalDB.Package_Softwares.InsertOnSubmit(item);
                }

                finalDB.SubmitChanges();

                return true;
            //}
            //catch { return false; }
        }
    }
}