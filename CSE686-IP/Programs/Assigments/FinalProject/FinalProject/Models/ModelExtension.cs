using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Web.Mvc;

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
    }
}