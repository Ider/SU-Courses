<%@ Page Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<MvcApplication2.Models.GridModel>" %>
<%@ Import Namespace="MvcApplication2.Models" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
    Home Page
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
<!--
  ///////////////////////////////////////////////////////////////
  // Grid.aspx - View to display Editable Grid of SQL data     //
  //                                                           //
  // Jim Fawcett, CSE686 - Internet Programming, Summer 2010   //
  ///////////////////////////////////////////////////////////////
-->
    <h2><%: ViewData["Message"] %></h2>
    <p/>
    <% using (Html.BeginForm("Grid", "Home"))
       { %>
    <div class="content">
      <table>
        <tr>
          <th colspan="5">Your Favorite Characters</th>
        </tr>
        <tr>
          <th>Name</th><th>Occupation</th><th>Location</th><th>Edit</th><th>Delete</th>
        </tr>
      <%
        string debug = "";
        //foreach (GridCharacter c in Model.Characters)
        for(int i=0; i<Model.Characters.Count; ++i)
        { 
          %>
          <tr>
            <td><%= Model.Characters[i].Name%></td>
            <td><%= Model.Characters[i].Occupation%></td>
            <td><%= Model.Characters[i].Location%></td>
            <td><%= Html.ActionLink("Edit", "Edit", new { id = i })%></td>
            <td><%= Html.ActionLink("Delete", "Delete", new { id = i })%></td>
          </tr>
        <% } %>
      </table>
    </div>
    <% } %>
    <p/>
    <% using (Html.BeginForm("Insert", "Home"))
       { %>
    <div class="content">
      <table>
        <tr>
          <td><%= Html.TextBox("Name") %></td>
          <td><%= Html.TextBox("Occupation") %></td>
          <td><%= Html.TextBox("Location") %></td>
          <td><input type="submit" value="Insert" /></td>
        </tr>
      </table>
    </div>
    <% } %>

</asp:Content>
