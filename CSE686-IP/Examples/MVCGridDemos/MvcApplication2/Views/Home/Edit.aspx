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
    <% using (Html.BeginForm("Save", "Home"))
       { %>
    <div class="content">
      <table>
        <tr>
          <th colspan="4">Your Favorite Characters</th>
        </tr>
        <tr>
          <th>Name</th><th>Occupation</th><th>Location</th><th>Edit</th>
        </tr>
      <%
        string debug = "";
        //foreach (GridCharacter c in Model.Characters)
        for (int i = 0; i < Model.Characters.Count; ++i)
        {
          if (!Model.Characters[i].Checked)
          {
          %>
            <tr>
              <td><%= Model.Characters[i].Name%></td>
              <td><%= Model.Characters[i].Occupation%></td>
              <td><%= Model.Characters[i].Location%></td>
              <td><%= Html.ActionLink("Edit", "Edit", "Home")%></td>
            </tr>
          <% }
          else
          {
            Session["Selected"] = i;
          %>
            <tr>
             <td><%= Html.TextBox("Name", Model.Characters[i].Name) %></td>
             <td><%= Html.TextBox("Occupation", Model.Characters[i].Occupation) %></td>
             <td><%= Html.TextBox("Location", Model.Characters[i].Location) %></td>
             <td><input type="submit" value="Save" /></td>
           </tr>
         <%
          }
        }
      %>
      </table>
    </div>
      <% } %>
    <p/>
</asp:Content>
