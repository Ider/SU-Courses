<%@ Page Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage" %>

<asp:Content ID="aboutTitle" ContentPlaceHolderID="TitleContent" runat="server">
    About Us
</asp:Content>
<asp:Content ID="aboutContent" ContentPlaceHolderID="MainContent" runat="server">
    <div class="caption">
        Layout
    </div>
    <div id="dialog" title="Upload files">
        <% using (Html.BeginForm("Upload", "Home", FormMethod.Post, new { enctype = "multipart/form-data" }))
           {%><br />
        <p>
            <input type="file" id="fileUpload" name="fileUpload" size="23" />
            ;</p>
        <br />
        <p>
            <input type="submit" value="Upload file" /></p>
        <% } %>
    </div>

    <div>
        &nbsp;
    </div>
</asp:Content>
