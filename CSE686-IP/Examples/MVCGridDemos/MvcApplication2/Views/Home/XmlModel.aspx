<%@ Page Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<MvcApplication2.Models.CharacterModel>" %>
<%@ Import Namespace="MvcApplication2.Models" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
    Home Page
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
<!--
  ///////////////////////////////////////////////////////////////
  // XmlModel.aspx - View to display data from an XML file     //
  //                                                           //
  // Jim Fawcett, CSE686 - Internet Programming, Summer 2010   //
  ///////////////////////////////////////////////////////////////

  http://www.howmvcworks.net/OnViews/BuildingAStronglyTypedView 
  http://weblogs.asp.net/scottgu/archive/2007/08/07/using-linq-to-xml-and-how-to-build-a-custom-rss-feed-reader-with-it.aspx
-->
    <h2><%: ViewData["Message"] %></h2>
    <p/>
    <div class="content">
      <table>
        <tr>
          <th colspan="3">Your Favorite Characters</th>
        </tr>
        <tr>
          <th>Name</th><th>Occupation</th><th>Location</th>
        </tr>
      <%
        foreach (Character c in Model.Characters)
        { %>
          <tr>
            <td><%= c.Name %></td>
            <td><%= c.Occupation %></td>
            <td><%= c.Location %></td>
          </tr>      
      <% } %>
      </table>
    </div>
    <p/>
</asp:Content>
