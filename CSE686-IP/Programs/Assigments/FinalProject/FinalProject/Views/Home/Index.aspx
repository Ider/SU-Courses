<%@ Page Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
    Home Page
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    <h2>
        <%: ViewData["Message"] %></h2>
    <p>
        To learn more about ASP.NET MVC visit <a href="http://asp.net/mvc" title="ASP.NET MVC Website">
            http://asp.net/mvc</a>.
    </p>
    <ul>
        <li>
            <%: Html.ActionLink("Software Requirement", "Index", "Requirement")%></li>
        <li>
            <%: Html.ActionLink("Work Package","Index", "Package")%></li>
        <li>
            <%: Html.ActionLink("Bug Report","Index", "BugReport")%></li>
        <li>
            <%: Html.ActionLink("Status Report","Index", "Status")%></li>
        <%--<li><%: Html.ActionLink("Layout", "Layout", "Home")%></li>--%>
    </ul>
</asp:Content>
