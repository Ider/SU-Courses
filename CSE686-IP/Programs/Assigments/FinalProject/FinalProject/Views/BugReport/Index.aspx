<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<FinalProject.Models.BugListModel>" %>

<%@ Import Namespace="FinalProject.Models" %>
<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
    Bug Report
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    <div class="caption">
        <%: ViewData["Message"] %>
    </div>
    <table width="100%" border="0" align="left" cellpadding="5" cellspacing="0" class="map">
        <thead>
            <tr>
                <td>
                    Number
                </td>
                <td>
                    ReportedBy
                </td>
                <td>
                    OwnedBy
                </td>
                <td>
                    Keywords
                </td>
                <td>
                    Description
                </td>
            </tr>
        </thead>
        <tbody>
            <%
                foreach (BugReport r in Model.Reports)
                { %>
            <tr>
                <td>
                    <%= r.Number %>
                </td>
                <td>
                    <%= r.ReportedBy%>
                </td>
                <td>
                    <%= r.OwnedBy%>
                </td>
                <td>
                    <%= r.Keywords%>
                </td>
                <td>
                    <%= r.Description%>
                </td>
            </tr>
            <% } %>
        </tbody>
    </table>
    <div>
        &nbsp;
    </div>
</asp:Content>
