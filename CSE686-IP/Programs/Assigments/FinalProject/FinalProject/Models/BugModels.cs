using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Runtime.Serialization;


namespace FinalProject.Models
{
    [Serializable]
    [DataContract]
    public class BugReport
    {
        [DataMember]
        public int Number { get; set; }
        [DataMember]
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