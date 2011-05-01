using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Runtime.Serialization;
using System.ComponentModel.DataAnnotations;


namespace FinalProject.Models
{
    [Serializable]
    [DataContract]
    [MetadataType(typeof(BugReportMD))]
    public class BugReport
    {
        [DataMember]

        public int Number { get; set; }
        [DataMember]
        [Required]
        public string ReportedBy { get; set; }
        [DataMember]
        public string OwnedBy { get; set; }
        [DataMember]
        public string Component { get; set; }
        [DataMember]
        public string Keywords { get; set; }
        [DataMember]
        public DateTime ReportedTime { get; set; }
        [DataMember]
        public string Description { get; set; }
        [DataMember]
        public IList<Comment> Comments { get; set; }


        public class BugReportMD
        {
            public int Number { get; set; }
            public string ReportedBy { get; set; }
            [Required(ErrorMessage = "Bug report owner should be specified.")]
            public string OwnedBy { get; set; }
            public string Component { get; set; }
            [Required(ErrorMessage = "Please add at least one keyword.")]
            public string Keywords { get; set; }
            public DateTime ReportedTime { get; set; }
            public string Description { get; set; }
        }

    }

    [Serializable]
    [DataContract]
    public class Comment
    {
        [DataMember]
        public string CommentedBy { get; set; }
        [DataMember]
        public DateTime Dtaetime { get; set; }
        [DataMember]
        public string Content { get; set; }
    }

}