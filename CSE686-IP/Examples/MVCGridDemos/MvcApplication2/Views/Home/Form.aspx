<%@ Page Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<MvcApplication2.Models.FormModel>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
    Home Page
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">

<!--
  ///////////////////////////////////////////////////////////////
  // Form.aspx - View to display Form with postback            //
  //                                                           //
  // Jim Fawcett, CSE686 - Internet Programming, Summer 2010   //
  ///////////////////////////////////////////////////////////////

  Strongly type views derive from ViewPage parameterized on the Model,
  in this case: MvcApplication2.Models.FormModel (see Page directive
  at top of this page).

  This view is typed to accept a FormModel.
  
  http://www.howmvcworks.net/OnViews/BuildingAStronglyTypedView
-->

    <h2><%: 
          ViewData["Message"] 
          %></h2>
    <p/>
      <% using (Html.BeginForm("Form", "Home"))  // args are method, controller
         { %> 
           <div class="content">
             <table>
               <tr><th>Parameter</th><th>Value</th></tr>
               <tr>
                 <td>Name:</td><td><%= Html.TextBox(Html.Encode("Name"))%></td>
               </tr>
               <tr>
                 <td>Email:</td><td><%= Html.TextBox(Html.Encode("Email"))%></td>
               </tr>
               <tr>
                 <td>Phone:</td><td><%= Html.TextBox(Html.Encode("Phone"))%></td>
               </tr>
             </table>
             <input type="submit" value="Submit Form's Data"/>
             <!--
               The text value of each TextBox will be bound to a property on
               the Form model, based on matching the Encode string to the name
               of a public property of the model.
             -->
             <%              
               if (Request.ContentLength > 0)
               {
                 if ((bool)ViewData["NameError"]) Response.Write("<br/>Please enter name");
                 else if ((bool)ViewData["EmailError"]) Response.Write("<br/>Please enter valid email");
                 else if ((bool)ViewData["PhoneError"]) Response.Write("<br/>Please enter phone number");

                 // Model holds the instance passed to View() its controller
                 else Response.Write("  Server received post from " + Model.Name);
               } 
             %>
             <p />
           </div>
      <% } %>
    <p/>
  
</asp:Content>
