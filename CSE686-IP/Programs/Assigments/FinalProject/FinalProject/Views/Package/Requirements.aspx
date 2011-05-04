<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<IEnumerable<FinalProject.Models.SelectedPakcagesResult>>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
    Requirements
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    <div class="caption">
        Softerware Requirements
    </div>
    <% using (Html.BeginForm())
       { %>
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
                    Selected
                </td>
            </tr>
        </thead>
        <% foreach (var item in Model)
           { %>
        <tr>
            <td>
                <%= Html.ActionLink(item.title, "Details", "Requirement", new { id = item.id }, null)%>
            </td>
            <td>
                <%: item.platform%>
            </td>
            <td style="width: 5%; text-align: center;">
                <input id="cb" type="checkbox" name="requirements" value="<%: item.id %>" <% if(item.selected??false) {%>checked="checked"
                    <%} %> />
            </td>
        </tr>
        <% } %>
    </table>
    <p>
        <input type="submit" value="Save" />
    </p>
    <%} %>

     <div>
        <%: Html.ActionLink("Back to Details", "Details", new { id = ViewData["WPid"]})%>
    </div>
</asp:Content>
