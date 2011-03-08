<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<dynamic>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	Index
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
<%= ViewData["Path"] %>
    <h2>Status Report is under construction...</h2>

      <br/>
    <br/>
    <div>

    In this page, Status Reports informations will be displayed in a list.<br/>
    When user pass a specific number, the Status Reports use this number as ID will be displayed. If no such
    Status Reports, an error message will be showed on page to tell user can not find the package.<br/>
    The page will also direct user to create/edit work paeckage, and user can also delete a Status Reports.
    </div>
      <br/>
    <br/>

  <h3>Data and Controls</h3> 
    <div>
    RoleModel, RoleControllers, StatusModel, StatusListModel, StatusControllers, BugReportModel, BugReportControllers
    </div>
</asp:Content>
