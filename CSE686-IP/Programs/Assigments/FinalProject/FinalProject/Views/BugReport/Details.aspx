<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<FinalProject.Models.BugReport>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
    Details
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    <div class="caption">
        Details
    </div>
    <fieldset>
        <legend>Fields</legend>
        <div class="display-label">
            Number</div>
        <div class="display-field">
            #<%: Model.Number %></div>
        <div class="display-label">
            ReportedBy</div>
        <div class="display-field">
            <%: Model.ReportedBy %></div>
        <div class="display-label">
            OwnedBy</div>
        <div class="display-field">
            <%: Model.OwnedBy %></div>
        <div class="display-label">
            Component</div>
        <div class="display-field">
            <%: Model.Component %></div>
        <div class="display-label">
            Keywords</div>
        <div class="display-field">
            <%: Model.Keywords %></div>
        <div class="display-label">
            ReportedTime</div>
        <div class="display-field">
            <%: String.Format("{0:g}", Model.ReportedTime) %></div>
        <div class="display-label">
            Description</div>
        <div class="display-field">
            <%: Model.Description %></div>
    </fieldset>
    <p>
        <%: Html.ActionLink("Edit", "Edit", new { id = Model.Number })%>
        |
        <%: Html.ActionLink("Back to List", "Index") %>
    </p>
</asp:Content>
