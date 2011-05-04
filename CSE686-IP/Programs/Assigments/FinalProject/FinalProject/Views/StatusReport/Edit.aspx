<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<FinalProject.Models.BugReport>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
    Edit
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    <h2>
        Edit</h2>
    <% using (Html.BeginForm())
       {%>
    <%: Html.ValidationSummary(true) %>
    <fieldset>
        <legend>Fields</legend>
        <div class="editor-label">
            <%: Html.LabelFor(model => model.Number) %>
        </div>
        <div class="editor-field">
            <%: Html.TextBoxFor(model => model.Number, new { @class="kk", hh="er"})%>
            <%: Html.ValidationMessageFor(model => model.Number) %>
        </div>
        <div class="editor-label">
            <%: Html.LabelFor(model => model.ReportedBy) %>
        </div>
        <div class="editor-field">
            <%: Html.TextBoxFor(model => model.ReportedBy, new { @hh = "er",value="default" })%>
            <%: Html.ValidationMessageFor(model => model.ReportedBy) %>
        </div>
        <div class="editor-field">
            <%: Html.TextBoxFor(model => model.ReportedBy) %>
            <%: Html.ValidationMessageFor(model => model.ReportedBy) %>
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
        <input id="Radio1" type="radio"  value="1"  name ="Comments" title="1"  /> 
        <input id="Radio2" type="radio"  value="2" name ="Comments"/>
        <input id="Radio3" type="radio"  value="3" name ="Comments"/>
        <input id="Radio4" type="radio"  value="4" name ="Comments"/>
        <input id="Radio5" type="radio"  value="5" name ="radios"/>
        <input id="Radio6" type="radio"  value="6" name ="radios"/>
        <input id="Checkbox2" type="checkbox" name="cheb" value="1"/>
        <input id="Checkbox3" type="checkbox" name="cheb" value="3"/>
        <input id="Checkbox4" type="checkbox" name="cheb" value="2"/>
        <input id="Checkbox1" type="checkbox" name="cheb" value="1"/>

    </fieldset>
    <% } %>
    <div>
        <%: Html.ActionLink("Back to List", "Index") %>
    </div>
</asp:Content>
