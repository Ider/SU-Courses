<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<List<FinalProject.Models.BugReport>>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
    Bug Report
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    <script src="../../Scripts/MicrosoftAjax.js" type="text/javascript"></script>
    <script src="../../Scripts/MicrosoftMvcAjax.js" type="text/javascript"></script>
    <script src="../../Scripts/jquery-1.4.1.min.js" type="text/javascript"></script>
    <script type="text/javascript">
        function handleUpdate(context) {
            // Load and deserialize the returned JSON data
            var json = context.get_data();
            var data = Sys.Serialization.JavaScriptSerializer.deserialize(json);
            // Update the page elements
            if (data.ID > 0) $('#row-' + data.ID).fadeOut('slow');

            $('#update-message').text(data.Message);
        }
    </script>
    <div class="caption">
        <%: ViewData["Message"] %>
    </div>
    <table width="100%" border="0" align="left" cellpadding="5" cellspacing="0" class="map">
        <thead>
            <tr>
                <td>
                    <%: Html.ActionLink("Number", "Sort"
                       , new { key = "Number", asc = System.Convert.ToBoolean(ViewData["OrderAsc"]) })%>
                </td>
                <td>
                    <%: Html.ActionLink("ReportedBy", "Sort"
                                            , new { key = "ReportedBy", asc = System.Convert.ToBoolean(ViewData["OrderAsc"]) })%>
                </td>
                <td>
                    <%: Html.ActionLink("OwnedBy", "Sort"
                                    , new { key = "OwnedBy", asc = System.Convert.ToBoolean(ViewData["OrderAsc"]) })%>
                </td>
                <td>
                    Keywords
                </td>
                <td>
                    <%: Html.ActionLink("ReportedTime", "Sort"
                                            , new { key = "ReportedTime", asc = System.Convert.ToBoolean(ViewData["OrderAsc"]) })%>
                </td>
                <% if (Page.User.IsInRole("Manager") || Page.User.IsInRole("Admin"))
                   {
                
                %>
                <td style="width: 20px;">
                    Edit
                </td>
                <td style="width: 20px;">
                    Delete
                </td>
                <%} %>
            </tr>
        </thead>
        <tbody>
            <%
                foreach (FinalProject.Models.BugReport r in Model)
                { %>
            <tr id="row-<%:r.Number %>">
                <td>
                    <%:Html.ActionLink("#" + r.Number, "Detail")%>
                </td>
                <td>
                    <%: r.ReportedBy%>
                </td>
                <td>
                    <%: r.OwnedBy%>
                </td>
                <td>
                    <%: r.Keywords%>
                </td>
                <td>
                    <%= r.ReportedTime.ToString("MM/dd/yyyy HH:mm:ss")%>
                </td>
                <% if (Page.User.IsInRole("Manager") || Page.User.IsInRole("Admin"))
                   {
                %>
                <td>
                    <%: Html.ActionLink("Edit", "Edit",
                    new { id = r.Number }, null)%>
                </td>
                <td>
                    <%: Ajax.ActionLink("Delete", "DeleteBugReport",
                                        new { id = r.Number }, 
                    new AjaxOptions { OnSuccess = "handleUpdate" })%>
                </td>
                <%} %>
            </tr>
            <% } %>
        </tbody>
    </table>
    <% if (Page.User.IsInRole("Admin"))
       { %>
    <div>
        <%: Html.ActionLink("Add", "Edit")%>
    </div>
    <%} %>
    <div id="update-message">
    </div>
</asp:Content>
