<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<FinalProject.Models.BugReport>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
    Edit
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    <% if (Model == null)
       { %>
    <span class="error">Can't Find Bug Report!</span>
    <div>
        <%: Html.ActionLink("Back to List", "Index") %>
    </div>
    <% return;
       } %>
    <h2>
        <%:(Model.Number <= 0?"Create":"Edit") %></h2>
    <% using (Html.BeginForm())
       {%>
    <%: Html.ValidationSummary(true) %>
    <fieldset>
        <legend>Bug Report</legend>
        <div class="editor-label">
            <%: Html.LabelFor(model => model.ReportedBy) %>
        </div>
        <div class="editor-field">
            <%: Html.TextBoxFor(model => model.ReportedBy) %>
            <%: Html.ValidationMessageFor(model => model.ReportedBy) %>
        </div>
        <div class="editor-label">
            <%: Html.LabelFor(model => model.OwnedBy) %>
        </div>
        <div class="editor-field">
            <%: Html.TextBoxFor(model => model.OwnedBy) %>
            <%: Html.ValidationMessageFor(model => model.OwnedBy) %>
        </div>
        <div class="editor-label">
            <%: Html.LabelFor(model => model.Component) %>
        </div>
        <div class="editor-field">
            <%: Html.TextBoxFor(model => model.Component) %>
            <%: Html.ValidationMessageFor(model => model.Component) %>
        </div>
        <div class="editor-label">
            <%: Html.LabelFor(model => model.Keywords) %>
        </div>
        <div class="editor-field">
            <%: Html.TextBoxFor(model => model.Keywords) %>
            <%: Html.ValidationMessageFor(model => model.Keywords) %>
        </div>
        <div class="editor-label">
            <%: Html.LabelFor(model => model.ReportedTime) %>
        </div>
        <div class="editor-label">
            <%: Html.LabelFor(model => model.Description) %>
        </div>
        <div class="editor-field">
            <%: Html.TextBoxFor(model => model.Description) %>
            <%: Html.ValidationMessageFor(model => model.Description) %>
        </div>
        <p>
            <input type="submit" value="Save" />
        </p>
    </fieldset>
    <% } %>
    <div>
        <%: Html.ActionLink("Back to List", "Index") %>
    </div>
</asp:Content>
