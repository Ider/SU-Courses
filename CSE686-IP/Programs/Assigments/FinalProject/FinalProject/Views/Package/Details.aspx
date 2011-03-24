﻿<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<FinalProject.Models.Work_Package>" %>

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
            id</div>
        <div class="display-field">
            <%: Model.id %></div>
        <div class="display-label">
            name</div>
        <div class="display-field">
            <%: Model.name %></div>
        <div class="display-label">
            task_id</div>
        <div class="display-field">
            <%: Model.task_id %></div>
        <div class="display-label">
            status</div>
        <div class="display-field">
            <%: Model.status %></div>
        <div class="display-label">
            notes</div>
        <div class="display-field">
            <%: Model.notes %></div>
        <div class="display-label">
            workorder</div>
        <div class="display-field">
            <%: Model.workorder %></div>
        <div class="display-label">
            createddate</div>
        <div class="display-field">
            <%: String.Format("{0:g}", Model.createddate) %></div>
        <fieldset>
            <legend>Description</legend>
            <div class="display-field">
                <%: Model.description %></div>
        </fieldset>
        <fieldset>
            <legend>Software Requirements</legend>
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
                        foreach (Package_Software ps in Model.Package_Software)
                        {
                            var r = ps.Software_Requirement;
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
        </fieldset>
    </fieldset>
    <p>
        <%: Html.ActionLink("Edit", "Edit", new { id=Model.id }) %>
        |
        <%: Html.ActionLink("Back to List", "Index") %>
    </p>
</asp:Content>