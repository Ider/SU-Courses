<%@ Page Title="" Language="C#" MasterPageFile="~/master.Master" AutoEventWireup="true"
    CodeBehind="synopsis.aspx.cs" Inherits="HTML.synopsis" %>

<%@ Register Src="fpnavigator.ascx" TagName="fpnavigator" TagPrefix="uc1" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <uc1:fpnavigator ID="fpnavigator1" runat="server" />
    <h2>
        Main Page:</h2>
    A login in page.
    <br />
    <h2>
        Home Page:</h2>
    List work assigments and bug reports that still on open status.
    <br />
    <h2>
        Software Requirment:</h2>
    Create or Modify(update/delete) requirements
    <br />
    View requirements
    <br />
    <h2>
        Work Package:</h2>
    Create or Modify(update/delete) work packages
    <br />
    View work packages
    <br />
    Associate work pacjages with software requirements
    <br />
    <h2>
        Bug Reports:</h2>
    Create bug report
    <br />
    View bug report
    <br />
    Assign bug reports to developers
    <br />
    Developers could reply bug reports
    <br />
    <h2>
        Status Reports:</h2>
    Create status report
    <br />
    View status report
    <br />
    Assign status reports to work package
    <br />
    <h2>
        Wiki:</h2>
    Create wiki topic
    <br />
    View wiki topic
    <br />
    Modify wiki topic
    <br />
    View wiki history
    <br />
</asp:Content>
