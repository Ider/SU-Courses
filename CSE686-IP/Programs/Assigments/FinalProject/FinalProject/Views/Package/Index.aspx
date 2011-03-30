<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<IEnumerable<FinalProject.Models.Work_Package>>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
    Index
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    <h2>
        Work Pakcages</h2>
    <table width="100%" border="0" align="left" cellpadding="5" cellspacing="0" class="map">
        <thead>
            <tr>
                <td>
                    Name
                </td>
                <td>
                    Task_id
                </td>
                <td>
                    Status
                </td>
                <td>
                    Work Order
                </td>
                <td>
                    Package Count
                </td>
            </tr>
        </thead>
        <% foreach (var item in Model)
           { %>
        <tr>
            <td>
                <%: Html.ActionLink(item.name, "Details", new { id=item.id })%>
            </td>
            <td>
                <%: item.task_id %>
            </td>
            <td>
                <%: item.Status.ToString() %>
            </td>
            <td>
                <%: item.workorder %>
            </td>
            <td>
                <%: item.RequirementCount%>
            </td>
        </tr>
        <% } %>
    </table>
    <p>
        <%: Html.ActionLink("Create New", "Create") %>
    </p>
</asp:Content>
