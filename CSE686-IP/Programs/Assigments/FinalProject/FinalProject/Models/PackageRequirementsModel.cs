
using System.Collections.Generic;

namespace FinalProject.Models
{
    public class PackageRequirementsModel
    {
        public List<Software_Requirement> Selected { get; set; }
        public List<Software_Requirement> UnSelected { get; set; }
    }
}