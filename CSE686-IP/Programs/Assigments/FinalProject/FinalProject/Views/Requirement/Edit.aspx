<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<FinalProject.Models.Software_Requirement>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
    Edit
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    <% if (Model == null)
       { %>
    <span class="error">Can't Find Software Requirement!</span>
    <div>
        <%: Html.ActionLink("Back to List", "Index") %>
    </div>
    <% return;
       } %>
    <h2>
        <%:(Model.id <= 0?"Create":"Edit") %></h2>
    <% using (Html.BeginForm())
       {%>
    <%: Html.ValidationSummary(true) %>
    <fieldset>
        <legend>Software Requirement</legend>
        <div class="editor-label">
            Titilt
        </div>
        <div class="editor-field">
            <%: Html.TextBoxFor(model => model.title) %>
            <%: Html.ValidationMessageFor(model => model.title) %>
        </div>
        <div class="editor-label">
            Create Date
        </div>
        <div class="display-field">
            <%:String.Format("{0:MM/dd/yyyy}", Model.createddate)%>
        </div>
        <div class="editor-label">
            Platform
        </div>
        <div class="editor-field">
            <%: Html.TextBoxFor(model => model.platform) %>
            <%: Html.ValidationMessageFor(model => model.platform) %>
        </div>
        <div class="editor-label">
            Description
        </div>
        <div class="editor-field">
            <%: Html.TextAreaFor(model => model.description, 10, 100, null)%>
            <%: Html.ValidationMessageFor(model => model.description) %>
        </div>
        <p>
            <input type="submit" value="Save" />
        </p>
    </fieldset>
    <% } %>
    <div>
        <%:  Model.id <= 0 ?
        Html.ActionLink("Back to List", "Index")
        : Html.ActionLink("Back to Details", "Details", new { id = Model.id})%>
    </div>
</asp:Content>
