using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Xml.Linq;
using FinalProject.Helper;
using FinalProject.Models;

namespace FinalProject.Services
{
    public class RequirementService
    {
        //revise this class to be singleton

        public IEnumerable<Software_Requirement> GetRequirements()
        {
            IPFinalDBDataContext finalDB = new IPFinalDBDataContext();
            var list = (from sr in finalDB.Software_Requirements
                        select sr).ToList();
            return list;
        }

        public Software_Requirement GetRequirementByID(int id)
        {
            if (id <= 0) return new Software_Requirement() { createddate = DateTime.Now };

            IPFinalDBDataContext finalDB = new IPFinalDBDataContext();
            var requirement = (from sr in finalDB.Software_Requirements
                               where sr.id == id
                               select sr).Single();
            return requirement;
        }

        public Software_Requirement InsertRequirement(Software_Requirement sr)
        {
            sr.createddate = DateTime.Now;

            IPFinalDBDataContext finalDB = new IPFinalDBDataContext();
            finalDB.Software_Requirements.InsertOnSubmit(sr);

            finalDB.SubmitChanges();

            return sr;
        }

        public Software_Requirement UpdateRequirement(Software_Requirement sr)
        {
            IPFinalDBDataContext finalDB = new IPFinalDBDataContext();
            var requirement = (from d in finalDB.Software_Requirements
                               where d.id == sr.id
                               select d).Single();

            requirement.description = sr.description;
            requirement.platform = sr.platform;
            requirement.title = sr.title;
            finalDB.SubmitChanges();

            return requirement;
        }

        public Software_Requirement DeleteRequirement(int id)
        {

            IPFinalDBDataContext finalDB = new IPFinalDBDataContext();
            var requirement = (from sr in finalDB.Software_Requirements
                               where sr.id == id
                               select sr).Single();
            finalDB.Software_Requirements.DeleteOnSubmit(requirement);

            finalDB.SubmitChanges();
            return null;
        }
    }
}