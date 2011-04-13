﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.1
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace FinalProject.FinalService {
    using System.Runtime.Serialization;
    using System;
    
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "4.0.0.0")]
    [System.Runtime.Serialization.DataContractAttribute(Name="BugReport", Namespace="http://schemas.datacontract.org/2004/07/WCFService.Models")]
    [System.SerializableAttribute()]
    public partial class BugReport : object, System.Runtime.Serialization.IExtensibleDataObject, System.ComponentModel.INotifyPropertyChanged {
        
        [System.NonSerializedAttribute()]
        private System.Runtime.Serialization.ExtensionDataObject extensionDataField;
        
        [System.Runtime.Serialization.OptionalFieldAttribute()]
        private FinalProject.FinalService.Comment[] CommentsField;
        
        [System.Runtime.Serialization.OptionalFieldAttribute()]
        private string ComponentField;
        
        [System.Runtime.Serialization.OptionalFieldAttribute()]
        private string DescriptionField;
        
        [System.Runtime.Serialization.OptionalFieldAttribute()]
        private string KeywordsField;
        
        [System.Runtime.Serialization.OptionalFieldAttribute()]
        private int NumberField;
        
        [System.Runtime.Serialization.OptionalFieldAttribute()]
        private string OwnedByField;
        
        [System.Runtime.Serialization.OptionalFieldAttribute()]
        private string ReportedByField;
        
        [System.Runtime.Serialization.OptionalFieldAttribute()]
        private System.DateTime ReportedTimeField;
        
        [global::System.ComponentModel.BrowsableAttribute(false)]
        public System.Runtime.Serialization.ExtensionDataObject ExtensionData {
            get {
                return this.extensionDataField;
            }
            set {
                this.extensionDataField = value;
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute()]
        public FinalProject.FinalService.Comment[] Comments {
            get {
                return this.CommentsField;
            }
            set {
                if ((object.ReferenceEquals(this.CommentsField, value) != true)) {
                    this.CommentsField = value;
                    this.RaisePropertyChanged("Comments");
                }
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute()]
        public string Component {
            get {
                return this.ComponentField;
            }
            set {
                if ((object.ReferenceEquals(this.ComponentField, value) != true)) {
                    this.ComponentField = value;
                    this.RaisePropertyChanged("Component");
                }
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute()]
        public string Description {
            get {
                return this.DescriptionField;
            }
            set {
                if ((object.ReferenceEquals(this.DescriptionField, value) != true)) {
                    this.DescriptionField = value;
                    this.RaisePropertyChanged("Description");
                }
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute()]
        public string Keywords {
            get {
                return this.KeywordsField;
            }
            set {
                if ((object.ReferenceEquals(this.KeywordsField, value) != true)) {
                    this.KeywordsField = value;
                    this.RaisePropertyChanged("Keywords");
                }
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute()]
        public int Number {
            get {
                return this.NumberField;
            }
            set {
                if ((this.NumberField.Equals(value) != true)) {
                    this.NumberField = value;
                    this.RaisePropertyChanged("Number");
                }
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute()]
        public string OwnedBy {
            get {
                return this.OwnedByField;
            }
            set {
                if ((object.ReferenceEquals(this.OwnedByField, value) != true)) {
                    this.OwnedByField = value;
                    this.RaisePropertyChanged("OwnedBy");
                }
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute()]
        public string ReportedBy {
            get {
                return this.ReportedByField;
            }
            set {
                if ((object.ReferenceEquals(this.ReportedByField, value) != true)) {
                    this.ReportedByField = value;
                    this.RaisePropertyChanged("ReportedBy");
                }
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute()]
        public System.DateTime ReportedTime {
            get {
                return this.ReportedTimeField;
            }
            set {
                if ((this.ReportedTimeField.Equals(value) != true)) {
                    this.ReportedTimeField = value;
                    this.RaisePropertyChanged("ReportedTime");
                }
            }
        }
        
        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;
        
        protected void RaisePropertyChanged(string propertyName) {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if ((propertyChanged != null)) {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "4.0.0.0")]
    [System.Runtime.Serialization.DataContractAttribute(Name="Comment", Namespace="http://schemas.datacontract.org/2004/07/WCFService.Models")]
    [System.SerializableAttribute()]
    public partial class Comment : object, System.Runtime.Serialization.IExtensibleDataObject, System.ComponentModel.INotifyPropertyChanged {
        
        [System.NonSerializedAttribute()]
        private System.Runtime.Serialization.ExtensionDataObject extensionDataField;
        
        [System.Runtime.Serialization.OptionalFieldAttribute()]
        private string CommentedByField;
        
        [System.Runtime.Serialization.OptionalFieldAttribute()]
        private string ContentField;
        
        [System.Runtime.Serialization.OptionalFieldAttribute()]
        private System.DateTime DtaetimeField;
        
        [global::System.ComponentModel.BrowsableAttribute(false)]
        public System.Runtime.Serialization.ExtensionDataObject ExtensionData {
            get {
                return this.extensionDataField;
            }
            set {
                this.extensionDataField = value;
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute()]
        public string CommentedBy {
            get {
                return this.CommentedByField;
            }
            set {
                if ((object.ReferenceEquals(this.CommentedByField, value) != true)) {
                    this.CommentedByField = value;
                    this.RaisePropertyChanged("CommentedBy");
                }
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute()]
        public string Content {
            get {
                return this.ContentField;
            }
            set {
                if ((object.ReferenceEquals(this.ContentField, value) != true)) {
                    this.ContentField = value;
                    this.RaisePropertyChanged("Content");
                }
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute()]
        public System.DateTime Dtaetime {
            get {
                return this.DtaetimeField;
            }
            set {
                if ((this.DtaetimeField.Equals(value) != true)) {
                    this.DtaetimeField = value;
                    this.RaisePropertyChanged("Dtaetime");
                }
            }
        }
        
        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;
        
        protected void RaisePropertyChanged(string propertyName) {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if ((propertyChanged != null)) {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }
    
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]
    [System.ServiceModel.ServiceContractAttribute(ConfigurationName="FinalService.IFinalWCFService")]
    public interface IFinalWCFService {
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IFinalWCFService/DoWork", ReplyAction="http://tempuri.org/IFinalWCFService/DoWorkResponse")]
        string DoWork();
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IFinalWCFService/GetBugReportByID", ReplyAction="http://tempuri.org/IFinalWCFService/GetBugReportByIDResponse")]
        FinalProject.FinalService.BugReport GetBugReportByID(int id);
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IFinalWCFService/InsertBugReport", ReplyAction="http://tempuri.org/IFinalWCFService/InsertBugReportResponse")]
        bool InsertBugReport(FinalProject.FinalService.BugReport br);
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IFinalWCFService/UpdateBugReport", ReplyAction="http://tempuri.org/IFinalWCFService/UpdateBugReportResponse")]
        bool UpdateBugReport(FinalProject.FinalService.BugReport br);
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IFinalWCFService/DeleteBugReport", ReplyAction="http://tempuri.org/IFinalWCFService/DeleteBugReportResponse")]
        bool DeleteBugReport(int id);
    }
    
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]
    public interface IFinalWCFServiceChannel : FinalProject.FinalService.IFinalWCFService, System.ServiceModel.IClientChannel {
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]
    public partial class FinalWCFServiceClient : System.ServiceModel.ClientBase<FinalProject.FinalService.IFinalWCFService>, FinalProject.FinalService.IFinalWCFService {
        
        public FinalWCFServiceClient() {
        }
        
        public FinalWCFServiceClient(string endpointConfigurationName) : 
                base(endpointConfigurationName) {
        }
        
        public FinalWCFServiceClient(string endpointConfigurationName, string remoteAddress) : 
                base(endpointConfigurationName, remoteAddress) {
        }
        
        public FinalWCFServiceClient(string endpointConfigurationName, System.ServiceModel.EndpointAddress remoteAddress) : 
                base(endpointConfigurationName, remoteAddress) {
        }
        
        public FinalWCFServiceClient(System.ServiceModel.Channels.Binding binding, System.ServiceModel.EndpointAddress remoteAddress) : 
                base(binding, remoteAddress) {
        }
        
        public string DoWork() {
            return base.Channel.DoWork();
        }
        
        public FinalProject.FinalService.BugReport GetBugReportByID(int id) {
            return base.Channel.GetBugReportByID(id);
        }
        
        public bool InsertBugReport(FinalProject.FinalService.BugReport br) {
            return base.Channel.InsertBugReport(br);
        }
        
        public bool UpdateBugReport(FinalProject.FinalService.BugReport br) {
            return base.Channel.UpdateBugReport(br);
        }
        
        public bool DeleteBugReport(int id) {
            return base.Channel.DeleteBugReport(id);
        }
    }
}