<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<dynamic>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
    Index
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    <h2>
        Work Package is under construction...</h2>
    <br />
    <br />
    <div>
        In this page, Work Packages informations will be displayed in a list.<br />
        When user pass a specific number, the Work package use this number as ID will be
        displayed. If no such Work Package, an error message will be showed on page to tell
        user can not find the package.<br />
        The page will also direct user to create/edit work paeckage, and user can also delete
        a work package.
    </div>
    <br />
    <h3>
        Data and Controls</h3>
    <div>
        RoleModel, RoleControllers, PackageModel, PackageListModel, PackageControllers,
    </div>
</asp:Content>
