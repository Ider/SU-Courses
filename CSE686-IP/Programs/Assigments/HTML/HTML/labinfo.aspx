<%@ Page Title="Lab Assiment Information" Language="C#" MasterPageFile="~/master.Master"
    AutoEventWireup="true" CodeBehind="labinfo.aspx.cs" Inherits="HTML.labinfo" %>

<%@ MasterType VirtualPath="master.master" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
    <script src="js/ajax/load_lab.js" type="text/javascript"></script>
    <link href="styles/tableformat.css" rel="stylesheet" type="text/css" /> 
    <style type="text/css">

        .map tbody td
        {
            vertical-align: top;
            width: 33.3%;
        }
    </style>
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <div class="caption">
        <asp:Label ID="lblCaption" runat="server" Text="Lab Assignment Information"></asp:Label>
    </div>
    <div id="lab">
    </div>
    <script type="text/javascript">
        loadXMLLab("lab", "map");
    </script>
</asp:Content>
