<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<IList<FinalProject.Models.Software_Requirement>>" %>

<%@ Import Namespace="FinalProject.Models" %>
<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
    Index
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    <h2>
        Software Requirement is under construction...</h2>
    <br />
    <br />
    <div>
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
                    foreach (Software_Requirement r in Model)
                    { %>
                <tr id="row-<%:r.id %>">
                    <td>
                        <%= Html.ActionLink(r.title,"Details",new{id=r.id},null)%>
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
    <br />
    <br />
    <h3>
        Data and Controls</h3>
    <div>
        RoleModel, RoleControllers, RequirementModel, RequirementListModel, RequirementControllers,
        PackageModel, PackageControllers
    </div>
</asp:Content>
