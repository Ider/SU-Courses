<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<FinalProject.Models.Work_Package>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
    Edit
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    <% if (Model == null)
       { %>
    <span class="error">Can't Find Work Package!</span>
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
        <legend>Fields</legend>
        <div class="editor-label">
            <%: Html.LabelFor(model => model.name) %>
        </div>
        <div class="editor-field">
            <%: Html.TextBoxFor(model => model.name) %>
            <%: Html.ValidationMessageFor(model => model.name) %>
        </div>
        <div class="editor-label">
            <%: Html.LabelFor(model => model.task_id) %>
        </div>
        <div class="editor-field">
            <%: Html.TextBoxFor(model => model.task_id) %>
            <%: Html.ValidationMessageFor(model => model.task_id) %>
        </div>
        <div class="editor-label">
            <%: Html.LabelFor(model => model.status) %>
        </div>
        <div class="editor-field">
            <select id="status" name="status">
                <%foreach (KeyValuePair<int, string> item in ViewData["Enum"] as IDictionary<int,string>)
                  {%>
                <option value="<%:item.Key %>">
                    <%: item.Value %>
                </option>
                <%  } %>
            </select>
        </div>
        <div class="editor-label">
            <%: Html.LabelFor(model => model.description) %>
        </div>
        <div class="editor-field">
            <%: Html.TextAreaFor(model => model.description, 10, 100, null)%>
            <%: Html.ValidationMessageFor(model => model.description) %>
        </div>
        <div class="editor-label">
            <%: Html.LabelFor(model => model.notes) %>
        </div>
        <div class="editor-field">
            <%: Html.TextAreaFor(model => model.notes, 10, 100, null)%>
            <%: Html.ValidationMessageFor(model => model.notes) %>
        </div>
        <div class="editor-label">
            <%: Html.LabelFor(model => model.createddate) %>
        </div>
        <div class="editor-field">
            <%: Html.Label(String.Format("{0:MM/dd/yyyy}", Model.createddate)) %>
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
