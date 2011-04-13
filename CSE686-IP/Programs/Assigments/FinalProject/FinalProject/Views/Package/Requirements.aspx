<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<PackageRequirementsModel>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
    Requirements
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    <h2>
        Requirements</h2>
    <table>
        <tr>
            <th>
                Selected
            </th>
            <th>
                title
            </th>
            <th>
                createddate
            </th>
            <th>
                platform
            </th>
            <th>
                description
            </th>
        </tr>
        <% foreach (var item in Model.Selected) { %>
        <tr>
            <td>
                <%: Html.ActionLink("Edit", "Edit", new { id=item.id }) %>
                |
                <%: Html.ActionLink("Details", "Details", new { id=item.id })%>
                |
                <%:Html.%>
            </td>
            <td>
                <%: item.id %>
            </td>
            <td>
                <%: item.title %>
            </td>
            <td>
                <%: String.Format("{0:g}", item.createddate) %>
            </td>
            <td>
                <%: item.platform %>
            </td>
            <td>
                <%: item.description %>
            </td>
        </tr>
        <% } %>
    </table>
    <p>
        <%: Html.ActionLink("Create New", "Create") %>
    </p>
</asp:Content>
