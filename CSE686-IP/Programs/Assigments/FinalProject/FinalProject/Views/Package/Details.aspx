<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<FinalProject.Models.Work_Package>" %>

<%@ Import Namespace="FinalProject.Models" %>
<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
    Details
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    <h2>
        Details</h2>
    <fieldset>
        <legend>Fields</legend>
        <div class="display-label">
            Name</div>
        <div class="display-field">
            <%: Model.name %></div>
        <div class="display-label">
           Task Id</div>
        <div class="display-field">
            <%: Model.task_id %></div>
        <div class="display-label">
            Status</div>
        <div class="display-field">
            <%: Model.status %></div>
        <div class="display-label">
            Notes</div>
        <div class="display-field">
            <%: Model.notes %></div>
        <div class="display-label">
            WorkOrder</div>
        <div class="display-field">
            <%: Model.workorder %></div>
        <div class="display-label">
            Createddate</div>
        <div class="display-field">
            <%: String.Format("{0:g}", Model.createddate) %></div>
        <fieldset>
            <legend>Description</legend>
            <div class="display-field">
                <%: Model.description %></div>
        </fieldset>
        <fieldset>
            <legend>Software Requirements</legend>
            <div style="margin-top: 5px;">
                <table width="100%" border="0" align="left" cellpadding="5" cellspacing="0" class="map">
                    <thead>
                        <tr>
                            <td>
                                Title
                            </td>
                            <td>
                                Platform
                            </td>
                            <td>
                                Createdate
                            </td>
                        </tr>
                    </thead>
                    <tbody>
                        <%
                            foreach (var p in Model.Package_Softwares)
                            {
                                var r = p.Software_Requirement;
                        %>
                        <tr id="row-<%:r.id %>">
                            <td>
                                <%= Html.ActionLink(r.title, "Details", "Requirement", new { id = r.id }, null)%>
                            </td>
                            <td>
                                <%: r.platform%>
                            </td>
                            <td>
                                <%= r.createddate%>
                            </td>
                        </tr>
                        <% } %>
                    </tbody>
                </table>
            </div>
            <div style="margin-top: 5px; clear:both;">
                <%: Html.ActionLink("Edit Software Requirements", "Requirements", new { id = Model.id })%>
            </div>
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
