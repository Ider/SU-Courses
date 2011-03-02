<%@ Page Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<MvcApplication2.Models.FileHandler>" %>
<%@ Import Namespace="MvcApplication2.Models" %>

<asp:Content ID="aboutTitle" ContentPlaceHolderID="TitleContent" runat="server">
    About Us
</asp:Content>

<asp:Content ID="aboutContent" ContentPlaceHolderID="MainContent" runat="server">
<!--
  ///////////////////////////////////////////////////////////////
  // About.aspx - View to display About page                   //
  //              Displays files in current virtual directory  //
  //                                                           //
  // Jim Fawcett, CSE686 - Internet Programming, Summer 2010   //
  ///////////////////////////////////////////////////////////////

-->
    <h2>Demo Application</h2>
    <%
      try {
        string[] files = Model.files;
        Response.Write("<h3>Find Files in Home Controller's Views Folder</h3>");
        foreach (string file in files)
          Response.Write(file + "<br/>");

        string path = Model.path;
        System.IO.FileInfo fi = new System.IO.FileInfo(path + "\\Index.Aspx");
        Response.Write("<p/>Index.Aspx Last Revised: " + fi.LastAccessTime.ToString());
      }
      catch { Response.Write("<p/>Error finding path or file"); }
    %>
    <p>
        This application is intended to host a set of tutorial demos for Asp.Net MVC.
        Each Tab will open a new demo example.  Eventually I will segregate them into 
        demo categories with a controller for each category.
    </p>
</asp:Content>
