<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<dynamic>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
    Layout
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    <div class="caption">
        Layout
    </div>
    <table width="100%" border="0" align="left" cellpadding="5" cellspacing="0" class="map">
        <thead>
            <tr>
                <td>
                    Requirement
                </td>
                <td>
                    Pages
                </td>
                <td>
                    Database Table
                </td>
                <td>
                    XML Files
                </td>
            </tr>
        </thead>
        <tbody>
            <tr>
                <td>
                    Requirements
                </td>
                <td>
                    Create Software requirements
                    <br />
                    Modify(update/delete) Software requirements
                    <br />
                    View requirements<br />
                    View requirement Detail
                </td>
                <td>
                    Software Requirement
                </td>
                <td>
                    &nbsp;
                </td>
            </tr>
            <tr>
                <td>
                    Work Package
                </td>
                <td>
                    Create Work Package
                    <br />
                    Modify(update/delete) Work Package
                    <br />
                    View Work Packages<br />
                    View Work Package Detail
                </td>
                <td>
                    Work_Package
                    <br />
                    Software_Requirement
                </td>
                <td>
                    &nbsp;
                </td>
            </tr>
            <tr>
                <td>
                    Bug Reports
                </td>
                <td>
                    Create Bug Report
                    <br />
                    Modify Bug Report status
                    <br />
                    View Bug Reports<br />
                    View Bug Report Detail<br />
                    Assign bug reports to developers
                    <br />
                    Reply bug reports
                </td>
                <td>
                    Work_Package
                    <br />
                    Status
                </td>
                <td>
                    Bugs
                </td>
            </tr>
            <tr>
                <td>
                    Status Reports
                </td>
                <td>
                    Create status report
                    <br />
                    View status report
                    <br />
                    Assign status reports to work package
                </td>
                <td>
                    Users
                </td>
                <td>
                    Status<br />
                    Bugs
                </td>
            </tr>
            <tr>
                <td>
                    Wiki
                </td>
                <td>
                    Create Wiki
                    <br />
                    Modify(Update/delete) Wiki
                    <br />
                    Read Wiki
                </td>
                <td>
                    Roles<br />
                    Users<br />
                    Wiki
                </td>
                <td>
                </td>
            </tr>
        </tbody>
    </table>
    <div>
        &nbsp;
    </div>
</asp:Content>
