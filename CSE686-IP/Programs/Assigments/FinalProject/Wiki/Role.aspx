<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true"
    CodeBehind="Role.aspx.cs" Inherits="Wiki.Account.Role" %>

<asp:Content ID="Content1" ContentPlaceHolderID="HeadContent" runat="server">
    <link href="../Styles/tableformat.css" rel="stylesheet" type="text/css" />
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    <div class="caption">
        Roles
    </div>
    <table width="100%" border="0" align="left" cellpadding="5" cellspacing="0" class="map">
        <thead>
            <tr>
                <td>
                    Role
                </td>
                <td>
                    Authority
                </td>
            </tr>
        </thead>
        <tbody>
            <tr>
                <td>
                    Software Requirement Manager
                </td>
                <td>
                    Add/Delete/Update/View Software Requirements
                </td>
            </tr>
            <tr>
                <td>
                    Software Requirement Director
                </td>
                <td>
                    Only can view/udpate Software Requirements
                </td>
            </tr>
            <tr>
                <td>
                    Software Requirement Member
                </td>
                <td>
                    Only can view Software Requirements
                </td>
            </tr>
            <tr>
                <td>
                    Work Package Manager
                </td>
                <td>
                    Add/Delete/Update/View Work Package
                </td>
            </tr>
            <tr>
                <td>
                    Work Package Director
                </td>
                <td>
                    Only can view/udpate Work Package, view Software Requirement and add them to Work
                    Pakcage
                </td>
            </tr>
            <tr>
                <td>
                    Work Package Member
                </td>
                <td>
                    Only can view Software Requirements
                </td>
            </tr>
            <tr>
                <td>
                    Bug Report Manager
                </td>
                <td>
                    Add/Delete/Update/View Bug Reports, assign bug report to some member
                </td>
            </tr>
            <tr>
                <td>
                    System Tester
                </td>
                <td>
                    Add/View Bug Reports, reply to bug reports
                </td>
            </tr>
            <tr>
                <td>
                    Bug Assignee
                </td>
                <td>
                    View Bug Reports that assigned to him/her, modify the status of bug report and reply
                    to this report
                </td>
            </tr>
            <tr>
                <td>
                    Status Report Manager
                </td>
                <td>
                    Add/Delete/Update/ViewStatus Reports
                </td>
            </tr>
            <tr>
                <td>
                    Status Report Director
                </td>
                <td>
                    Only can view/udpate Status Reports
                </td>
            </tr>
            <tr>
                <td>
                    StatusReport<span style="mso-spacerun: yes">&nbsp; </span>Member
                </td>
                <td>
                    Only can view Status Reports
                </td>
            </tr>
            <tr>
                <td>
                    Wiki Module Manager
                </td>
                <td>
                    Every Team Manager is Wiki Manager, but they only can manage the module associate
                    with them
                </td>
            </tr>
            <tr>
                <td>
                    Wiki Manage
                </td>
                <td>
                    Can View/Reply every Wiki Topic
                </td>
            </tr>
            <tr>
                <td>
                    Wiki Normal User
                </td>
                <td>
                    Every Team Member is Wiki User, they can view every wiki, but only can reply/edit
                    Wiki topic that associate with them
                </td>
            </tr>
        </tbody>
    </table>
    <div>
        &nbsp;</div>
</asp:Content>
