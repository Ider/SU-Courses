<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<FinalProject.Models.Software_Requirement>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
    Details
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    <h2>
        Details</h2>
    <fieldset>
        <legend>Software Requirements</legend>
        <div class="display-label">
            Title:</div>
        <div class="display-field">
            <%: Model.title %></div>
        <div class="display-label">
            Date:</div>
        <div class="display-field">
            <%: String.Format("{0:g}", Model.createddate) %></div>
        <fieldset>
            <legend>Description</legend>
            <div class="display-field">
                <%: Model.description %></div>
        </fieldset>
    </fieldset>
    <p>
        <%: Html.ActionLink("Edit", "Edit", new { id=Model.id }) %>
        |
        <%: Html.ActionLink("Delete", "Delete", new { id=Model.id }) %>
        |
        <%: Html.ActionLink("Back to List", "Index") %>
    </p>
</asp:Content>
