<%@ Page Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
    Home Page
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
<!--
  ///////////////////////////////////////////////////////////////
  // Index.aspx - View to display Home page                    //
  //                                                           //
  // Jim Fawcett, CSE686 - Internet Programming, Summer 2010   //
  ///////////////////////////////////////////////////////////////

-->
    <h2><%: ViewData["Message"] %></h2>
    <p>
      <h3>Steps to map Wizard's solution into this application:</h3>
        <ol>
          <li>Removed Account controller, Account model folders</li>
          <li>Removed Login control from Site.Master</li>
          <li>Changed text in Index.aspx placeholders</li>
          <li>Changed Site.css styles to suit my tastes</li>
          <li>Added additional tabs for future pages</li>
          <li>Added one Aspx file for each new tab, with placeholder content</li>
          <li>Added Controller methods to load each page</li>
        </ol>
    </p>
</asp:Content>
