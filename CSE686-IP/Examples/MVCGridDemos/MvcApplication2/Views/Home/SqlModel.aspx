<%@ Page Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<MvcApplication2.Models.CharacterDataDataContext>" %>
<%@ Import Namespace="MvcApplication2.Models" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
    Home Page
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
<!--
  ///////////////////////////////////////////////////////////////
  // SqlModel.aspx - View to display data from an SQL database //
  //                                                           //
  // Jim Fawcett, CSE686 - Internet Programming, Summer 2010   //
  ///////////////////////////////////////////////////////////////

  http://www.asp.net/mvc/videos/displaying-a-table-of-database-data
  http://www.asp.net/mvc/tutorials/creating-model-classes-with-linq-to-sql-cs
  http://msdn.microsoft.com/en-us/library/bb425822.aspx
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
        foreach (CharacterTable c in (IEnumerable)(Model.CharacterTables))
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
