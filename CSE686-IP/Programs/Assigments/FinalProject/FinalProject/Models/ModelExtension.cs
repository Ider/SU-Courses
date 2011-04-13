using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Web.Mvc;
using System.Collections.Generic;
using System;

namespace FinalProject.Models
{
    public enum WorkStatus
    {
        Planing = 0,
        Doing = 1,
        Finish = 2,
        Pending = 3,
        Closed = 4,
        NotSet = 5,
        Success = 6,
        Failure = 7
    }

    public partial class Work_Package
    {
        public WorkStatus Status
        {
            get { return (WorkStatus)_status; }
        }

        public int RequirementCount
        {
            get
            {
                if (_Package_Softwares.Count > 0)
                {
                    return _Package_Softwares.Count;
                }
                else return _RequirementsCount;
            }
            set
            {
                _RequirementsCount = value;
            }
        }

        private int _RequirementsCount = 0;



    }


}